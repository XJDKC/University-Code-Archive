#include<stdio.h>
#include<math.h>
#define p ((a+b+c)/2)
#define s (sqrt(p*(p-a)*(p-b)*(p-c)))
int main()
{
	int t;
	double a,b,c;
	scanf("%d",&t);
	while (t--)
	{
		scanf("%lf%lf%lf",&a,&b,&c);
		printf("area=%lf\n",s);
	}
	return 0;
}
