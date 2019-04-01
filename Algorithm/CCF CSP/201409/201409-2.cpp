//
// Created by xjdkc on 19-3-14.
//

#include <iostream>
#include <algorithm>
using namespace std;
const int N = 105;

bool draw[N][N];

int main()
{
    int n,ans=0;
    int x1,y1,x2,y2;
    cin>>n;

    for (int i=0;i<n;i++)
    {
        cin>>x1>>y1>>x2>>y2;
        for (int j=x1;j<x2;j++)
            for (int k=y1;k<y2;k++)
            {
                if (!draw[j][k])
                    ans++;
                draw[j][k]=true;
            }
    }
    cout<<ans<<endl;
    return 0;
}