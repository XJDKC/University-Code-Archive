#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m,minstep=0x7fffffff,bsize=0;

void cal(bool visited[][6],bool block[][6],int a[][6],int x,int y,int color)
{
	block[x][y]=visited[x][y]=true;
	bsize++;
	if (x-1>=0&&!block[x-1][y]&&a[x-1][y]==color) cal(visited,block,a,x-1,y,color);
	if (x+1<n&&!block[x+1][y]&&a[x+1][y]==color) cal(visited,block,a,x+1,y,color);
	if (y-1>=0&&!block[x][y-1]&&a[x][y-1]==color) cal(visited,block,a,x,y-1,color);
	if (y+1<m&&!block[x][y+1]&&a[x][y+1]==color) cal(visited,block,a,x,y+1,color);
}

void move(bool block[][6],int a[][6],int b[][6])
{
	bool mark = false;
	int down,left=0;
	for (int j=0;j<m;j++)
	{
		down=n-1;
		mark = false;
		for (int k=n-1;k>=0;k--)
		{
			if (!block[k][j]) mark=(b[down--][left]=a[k][j])||mark?true:false;
		}
		if (mark) left++;
	}
}

void solve(int a[6][6],int step,int num)
{
	if (num==0)
	{
		minstep=min(step,minstep);
	}
	if (step+1>minstep) return ;
	else
	{
		bool visited[6][6]={false},block[6][6]={false};
		int b[6][6] = { 0 };

		for (int j=0;j<m;j++)
		for (int i=n-1;i>=0;i--)
		{
			if (a[i][j]==0) break;
			if (!visited[i][j]&&a[i][j])
			{
				bsize=0;
				memset(block,0,sizeof(block));
				memset(b, 0, sizeof(b));
				cal(visited,block,a,i,j,a[i][j]);
				move(block,a,b);
				solve(b,step+1,num-bsize);
			}
		}
	}
}
int main()
{
	int map[6][6],num=0;
	while (cin>>n>>m)
	{
		minstep=0x7fffffff;
		num = 0;
		memset(map,0,sizeof(map));
		for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
		{
			cin>>map[i][j];
			if (map[i][j]) num++;
		}
		solve(map,0,num);
		cout<<minstep<<endl;
	}
	return 0;
}
