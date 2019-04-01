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
int dp[2006],a[2006];
int main()
{
    int t,n,HH,MM,SS;
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d",&n);
        memset(dp,0,sizeof(dp));
        for (int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        dp[1]=a[1];
        for (int i=1,x;i<n;i++)
        {
            scanf("%d",&x);
            dp[i+1]=min(dp[i-1]+x,dp[i]+a[i+1]);
        }
        SS=dp[n]%60;
        MM=dp[n]/60;
        HH=MM/60+8;
        MM%=60;
        if (HH<13) printf("%02d:%02d:%02d am\n",HH,MM,SS);
        else printf("%02d:%02d:%02d pm\n",HH-12,MM,SS);
    }
    system("pause");
    return 0;
}