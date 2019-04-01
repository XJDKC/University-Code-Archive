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
int a[1005],dp[1005];
int main()
{
    int n,ans=0;
    while (scanf("%d",&n)&&n)
    {
        ans=0;
        for (int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            dp[i]=a[i];
        }
        for (int i=2;i<=n;i++)
        {
            for (int j=1;j<i;j++)
            {
                if (a[j]<a[i]&&dp[j]+a[i]>dp[i])
                {
                    dp[i]=dp[j]+a[i];
                }
            }
            ans=max(ans,dp[i]);
        }
        printf("%d\n",ans);
    }
    system("pause");
    return 0;
}