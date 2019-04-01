//
// Created by xjdkc on 19-3-14.
//

#include <iostream>
#include <algorithm>
using namespace std;
const int N = 106;

int n,m,q;
char canvas[N][N];
bool visited[N][N];
int direct[4][2]={{0,1},{0,-1},{1,0},{-1,0}};

bool isLegal(int x,int y)
{
    return (!(x<0||x>=m||y<0||y>=n));
}

void drawLine(int x1,int y1,int x2,int y2)
{
    y1=n-1-y1;
    y2=n-1-y2;
    if (x1==x2)
    {
        if (y1>y2)
            swap(y1,y2);
        for (int i=y1;i<=y2;i++)
        {
            if (canvas[i][x1]!='-'&&canvas[i][x1]!='+')
                canvas[i][x1]='|';
            else
                canvas[i][x1]='+';
        }
    }
    if (y1==y2)
    {
        if (x1>x2)
            swap(x1,x2);
        for (int i=x1;i<=x2;i++)
        {
            if (canvas[y1][i]!='|'&&canvas[y1][i]!='+')
                canvas[y1][i]='-';
            else
                canvas[y1][i]='+';
        }
    }
}

void Fill(int x,int y,char c)
{
    int xx,yy;
    canvas[y][x]=c;
    visited[y][x]=true;
    for (int i=0;i<4;i++)
    {
        xx=x+direct[i][0];
        yy=y+direct[i][1];
        if (isLegal(xx,yy)&&!visited[yy][xx]&&canvas[yy][xx]!='-'&&canvas[yy][xx]!='|'&&canvas[yy][xx]!='+')
        {
            visited[yy][xx]=true;
            Fill(xx,yy,c);
        }
    }
}

int main()
{
    char c;
    int type,x1,y1,x2,y2;
    cin>>m>>n>>q;
    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++)
            canvas[i][j]='.';

    for (int i=0;i<q;i++)
    {
        cin>>type;
        if (type==0)
        {
            cin>>x1>>y1>>x2>>y2;
            drawLine(x1,y1,x2,y2);
        }
        else
        {
            cin>>x1>>y1>>c;
            y1=n-1-y1;
            fill(visited[0],visited[0]+N*N,false);
            Fill(x1,y1,c);
        }
    }
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<m;j++)
                cout<<canvas[i][j];
        cout<<endl;
    }
    return 0;
}