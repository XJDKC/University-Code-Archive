#include<stdio.h>
#include<math.h>
int main()
{
	int t;
	float a,b,c,p,s;
	scanf("%d",&t); 
	while (t--)
	{
		scanf("%f%f%f",&a,&b,&c);
		p=(a+b+c)/2;
		s=sqrt(p*(p-a)*(p-b)*(p-c));
		printf("area=%f\n",s);
	}
	return 0;
} 
