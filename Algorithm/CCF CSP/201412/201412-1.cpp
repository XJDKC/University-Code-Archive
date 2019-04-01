//
// Created by xjdkc on 19-3-14.
//

#include <iostream>
using namespace std;
const int N = 1006;

int f[N];

int main()
{
    int n,x;
    cin>>n;
    for (int i=0;i<n;i++)
    {
        cin>>x;
        ++f[x];
        cout<<f[x];
        if (i<n-1)
            cout<<" ";
        else
            cout<<endl;
    }
    return 0;
}