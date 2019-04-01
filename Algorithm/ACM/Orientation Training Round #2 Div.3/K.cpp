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
}myq[30];
bool map[7][7],visited[7][7];
int way[7][7],head,tail,direct[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
void bfs()
{
    int x,y;
    memset(visited,0,sizeof(visited));
    head=tail=0;
    visited[1][1]=true;
    myq[0].x=myq[0].y=1;
    while (head<=tail)
    {
        x=myq[head].x;
        y=myq[head].y;
        if (x==5&&y==5) break;
        for (int i=0,xx,yy;i<4;i++)
        {
            xx=x+direct[i][0];
            yy=y+direct[i][1];
            if (!map[xx][yy]&&!visited[xx][yy])
            {
                visited[xx][yy]=true;
                way[xx][yy]=i;
                myq[++tail].x=xx;
                myq[tail].y=yy;
            }
        }
        head++;
    }
}
void output(int x,int y)
{
    if (x==1&&y==1)
    {
        printf("(%d, %d)\n",x-1,y-1);
        return ;
    }
    else
    {
        int temp=way[x][y];
        output(x-direct[temp][0],y-direct[temp][1]);
        printf("(%d, %d)\n",x-1,y-1);
    }
}
int main()
{
    memset(map,true,sizeof(map));
    for (int i=1;i<=5;i++)
    for (int j=1;j<=5;j++)
    {
        cin>>map[i][j];
    }
    bfs();
    output(5,5);
    system("pause");
    return 0;
}
