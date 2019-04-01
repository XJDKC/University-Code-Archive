#include<stdio.h>
int main()
{
    int n;
    unsigned short x;
	scanf("%d",&n);
	while (n--)
	{
		scanf("%hu",&x);
		x=(x>>12)|(x&0x0ff0)|(x<<12);
		printf("%hu\n",x);
    }	 
    return 0;
} 
