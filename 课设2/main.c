#include <reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
#define out P1 
long int light;
sbit en=P0^5;
sbit rw=P0^6;
sbit rs=P0^7;

sbit add_a=P0^0;
sbit add_b=P0^1;
sbit add_c=P0^2;
sbit start=P3^3;
sbit eoc=P3^4;
sbit clock=P3^5;	 
sbit oe=P3^6;
uchar T;


void delay(uint z)
{																							   
    uint i,j;
    for(i=z;i>0;i--)
        for(j=110;j>0;j--);
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
void write_sfm(uchar add,uchar dat)
{
	write_command(0x80+add);
	write_data(0x30+dat/100%10);
	write_data(0x30+dat/10%10);
	write_data(0x30+dat%10);
}
void write_sfm1(uchar add,uchar dat)
{
	write_command(0x80+add);
	write_data(0x30+dat/10%10);
	write_data(0x30+dat%10);
}

void Initial_com(void)
{       
 TMOD=0x20;//设置为定时器T1的方式2   
 PCON=0x00; //倍增0  
 SCON=0x50;//串口方式可发可收   
 TH1=0xf4;//9600波特率    
 TL1=0xf4;
 TR1=1;//发送波特率       

}
void send(uchar dat)
{
 SBUF=dat;
 while(TI==0);
 TI=0;
}

uchar receive(void)
{
uchar dat;
while(RI==0);
 RI=0;
 dat=SBUF;
 return dat;
}

void main()
{	
	
	lcd_initial();
	Initial_com();
	add_a=0;add_b=0;add_c=0;
	string(0x80,"light:"); string(0xc0,"T:");string(0xc4,".");
	while(1)
	{
		start=0;start=1;start=0;
		while(1)
		{
			clock=!clock;//	 时钟信号必须有外部方波
			if(eoc==1)break;//等待转换结束
			oe=1;		//允许输出
		    light=out;	//暂存转换结果		
			oe=0;		//关闭输出
			write_sfm(0x06,light);	 
			send(light);
			delay(5);
			T=receive();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
			if(T>=100&&T<200)
			write_sfm1(0x42,T%100);
			if(T>=200)
			write_sfm1(0x45,T%100);	

		 }
	}	
}