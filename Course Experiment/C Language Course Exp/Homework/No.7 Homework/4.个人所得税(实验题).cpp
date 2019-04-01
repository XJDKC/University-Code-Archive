#include<stdio.h>
double cal(double x);
int main()
{
	double x;
	while (scanf("%lf",&x)&&x)
	{
		printf("%lf\n",cal(x));
	}
	return 0;
}
double cal(double x)
{
	double ans=0,i=0;
	while (x>0)
	{
		if (x>=1000) ans+=1000*i*0.05;
		else ans+=x*i*0.05;
		x-=1000;
	    if (i<5) i++;	
	}
	return ans;
}
