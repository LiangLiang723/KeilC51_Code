#include<reg51.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
#define out P0
sbit RS=P2^0;
sbit RW=P2^1;
sbit E=P2^2	;
sbit s1=P1^0;
sbit s2=P1^1;
sbit s3=P1^2;
uchar a[]="0123456789";
uchar b[]="0123456789";
void delay(uint i)
{
	uchar x,y;
	for(x=0;x<i;x++)
		for(y=0;y<123;y++);
}

void check_busy(void)
{
  uchar dt;
  do
  {
      dt=0xff;
	  E=0;
	  RS=0;
	  RW=1;
	  E=1;
	  dt=out;
  }while(dt&0x80);
  E=0;
}
void write_command(uchar com)
{
  check_busy();
  E=0;
  RS=0;
  RW=0;
  out=com;
  E=1;
  _nop_( );
  E=0;
  delay(1);
}
void LCD_initial(void)
{
  write_command(0x38);
  _nop_();
  write_command(0x0c);
  _nop_();
  write_command(0x06);
  _nop_();
  write_command(0x01);
  _nop_();
  delay(1);
}
void write_data(uchar dat)
{
   check_busy();
      E=0;
	  RS=1;
	  RW=0;
	  out=dat;
	  E=1;
	  _nop_( );
	  E=0;
	  delay(1);
}
void string(uchar ad,uchar *s)
{
   	 write_command(ad);
	 while(*s>0)
	 {
	    write_data(*s++);
	
	 }
}
void main(void)
{
   char i,j;
   i=0;
   j=0;	
   LCD_initial( );
   
   string(0x80,"count: ");
   string(0xc0,"s1:+ s2:- s3:r");
while(1)
{
if(P1==0xfe&&i!=9)
{
delay(10); 
if(P1==0xfe&&i!=9)
{
while(P1==0xfe);
i++;  
}	
}
if(P1==0xfd&&i!=0)
i--;
if(P1==0xfb)
i=0;
if(P1==0xfe&&i==9)
j++,i=0;
if(P1==0xfd&&i==0)
j--,i=9;
write_command(0x87);
write_data(a[j]);
write_command(0x88);
write_data(a[i]); 
}
}
