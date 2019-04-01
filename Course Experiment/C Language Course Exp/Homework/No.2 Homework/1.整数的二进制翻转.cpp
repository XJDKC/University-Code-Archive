#include<stdio.h>
int main()
{
	int x,x1,p,n,i,mask=1<<31,ans;
	scanf("%d%d%d",&x,&p,&n);
	x1=x;
	for (i=31;i>=0;i--)
	{
	    if(x&mask) ans=1;
	    else ans=0;
	    x<<=1;
	    printf("%d",ans);
	    if (i%8==0&&i>0) printf(" ");
	}
	printf("\n");
	for (i=31;i>=0;i--)
	{
		if (x1&mask) ans=1;
		else ans=0;
		x1<<=1;
		if (i<=n+p-1&&i>=p) ans=ans==0?1:0;
		printf("%d",ans);
		if (i%8==0&&i) printf(" ");
	}
	printf("\n");
	return 0;
} 
