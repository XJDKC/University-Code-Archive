#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cmath>
using namespace std;
int dp[105][105],a[105][105];
int main()
{
    int n,ans=0;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    for (int j=1;j<=i;j++)
    {
        scanf("%d",&a[i][j]);
        dp[i][j]=max(dp[i-1][j],dp[i-1][j-1])+a[i][j];
        if (i==n) ans=max(ans,dp[i][j]);
    }
    printf("%d\n",ans);
    return 0;
}