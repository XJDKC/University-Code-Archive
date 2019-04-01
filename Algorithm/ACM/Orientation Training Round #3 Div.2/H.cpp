#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cmath>
using namespace std;
struct node{
    int x,y,z;
}a[181];
int dp[181];
bool comp(const node &p,const node &q)
{
    if (p.x!=q.x) return p.x>q.x;
    if (p.y!=q.y) return p.y>q.y;
    if (p.z!=q.z) return p.z>q.z;
}
int main()
{
    int n,ans=0,t=0;
    a[0].z=0;
    a[0].x=a[0].y=0x7fffffff;
    while (scanf("%d",&n)&&n)
    {
        t++;
        ans=0;
        memset(dp,0,sizeof(dp));
        for (int i=0,xx,yy,zz;i<n;i++)
        {
            scanf("%d%d%d",&xx,&yy,&zz);
            a[6*i+1].x=xx,a[6*i+1].y=yy,a[6*i+1].z=zz;
            a[6*i+2].x=yy,a[6*i+2].y=xx,a[6*i+2].z=zz;
            a[6*i+3].x=xx,a[6*i+3].y=zz,a[6*i+3].z=yy;
            a[6*i+4].x=zz,a[6*i+4].y=xx,a[6*i+4].z=yy;
            a[6*i+5].x=zz,a[6*i+5].y=yy,a[6*i+5].z=xx;
            a[6*i+6].x=yy,a[6*i+6].y=zz,a[6*i+6].z=xx;
        }
        sort(a,a+6*n+1,comp);
        for (int i=1;i<=6*n;i++)
        {
            for (int j=0;j<i;j++)
            {
                if (a[j].x>a[i].x&&a[j].y>a[i].y)
                {
                    dp[i]=max(dp[i],dp[j]+a[i].z);
                }
            }
            ans=max(ans,dp[i]);
        }
        printf("Case %d: maximum height = %d\n",t,ans);
    }
    return 0;
}