#include<stdio.h>
#include<math.h>
int isprime(int t)
{
	if (t==2) return 1;
	else 
	{
		int k,m=sqrt(t)+1;
		for (k=2;k<=m;k++)
		{
			if (t%k==0) return 0;
		}
		return 1;
	}
}
int main()
{
	int n,x,i;
	scanf("%d",&n);
	while (n--)
	{
		scanf("%d",&x);
		for (i=2;i<=x/2;i++)
		{
			if (isprime(i)&&isprime(x-i))
			{
			    printf("%d=%d+%d\n",x,i,x-i);
		        break;
		    }
		}
	}
	return 0;
}
