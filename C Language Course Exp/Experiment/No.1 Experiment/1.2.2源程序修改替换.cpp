#include<stdio.h>
int main( )
{
   int a, b;
   printf("Input two integers:");
   scanf("%d %d",&a,&b);
   a=a+b;b=a-b;a=a-b;          //�迪ʼa��b�ֱ�Ϊa0,b0��������  
   printf("\na=%d,b=%d",a,b);  //a=a+b��Ϊ aΪa0+b0 
   return 0;                   //b=a-b��Ϊ bΪa0 
}                              //a=a-b��Ϊ aΪb0 

