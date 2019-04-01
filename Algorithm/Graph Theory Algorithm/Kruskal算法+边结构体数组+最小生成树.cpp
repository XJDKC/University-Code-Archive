#include<iostream>
#include<algorithm>
using namespace std;
const int N=10005;
struct edge
{
	int head;
	int tail;
	int v;
};
int n,m,ans=0,f[N];
edge g[N];

bool comp(struct edge &x,struct edge &y)
{
	return (x.v<y.v);
}

int find(int no)
{
	int p=no,q;
	while (p!=f[p]) p=f[p];
	while (no!=f[no])
	{
		q=f[no];
		f[no]=p;
		no=q;
	}
	return p;
}

void solve(int no)
{
	int f1,f2;
	f1=find(g[no].head);
	f2=find(g[no].tail);
	if (f1!=f2)
	{
		f[f2]=f1;
		ans+=g[no].v;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for (int i=0;i<m;i++)
	{
		cin>>g[i].head>>g[i].tail>>g[i].v;
	}
	sort(g,g+m,comp);
	for (int i=0;i<n;i++)	f[i]=i;
	for (int i=0;i<m;i++) solve(i);
	cout<<ans<<endl;
	return 0;
}