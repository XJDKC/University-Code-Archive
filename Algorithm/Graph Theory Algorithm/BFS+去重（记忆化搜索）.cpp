#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
struct node
{
	int t[6][6];
	int turn,bu;//1 ÎªºÚ£¬2 Îª°×¡£ 
	void init()
	{
		fill(t[0],t[0]+6*6,0);
	}
}state;
queue<node> q;
bool can(struct node con)
{
	for (int i=1;i<=4;i++)
	{
	    if (con.t[i][1]==con.t[i][2]&&con.t[i][1]==con.t[i][3]&&con.t[i][1]==con.t[i][4])
	    return true;
		if (con.t[1][i]==con.t[2][i]&&con.t[1][i]==con.t[3][i]&&con.t[1][i]==con.t[4][i])
	    return true;
	}
	if (con.t[1][1]==con.t[2][2]&&con.t[1][1]==con.t[3][3]&&con.t[1][1]==con.t[4][4])
	return true;
	if (con.t[1][4]==con.t[2][3]&&con.t[1][4]==con.t[3][2]&&con.t[1][4]==con.t[4][1])
	return true;
	return false;
}
void BFS()
{
	while (!q.empty())
	{
		node con=q.front();
		q.pop();
		if (can(con)) 
		{
		   printf("%d\n",con.bu);
		   break;
		}
		for (int i=1;i<=4;i++)
		for (int j=1;j<=4;j++)
		{
			if (con.t[i][j]==0)
			{
				if (con.t[i-1][j]==con.turn)
				{
					state=con;
					swap(state.t[i-1][j],state.t[i][j]);
					state.bu++;
					state.turn=state.turn==1?2:1;
					q.push(state);
				}
				if (con.t[i+1][j]==con.turn)
				{
					state=con;
					swap(state.t[i+1][j],state.t[i][j]);
					state.bu++;
					state.turn=state.turn==1?2:1;
					q.push(state);
				}
				if (con.t[i][j-1]==con.turn)
				{
					state=con;
					swap(state.t[i][j-1],state.t[i][j]);
					state.bu++;
					state.turn=state.turn==1?2:1;
					q.push(state);
				}
				if (con.t[i][j+1]==con.turn)
				{
					state=con;
					swap(state.t[i][j+1],state.t[i][j]);
					state.bu++;
					state.turn=state.turn==1?2:1;
					q.push(state);
				}
			}
		}
 	}
 	return ;
}
int main()
{
	char x;
	for (int i=1;i<=4;i++)
	for (int j=1;j<=6;j++)
	{
		scanf("%c",&x);
		if (x=='\n'||x==' ') continue;
	    if (x=='B') state.t[i][j]=1;
	    else if (x=='W') state.t[i][j]=2;
	    else state.t[i][j]=0;
	}
	state.bu=0;
	state.turn=1;
	q.push(state);
	state.turn=2;
	q.push(state);
	BFS();
	return 0;
}

