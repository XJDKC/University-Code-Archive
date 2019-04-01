#include<stdio.h>
int main()
{
	int n,i,ans;
	long int num;
	char *p;
	scanf("%d",&n);
	while (n--)
	{
		scanf("%ld",&num);
		p=(char *)&num+4;
		for (i=0;i<4;i++)
		{
			p--;
			ans=(*p)&0xf0;
			ans>>=4; 
			printf("%X ",ans);
			ans=(*p)&0x0f;
			printf("%X",ans);
			if (i<3) printf(" ");
			else printf("\n");
		}
	}
	return 0;
}
