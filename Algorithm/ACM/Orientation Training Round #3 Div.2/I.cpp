#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cmath>
using namespace std;
int dp[100005],v,w;
int main()
{
    int N,M;
    scanf("%d%d",&N,&M);
    for (int i=1;i<=N;i++)
    {
        scanf("%d%d",&v,&w);
        for (int j=v;j<=M;j++)
        {
            dp[j]=max(dp[j],dp[j-v]+w);
        }
    }
    printf("%d\n",dp[M]);
    system("pause");
    return 0;
}
