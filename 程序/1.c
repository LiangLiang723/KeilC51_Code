#include <reg51.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
uchar code a[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
uchar code b[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
void delay(uint n)
 {
uint i,j;			
for(i=0;i<n;i++)		
for(j=0;j<123;j++);
  }
void main()
{	uchar i=0,j=0;
     P2=0xff;
 while(1)
 {	
       if(P1==0xfe&&i!=9)
       {delay(10);if(P1==0xfe);i++;P0=a[i],P0=b[i];}
	   if(P1==0xfe&&i==9)
       {delay(10);if(P1==0xfe);i=0,j++;P0=a[i],P0=b[i];}
	   if(P1==0xfd&&i!=0)
       {delay(10);if(P1==0xfe);i--;P0=a[i],P0=b[i];}
		if(P1==0xfe&&i==0)
       {delay(10);if(P1==0xfe);i=9,j--;P0=a[i],P0=b[i];}
 } 

}