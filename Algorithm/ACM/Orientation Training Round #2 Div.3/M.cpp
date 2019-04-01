#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cmath>
using namespace std;
struct node
{
    int s,a,b;
    int step;
}myq[10005];
bool visited[101][101][101];
int S,A,B,start[3],head,tail;
bool pour(int p[],int q[],int i,int j)
{
    int mark=true;
    if (!p[i]||p[j]==start[j]) return false;
    q[j]=p[j]+min(start[j]-p[j],p[i]);
    q[i]=p[i]-min(start[j]-p[j],p[i]);
    for (int k=0;k<3;k++)
    {
        if (k!=i&&k!=j)
        {
            q[k]=p[k];
        }
    }
    if (visited[q[0]][q[1]][q[2]]) return false;
    return true;
}
int bfs()
{
    bool mark=false;
    int p[3],q[3];
    head=tail=0;
    myq[0].s=S;
    myq[0].a=0;
    myq[0].b=0;
    myq[0].step=0; 
    visited[S][0][0]=true;
    while (head<=tail)
    {
        p[0]=myq[head].s;
        p[1]=myq[head].a;
        p[2]=myq[head].b;  
        for (int i=0,num=0;i<3;i++)
        {
            if (p[i]==S/2) num++;
            if (num==2) mark=true;
        }
        if (mark) break;
        for (int i=0;i<3;i++)
        {
            for (int j=0;j<3;j++)
            {
                if (i!=j)
                {
                    if (pour(p,q,i,j))
                    {
                        myq[++tail].s=q[0];
                        myq[tail].a=q[1];
                        myq[tail].b=q[2];
                        myq[tail].step=myq[head].step+1;
                        visited[q[0]][q[1]][q[2]]=true;
                    }
                }
            }
        }
        head++;
    }
    return mark;
}
int main()
{
    while (scanf("%d%d%d",&S,&A,&B)&&S)
    {
        if (S%2||(max(A,B)<S/2))
        { 
            printf("NO\n");
            continue;
        }
        start[0]=S;
        start[1]=A;
        start[2]=B;
        memset(visited,0,sizeof(visited));        
        if (bfs()) printf("%d\n",myq[head].step);
        else printf("NO\n");
    }
    return 0;
}