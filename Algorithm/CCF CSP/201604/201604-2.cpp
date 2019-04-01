//
// Created by xjdkc on 19-3-14.
//
#include <iostream>
using namespace std;
int map[20][20];
int block[20][20];
int main()
{
    int c;
    for (int i=1;i<=15;i++)
        for (int j=1;j<=10;j++)
        {
            cin>>map[i][j];
        }
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
            cin>>block[i][j];
    cin>>c;
    for (int i=1;i<=10;i++)
        map[16][i]=1;

    int ans=1;
    bool flag=true;
    while (flag)
    {
        ans++;
        for (int i=0;i<4;i++)
            for (int j=0;j<4;j++)
                if (map[ans+i][c+j]+block[i][j]>1)
                {
                    flag=false;
                    break;
                }
    }
    ans--;
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
            map[ans+i][c+j]+=block[i][j];
    for (int i=1;i<=15;i++)
        for (int j=1;j<=10;j++)
        {
            cout<<map[i][j];
            if (j<10)
                cout<<" ";
            else
                cout<<endl;
        }
    return 0;
}