#include<stdio.h>
int main()
{
	int x,n;
	scanf("%d%d",&x,&n);
	n%=(sizeof(int)*8);
	x=(x>>n)&~(~0<<(sizeof(int)*8-n))|(x<<(sizeof(int)*8-n));
	printf("%d\n",x);
	return 0;
}
