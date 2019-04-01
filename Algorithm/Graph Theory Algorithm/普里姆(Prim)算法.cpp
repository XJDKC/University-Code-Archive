#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=5005;
int n,g[N][N],c[N],ans(0);//c[i]��ʾ����ͨ�Ķ����鵽i�����̾��� 
int minv(){
	int min=0x7fffffff,k;
	for (int i=0;i<n;i++){
		if(c[i]&&c[i]<min)
			min=c[i],k=i;
	}
	return k;
}//��̾���������һ����� 
void solve(){
	int v;
	for (int i=1;i<n;i++){
		v=minv();
		ans+=c[v];
		c[v]=0;//���������Ϊ0 
		for (int j=0;j<n;j++)
			if(c[j]&&g[v][j]<c[j])
				c[j]=g[v][j];//����c���� 
	}
}
int main(){
	ios::sync_with_stdio(false);
	int m;
	cin>>n>>m;
	memset(g,0x7f,sizeof(g));
	for (int i=0;i<n;i++) g[i][i]=0;
	for (int i=0;i<m;i++){
		int x,y,v;
		cin>>x>>y>>v;
		g[x][y]=g[y][x]=v;
	}
	for (int i=0;i<n;i++) c[i]=g[0][i];
	solve();
	cout<<ans<<endl;
	return 0;
}
