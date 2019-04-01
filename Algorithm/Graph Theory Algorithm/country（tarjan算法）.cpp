/*详细过程见：
http://baike.baidu.com/view/6156928.htm?fr=aladdin
*/
#include<iostream>
#include<cstring>
#include<stack>
#include<algorithm>
using namespace std;
const int N(100008);
struct edgeT{
    int adj;
    struct edgeT *next;
};
struct node{
    int dfn,low,belong;
    struct edgeT *head;
};
int n,m,scc_n,idx,country[N]; //scc_n:强连通分量个数 idx:时间戳 country[]:国家人数 
node g[N];
bool instack[N];
stack<int> s;
void tarjan(int u)
{
    int v;
    g[u].dfn=g[u].low=++idx;
    s.push(u);
    instack[u]=true;
    edgeT *p;
    p=g[u].head;
    while (p)
    {
        v=p->adj;
        if (!g[v].dfn)
        {
            tarjan(v);
            g[u].low=min(g[u].low,g[v].low);//树枝边用Low来比较 
        }else if (instack[v]) g[u].low=min(g[u].low,g[v].dfn);//注意，横叉边用时间戳来比较 
        p=p->next;
    }
    if (g[u].dfn==g[u].low)
    {
        scc_n++;
        do{
            v=s.top();
            g[v].belong=scc_n;
            s.pop();
            country[scc_n]++;
            instack[v]=false;
        }while (v!=u);
    }
}         

int main()
{  
    int x,y;
    edgeT *p;
    std::ios::sync_with_stdio(false);
    while (cin>>n>>m)
    {
        memset(g,0,(n+1)*sizeof(node));
        for (int i=1;i<=m;i++)
        {
            cin>>x>>y;
            p=new edgeT;
            p->adj=y;
            p->next=g[x].head;
            g[x].head=p;
        }
        scc_n=idx=0; 
        memset(country,0,(n+1)*sizeof(int));
        memset(instack,0,(n+1)*sizeof(bool));
        for (int i=1;i<=n;i++)
            if (!g[i].dfn) tarjan(i);
        sort(country+1,country+scc_n+1);
        for (int i=1;i<=scc_n;i++) cout<<country[i]<<" ";
        cout<<endl;
    }
    
    return 0;
}
