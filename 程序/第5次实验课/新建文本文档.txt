#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
uchar second=30,minute=23,num=0;

sbit en=P2^2;
sbit rw=P2^1;
sbit rs=P2^0;
sbit P23=P2^3;
sbit P24=P2^4;
sbit P25=P2^5;
 
void delay(uint t)	 
{  uint i,j;
   for(i=0;i<t;i++)
      for(j=0;j<123;j++); }

void check_busy(void)
{  uchar dt;
   do{  dt=0xff;
        en=0;  rs=0;  rw=1;  en=1;  
		dt=P0;  } while(dt&0x80);
   en=0;   }

void write_command(uchar com)
{  check_busy();
   en=0;  rs=0;  rw=0;  
   P0=com;
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
   P0=dat;
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
write_data(0x30+dat/10);
write_data(0x30+dat%10);
}
void main(void)
{
lcd_initial();
string(0x82,"201741055076");
string(0xc3,"TIME 23:30");
TMOD=0x01;  EA=1;ET0=1;
TH0=(65536-50000)/256;
TL0=(65536-50000)%256;

while(1)
{ 	   
if (P23==0)TR0=1;
if(P24==0){delay(1);if(P24==0)while(P24==0);minute++;}
if(P25==0){delay(1);if(P25==0)while(P25==0);second=second+5;if(second>=60){second=0;minute++;}}
 write_sfm(0x48,minute);
 write_sfm(0x4b,second);}	}

void timer0 () interrupt 1
{  
TH0=(65536-50000)/256;
TL0=(65536-50000)%256;
num++;
if(num==20)
{
num=0;second--;
}
if(second==0)
{
second=59;minute--;
}

}	 
