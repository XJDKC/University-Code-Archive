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
    int dead;
    int cost;
    char name[105];
}a[16];
struct dpnode{
    int prev;
    int cost;
    int reduce;
}dp[40000];
void output(int state)
{
    if (state==0)
        return ;
    else{
        output(dp[state].prev);
        int temp=state-dp[state].prev,count=0;
        while (temp) 
        {
            temp/=2;
            count++;
        }
        printf("%s\n",a[count].name);
    }
}
int main()
{
    int t,n,maxstate,curstate,temp,last;
    scanf("%d",&t);
    while (t--)
    {
        memset(dp,0,sizeof(dp));
        scanf("%d",&n);
        for (int i=1;i<=n;i++)
        {
            scanf("%s%d%d",a[i].name,&a[i].dead,&a[i].cost);
        }
        maxstate=1<<n;
        for (int i=1;i<maxstate;i++)
        {
            dp[i].reduce=oo;
            for (int j=n;j>=1;j--)  //由于要字典序升序输出 所以第二重循环要从后往前遍历 即字典序靠后的后枚举 若出现相同情况 字典序靠前的会先输出
            {
                curstate=1<<(j-1);
                if (i&curstate) //如果第j位有值说明 该状态下完成了 j作业
                {
                    last=i-curstate;
                    temp=dp[last].reduce;
                    if (a[j].cost+dp[last].cost>a[j].dead)
                        temp+=a[j].cost+dp[last].cost-a[j].dead;
                    if (temp<dp[i].reduce)
                    {
                        dp[i].prev=last;
                        dp[i].cost=dp[last].cost+a[j].cost;
                        dp[i].reduce=temp;
                    }
                }
            }
        }
        printf("%d\n",dp[maxstate-1].reduce);
        output(maxstate-1);
    }
    system("pause");
    return 0;
}