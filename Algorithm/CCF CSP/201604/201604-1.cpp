//
// Created by xjdkc on 19-3-14.
//

#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1006;
int f[N];
int main()
{
    int n,ans=0;
    cin>>n;
    for (int i=0;i<n;i++)
        cin>>f[i];
    for (int i=1;i<n-1;i++)
    {
        if (f[i]>f[i-1]&&f[i]>f[i+1]||f[i]<f[i-1]&&f[i]<f[i+1])
            ans++;
    }
    cout<<ans<<endl;
}