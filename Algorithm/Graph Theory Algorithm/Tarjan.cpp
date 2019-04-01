#include<iostream>
#include<algorithm>
using namespace std;
const int N = 10005;
struct node
{
    int v;              //有向边另一端点的编号
    //int w;              //有向边的权值
    struct node *next;  //当前链表下一条有向边
};
node *map[N];
int num;
int DFN[N],LOW[N],stack[N];
bool visited[N],instack[N];
void tarjan(int u)
{
    stack[++stack[0]] = u;
    visited[u] = instack[u] = true;
    DFN[u] = LOW[u] = ++num;
    for (node *p = map[u]; p != NULL;p=p->next)
    {
        if (!visited[p->v])
        {
            tarjan(p->v);
            LOW[u] = min(LOW[u], LOW[p->v]);
        }
        else if (instack[p->v])
            LOW[u] = min(LOW[u], LOW[p->v]);
    }
    if (LOW[u]==DFN[u])
    {
        do
        {
            cout << stack[stack[0]] << " ";
            instack[stack[stack[0]]] = false;
            stack[0]--;
        }while (stack[stack[0]+1]!=u);
        cout << endl;
    }
}
int main()
{
    node *p;
    int n, m;
    cin >> n >> m;
    for (int i = 0,x,y; i < m;i++)
    {
        cin >> x >> y;
        p = new node;
        p->v = y;
        p->next = map[x];
        map[x] = p;
    }
    tarjan(1);
    return 0;
}
/*
6 8
1 2
1 3
2 4
3 4
3 5
4 1
4 6
5 6
*/