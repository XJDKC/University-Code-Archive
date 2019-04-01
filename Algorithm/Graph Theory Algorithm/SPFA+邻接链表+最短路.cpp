#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
const int N=10005;
const int oo=0x7fffffff;
struct node
{
	int no;
	int v;
	node *next;
};
int n,m,dis[N];
bool inq[N];
node *g[N];
queue<int> q;


void SPFA()//shotest path fast algorithm
{
	int k;
	node *link;
	while (!q.empty()) 
	{
		k=q.front();
		q.pop();
		inq[k]=false;
		link=g[k];
		while (link)
		{
			if (link->v+dis[k]<dis[link->no])
			{
				dis[link->no]=link->v+dis[k];
				if (!inq[link->no])	
				{
					q.push(link->no);
					inq[link->no]=true;
				}
			}
			link=link->next;
		}
	}

} 

int main()
{
	int s;
	node *p;
	cin>>n>>m;
	for (int i=0,x,y,z;i<m;i++)
	{
		cin>>x>>y>>z;
		p=new(node);
		p->v=z;p->no=y;p->next=g[x];g[x]=p;
	}
	while (cin>>s)
	{
		fill(inq,inq+n,0);
		fill(dis,dis+n,oo);
		dis[s]=0;
		q.push(s);
		inq[s]=true;
		SPFA();
		for (int i=0;i<n;i++)
		{
			if (dis[i]==oo) cout<<"∞ ";
			else cout<<dis[i]<<" ";
		}
	}
}