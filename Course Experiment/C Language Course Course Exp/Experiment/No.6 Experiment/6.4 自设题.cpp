/*我们用数组d记录每个结点的最短路径估计值，而且用邻接表来存储图G。
我们采取的方法是动态逼近法：设立一个先进先出的队列用来保存待优
化的结点，优化时每次取出队首结点u，并且用u点
当前的最短路径估计值对离开u点所指向的结点v进行松弛操作，
如果v点的最短路径估计值有所调整，且v点不在当前的队列中，就将v点放入队尾。
这样不断从队列中取出结点来进行松弛操作，直至队列空为止。
定理: 只要最短路径存在，上述SPFA算法必定能求出最小值。*/
#include<iostream>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
struct node{
	int a,v;
	node *next;
};
const int N=100005,oo=0x7fffffff;
queue<int> q;
node *g[N]; 
int n,m,s,dis[N];
bool inq[N];
void solve(){
	dis[s]=0;
	q.push(s);
	inq[s]=true;
	while(!q.empty()){
		int k=q.front();
		q.pop();
		inq[k]=false;
		node *p=g[k];
		while(p){
			if(dis[p->a]>dis[k]+p->v){
				dis[p->a]=dis[k]+p->v;
				if(!inq[p->a]){
					q.push(p->a);
					inq[p->a]=true;
				}
			}
			p=p->next;
		}
	}
}
int main(){
	cin>>n>>m;
	node *p;
	for (int i=0,x,y,z;i<m;i++){
		cin>>x>>y>>z;
		p=new(node);p->a=y;p->v=z;p->next=g[x];g[x]=p;
	}
	while(cin>>s){
		fill(inq,inq+n,0);
		fill(dis,dis+n,oo);
		solve();
		for (int i=0;i<n;i++){
			if(dis[i]==oo) cout<<"∞ " ;
			else cout<<dis[i]<<" ";
		} 
		cout<<endl;
	}
	return 0;
}
