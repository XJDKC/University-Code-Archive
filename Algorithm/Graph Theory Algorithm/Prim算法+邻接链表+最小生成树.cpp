#include<iostream>
#include<algorithm>
using namespace std;
const int N=10005;
const int oo=0x7fffffff;
struct node
{
	int no;
	int v;
	node *next;
};
node *g[N];
int n,dis[N],ans=0;

int minv()
{
	int v,min_v=oo;
	for (int i=0;i<n;i++)
	{
		if (dis[i]>0&&dis[i]<min_v)
		{
			min_v=dis[i];
			v=i;
		}
	}
	return v;
}

node *find(int x,int y)
{
	node *p;
	for (p=g[x];p!=NULL;p=p->next)
	{
		if (p->no==y)
		{
			break;
		}
	}
	return p;
}

void Prim()
{
	int v;
	node *p;
	dis[0]=0;
	for (int i=1;i<n;i++)
	{
		p=find(i,0);
		if (p)
		{
			dis[i]=p->v;
		}
		else 
		{
			dis[i]=oo;
		}
	}

	for (int i=1;i<n;i++)
	{
		v=minv();
		ans+=dis[v];
		dis[v]=0;
		for (int j=1;j<n;j++)
		{
			if (dis[j])
			{
				p=find(j,v);
				if (p&&dis[j]>p->v)
				{
					dis[j]=p->v;
				}
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	int m;
	node *p;
	cin>>n>>m;
	for (int i=0,x,y,z;i<m;i++)
	{
		cin>>x>>y>>z;
		p=new(node);
		p->no=y;p->v=z;p->next=g[x];g[x]=p;
		p=new(node);
		p->no=x;p->v=z;p->next=g[y];g[y]=p;
	}
	Prim();
	cout<<ans<<endl;
	return 0;
}