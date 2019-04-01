//
// Created by xjdkc on 19-3-14.
//

#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    int n,x,ans=0,prev=-1;
    cin>>n;
    for (int i=0;i<n;i++)
    {
        cin>>x;
        if (x!=prev)
            ans++;
        prev=x;
    }
    cout<<ans<<endl;
}