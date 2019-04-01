#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
int visited[200005]={0};
int inq[200005],head,tail;
int N,K;
int bfs()
{
    int cur;
    while (head<=tail)
    {
        cur=inq[head];
        if (cur==K) break;
        if (cur<K)
        {
            if (!visited[cur+1]) 
            {
                visited[cur+1]=visited[cur]+1;
                inq[++tail]=cur+1;
            }
            if (cur-1>=0&&!visited[cur-1])
            {
                visited[cur-1]=visited[cur]+1;
                inq[++tail]=cur-1;
            }
            if(!visited[2*cur])
            {
                visited[2*cur]=visited[cur]+1;
                inq[++tail]=cur*2;
            }
        }
        else 
        {
            if (!visited[cur-1])
            {
                visited[cur-1]=visited[cur]+1;
                inq[++tail]=cur-1;
            }
        }
        head++;
    }
    return visited[K];
} 
int main()
{
    cin>>N>>K;
    if (N>=K) printf("%d\n",N-K);
    else 
    {
        head=tail=0;
        inq[0]=N;
        printf("%d\n",bfs());
    }
    return 0;
}