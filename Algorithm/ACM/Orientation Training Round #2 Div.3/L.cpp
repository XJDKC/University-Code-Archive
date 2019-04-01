#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cmath>
using namespace std;
bool map[105][105];
int block[105][105],direct[8][2]={{1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,1},{1,-1},{-1,-1}};
int n,m,k=0;
void find(int x,int y,int k)
{
    block[x][y]=k;
    for (int i=0,xx,yy;i<8;i++)
    {
        xx=x+direct[i][0];
        yy=y+direct[i][1];
        if (map[xx][yy]&&!block[xx][yy]) 
            find(xx,yy,k);
    }
}
void solve()
{
    k=1;
    for (int i=1;i<=m;i++)
    for (int j=1;j<=n;j++)
    {
        if (map[i][j]&&!block[i][j])
        {
            find(i,j,k);
            k++;
        }
    }
    k--;
}
int main()
{
    char c;
    while (scanf("%d%d",&m,&n)!=EOF&&m)
    {
        memset(map,0,sizeof(map));
        memset(block,0,sizeof(block));
        getchar();
        for (int i=1;i<=m;i++)
        {
            for (int j=1;j<=n;j++)
            {
                scanf("%c",&c);
                if (c=='*')
                    map[i][j]=false;
                else
                    map[i][j]=true;
            }
            getchar();
        }
        solve();
        printf("%d\n",k);
    }
    return 0;
}