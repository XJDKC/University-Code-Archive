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
int dp[10005];
int main()
{
    int n,j;
    while (scanf("%d",&n)!=EOF)
    {
        memset(dp,0,sizeof(dp));
        for (int i=1,x;i<=n;i++)
        {
            scanf("%d",&x);
            for (j=dp[0];j>=1;j--)
            {
                if (dp[j]<x)
                    break;
            }
            if (j==dp[0])
            {
                dp[++dp[0]]=x;
            }
            else
            {
                dp[j+1]=x;
            }
        }
        printf("%d\n",dp[0]);
    }
    system("pause");
    return 0;
}