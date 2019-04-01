//
// Created by xjdkc on 19-3-14.
//

#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    int n,ans=0;
    cin>>n;
    while (n)
    {
        ans+=n%10;
        n/=10;
    }
    cout<<ans<<endl;
    return 0;
}