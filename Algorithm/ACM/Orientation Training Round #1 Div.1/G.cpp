#include<iostream>
#include<algorithm>
using namespace std;
int order[25],judge[25],dp[25];
int LIS(int n)
{
	int maxlen=1;
	fill(dp,dp+25,1);
	for (int i=2;i<=n;i++)
	{
		for (int j=1;j<i;j++)
		{
			if (order[judge[j]]<order[judge[i]]&&dp[j]+1>dp[i])
			{
				dp[i] = dp[j] + 1;
			}
		}
		maxlen=max(maxlen,dp[i]);
	}
	return maxlen;
}
int main()
{
	char c;
	int n,temp,ans,x;
	while (cin>>temp)
	{
		c=getchar();
		if (c=='\n')
		{
			n=temp;
			for (int i=1;i<=n;i++)
			{
				cin>>order[i];
			}
		}
		else 
		{
			judge[temp]=1;
			for (int i=2;i<=n;i++)
			{
				cin>>x;
				judge[x]=i;
			}
			ans=LIS(n);
			cout<<ans<<endl;
		}
	}
	return 0;
}

