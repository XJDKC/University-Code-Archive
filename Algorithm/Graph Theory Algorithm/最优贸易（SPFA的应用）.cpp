/* 
��http://ylzx.acmclub.com/index.php?app=problem_title&id=197&problem_id=3655
������
��1��i���һ·�϶�������ֻ���¼һ·����С������۸񼴿�
ͬ����i��nһ·�϶���������ֻ���¼һ·�����������۸�
��������ͼ��һ����1��i�����ڸ���i����С����۸񣩣�
��һ����n����ȥi (���ڸ���i����������۸�)����SPFA��� 
�����һ�������۸�������۸������ֵ���� 
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
int buy[N],sell[N],a[N],n,ans(0);//buy��ʾ��i���һ·�ϵ���С����۸�
//sell��ʾ��i��nһ·����������۸� 
node *g[N],*h[N];//����ͼ��gͼ��ʾ��1ȥ��i��hͼ��ʾn����Դ�i�ߵ� 
bool f[N];
void solve1(){}//SPFA�㷨
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
			int v=min(buy[k],a[p->adj]);//�õ�ǰ��С����۸��뵱������۸�Ľ�Сֵ���� 
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
	}//��ͼ 
	for (int i=1;i<=n;i++) buy[i]=oo;
	for (int i=1;i<=n;i++) sell[i]=0;//��ʼ�� 
	solve();
	cout<<ans<<endl;
	return 0;
}
