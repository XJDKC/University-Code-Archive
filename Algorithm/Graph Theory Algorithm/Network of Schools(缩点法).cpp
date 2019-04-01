/*
题目见:http://ylzx.acmclub.com/index.php?app=problem_title&id=197&problem_id=10297 
缩点法:用tarjan算法将强连通分量求出后,将每个强连通分量当做一个单独的点
再对每条边进行考察:若边的两个端点a->b不在同一个强连通分量内,
则这两个强连通分量之间有一条边,方向g[a].belong->g[b].belong 
*/
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<stack>
using namespace std;
struct edge{
	int adj;
	edge *next;
};
struct node{
	int dfn,low,belong;
	edge *head;
};
const int N=105;
stack<int> s;
int n,x,sumn,idx,ans1,ans2;
bool instack[N],init[N],outit[N];
node g[N];
void tarjan(int u){
	int v;edge *p;
	g[u].dfn=g[u].low=++idx;
	s.push(u);
	instack[u]=true;
	p=g[u].head;
	while(p){
		v=p->adj;
		if(!g[v].dfn){
			tarjan(v);
			g[u].low=min(g[v].low,g[u].low);
		}else if(instack[v]) g[u].low=min(g[u].low,g[v].dfn);
		p=p->next;
	}
	if(g[u].dfn==g[u].low){
		sumn++;
		do{
			v=s.top();
			s.pop();
			instack[v]=false;
			g[v].belong=sumn;
		}while(v!=u);
	}
}
void solve(){
	idx=0;sumn=0;
	memset(instack,false,sizeof(instack));
	memset(init,false,sizeof(init));
	memset(outit,false,sizeof(outit));	
	while(!s.empty()) s.pop();
	for (int i=1;i<=n;i++) if(!g[i].dfn) tarjan(i);
	edge *p;int v;
	for (int i=1;i<=n;i++){
		p=g[i].head;
		while(p){
			v=p->adj;
			if(g[i].belong!=g[v].belong){
				init[g[v].belong]=true;
				outit[g[i].belong]=true;
			}
			p=p->next;
		}
	}//缩点法
	ans1=0;ans2=0;
	for (int i=1;i<=sumn;i++){
		if(!init[i]) ans1++;
		if(!outit[i]) ans2++;
	}
	ans2=max(ans1,ans2);
	if(sumn==1) ans2=0;
	if(ans1==0) ans1=1;
}
int main(){
	scanf("%d",&n);
	memset(g,0,sizeof(g));
	edge *p;
	for (int i=1;i<=n;i++)
		while(scanf("%d",&x)){
			if(!x) break;
			p=new(edge);
			p->adj=x;
			p->next=g[i].head;
			g[i].head=p;
		}
	solve();
	printf("%d\n%d\n",ans1,ans2);
	return 0;
}
