#include<iostream>
#include<algorithm>
using namespace std;
const int N=30005;
int f[N],ans(0);				//f表示x的父节点编号
struct edge{
	int head,tail,v;
};
edge a[N];						//由于只关注边 对于边来存储整个图
int find(int x){
	int r=x,k;
	while(r!=f[r]) r=f[r];		//循环找到x节点的祖先 
	while(x!=f[x]){				//如果要寻找节点的祖先不等于自己	说明x节点需要经过一个 回溯 找父亲的过程来知道自己的祖先的编号
		k=f[x];					//那么将上一层节点的编号记录下来
		f[x]=r;					//直接将祖先的编号赋值为x的父节点 这样之后找祖先就不用循环找了 
		x=k;
	}
	return r;					//返回找到的祖先编号
}
bool comp(const edge &x,const edge &y){
	return x.v<y.v;				//比较函数 根据边权比较
}
void solve(int i){
	int k1,k2;
	k1=find(a[i].head);			//寻找要加入边的头节点祖先
	k2=find(a[i].tail);			//寻找要加入边的尾节点祖先 
	if (k1!=k2){				//如果两个祖先相同说明构成环 不同则说明是可以加入的边
		f[k2]=k1;				//那么将该节点的父节点置为 k1
		ans+=a[i].v;			//将该边的边权加入 最终计算结果
	}
}
int main(){
	ios::sync_with_stdio(false);
	int n,m;
	cin>>m>>n;
	for (int i=1;i<=n;i++)
		cin>>a[i].head>>a[i].tail>>a[i].v;
	for (int i=0;i<m;i++) f[i]=i;
	sort(a+1,a+n+1,comp);
	for (int i=1;i<=n;i++) solve(i);
	cout<<ans<<endl;
	return 0;
}
/*
7 9
0 1 28
0 5 10
1 2 16
1 6 14 
3 6 18
2 3 12
4 6 24
3 4 22
4 5 25

99
*/
