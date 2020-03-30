#include<reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint  unsigned int

char m1=30,m2=5,fq=0,g=0,L,Q=5,N=5,J=0,V,Y[]= {0xbe,0xbe,0xbe,0xbe},S[]= {0,0,0,0};
char num,num1,num2,numm=0,numm1=0,numm2=0,h=0;


sbit en=P0^5;
sbit rw=P0^6;
sbit rs=P0^7;
sbit fmq=P3^6;
void delay(uint i)
{
    uint x,y;
    for(x=0; x<i; x++)
        for(y=0; y<123; y++) ;
}

void check_busy(void)
{   uchar dt;
    do {
        dt=0xff;
        en=0;
        rs=0;
        rw=1;
        en=1;
        dt=P2;
    }
    while(dt&0x80);
    en=0;
}

void write_command(uchar com)
{   check_busy();
    en=0;
    rs=0;
    rw=0;
    P2=com;
    en=1;
    _nop_();
    en=0;
    delay(1);
}

void lcd_initial(void)
{   write_command(0x38);
    write_command(0x0c);
    write_command(0x06);
    write_command(0x01);
    delay(1);
}


void write_data(uchar dat)
{   check_busy();
    en=0;
    rs=1;
    rw=0;
    P2=dat;
    en=1;
    _nop_();
    en=0;
    delay(1);
}

void string(uchar position, uchar *s)
{   write_command(position);
    while(*s>0)
    {   write_data(*s++);
        delay(1);
    }
}

void write_sfm(uchar add, uchar dat)
{
    write_command(0x80+add);
    write_data(0x30+dat/10);
    write_data(0x30+dat%10);
}

uchar keyscan(void)
{   uchar valuel,valueh;
    P1=0xf0;
    if((P1&0xf0)!=0xf0)
    {   delay(10);
        if((P1&0xf0)!=0xf0)
        {   valuel=P1&0xf0;
            P1=0x0f;
            valueh=P1&0x0f;
            while((P1&0x0f)!=0x0f);
            return(valuel+valueh);
        }
    }
}
void di(void)
{
    fmq=0;
    delay(4);
    fmq=1;
    delay(4);
    fmq=0;
}
uchar mima(void)
{
    uchar temp,i=0;
    while(i<4)
    {

        temp=keyscan();
        switch(temp)
        {
        case 0xee:
            S[i]=0xee;
            i++;
            string(0x8b+i,"*");
            string(0x8b+i,"*");
            break;
        case 0xde:
            S[i]=0xde;
            i++;
            string(0x8b+i,"*");
            string(0x8b+i,"*");
            break;
        case 0xbe:
            S[i]=0xbe;
            i++;
            string(0x8b+i,"*");
            string(0x8b+i,"*");
            break;
        case 0x7e:
            S[i]=0x7e;
            i++;
            string(0x8b+i,"*");
            string(0x8b+i,"*");
            break;
        case 0xed:
            S[i]=0xed;
            i++;
            string(0x8b+i,"*");
            string(0x8b+i,"*");
            break;
        case 0xdd:
            S[i]=0xdd;
            i++;
            string(0x8b+i,"*");
            string(0x8b+i,"*");
            break;
        case 0xbd:
            S[i]=0xbd;
            i++;
            string(0x8b+i,"*");
            string(0x8b+i,"*");
            break;
        case 0x7d:
            S[i]=0x7d;
            i++;
            string(0x8b+i,"*");
            string(0x8b+i,"*");
            break;
        case 0xeb:
            S[i]=0xeb;
            i++;
            string(0x8b+i,"*");
            string(0x8b+i,"*");
            break;
        case 0xdb:
            S[i]=0xdb;
            i++;
            string(0x8b+i,"*");
            string(0x8b+i,"*");
            break;
        case 0xbb:
            S[i]=0xbb;
            i++;
            string(0x8b+i,"*");
            string(0x8b+i,"*");
            break;
        case 0x7b:
            S[i]=0x7b;
            i++;
            string(0x8b+i,"*");
            string(0x8b+i,"*");
            break;
        case 0xe7:
            S[i]=0xe7;
            i++;
            string(0x8b+i,"*");
            string(0x8b+i,"*");
            break;
        case 0xd7:
            S[i]=0xd7;
            i++;
            string(0x8b+i,"*");
            string(0x8b+i,"*");
            break;
        case 0xb7:
            S[i]=0xb7;
            i++;
            string(0x8b+i,"*");
            string(0x8b+i,"*");
            break;
        case 0x77:
            S[i]=0x77;
            i++;
            string(0x8b+i,"*");
            string(0x8b+i,"*");
            break;

        }
        delay(100);
    }
    if(Y[0]==S[0]&&Y[1]==S[1]&&Y[2]==S[2]&&Y[3]==S[3]) {
        string(0x8c,"P76     ");
        string(0x8c,"P76     ");
        return (0);
    }
    else {
        string(0x8c,"X76     ");
        string(0x8c,"X76     ");
        return (1);
    }
}
void qie(void)
{
    lcd_initial();
    while(J<5)
    {
        m1=30;
        m2=5;
        fq=0;
        num=0;
        num1=0;
        num2=0;
        string(0x80,"W:30:00");
        string(0x87,"T00");
        string(0x8d,"76");
        string(0xc0,"R:05:00");
        string(0xc8,"S:");
        string(0xcc,":");
        J++;
    }
}


