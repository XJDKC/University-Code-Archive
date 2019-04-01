#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cmath>
using namespace std;
int dp[1005],a[1005];
int main()
{
    int n,ans=1;
    cin>>n;
    fill(dp,dp+1005,1);
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    for (int i=2;i<=n;i++)
    {
        for (int j=1;j<i;j++)
        {
            if (a[j]<a[i]&&dp[j]+1>dp[i])
            {
                dp[i]=dp[j]+1;
            }
        }
        ans=max(dp[i],ans);
    }
    printf("%d\n",ans);
    system("pause");
    return 0;
}