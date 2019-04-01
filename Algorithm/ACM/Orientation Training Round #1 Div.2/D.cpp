#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=36;
const int oo=0x7fffffff;
bool visited[N];
int cost[N][N],deadline[N];  
int n,minlen=oo;

void floyd()
{
	for (int k=0;k<n;k++)
	{
		for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
		{
			cost[i][j]=min(cost[i][j],cost[i][k]+cost[k][j]);
		}
	}
}

void dfs(int num,int rest,int curlen,int sum)
{
	if (rest==0)
	{
		minlen=min(minlen,sum);
		return ;
	}
	for (int i = 1; i < n; i++)
	{
		if (!visited[i]&&curlen+cost[num][i]>deadline[i]) return ;
	}
	for (int i=0;i<n;i++)
	{
		if (i==num||sum+cost[num][i]*rest>minlen) continue;
		else if (!visited[i])
		{
			visited[i]=true;
			dfs(i,rest-1,curlen+cost[num][i],sum+cost[num][i]*rest);
			visited[i]=false;
		}
	}
}
int main()
{
	while (cin>>n)
	{
		minlen=oo;
		memset(visited,0,sizeof(visited));
		for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
		{
			cin>>cost[i][j];
		}
		floyd();
		for (int i=1;i<n;i++)
		{
			cin>>deadline[i];
		}
		visited[0]=true;
		dfs(0,n-1,0,0);
		if (minlen==oo)
			cout<<"-1"<<endl;
		else 
			cout<<minlen<<endl;
	}
	return 0;
}