//
// Created by xjdkc on 19-3-14.
//

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 100006;
const int M = 10006;

struct Tree
{
    vector<int> no;
}tree[N+M];

int depth[N+M],step[N+M];

void cal(int no,int &d,int &maxstep)
{
    int childno,maxdepth1=0,maxdepth2=0;
    for (int i=0;i<tree[no].no.size();i++)
    {
        childno=tree[no].no[i];
        cal(childno,depth[childno],step[childno]);
        if (depth[childno]>maxdepth2)
        {
            if (depth[childno]>maxdepth1)
            {
                maxdepth2=maxdepth1;
                maxdepth1=depth[childno];
            }
            else
                maxdepth2=depth[childno];
        }
        maxstep=max(maxstep,step[childno]);
    }
    maxstep=max(maxstep,maxdepth1+maxdepth2);
    d=max(maxdepth1,maxdepth2)+1;
}

int main()
{
    int n,m,no;
    cin>>n>>m;
    for (int i=2;i<=n;i++)
    {
        cin>>no;
        tree[no].no.push_back(i);
    }
    for (int i=1;i<=m;i++)
    {
        cin>>no;
        tree[no].no.push_back(i+n);
    }
    cal(1,depth[1],step[1]);
    cout<<step[1]<<endl;
    return 0;
}