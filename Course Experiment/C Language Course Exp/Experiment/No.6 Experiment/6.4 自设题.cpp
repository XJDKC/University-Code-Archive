/*����������d��¼ÿ���������·������ֵ���������ڽӱ����洢ͼG��
���ǲ�ȡ�ķ����Ƕ�̬�ƽ���������һ���Ƚ��ȳ��Ķ��������������
���Ľ�㣬�Ż�ʱÿ��ȡ�����׽��u��������u��
��ǰ�����·������ֵ���뿪u����ָ��Ľ��v�����ɳڲ�����
���v������·������ֵ������������v�㲻�ڵ�ǰ�Ķ����У��ͽ�v������β��
�������ϴӶ�����ȡ������������ɳڲ�����ֱ�����п�Ϊֹ��
����: ֻҪ���·�����ڣ�����SPFA�㷨�ض��������Сֵ��*/
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
			if(dis[i]==oo) cout<<"�� " ;
			else cout<<dis[i]<<" ";
		} 
		cout<<endl;
	}
	return 0;
}
