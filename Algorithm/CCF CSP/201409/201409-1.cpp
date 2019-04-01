//
// Created by xjdkc on 19-3-14.
//

#include <iostream>
#include <algorithm>
using namespace std;
const int N = 10005;
bool f[N];
int main()
{
    int n,x,ans=0;
    cin>>n;
    for (int i=0;i<n;i++)
    {
        cin>>x;
        f[x]=true;
    }
    for (int i=0;i<N;i++)
        if (f[i]&&f[i+1])
            ans++;
    cout<<ans<<endl;
    return 0;
}
