#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cmath>
using namespace std;
const int N=205;
struct node{
    int x;
    int y;
}myq[N*N];
bool visited[N][N];
int n,m,head,tail,minstep;
int map[N][N];
int cost[N][N][2],start[2][2],direct[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
void bfs(int k)
{
    int x,y;
    memset(visited,0,sizeof(visited));
    visited[start[k][0]][start[k][1]]=true;
    cost[start[k][0]][start[k][1]][k]=0;
    myq[0].x=start[k][0];
    myq[0].y=start[k][1];
    head=tail=0;
    while (head<=tail)
    {
        x=myq[head].x;
        y=myq[head].y;
        for (int i=0,xx,yy;i<4;i++)
        {
            xx=x+direct[i][0];
            yy=y+direct[i][1];
            if (map[xx][yy]&&!visited[xx][yy])
            {
                visited[xx][yy]=true;
                myq[++tail].x=xx;
                myq[tail].y=yy;
                cost[xx][yy][k]=cost[x][y][k]+1;
            }
        }
        head++;
    }
}
int main()
{
    char c;
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        minstep=0x7fffffff;
        memset(map,0,sizeof(map));
        memset(cost,0,sizeof(cost));
        getchar();
        for(int i=1;i<=n;i++)
        {
            for (int j=1;j<=m;j++)
            {
                scanf("%c",&c);
                switch(c)
                {
                    case '#':map[i][j]=0;break;
                    case '.':map[i][j]=1;break;
                    case '@':map[i][j]=2;break;
                    case 'Y':map[i][j]=1;start[0][0]=i;start[0][1]=j;break;
                    case 'M':map[i][j]=1;start[1][0]=i;start[1][1]=j;break;
                }
            }
            getchar();
        } 
        bfs(0);
        bfs(1);
        for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
        {
            if (map[i][j]==2&&cost[i][j][0]&&cost[i][j][1])
            {
                minstep=min(minstep,cost[i][j][0]+cost[i][j][1]);
            }
        }
        printf("%d\n",minstep*11);
    }
    return 0;
}