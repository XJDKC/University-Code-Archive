#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cmath>
using namespace std;
int a[100001][11];
int dp[100001][11];
int main()
{
    int n,maxt=0,ans=0;
    while (scanf("%d",&n)&&n)
    {
        memset(a,0,sizeof(int)*11*(maxt+1));
        memset(dp,0,sizeof(int)*11*(maxt+1));
        maxt=ans=0;
        for (int i=0,x,T;i<n;i++)
        {
            scanf("%d%d",&x,&T);
            a[T][x]++;
            maxt=max(maxt,T);
        }
        dp[0][5]=1;
        for (int i=1;i<=maxt;i++)
        {
            for (int j=0;j<11;j++)
            {
                if (j&&dp[i-1][j-1])
                {
                    dp[i][j]=max(dp[i][j],dp[i-1][j-1]+a[i][j]);
                }
                if (dp[i-1][j])
                {
                    dp[i][j]=max(dp[i][j],dp[i-1][j]+a[i][j]);
                }
                if (j<10&&dp[i-1][j+1])
                {
                    dp[i][j]=max(dp[i][j],dp[i-1][j+1]+a[i][j]);
                }
            }
        }
        for (int i=0;i<11;i++)
            ans=max(ans,dp[maxt][i]);
        printf("%d\n",ans-1);
    }
    return 0;
}