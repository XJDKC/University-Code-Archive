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
struct node{
    int no;
    int weight;
    int speed;
}a[1006];
int dp[1006],pre[1006];
bool comp(const node &x,const node &y)
{
    return x.weight<y.weight;
}
void output(int last)
{
    if (last!=pre[last]) 
    {
        output(pre[last]);
    }
    printf("%d\n",a[last].no);
}
int main()
{
    int no=0,w,s,maxn=0,maxno=1;        //no初始化
    while (scanf("%d%d",&w,&s)!=EOF)
    {
        a[++no].weight=w;
        a[no].speed=s;
        a[no].no=no;
    }
    sort(a+1,a+no+1,comp);    
    for (int i=1;i<=no;i++)
    {
        dp[i]=1;
        pre[i]=i;
    }
    for (int i=1;i<=no;i++)
    {
        for (int j=1;j<i;j++)
        {
            if (a[j].speed>a[i].speed&&a[i].weight>a[j].weight&&dp[i]<dp[j]+1)
            {
                dp[i]=dp[j]+1;
                pre[i]=j;
            }
        }
        if (maxn<dp[i]) maxn=dp[i],maxno=i;
    }
    printf("%d\n",maxn);
    if (maxn) output(maxno);
    //system("pause");
    return 0;
}
