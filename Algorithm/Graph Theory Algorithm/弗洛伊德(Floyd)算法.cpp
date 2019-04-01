/*
三重循环 
*/
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=303,oo=0x7fffffff;
int n,m,dis[N][N]={0};
void init(){
	memset(dis,0,sizeof(dis));
	scanf("%d%d",&n,&m);
	for (int i=0,x,y,z;i<m;i++){
		scanf("%d%d%d",&x,&y,&z);
		dis[x][y]=z;
	}
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			if(dis[i][j]==0) dis[i][j]=oo;
	for (int i=0;i<n;i++)
		dis[i][i]=0;
}
void floyd(){
	for (int k=0;k<n;k++)
		for (int i=0;i<n;i++)
			for (int j=0;j<n;j++)
				if(dis[i][k]!=oo&&dis[k][j]!=oo)
				dis[i][j]=min(dis[i][k]+dis[k][j],dis[i][j]);
}//*外层循环k表示中转点,枚举一个中转点的所有情况* 
void output(){
	printf("     ");
	for (int i=0;i<n;i++) printf("%5d",i);
	printf("\n");
	for (int i=0;i<n;i++){
		printf("%5d",i);
		for (int j=0;j<n;j++)
			if(dis[i][j]==oo) printf("%5s","∞");
			else printf("%5d",dis[i][j]);
		printf("\n");
	}		
}
int main(){
	init();
	floyd();
	output();
	return 0;
}
