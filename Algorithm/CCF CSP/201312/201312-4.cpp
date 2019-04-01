//
// Created by xjdkc on 19-3-2.
//

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
#define ll long long
#define mod 1000000007
const int N = 1005;
ll n;
ll f[N];

ll cal(int num1,int num3)
{
    int a,b;
    a = min(num1,num3);
    b = max(num1,num3);
    if (num1<num3)
        return (((f[num1-2]-1)*f[num3-num1-1])%mod*f[n-num3])%mod;
    else
        return (((f[a-2]*f[b-a-1]-1)%mod)*f[n-b]%mod);
}

int main()
{
    ll ans=0;
    f[0]=1;
    f[1]=2;
    for (int i=2;i<N;i++)
        f[i]=(f[i-1]*2)%mod;

    cin>>n;
    for (int i=3;i<=n;i++)
        for (int j=2;j<=n;j++)
        {
            if (i!=j&&(j>i||i>=4))
                ans=(ans+cal(i,j))%mod;
        }
    cout<<ans<<endl;
    return 0;
}

/*
 *
 *
 */