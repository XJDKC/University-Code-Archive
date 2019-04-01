#include<stdio.h>
#define PI 3.1415926
int main()
{
	int n;
	double r,h,s,v;
	scanf("%d",&n);
    while (n--)
    {
    	scanf("%lf%lf",&r,&h);
    	s=PI*r*r*2+2*PI*r*h;
    	v=PI*r*r*h;
    	printf("%.6lf %.6lf\n",s,v);
	}
	return 0;
}
