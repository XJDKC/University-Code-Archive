//
// Created by xjdkc on 19-3-14.
//

#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 1006;

struct node
{
    int x,y;
    int value;
    node(){}
    node(int x,int y)
    {
        this->x=x;
        this->y=y;
    }
};

node r[N*N];
node c[N*N];
int n,m,k,d,total;
int map[N][N];
long long dis[N][N],num[N][N];
bool visited[N][N];
queue<node> q;
int direct[4][2]={{-1,0},{1,0},{0,-1},{0,1}};

void bfs()
{
    node cur;
    int xx,yy;
    fill(visited[0],visited[0]+N*N,false);
    for (int i=0;i<m;i++)
    {
        dis[r[i].x][r[i].y]=0;
        visited[r[i].x][r[i].y]=true;
        q.push(node(r[i]));
    }
    while (!q.empty())
    {
        cur=q.front();
        q.pop();
        for (int i=0;i<4;i++)
        {
            xx=cur.x+direct[i][0];
            yy=cur.y+direct[i][1];
            if (xx<1||xx>n||yy<1||yy>n)
                continue;
            if ((!visited[xx][yy])&&map[xx][yy]>=0)
            {
                visited[xx][yy]=true;
                dis[xx][yy]=dis[cur.x][cur.y]+1;
                q.push(node(xx,yy));
            }
        }
    }
}
int main()
{
    int x,y,z;
    long long ans=0;
    cin>>n>>m>>k>>d;
    for (int i=0;i<m;i++)
        cin>>r[i].x>>r[i].y;
    for (int i=0;i<k;i++)
    {
        cin>>x>>y>>z;
        c[i].x=x;
        c[i].y=y;
        c[i].value=z;
        dis[x][y]=0;
    }
    for (int i=0;i<d;i++)
    {
        cin>>x>>y;
        map[x][y]=-1;
    }

    bfs();

    for (int i=0;i<k;i++)
        ans+=dis[c[i].x][c[i].y]*c[i].value;
    cout<<ans<<endl;
    return 0;
}
/*
 *
10 2 4 3
1 1
8 8
1 5 1
1 5 1
2 3 3
6 7 2
1 2
2 2
6 8
 */