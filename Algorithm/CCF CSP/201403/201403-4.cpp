//
// Created by xjdkc on 19-3-1.
//

#include <iostream>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
const int N=205;

struct point
{
    long long x;
    long long y;
    point() {}
    point(long long a,long long b)
    {
        x=a;
        y=b;
    }
}Point[N];

int n,m,k,r;
bool map[N][N];
bool visited[N];
queue<point> q;


void input();
int bfs();


int main() {

    input();
    cout<<bfs()<<endl;
    return 0;
}

//由于权值为1 二维费用的最短路退化成BFS 而且出队顺序就是优先队列顺序 而且根据BFS特性 一旦找到 就一定跳数最短 所以就可以快速得出答案
int bfs()
{
    int l=0,len=1;
    visited[0]=true;
    q.push(point(0,0));
    while (!q.empty())
    {
        point s=q.front();
        q.pop();
        if (s.x==1) return l-1;
        for (int i=0;i<n+m;i++)
        {
            if (!visited[i]&&map[s.x][i])
            {
                if (i<n)
                {
                    visited[i]=true;
                    q.push(point(i,s.y));
                }
                else if (s.y+1<=k)
                {
                    visited[i]=true;
                    q.push(point(i,s.y+1));
                }
            }
        }
        len--;
        if (len==0)
        {
            len=q.size();
            l++;
        }
    }
}

void input()
{
    long long deltax,deltay;
    cin>>n>>m>>k>>r;
    for (int i=0;i<n+m;i++)
    {
        cin>>Point[i].x>>Point[i].y;
    }
    for (int i=0;i<n+m;i++)
        for (int j=0;j<i;j++)
        {
            deltax=abs(Point[i].x-Point[j].x);
            deltay=abs(Point[i].y-Point[j].y);
            if (sqrt(deltax*deltax+deltay*deltay)<=r)
                map[i][j]=map[j][i]=true;
            else
                map[i][j]=map[j][i]=false;
        }
}