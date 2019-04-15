#include<stdio.h>
int main()
{
	int n;
	short x,ans;
	scanf("%d",&n);
	while (n--)
	{
		scanf("%hd",&x);
		ans=(x>>8)&0x00ff;
		printf("%c,",ans);
		ans=x&0x00ff;
		printf("%c\n",ans);
	}
	return 0;
}
