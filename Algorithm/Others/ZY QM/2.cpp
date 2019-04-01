#include<stdio.h>
int ans=0;
int cal(int n,int a,int b)
{
	if (n==0) return 1;
	else
	{
		int i,j,m=0; 
		for (i=0;i<=a;i++)
		for (j=0;j<=b;j++)
		m+=cal(n-1,a-i,b-j);
		return m;
	}
}
int main()
{
	int n,a,b;
	scanf("%d%d%d",&n,&a,&b);
	ans=cal(n,a,b);
	printf("%d\n",ans);
	return 0; 
}
