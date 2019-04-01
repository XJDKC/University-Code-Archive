//
// Created by xjdkc on 19-3-14.
//

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 10006;
const int M = 100006;

struct Edge
{
    bool visited;
    int tail;
    Edge *next;
};

int n,m,num;
Edge *edge[N],*f[M];
int du[N],visited[N];
vector<int> ans;

void setVisited(int head,int tail)
{
    Edge *p=edge[head];
    while (p)
    {
        if (p->tail==tail)
        {
            p->visited=true;
            break;
        }
        p=p->next;
    }

}

void travel(int no)
{
    Edge *p;
    if (!visited[no])
    {
        visited[no]=true;
        num++;
    }
    ans.push_back(no);
    for (p=edge[no];p!=NULL;p=p->next)
    {
        if (p->visited==false)
        {
            p->visited=true;
            if (!visited[p->tail])
            {
                visited[p->tail]=true;
                num++;
            }
            setVisited(p->tail,no);
            travel(p->tail);
            break;
        }
    }
}

void insertEdge(Edge *p,int no)
{
    Edge *pcur=edge[no],*pprev=NULL;
    while (pcur)
    {
        if (p->tail<=pcur->tail)
        {
            if (pprev==NULL||pprev->tail<p->tail)
            {
                p->next=pcur;
                if (pprev)
                    pprev->next=p;
                else
                    edge[no]=p;
                break;
            }
        }
        pprev=pcur;
        pcur=pcur->next;
    }
    if (pcur==NULL)
    {
        if (pprev!=NULL)
            pprev->next=p;
        else
        {
            p->next=NULL;
            edge[no]=p;
        }
    }
}

int main()
{
    Edge *p;
    bool flag=true;
    int x,y;
    cin>>n>>m;
    for (int i=0;i<m;i++)
    {
        cin>>x>>y;
        p=new Edge;p->tail=y;insertEdge(p,x);
        p=new Edge;p->tail=x;insertEdge(p,y);
        du[x]++;
        du[y]++;
    }
    for (int i=1,num=0;i<=n;i++)
    {
        if (du[i]%2)
            num++;
        if (num>2||du[i]==0)
        {
            flag=false;
            break;
        }
    }
    if (num==2&&du[1]%2==0)
        flag=false;
    if (flag)
    {
        travel(1);
        if (num<n)
            cout<<-1<<endl;
        else
        {
            cout<<1;
            for (int i=1;i<ans.size();i++)
                cout<<" "<<ans[i];
            cout<<endl;
        }
    }
    else
        cout<<-1<<endl;
    return 0;

}

