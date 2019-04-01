/* 
见http://ylzx.acmclub.com/index.php?app=problem_title&id=197&problem_id=3655
解析：
从1到i点的一路上都可以买，只需记录一路上最小的买入价格即可
同理，从i到n一路上都可以卖，只需记录一路上最大的卖出价格
构建两个图，一个从1到i（用于更新i点最小买入价格），
另一个从n逆向去i (用于更新i点最大卖出价格)，用SPFA求解 
最后找一个卖出价格与买入价格的最大差值即可 
*/
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
queue<int> q1,q2;
struct node{
	int adj;
	node *next;
};
const int N=100005,oo=0x7fffffff;
int buy[N],sell[N],a[N],n,ans(0);//buy表示到i点的一路上的最小买入价格
//sell表示从i到n一路上最大卖出价格 
node *g[N],*h[N];//两个图，g图表示从1去到i，h图表示n点可以从i走到 
bool f[N];
void solve1(){}//SPFA算法
	node *p;
	q1.push(1);
	f[1]=true;
	buy[1]=a[1];
	while(!q1.empty()){
		int k=q1.front();
		q1.pop();
		f[k]=false;
		p=g[k];
		while(p){
			int v=min(buy[k],a[p->adj]);//用当前最小买入价格与当地买入价格的较小值更新 
			if(buy[p->adj]>v){
				buy[p->adj]=v;
				if(!f[p->adj]){
					q1.push(p->adj);
					f[p->adj]=true;
				}
			}
			p=p->next;
	}
	}	
}
void solve2(){
	node *p;
	sell[n]=a[n];
	q2.push(n);
	f[n]=true;
	while(!q2.empty()){
		int k=q2.front();
		q2.pop();
		f[k]=false;
		p=h[k];
		while(p){
			int v=max(sell[k],a[p->adj]);
			if(sell[p->adj]<v){
				sell[p->adj]=v;
				if(!f[p->adj]){
					q2.push(p->adj);
					f[p->adj]=true;
				}	
			}
			p=p->next;
		}
	}
}
void solve(){
	for (int i=1;i<=n;i++) f[i]=false;
	solve1();
	for (int i=1;i<=n;i++) f[i]=false;
	solve2();
	for (int i=1;i<=n;i++) 
		if(sell[i]-buy[i]>ans) ans=sell[i]-buy[i];
}
int main(){
	ios::sync_with_stdio(false);
	int m;
	cin>>n>>m;
	for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=1,x,y,z;i<=m;i++){
		node *p;
		cin>>x>>y>>z;
		if(z==1){
			p=new(node);p->adj=y;p->next=g[x];g[x]=p;
			p=new(node);p->adj=x;p->next=h[y];h[y]=p;
		}
		if(z==2){
			p=new(node);p->adj=y;p->next=g[x];g[x]=p;
			p=new(node);p->adj=x;p->next=h[y];h[y]=p;
			p=new(node);p->adj=x;p->next=g[y];g[y]=p;
			p=new(node);p->adj=y;p->next=h[x];h[x]=p;
		}
	}//建图 
	for (int i=1;i<=n;i++) buy[i]=oo;
	for (int i=1;i<=n;i++) sell[i]=0;//初始化 
	solve();
	cout<<ans<<endl;
	return 0;
}
