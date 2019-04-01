#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cmath>
using namespace std;
int N,M,mins=0x7fffffff;
int minv[25],minss[25];
bool judge(int r,int h,int v,int m,int s)
{
    if (2*v/r>=mins-s) return false;
    if (s+minss[m]>mins||v<minv[m]) return false;
    return true;
}
void dfs(int r,int h,int v,int m,int s)   //上一层半径 高度 总体积 总层数 总面积
{
    if (v==0&&m==0)
    {
        mins=min(mins,s);
    }
    else if (m<=0||v<=0) return ;
    else if (judge(r,h,v,m,s))
    {
        int maxr=min(r-1,(int)sqrt((double)((v-minv[m-1])/m)));
        for (int i=maxr;i>=m;i--)
        {
            if (m==M) s=i*i;
            for (int j=min(h-1,(v-minv[m-1])/i/i);j>=m;j--)
            {
                if (v-i*i*j-minv[m-1]>=0&&s+2*i*j+minss[m-1]<=mins)
                {
                    dfs(i,j,v-i*i*j,m-1,s+2*i*j);
                }
            }
        }
    }
}
int main()
{
    scanf("%d%d",&N,&M);
    for (int i=1;i<=20;i++)
    {
        minv[i]=minv[i-1]+i*i*i;
        minss[i]=minss[i-1]+2*i*i;
    }
    dfs(N+1,N+1,N,M,0);
    if (mins==0x7fffffff)
        printf("0\n");
    else 
        printf("%d\n",mins);
    system("pause");
    return 0;
}