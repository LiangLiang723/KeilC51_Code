#include<reg51.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
uchar  code a[]= {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
uchar   b[]= {0x82,0xf8,0xc0,0x92};
uchar key;
char x;
void delay(uint n)
{
    int i,j;
    for(i=0; i<n; i++)
        for(j=0; j<123; j++);
}
uchar keyscan(void)
{
    uchar l,h;
    P1=0xf0;
    if((P1&0xf0)!=0xf0)
    {
        delay(10);
        if((P1&0xf0)!=0xf0)
        {
            l=P1&0xf0;
            P1=0x0f;
            h=P1&0x0f;
            while((P1&0x0f)!=0x0f);
            return(l+h);
        }
    }
}
void abc()
{
    int p;
    uchar q;
    while(1)
    {
        key=keyscan();
        for(p=0,q=0x01; p<4; p++)
        {
            P0=b[p];
            P2=q ;
            q=_crol_(q,1);
            P2=0;
        }
        if(key==0xde||key==0x7b)
        {
            P2=0x01,x=9;
            P0=a[x];
            break;
        }
        if(key==0xbd)
        {
            P2=0x01;
            P0=a[--x];
            break;
        }
    }
}
void main(void)
{
    P2=0x01;
    while(1)
    {
        key=keyscan();
        switch(key)
        {
        case 0xde:
            P2=0x01,x=9;
            P0=a[x];
            break;
        case 0xbd:
            P2=0x01,x--,P0=a[x];
            break;
        case 0x7b:
            P2=0x01,x=9;
            P0=a[x];
            break;
        case 0xeb:
            abc();
            break;
        }
        if(x<0)
        {
            x=9;
            P0=a[x];
        }
    }
}