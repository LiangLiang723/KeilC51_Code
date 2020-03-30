#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int

sbit wr=P3^6;
sbit rd=P3^2;
sbit k1=P1^0;
sbit k2=P1^1;
void delay(uint n)
{
	uint i,j;
	for(i=0;i<n;i++)
		for(j=0;j<123;j++);
}
void init_DA0832()
{
	rd=0;
	wr=0;
}
void Trapezoidal()
{
	P2=0xff;
	do
	{
		P2=P2+1;
	}while(P2<0xff);
	delay(2);
	do
	{
		P2=P2-1;
	}while(P2>0); 
}
void Square()
{
P2=0;
delay(70);
P2=0xff;
delay(60);
}
void main()
{
	init_DA0832();
	if(k1==0)
	{
		delay(5);
		if(k1==0)
		{
			while(k1==0);
			while(k2!=0)
			Trapezoidal();
		}
	}
	if(k2==0)
	{
		delay(5);
		if(k2==0)
		{
			while(k2==0);
			while(k1!=0)
			Square();
		}
	}	
}