#include<reg52.h>
#include<intrins.h>
#include<stdlib.h>
#define uchar unsigned char
#define uint unsigned int
sbit DQ=P3^7;
sbit en=P0^5;
sbit rw=P0^6;
sbit rs=P0^7;
bit fg=1;
uchar L;
void delay(uint t)	 
{  uint i,j;					
   for(i=0;i<t;i++)
      for(j=0;j<123;j++); }


 void delay1(uint t)
 { 
 uint i;
  for(i=0;i<t;i++);
 }
 void check_busy(void)
{  uchar dt;
   do{  dt=0xff;
        en=0;  rs=0;  rw=1;  en=1;  
		dt=P2;  } while(dt&0x80);
   en=0;   }


void write_command(uchar com)
{  check_busy();
   en=0;  rs=0;  rw=0;  
   P2=com;
   en=1;
   _nop_();
   en=0;
   delay(1);   }

void lcd_initial(void)
{ write_command(0x38);
  write_command(0x0c);
  write_command(0x06);
  write_command(0x01);
  delay(1);              }


void write_data(uchar dat)												 
{  check_busy();
   en=0;  rs=1;  rw=0;  
   P2=dat;
   en=1;
   _nop_();
   en=0;
   delay(1);   }
void string(uchar position, uchar *s)
{  write_command(position);
   while(*s>0)
   {  write_data(*s++);
      delay(1);        
	                      }    }
void write_sfm1(uchar add,uchar dat)
{
	write_command(0x80+add);
	write_data(0x30+dat/100);
	write_data(0x30+dat/10%10);
	write_data(0x30+dat%10);
	}
	void write_sfm(uchar add,uchar dat)
{
	write_command(0x80+add);
	write_data(0x30+dat);;
	}
unsigned char tempL=0; 		
unsigned char tempH=0; 	 
unsigned int sdata,sdata1,sdata2;		
unsigned char xiaoshu1;		
unsigned char xiaoshu2;		
unsigned char xiaoshu;
uint num1=0,num2=0;
uint MAX=25,MIN=15;	
	  	
 void Init_DS18B20(void) 
{
	unsigned char x=0;
	DQ=1; 					
	delay1(8); 				
	DQ=0; 					
	delay1(80); 				 
	DQ=1; 					
	delay1(5); 			
	x=DQ; 					
	delay1(20); 
}


ReadOneChar(void)  			
{
	unsigned char i=0; 		
	unsigned char dat=0; 
	for (i=8;i>0;i--) 		
	{
		DQ=1; 
		delay1(1); 
		DQ=0;
		dat>>=1; 
		DQ=1; 
		if(DQ) 
		dat|=0x80; 
		delay1(4);
	} 
	return(dat);
}

void WriteOneChar(unsigned char dat) 
{ 
	unsigned char i=0; 		
	for(i=8;i>0;i--) 		
	{
		DQ=0; 				
		DQ=dat&0x01; 
		delay1(5); 
		DQ=1; 
		dat>>=1;
	} 
	delay1(4);
}
void ReadTemperature(void) 
{ 
	Init_DS18B20(); 					
	WriteOneChar(0xcc); 			
	WriteOneChar(0x44); 			
	delay(125); 						
	Init_DS18B20(); 				
	WriteOneChar(0xcc); 				
	WriteOneChar(0xbe); 		
	tempL=ReadOneChar(); 			
	tempH=ReadOneChar(); 			
	if(tempH>0x7f)      				
	{
		tempL=~tempL;					
		tempH=~tempH+1;       
		fg=0;      						
	}
	sdata = tempL/16+tempH*16;      
	sdata1 = sdata/10;
	sdata2 = sdata%10;
	xiaoshu1 = (tempL&0x0f)*10/16; 	
	xiaoshu2 = (tempL&0x0f)*100/16%10;	
	xiaoshu=xiaoshu1*10+xiaoshu2;
}
void send(uchar dat)
{
SBUF=dat;
while(TI=0);
TI=0;
}
uchar receice(void)
{
uchar dat;
while(RI==0);
RI=0;
dat=SBUF;
return dat;
}
void main()
  { lcd_initial();
 TMOD=0x20;
 TH1=0xf4;
 TL1=0xf4;
 PCON=0;
 SCON=0x50;
 TR1=1;
while(1)
{           ReadTemperature();
            send(100+sdata);
			delay(5);
			send(200+xiaoshu);
			delay(5);
			L=receice();
            write_sfm1(0x42,L);
			string(0x80,"T");
			string(0x81,":");string(0xc1,":"); 	string(0xc0,"L");
			write_command(0x82);	
			write_data(sdata1+0x30);	 
			write_data(sdata2+0x30);
			string(0x84,".");
			write_command(0x85);  
			write_data(xiaoshu1+0x30);
			write_data(xiaoshu2+0x30);
				 }
													   }