#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int oo=0x7fffffff;
int minstep=oo,predict;
int map[4][4];
bool judge()
{
	bool mark1=true,mark2=true;
	int a=0,b=0,num1=0,num2=0;
	bool existed1[5],existed2[5];
	for (int i=0;i<4;i++)
	{
		num1=num2=0;
		memset(existed1,0,sizeof(existed1));
		memset(existed2,0,sizeof(existed2));
		for (int j=0;j<4;j++)
		{
			if (!existed1[map[i][j]]) existed1[map[i][j]]=true,num1++;
			if (!existed2[map[j][i]]) existed2[map[j][i]]=true,num2++;
		}
		a+=num1-1;
		b+=num2-1;
	}
	predict=(min(a,b)+3)/4;				//需要+3 如果出现min(a,b)处于(4k,4(k+1))时 需要至少k+1步
	if (a==0||b==0) return true;
	else return false;
}
void rot(int x,int y,int direct)
{
	int temp,k,next;
	k=0;
	if (x>=0)
	{
		temp=map[x][0];
		for (int i=0;i<4;i++)
		{
			next=(k+direct+4)%4;
			temp^=map[x][next];
			map[x][next]^=temp;
			temp^=map[x][next];
			k=next;
		}
	}
	else if (y>=0) 
	{
		temp=map[0][y];
		for (int i=0;i<4;i++)
		{
			next=(k+direct+4)%4;
			temp^=map[next][y];
			map[next][y]^=temp;
			temp^=map[next][y];
			k=next;
		}
	}
}
bool find(int step,int deep)
{
	if (judge())
	{
		minstep = min(minstep, step);
		return true;
	}
	else if (step==deep) return false;
	else if (predict + step > deep) return false;
	else
	{
		bool mark;
		for (int i=0;i<4;i++)
		{
			rot(i,-1,-1);mark=find(step+1,deep);rot(i,-1,1);
			if (mark) return mark;
			rot(i,-1,1);mark=find(step+1,deep);rot(i,-1,-1);
			if (mark) return mark;
			rot(-1,i,-1);mark=find(step+1,deep);rot(-1,i,1);
			if (mark) return mark;
			rot(-1,i,1);mark=find(step+1,deep);rot(-1,i,-1);
			if (mark) return mark;
		}
		return false;
	}
}
int main()
{
	int t;
	cin>>t;
	while (t--)
	{
		minstep=oo;
		for (int i=0;i<4;i++)
		for (int j=0;j<4;j++)
		{
			cin>>map[i][j];
		}
		for (int i = 1; i<=5; i++)
			if (find(0, i)) 
				break;
		if (minstep==oo) cout<<"-1"<<endl;
		else cout<<minstep<<endl;
	}
	return 0;
}