#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
struct node
{
	int w,h;
};
node p0;
queue<node> q;
int map[25][25],ans,w,h;
bool visited[25][25];
void bfs()
{
	node p,*temp;
	
	while (!q.empty())
	{
		p=q.front();
		q.pop();
		if (p.w>1&&map[p.h][p.w-1]>0&&!visited[p.h][p.w-1])
		{
			visited[p.h][p.w-1]=true;ans++;
			temp = new(node);
			*temp = p;
			temp->w--;
			q.push(*temp);
		}
		if (p.w<w&&map[p.h][p.w+1]>0&&!visited[p.h][p.w+1])
		{
			visited[p.h][p.w + 1] = true; ans++;
			temp = new(node);
			*temp = p;
			temp->w++;
			q.push(*temp);
		}
		if (p.h>1&&map[p.h-1][p.w]>0&&!visited[p.h-1][p.w])
		{
			visited[p.h - 1][p.w] = true; ans++;
			temp = new(node);
			*temp = p;
			temp->h--;
			q.push(*temp);
		}
		if (p.h<h&&map[p.h+1][p.w]>0&&!visited[p.h+1][p.w])
		{
			visited[p.h + 1][p.w] = true; ans++;
			temp = new(node);
			*temp = p;
			temp->h++;
			q.push(*temp);
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	char c;
	while (cin>>w>>h&&w&&h)
	{
		for (int i=1;i<=h;i++)
		{
			for (int j=1;j<=w;j++)
			{
				cin>>c;
				switch(c)
				{
					case '.':map[i][j]=1;break;
					case '#':map[i][j]=-1;break;
					case '@':map[i][j]=1,p0.h=i,p0.w=j;break;
					default:break;
				}
			}
		}
		
		q.push(p0);
		ans=1;
		fill(visited[0],visited[0]+25*25,0);
		visited[p0.h][p0.w]=true;
		bfs();
		cout << ans << endl;
	}
	return 0;
}
