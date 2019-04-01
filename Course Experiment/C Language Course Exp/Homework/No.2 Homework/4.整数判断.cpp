#include<stdio.h>
int main()
{
    int a;
	while (scanf("%d",&a))
	{
		if (a%3==0&&a%10==5)
		   printf("1\n");
		else
		   printf("0\n"); 
	}
	return 0;
} 
