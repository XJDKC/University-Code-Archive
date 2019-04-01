//
// Created by xjdkc on 19-3-14.
//

#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
int map[36][36],f[36][36];
int direct[6][2][2]={{{0,-1},{0,1}},{{-1,0},{1,0}},{{0,-2},{0,-1}},{{0,1},{0,2}},{{-2,0},{-1,0}},{{2,0},{1,0}}};
int n,m;

bool isLegal(int x,int y)
{
    if (x<0||x>=n||y<0||y>m)
        return false;
    return true;
}

void cancel(int x,int y)
{
    int x1,x2,y1,y2;
    for (int i=0;i<6;i++)
    {
        x1=x+direct[i][0][0];
        x2=x+direct[i][1][0];
        y1=y+direct[i][0][1];
        y2=y+direct[i][1][1];
        if (isLegal(x1,y1)&&isLegal(x2,y2))
        {
            if (map[x][y]==map[x1][y1]&&map[x][y]==map[x2][y2])
            {
                if (!f[x1][y1])
                {
                    f[x1][y1]=1;
                    cancel(x1,y1);
                }
                if (!f[x2][y2])
                {
                    f[x2][y2]=1;
                    cancel(x2,y2);
                }
            }
        }
    }
}
int main()
{
    cin>>n>>m;
    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++)
            cin>>map[i][j];
    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++)
        {
            cancel(i,j);
        }
    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++)
        {
            if (f[i][j])
                cout<<0;
            else
                cout<<map[i][j];
            if (j<m-1)
                cout<<" ";
            else
                cout<<endl;
        }
    return 0;
}