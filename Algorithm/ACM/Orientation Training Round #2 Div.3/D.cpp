#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;
int M,N,minstep=0x7fffffff,firststep=0;
bool map[15][15];
bool test[15][15];
bool press[15][15];
bool ans[15][15]={true};
void flip(bool aim[][15],int x,int y)
{
    aim[x][y]=!aim[x][y];
    if (x-1>=0) aim[x-1][y]=!aim[x-1][y];
    if (x+1<M)  aim[x+1][y]=!aim[x+1][y];
    if (y-1>=0) aim[x][y-1]=!aim[x][y-1];
    if (y+1<N)  aim[x][y+1]=!aim[x][y+1];
}

bool judge()
{
	for (int i=0;i<M;i++)
	for (int j = 0; j < N; j++)
	{
		if (ans[i][j] != press[i][j])
			return (press[i][j] < ans[i][j]);
	}
}
void dfs(int depth)
{
    if (depth==N)
    {
		int step=firststep;
		bool mark=true;
        for (int i=0;i<M;i++)
        for (int j=0;j<N;j++)
            test[i][j]=map[i][j];
        for (int i=1;i<M;i++)
        for (int j=0;j<N;j++)
        {
            press[i][j]=false;
            if (test[i-1][j])
            {
                press[i][j]=true;
                flip(test,i,j);
				step++;
            }
        }
        for (int i=0;i<N;i++)
        {
            if (test[M-1][i])
            {
                mark=false;
                break;
            }
        }
		if (mark)
		{
			if (step < minstep||(step == minstep&&judge()))
			{
				minstep = step;
				for (int i=0;i<M;i++)
				for (int j = 0; j < N; j++)
				{
					ans[i][j] = press[i][j];
				}
			}
        }
    }
    else 
    {
        dfs(depth+1);
        flip(map,0,depth);
		firststep++;
		press[0][depth] = true;
        dfs(depth+1);
        flip(map,0,depth);
		firststep--;
		press[0][depth] = false;
    }
}

int main()
{
    bool mark=true;
    cin>>M>>N;
    memset(ans,true,sizeof(ans));
    for (int i=0;i<M;i++)
    for (int j=0;j<N;j++)
    {
        cin>>map[i][j];
    }
	dfs(0);
    if (minstep!=0x7fffffff)
    {
        for (int i=0;i<M;i++)
        for (int j=0;j<N;j++)
        {
            cout<<ans[i][j];
            if (j<N-1) cout<<" ";
            else cout<<endl;
        }
    }
	else cout << "IMPOSSIBLE" << endl; 
    system("pause");
    return 0;
}
