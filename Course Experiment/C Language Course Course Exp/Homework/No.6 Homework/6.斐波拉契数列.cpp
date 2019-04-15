#include<stdio.h>
int fab(int n)
{
	if (n==1|n==2) return 1;
	else return fab(n-1)+fab(n-2);
}
int main()
{
	freopen("fab.in","r",stdin);
	freopen("fab.out","w",stdout);
	int n,no=0,i;
	while (scanf("%d",&n))
	{
		if (n==0) break;
		if (no==0) no=1;
		else printf("\n");
		if (n<3&&n>0) printf("Error!\n");
		else
		{
			for(i=1;i<=n;i++)
			{
				printf("%10d",fab(i));
				if (i%8==0) printf("\n");
			}
			if (n%8) printf("\n");
		}
	}
	printf("\n");
	return 0;
}
