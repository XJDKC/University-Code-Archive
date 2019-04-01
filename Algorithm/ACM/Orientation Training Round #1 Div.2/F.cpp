#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int N = 20;
int n,m,bsize=0,score;
int xx,yy;
int map[N][N];

void cal(int block[][N],int x,int y,int color,int no)
{
	block[x][y]=no;
	bsize++;
	if (x<xx||(x==xx)&&y<yy) xx=x,yy=y;
	if (x-1>=0&&!block[x-1][y]&&map[x-1][y]==color) cal(block,x-1,y,color,no);
	if (x+1<n&&!block[x+1][y]&&map[x+1][y]==color) cal(block,x+1,y,color,no);
	if (y-1>=0&&!block[x][y-1]&&map[x][y-1]==color) cal(block,x,y-1,color,no);
	if (y+1<m&&!block[x][y+1]&&map[x][y+1]==color) cal(block,x,y+1,color,no);
}

void move(int block[][N],int no)
{
	bool mark = false;
	int down,left=0;
	for (int j = 0; j < m; j++)
	{
		down = n - 1;
		mark = false;
		for (int k = n - 1; k >= 0; k--)
		{
			if (block[k][j] != no)
			{
				if (block[k][j]) mark =  true;
				map[down--][left] = map[k][j];
			}
		}
		while (down >= 0) map[down--][left] = 0;
		if (mark) left++;
	}
	
	while (left < m)
	{
		for (int i=0;i<n;i++)
			map[i][left] = 0;
		left++;
	}

}

bool end(int &x,int &y,int block[N][N])
{
	int maxsize=0,minx,miny,maxno;
	int no=1;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			block[i][j] = 0;
	for (int i=0;i<n;i++)
	for (int j=0;j<m;j++)
	{
		if (map[i][j]&&!block[i][j])
		{
			bsize=0;
			xx=n-1;
			yy=m-1;
			cal(block,i,j,map[i][j],no);
			if (maxsize<bsize||(maxsize==bsize)&&(xx<minx||(yy==miny)&&yy<miny))
			{
				maxsize=bsize;
				maxno=no;
				minx=xx;
				miny=yy;
				x=i;
				y=j;
			}
			no++;
		}
	}
	no = maxno;
	bsize = maxsize;
	if (bsize<=1) return false;
	else return true;
}

void solve()
{
	int x,y;
	int block[N][N]={false};
	while (end(x,y,block))
	{
		move(block,block[x][y]);
		score+=bsize*(bsize-1);
	}
}

int main()
{
	char c;
	while (cin>>n>>m)
	{		
		score=0;
		memset(map,0,sizeof(map));
		for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
		{
			cin>>c;
			map[i][j]=c-'0';
		}
		solve();
		cout<<score<<endl;
	}
	return 0;
}
