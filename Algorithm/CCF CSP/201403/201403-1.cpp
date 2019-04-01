//
// Created by xjdkc on 19-3-1.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

const int N=1006;

bool f[N][2]={false};

int main()
{
    int ans=0;
    int n,x;
    cin>>n;
    for (int i=0;i<n;i++)
    {
        cin>>x;
        if (x<0)
            f[abs(x)][1]=true;
        else
            f[abs(x)][0]=true;

        if (f[abs(x)][1]&&f[abs(x)][0])
            ans++;
    }
    cout<<ans<<endl;
    return 0;
}