//
// Created by xjdkc on 19-3-14.
//

#include <iostream>
#include <algorithm>
#include <string>
#include <stack>
using namespace std;
const int N = 10006;
struct Edge
{
    int tail;
    struct Edge *next;
};

int idx,sc_num;
int LOW[N],DFN[N],num[N];
stack<int> s;
Edge *edge[N];
bool instack[N];

void tarjan(int no)
{
    LOW[no]=DFN[no]=++idx;
    s.push(no);
    instack[no]=true;
    for (Edge *p=edge[no];p!=NULL;p=p->next)
    {
        if (!DFN[p->tail])          //如果还没有访问过 就访问该点
        {
            tarjan(p->tail);
            LOW[no]=min(LOW[no],LOW[p->tail]);
        }
        else if (instack[p->tail])  //如果访问过 并且还在栈中 说明 构成回路 那么回路上所有点均属于一个联通子图
        {
            LOW[no]=min(LOW[no],DFN[p->tail]);  //更新为较小的那个
        }
    }
    int temp;
    if (DFN[no]==LOW[no])           //如果发现当前节点时间戳和祖先相等 说明为一个联通子图的祖先
    {
        sc_num++;                   //联通子图数+1
        do{
            temp=s.top();           //退栈直到当前节点退栈 退出所有元素均为以当前节点为祖先的联通子图
            s.pop();
            num[sc_num]++;
            instack[temp]=false;
        }while (no!=temp);
    }
}

int main()
{
    Edge *p;
    int ans=0;
    int n,m,head,tail;
    cin>>n>>m;
    for (int i=0;i<m;i++)
    {
        cin>>head>>tail;
        p = new Edge;
        p->tail=tail;
        p->next=edge[head];
        edge[head]=p;
    }
    for (int i=1;i<=n;i++)
        if (!DFN[i])
            tarjan(i);
    for (int i=1;i<=sc_num;i++)
    {
        ans+=num[i]*(num[i]-1)/2;
    }
    cout<<ans<<endl;
    return 0;
}