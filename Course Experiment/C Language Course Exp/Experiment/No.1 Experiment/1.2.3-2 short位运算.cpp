#include<stdio.h>
int main()
{
unsigned short x,m,n,mask;
scanf("%hx%hx%hx",&x,&m,&n); 
mask=(~0>>(sizeof(unsigned short)*8-n-m))&(~0<<m);//�����߼���
x=(x&mask)<<(sizeof(unsigned short)*8-n-m); //��xָ������ȡ������
printf("%hx\n",x); 
return 0;
}

