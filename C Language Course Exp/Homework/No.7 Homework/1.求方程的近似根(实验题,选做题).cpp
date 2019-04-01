#include<stdio.h>
#define exp 1.0e-6
double cal(double a);
double abss(double a,double b);
int main()
{
    double a=-1.5,b;
    b=cal(a);
	while (abss(a,b)>exp)
	{
	     a=b;
		 b=cal(a);	
    }   	
    printf("%lf\n",a);
    return 0;
} 
double cal(double a)
{
	double x,y;
	x=3*a*a*a-4*a*a-5*a+13;
	y=9*a*a-8*a-5;
	return (a-x/y);
}
double abss(double a,double b)
{
	if (a-b>0) return a-b;
	else return b-a;
}
