//
// Created by xjdkc on 19-3-1.
//

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

struct rect
{
    int no;
    int x1,x2,y1,y2;

    rect();
    rect(int no,int a,int b,int c,int d);
    bool insideRect(int x,int y);
};

vector<rect> windows;

int main()
{
    int n,m;
    int x1,x2,y1,y2;
    int x,y;
    rect temp;
    cin>>n>>m;

    for (int i=0;i<n;i++)
    {
        cin>>x1>>y1>>x2>>y2;
        windows.insert(windows.begin(),rect(i+1,x1,y1,x2,y2));
    }

    for (int i=0,j;i<m;i++)
    {
        cin>>x>>y;
        for (j=0;j<n;j++)
        {
            if (windows[j].insideRect(x,y))
                break;
        }
        if (j<n)
        {
            cout<<windows[j].no<<endl;
            temp=windows[j];
            windows.erase(windows.begin()+j);
            windows.insert(windows.begin(),temp);
        }
        else
        {
            cout<<"IGNORED"<<endl;
        }
    }
    return 0;
}


rect::rect()
{
    x1=x2=y1=y2=0;
}

rect::rect(int no,int a, int b, int c, int d)
{
    x1=a; y1=b;
    x2=c; y2=d;
    this->no=no;
}

bool rect::insideRect(int x, int y)
{
    if (x1<=x&&x<=x2&&y1<=y&&y<=y2)
        return true;
    return false;
}