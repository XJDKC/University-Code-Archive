#include<stdio.h>
#include<math.h>
#define s(a,b,c) (((a)+(b)+(c))/2)
#define area(s,a,b,c) (sqrt((s)*((s)-(a))*((s)-(b))*((s)-(c))))
int main()
{
	int a,b,c,s;
	while (scanf("%d%d%d",&a,&b,&c)!=EOF)
	{
		s=s(a,b,c);
		printf("%d %lf\n",s,area(s,a,b,c));
	}
	return 0;
}
