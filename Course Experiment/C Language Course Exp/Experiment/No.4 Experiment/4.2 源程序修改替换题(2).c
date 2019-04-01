#include<stdio.h>
#define max(a,b,c) ((a)>(b)?((a)>(c)?(a):(c)):((b)>(c)?(b):(c)))
float sum(float x, float y);
int main()
{
    int a, b, c;
    float d, e;
    printf("Enter three integers:");
    scanf("%d,%d,%d",&a,&b,&c);
    printf("\nthe maximum of them is %d\n",max(a,b,c));
    printf("Enter two floating point numbers:");
    scanf("%f,%f",&d,&e);
    printf("\nthe sum of them is  %f\n",sum(d,e));
}
float sum(float x, float y)
{
  return x+y;
}

