//
// Created by xjdkc on 19-3-2.
//

#include <iostream>

using namespace std;

const int N=10006;

int f[N]={0};

int main()
{
    int n,x,ans,time=0;
    cin>>n;
    for (int i=0;i<n;i++)
    {
        cin>>x;
        f[x]++;
    }
    for (int i=1;i<=10000;i++)
        if (f[i]>time)
        {
            ans=i;
            time=f[i];
        }
    cout<<ans<<endl;
    return 0;
}