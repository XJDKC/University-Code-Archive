/*
��֪��������,��t�ŵ㵽��������·�� 
��:
����:
5 7 
0 1 10
0 3 30
0 4 100
1 2 50
2 4 10
3 2 20
3 4 60
���:
0 10 50 30 60
*/
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=5005,oo=0x7fffffff;
int g[N][N],dis[N],n,ans(0),t;
bool f[N]={false};
int minv(){
	int k,min=oo;
	for (int i=0;i<n;i++){
		if(!f[i]&&dis[i]<min)
		min=dis[i],k=i;
	}
	return k;
}
void solve(){
	int v;
	for (int i=1;i<n;i++){
		v=minv();//�ҳ���t������ĵ� 
		for (int j=0;j<n;j++)
			if (!f[j]&&g[v][j]!=oo&&dis[v]!=oo&&dis[j]>dis[v]+g[v][j])//��������δ���ʵĵ� 
				dis[j]=dis[v]+g[v][j];
		f[v]=true;//���ʱ�� 
	}
}
int main(){
	int m;
	cin>>n>>m;
	for (int i=0;i<n;i++) 
		for (int j=0;j<n;j++) 
			g[i][j]=oo;
	for (int i=0;i<n;i++) g[i][i]=0;
	for (int i=0;i<m;i++) {
		int x,y,v;
		cin>>x>>y>>v;
		g[x][y]=v;
	}
	while(cin>>t){
		for (int i=0;i<n;i++) dis[i]=g[t][i];//t�㵽���������̾��� 
		for (int i=0;i<n;i++) f[i]=false;
		f[t]=true;
		solve();
		for (int i=0;i<n;i++){
			if(dis[i]==oo) cout<<"�� " ;
			else cout<<dis[i]<<" ";
		} 
		cout<<endl;	
	}
	
	return 0;
}
