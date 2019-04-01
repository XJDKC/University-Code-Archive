#include<stdio.h>
int main( )
{
   int a, b;
   printf("Input two integers:");
   scanf("%d %d",&a,&b);
   a=a+b;b=a-b;a=a-b;          //设开始a，b分别为a0,b0加以区别  
   printf("\na=%d,b=%d",a,b);  //a=a+b后为 a为a0+b0 
   return 0;                   //b=a-b后为 b为a0 
}                              //a=a-b后为 a为b0 

