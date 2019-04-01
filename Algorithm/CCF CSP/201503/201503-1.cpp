//
// Created by xjdkc on 19-3-14.
//

#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1006;
int f[N][N];
int main()
{
    int n,m;
    cin>>n>>m;
    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++)
            cin>>f[i][j];
    for (int i=m-1;i>=0;i--)
        for (int j=0;j<n;j++)
        {
            cout<<f[j][i];
            if (j<n-1)
                cout<<" ";
            else
                cout<<endl;
        }
    return 0;
}