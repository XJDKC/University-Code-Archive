#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cmath>
using namespace std;
double f[40];
double dp[40];
int main()
{
    bool mark;
    double maxm,price,temp,ans=0,A,B,C;
    int n,num,m;
    char c;
    while (scanf("%lf%d",&maxm,&n)&&n)
    {
        num=0;
        ans=0;
        memset(f,0,sizeof(f));
        memset(dp,0,sizeof(dp));
        for (int i=0;i<n;i++)
        {
            scanf("%d",&m);
            getchar();
            mark=true;
            f[num]=A=B=C=0;
            for (int i=0;i<m;i++)
            {
                scanf("%c:%lf",&c,&price);
                getchar();
                if ((c=='A'||c=='B'||c=='C')&&mark)
                {
                    f[num]+=price;
                    switch (c)
                    {
                        case 'A':A+=price;break;
                        case 'B':B+=price;break;
                        case 'C':C+=price;break;
                    }
                }
                else
                {
                    mark=false;
                }
            }
            if (mark&&A<=600&&B<=600&&C<=600) num++;
        }
        for (int i=0;i<num;i++)
        {
            for (int j=1;j<=num;j++)
            {
                temp=dp[j-1]+f[i];
                if (temp>dp[j]&&temp<=maxm)
                {
                    dp[j]=temp;
                }
                ans=max(ans,dp[j]);
            }
        }
        printf("%.2lf\n",ans);
    }
    return 0;
}