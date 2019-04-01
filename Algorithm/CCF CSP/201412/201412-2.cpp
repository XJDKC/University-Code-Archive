//
// Created by xjdkc on 19-3-14.
//

#include <iostream>
using namespace std;
const int N = 506;
int f[N][N];
int main()
{
    int n;
    int x,y;
    cin>>n;
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            cin>>f[i][j];

    for (int i=0;i<2*n-1;i++)
    {
        for (int j=0;j<i+1;j++)
        {
            if (i%2)
            {
                x=j;
                y=i-j;
            }
            else
            {
                y=j;
                x=i-j;
            }
            if (x>=n||y>=n)
                continue;
            cout<<f[x][y];
            if (j==i&&i==2*n-2)
                cout<<endl;
            else
                cout<<" ";
        }
    }
    return 0;
}