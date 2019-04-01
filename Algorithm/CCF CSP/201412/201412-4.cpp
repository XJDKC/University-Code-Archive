//
// Created by xjdkc on 19-3-14.
//

#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1005;
const int M = 100006;

struct Edge
{
    int head,tail,value;
    bool operator < (const Edge &b)const {
        return value<b.value;
    }
}edge[M];

int ans;
int f[N];

int findRoot(int no)
{
    int r=no,k;
    while (f[r]!=r) r=f[r];
    while (no!=f[no])
    {
        k=f[no];
        f[no]=r;
        no=k;
    }
    return r;
}

void solve(int no)
{
    int hRoot,tRoot;
    hRoot=findRoot(edge[no].head);
    tRoot=findRoot(edge[no].tail);
    if (hRoot!=tRoot)
    {
        f[tRoot]=hRoot;             //需要将祖先连接起来
        ans+=edge[no].value;
    }

}

int main()
{
    int n,m;
    cin>>n>>m;
    for (int i=0;i<m;i++)
        cin>>edge[i].head>>edge[i].tail>>edge[i].value;

    sort(edge,edge+m);

    for (int i=1;i<=n;i++)
        f[i]=i;

    for (int i=0;i<m;i++)
        solve(i);
    cout<<ans<<endl;
    return 0;
}