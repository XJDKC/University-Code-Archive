#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cmath>
using namespace std;
const int oo=0x7fffffff;
int map[11][11],block[11][11],myq[105],step[11][11];
int direct[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
bool visited[11][11];
int n,m;
int minstep,k,head,tail;
void find(int x,int y,int k)
{
    block[x][y]=k;
    if (map[x-1][y]&&!block[x-1][y]) find(x-1,y,k);
    if (map[x+1][y]&&!block[x+1][y]) find(x+1,y,k);
    if (map[x][y-1]&&!block[x][y-1]) find(x,y-1,k);
    if (map[x][y+1]&&!block[x][y+1]) find(x,y+1,k);
}
bool judge()
{
    k=1;
    for (int i=1;i<=n;i++)
    for (int j=1;j<=m;j++)
    {
        if (map[i][j]&&!block[i][j])
        {
            find(i,j,k);
            k++;
        }
    }
    k--;
    if (k>2) return false;
    else return true; 
}
void solve(int x1,int y1,int x2,int y2)
{
    if (k==2&&block[x1][y1]==block[x2][y2]) return ;
    int x,y,nextx,nexty,curstep=0;
    head=0;
    tail=1;
    myq[0]=x1*100+y1;
    myq[1]=x2*100+y2;
    step[x1][y1]=step[x2][y2]=0;
    memset(visited,0,sizeof(visited));    
    visited[x1][y1]=visited[x2][y2]=true;
    while (head<=tail)
    {
        x=myq[head]/100;
        y=myq[head]%100;
        for (int i=0;i<4;i++)
        {
            nextx=x+direct[i][0];
            nexty=y+direct[i][1];
            if (map[nextx][nexty]&&!visited[nextx][nexty])
            {
                visited[nextx][nexty]=true;
                myq[++tail]=nextx*100+nexty;
                step[nextx][nexty]=step[x][y]+1;
                curstep=max(curstep,step[x][y]+1);
            }
        }
        head++;
    }
    minstep=min(minstep,curstep);
}
int main()
{
    char c;
    int t;
    scanf("%d",&t);
    for (int no=1;no<=t;no++)
    {
        minstep=oo;
        memset(map,0,sizeof(map));
        memset(block,0,sizeof(block));
        scanf("%d%d",&n,&m);
        getchar();
        for (int i=1;i<=n;i++)
        {
            for (int j=1;j<=m;j++)
            {
                scanf("%c",&c);
                if (c=='.') map[i][j]=0;
                else map[i][j]=1;
            }
            getchar();
        }
        if (!judge()) printf("Case %d: -1\n",no);
        else 
        {
            for (int i=1;i<=n;i++)
            for (int j=1;j<=m;j++)
            {
                if (map[i][j])
                {
                    for (int p=j;p<=m;p++)
                    if (map[i][p])
                        solve(i,j,i,p);
                    for (int p=i+1;p<=n;p++)
                    for (int q=1;q<=m;q++)
                    if (map[p][q])
                        solve(i,j,p,q);
                }
            }
            printf("Case %d: %d\n",no,minstep);
        }
    }
    system("pause");
    return 0;
}