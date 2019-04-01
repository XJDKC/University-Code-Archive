#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cmath>
using namespace std;
struct node{
    int x;
    int y;
    int step;
}myq[1000005];
bool map[1005][1005],visited[1005][1005];
int n,m;
int step[1005][1005],direct[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int startx,starty,head,tail;
void init()
{
    int x,y;
    while (head<tail)
    {
        x=myq[head].x;
        y=myq[head].y;
        for (int i=0,tempx,tempy;i<4;i++)
        {
            tempx=x+direct[i][0];
            tempy=y+direct[i][1];
            if (map[tempx][tempy]&&(!step[tempx][tempy]||step[tempx][tempy]>step[x][y]+1))
            {
                step[tempx][tempy]=step[x][y]+1;
                myq[tail].x=tempx;
                myq[tail++].y=tempy;
            }
        }
        head++;
    }
}
bool bfs()
{
    bool mark=false;
    int x,y;
    head=tail=0;
    memset(visited,0,sizeof(visited));
    visited[startx][starty]=true;
    myq[0].x=startx;
    myq[0].y=starty;
    myq[0].step=0;
    visited[startx][starty]=true;
    while (head<=tail&&!mark)
    {
        x=myq[head].x;
        y=myq[head].y;
        if (x==1||y==1||x==n||y==m) {mark=true;break;}
        for (int i=0,tempx,tempy;i<4;i++)
        {
            tempx=x+direct[i][0];
            tempy=y+direct[i][1];
            if (map[tempx][tempy]&&!visited[tempx][tempy]&&(!step[tempx][tempy]||myq[head].step+1<step[tempx][tempy]-1))
            {
                visited[tempx][tempy]=true;
                myq[++tail].x=tempx;
                myq[tail].y=tempy;
                myq[tail].step=myq[head].step+1;
            }
        }
        head++;
    }
    return mark;
}
int main()
{
    char c;
    int t;
    scanf("%d",&t);
    while (t--)
    {
        head=tail=0;
        memset(step,0,sizeof(step));
        memset(map,0,sizeof(map));
        scanf("%d%d",&n,&m);
        getchar();
        for (int i=1;i<=n;i++)
        {
            for (int j=1;j<=m;j++)
            {
                scanf("%c",&c);
                switch(c)
                {
                    case '#':map[i][j]=false;break;
                    case '.':map[i][j]=true;break;
                    case 'J':map[i][j]=true;startx=i;starty=j;break;
                    case 'F':map[i][j]=true;
                             myq[tail].x=i;myq[tail++].y=j;
                             step[i][j]=1;break;
                }
            }
            getchar();
        }
        init();
        // for (int i=1;i<=n;i++)
        // {
        //     for (int j=1;j<=m;j++)
        //     {
        //         cout<<step[i][j];
        //     }
        //     cout<<endl;
        // }
        if (bfs())
        {
            printf("%d\n",myq[head].step+1);
        }
        else
        {
            printf("IMPOSSIBLE\n");
        }
    }
    system("pause");
    return 0;
}