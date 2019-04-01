/*T23662
���������±��Ϊ������ż���ĵ㣬���ɶ���ͼ�����������㷨��� 
*/
#include<iostream>
#include<cstring>
using namespace std;
const int N=105;
int g[N][N],g2[N][N],adj[N*N][N],match[N*N],n,m,k=0,ans(0);
int dx[5]={0,-1,1,0,0},dy[5]={0,0,0,-1,1};
bool used[N*N];//ע�����鷶Χ 
void init(){
	cin>>n>>m;
	memset(g2,0,sizeof(g2));
	memset(g,0,sizeof(g));
	memset(adj,0,sizeof(adj));
	memset(match,0,sizeof(match));
	memset(used,0,sizeof(used));
	for (int i=1,x,y;i<=m;i++){
		cin>>x>>y;
		g[x][y]=1;
	}
	for (int i=1,p=0,q=0;i<=n;i++)
		for (int j=1;j<=n;j++){
			if((i+j)%2) g2[i][j]=++p;
			else g2[i][j]=++q;
		}//ͳ���±��Ϊ������ż���ĵ㣬����Ϊ��Ŵ��� 
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if((i+j)%2&&!g[i][j]){//������������ͳ�ƣ�ע�ⲻ��ͳ�Ʊ�ɾ���ĵ㣡 
				k++;
				for (int d=1;d<=4;d++)
					if(i+dx[d]>=1&&i+dx[d]<=n
					&&j+dy[d]<=n&&j+dy[d]>=1){
						if(!g[i+dx[d]][j+dy[d]])//�����߽磬����ɾ�� 
						adj[k][++adj[k][0]]=g2[i+dx[d]][j+dy[d]];
					}//��������ͼ		 
			}
}
bool cross(int x){
	if(!x) return false;
	for (int i=1;i<=adj[x][0];i++){
		int j=adj[x][i];
		if(!used[j]){
			used[j]=true;
			if(!match[j]||cross(match[j])){
				match[j]=x;
				return true;
			}
		}
	}
	return false;
}
void solve(){
	ans=0;
	for (int i=1;i<=k;i++){
		if(cross(i)) ans++;
		memset(used,0,sizeof(used));
	}
}//�������㷨 
int main(){
	ios::sync_with_stdio(false);
	init();
	solve();
	cout<<ans<<endl;
	return 0;
}
