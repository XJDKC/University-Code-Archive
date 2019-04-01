/*
BFS 宽度优先搜索
基本思想:对于一个图 如何遍历整个图的所有节点呢？
		首先从一个节点出发 将该节点加入队列中 并将访问标记置为true 表示已经访问过了 
		然后循环从队列中取出一个元素 将该元素连接的其他节点也加入队列（如果没有访问的话）
		由于队列具有先进先出的特点 先访问的一定是最开始加入队列的节点 也就是初始节点邻接的节点
		初始节点邻接的节点访问完后 那么接下来访问的便是与初始节点邻接的节点的邻接的节点
		可以看到在遍历的过程中 先是将一个节点相邻的节点访问完了 然后才访问其他节点 也就是注重了广度
		而不是循着一条路径 一直往下走 这就是宽度优先搜索
*/
#include<iostream>		
#include<queue>
#include<algorithm>
using namespace std;
const int N=10005;
struct node				//边结构体
{
	int no;				//该边的另一端的节点编号
	int v;				//该边的边权
	node *next;			//指向i节点连接的另一条边
};
node *g[N];				//指针数组 g[i]表示 i节点周围所有边构成的链表表头
int n;					//节点的个数
bool visited[N];		//访问标记数组
queue<int> q;			//声明一个整型队列q 这个在STL中有

void bfs()
{
	int num;							//从队头取出的节点编号
	node *p;							
	while (!q.empty())					//如果队不为空
	{	
		num=q.front();					//那么取出队头节点编号
		q.pop();						//将队头元素出队
		p=g[num];						//得到num节点周围边的链头
		cout<<num<<" ";					//出队表示访问了 所以将访问节点编号输出
		while (p!=NULL)					//如果链表非空 则说明有还有边
		{
			if (!visited[p->no])		//如果这条边另一端的节点没有被访问过
			{
				q.push(p->no);			//将另一端节点入队
				visited[p->no]=true;	//访问标记置为true;
			}
			p=p->next;					//判断下一条边
		}
	}
} 

int main()
{
	int m;
	node *p;
	cin>>n>>m;									//输入节点数 和 边数
	for (int i=0,x,y,z;i<m;i++)					//依次输入每条边的信息
	{
		cin>>x>>y>>z;							//分别表示边的头 尾 边权值 表示一条由x->y的边权为z的有向边
		p=new(node);							//为p分配新的空间
		p->v=z;p->no=y;p->next=g[x];g[x]=p;		//将信息赋值给p  并将p加入g[x]链的链头
	}
	q.push(0);									//将0号节点入队 从0号节点开始对整个图进行搜索
	visited[0]=true;							//访问标记更新
	bfs();										//宽搜
	return 0;
}