void main(void)
{   uchar key;

    lcd_initial();
    EA=1;
    TMOD=0x01;
    ET0=1;
    TH0=(65536-50000)/256;
    TR0=(65536-50000)%256;
    TR0=0;
    TMOD=0x11;
    ET1=1;
    TH1=(65536-50000)/256;
    TR1=(65536-50000)%256;
    TR1=1;
    string(0x80,"W:30:00");
    string(0x87,"T00");
    string(0x8d,"76");
    string(0xc0,"R:05:00");
    string(0xc8,"S:00:00");
    while(1)
    {   if(TR0==1) {
            V=1;
        }
        if(fq>=10) {
            J=0;
            lcd_initial();
            fq=0;
            TR0=0;
            string(0xc8,"S:");
            string(0xcc,":");
            while(key!=0xee) {
                key=keyscan();
                string(0x83,"WellDone");
            }
            lcd_initial();
            while(J<3)
            {   m1=2;
                m2=1;
                fq=0;
                num=0;
                num1=0;
                num2=0;
                delay(10);
                string(0x80,"W:30:00");
                delay(2);
                string(0xc0,"R:05:00");
                delay(2);
                string(0x87,"T00");
                delay(2);
                string(0x8d,"76");
                delay(2);
                string(0xc8,"S:");
                delay(2);
                string(0xcc,":");
                delay(2);
                J++;
            }
        }
        if(num2==m1)
        {
            while(g<20) {
                di();
                g++;
            }
        }
        if(N==0)
        {
            while(g>0) {
                di();
                g--;
                delay(5);
                N++;
            }
        }

        key=keyscan();
        switch(key)
        {
        case 0xee:
            TR0=1;
            string(0x8c," ");
            break;
        case 0xde:
            TR0=0;
            string(0x8c,"!    ");
            string(0x8c,"!    ");
            delay(5);
            TR0=mima();
            break;
        case 0xbe:
            if(V==1)break;
            m1++;
            write_sfm(0x02,m1);
            break;
        case 0x7e:
            if(V==1)break;
            m1--;
            if(m1<5*m2)m1++;
            delay(2);
            if(m1<0) m1=0;
            write_sfm(0x02,m1);
            break;
        case 0xed:
            if(V==1)break;
            m2++;
            if(5*m2>m1)m2--;
            delay(2);
            write_sfm(0x42,m2);
            break;
        case 0xdd:
            if(V==1)break;
            m2--;
            if(m2<0) m2=0;
            write_sfm(0x42,m2);
            break;
        case 0xbd:
            if(V==1)break;
            fq++;
            write_sfm(0x08,fq);
            break;
        case 0x7d:
            if(V==1)break;
            fq--;
            if(fq<0) fq=0;
            write_sfm(0x08,fq);
            break;
        case 0xeb:
            if(V==1)break;
            numm2++;
            write_sfm(0x4d,numm2);
            break;
        case 0xdb:
            if(V==1)break;
            numm2--;
            if(numm2<0) numm2=0;
            write_sfm(0x4d,numm2);
            break;
        case 0xbb:
            if(V==1)break;
            h++;
            write_sfm(0x4a,h);
            break;
        case 0x7b:
            if(V==1)break;
            h--;
            if(h<0) h=0;
            write_sfm(0x4a,h);
            break;
        case 0xe7:
            if(V==1)break;
            Q++;
            break;
        case 0xd7:
            if(V==1)break;
            Q--;
            if(Q<0) Q=0;
            break;
        case 0xb7:
            TR0=0;
            J=0;
            lcd_initial();
            while(1) {
                string(0xc8,"S:");
                string(0xcc,":");
                string(0x81,"YU:05:00");
                key=keyscan();
                if(h>=Q) {
                    qie();
                    delay(5);
                    TR0=1;
                    break;
                }
                if(key==0xee) {
                    qie();
                    break;
                }
                if(key==0xbb) {
                    h++;
                    write_sfm(0x4a,h);
                }
                if(key==0x7b) {
                    h--;
                    if(h<0) h=0;
                    write_sfm(0x4a,h);
                }
                if(key==0xe7) {
                    Q++;
                }
                if(key==0xd7) {
                    Q--;
                    if(Q<0) Q=0;
                }
            }
            break;
        case 0x77:
            TR0=0;
            string(0x8c,"!     ");
            string(0x8c,"!    ");
            delay(5);
            L=mima();
            J=0;
            V=0;
            if(L==0)
            {
                lcd_initial();
                while(J<3)
                {
                    m1=30;
                    m2=5;
                    fq=0;
                    num=0;
                    num1=0;
                    num2=0;
                    numm=0;
                    numm1=0;
                    numm2=0;
                    h=0;
                    delay(5);
                    string(0x80,"W:30:00");
                    delay(5);
                    string(0x87,"T00");
                    delay(5);
                    string(0x8d,"76");
                    delay(5);
                    string(0xc0,"R:05:00");
                    delay(5);
                    string(0xc8,"S:");
                    delay(5);
                    delay(5);
                    string(0xcc,":");
                    delay(5);
                    J++;
                }
            }
            else TR0=1;
            break;
        }


    }

}
void 	timer0 () interrupt 1
{

    TH0=(65536-50000)/256;
    TR0=(65536-50000)%256;
    num++;
    string(0x87,"T");
    string(0x80,"W:");
    string(0x84,":");
    string(0x8d,"76");
    string(0xc0,"R:");
    string(0xc4,":");
    if(num==1) {
        num=0;
        num1++;
    }
    if(num1==60) {
        num1=0;
        num2++;
    }
    if(num2<m1)
    {
        write_sfm(0x02,m1-num2-1);
        write_sfm(0x05,59-num1);
    }


    else if(num2>=m1 && num2<m1+m2)
    {

        write_sfm(0x42,m1+m2-num2-1);
        write_sfm(0x45,59-num1);


    }

    else if(num2>=m1+m2)
    {
        write_sfm(0x02,m1);
        write_sfm(0x42,m2);
        num2=0;
        N=0;
        fq++;
        write_sfm(0x08,fq);
    }



}
void 	timer1 () interrupt 3
{

    TH1=(65536-50000)/256;
    TR1=(65536-50000)%256;
    numm++;
    if(numm==1) {
        numm=0;
        numm1++;
    }
    if(numm1==60) {
        numm1=0;
        numm2++;
    }
    if(numm2==60) {
        numm2=0;
        h++;
    }
    string(0xcc,":");
    write_sfm(0x4a,h);
    write_sfm(0x4d,numm2);
    string(0xcf," ");
}