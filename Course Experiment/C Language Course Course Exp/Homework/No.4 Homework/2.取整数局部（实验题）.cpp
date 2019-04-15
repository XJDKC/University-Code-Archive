#include<stdio.h>
int main()
{
	int t;
	unsigned short x,m,n,mask;
	scanf("%d",&t);
	while (t--)
	{
		scanf("%hu%hu%hu",&x,&m,&n);
		mask=(~0>>(sizeof(unsigned short)*8-n-m))&(~0<<m);
		x=(x&mask)<<(sizeof(unsigned short)*8-n-m);
		printf("%hu\n",x); 
	}
	return 0;
}
