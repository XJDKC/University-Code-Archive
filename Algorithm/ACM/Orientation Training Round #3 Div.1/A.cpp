#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cctype>
#include<string>
#include<cmath>
#include<queue>
#include<stack>
#include<set>
#include<map>
using namespace std;
#define ll long long
const int oo=0x7fffffff;
const ll loo=0x7fffffffffffffff;
const int N=1000006;
int n,m;
int a[N];
ll dp[N],maxlast[N];
int main()
{
    ll ans=0;
    while (scanf("%d%d",&m,&n)!=EOF)
    {
        ans=-(loo-1);
        memset(dp,0,sizeof(dp));
        memset(maxlast,0,sizeof(maxlast));
        dp[0]=-(loo-1);
        for (int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for (int i=1;i<=m;i++)
        {
            for (int j=i;j<=n;j++)
            {
                if (i==j) dp[j]=maxlast[j-1]+a[j];
                else
                    dp[j]=max(dp[j-1],maxlast[j-1])+a[j];
                if (j==i+1) maxlast[j-1]=dp[j-1];
                else maxlast[j-1]=max(dp[j-1],maxlast[j-2]);
            }
        }
        for (int i=m;i<=n;i++)
            ans=max(ans,dp[i]);
        printf("%lld\n",ans);
    }
    system("pause");
    return 0;
}