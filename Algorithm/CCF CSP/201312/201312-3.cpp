//
// Created by xjdkc on 19-3-2.
//

#include <iostream>
using namespace std;

const int N = 1005;
int f[N];

int main()
{
    int n,ans=0;
    cin>>n;
    for (int i=0;i<n;i++)
        cin>>f[i];

    for (int i=0;i<n;i++)
    {
        int minh=0x7fffffff;
        for (int j=i;j<n;j++)
        {
            minh=min(minh,f[j]);
            ans=max(minh*(j-i+1),ans);
        }
    }
    cout<<ans<<endl;
    return 0;
}