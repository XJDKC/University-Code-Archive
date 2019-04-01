#include<stdio.h>
int main()
{
	int t,x,i,ans;
	scanf("%d",&t); 
	while (t--)
	{
		ans=0;
		for (i=1;i<=10;i++)
		{
			scanf("%d",&x);
			ans+=x; 
		} 
		printf("sum=%d\n",ans);
	} 
	return 0;
}
