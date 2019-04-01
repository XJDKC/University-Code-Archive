#include<iostream>
#include<algorithm>
using namespace std;
const int N=1005;
struct node
{
	int no;
	node *next;
};
node *g[N];
int n,m;
bool visited[N],mark;

bool find(node *head,int no)
{
	node *p;
	p=head;
	while (p)
	{
		if (p->no==no)
		{
			return true;
		}
		p=p->next;
	}
	return false;
}

void dfs(int no,int head)
{
	node *p;
	p=g[no];
	while (p)
	{
		if (!visited[p->no])
		{
			visited[p->no]=true;
			dfs(p->no,head);
		}
		else if (visited[p->no]==true&&p->no==head)
		{
			mark=true;
		}
		if (mark==true) return ;
		p=p->next;
	}
}

int main()
{
	node *p;
	cin>>n>>m;
	for (int i=0,x,y;i<m;i++)
	{
		cin>>x>>y;
		if (!find(g[x],y))
		{
			p=new(node);
			p->no=y;p->next=g[x];g[x]=p;
		}
	}
	for (int i=1;i<=n;i++)
	{
		if (g[i]==NULL) cout<<"F"<<endl;
		else 
		{
			fill(visited+1,visited+n+1,0);
			mark=false;
			visited[i]=true;
			dfs(i,i);
			if (mark)
			{
				cout<<"T"<<endl;
			}
			else 
			{
				cout<<"F"<<endl;
			}
		}

	}
	return 0;
}