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
int w[506],p[506],dp[10006];

int main()
{
    int t,n,E,F;
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d%d%d",&E,&F,&n);
        F-=E;
        memset(dp,0x3f,sizeof(dp));
        for (int i=1;i<=n;i++)
        {
            scanf("%d%d",&p[i],&w[i]);
        }
        dp[0]=0;
        for (int i=1;i<=n;i++)
        {
            for (int j=w[i];j<=F;j++)
            {
                if (dp[j-w[i]]+p[i]<dp[j])
                {
                    dp[j]=dp[j-w[i]]+p[i];
                }
            }
        }
        if (dp[F]==0x3f3f3f3f) printf("This is impossible.\n");
        else printf("The minimum amount of money in the piggy-bank is %d.\n",dp[F]);
    }
    system("pause");
    return 0;
}