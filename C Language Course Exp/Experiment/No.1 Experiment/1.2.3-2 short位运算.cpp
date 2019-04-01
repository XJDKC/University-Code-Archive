#include<stdio.h>
int main()
{
unsigned short x,m,n,mask;
scanf("%hx%hx%hx",&x,&m,&n); 
mask=(~0>>(sizeof(unsigned short)*8-n-m))&(~0<<m);//构建逻辑尺
x=(x&mask)<<(sizeof(unsigned short)*8-n-m); //将x指定区域取出左移
printf("%hx\n",x); 
return 0;
}

