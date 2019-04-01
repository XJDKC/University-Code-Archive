#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
struct node
{
	int x;
	int y;
};
node block[55];
node direct[4]={{1,0},{0,1},{0,-1},{-1,0}};
bool visited[230][230]={0};			//由于不能直走 20步最多到达(2+20)*10/2=110 两个方向最多为220
int n,m,num=0;
string s(25,'\0'),word="ensw";		//按照这个顺序排 自然呈字典序

bool judge(node from,node to)
{
	for (int i=0;i<m;i++)
	{
		if (from.x==to.x&&block[i].x==to.x)
		{
			if ((block[i].y-from.y)*(block[i].y-to.y)<=0)
			{
				return false;
			}
		}
		else if (from.y==to.y&&block[i].y==to.y)
		{
			if ((block[i].x-from.x)*(block[i].x-to.x)<=0)
			{
				return false;
			}
		}
	}
	if (visited[to.x+110][to.y+110]) return false;
	return true;
}

void solve(node pos,int cur,int last)
{
	if (pos.x==0&&pos.y==0&&cur==n)
	{
		for (int i=0;i<n;i++)
		{
			cout<<s[i];
		}
		cout<<endl;
		num++;
	}
	else if (cur<n)
	{
		cur++;
		node next;
		for (int i=0;i<4;i++)
		{
			if (last==-1||i!=last&&i!=3-last)
			{
				next.x=pos.x+direct[i].x*cur;
				next.y=pos.y+direct[i].y*cur;
				if (judge(pos,next))
				{
					s[cur-1]=word[i];
					visited[next.x + 110][next.y + 110] = true;
					solve(next,cur,i);
					visited[next.x + 110][next.y + 110] = false;
				}				
			}

		}
	}
}

int main()
{
	int t;
	node original={0,0};
	cin>>t;
	while (t--)
	{
		cin>>n>>m;
		memset(visited,0,sizeof(visited));
		for (int i=0;i<m;i++)
		{
			cin>>block[i].x>>block[i].y;
		}
		num=0;
		solve(original,0,-1);
		cout<<"Found "<<num<<" golygon(s)."<<endl;
		cout<<endl;
	}
	return 0;
}