#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdlib>
using namespace std;
int n,n2;
int rec[10][10];
bool used[3][10][10];
bool find()
{
	bool mark=false,found=false;
	int i,j,k;
	for (i=0;i<n2;i++)
	{
		for (j=0;j<n2;j++)
		{
			if (rec[i][j]==0)
			{
				break;
			}
		}
		if (j<n2) break;
	}
	if (i==n2&&j==n2) return true;
	else 
	{
		for (k=1;k<=9;k++)
		{
			if (!used[0][i][k]&&!used[1][j][k]&&!used[2][i/n*n+j/n][k])
			{
				mark=true;
				rec[i][j]=k;
				used[0][i][k]=used[1][j][k]=used[2][i/n*n+j/n][k]=true;
				found=find();
				if (found) return true;
				else 
				{
					rec[i][j] = 0;
					used[0][i][k]=used[1][j][k]=used[2][i/n*n+j/n][k]=false;
				}
			}
		}
		return false;
	}

}
int main()
{
	bool mark = false;
	char c;
	while (cin>>n)
	{
		if (mark) cout << endl;
		mark = true;
		memset(used,0,sizeof(used));
		n2=n*n;
		for (int i=0;i<n2;i++)
		for (int j=0;j<n2;j++)
		{
			cin>>rec[i][j];
			if (rec[i][j])
			{
				used[0][i][rec[i][j]]=true;
				used[1][j][rec[i][j]]=true;
				used[2][i/n*n+j/n][rec[i][j]]=true;
			}

		}
		if (!find()) cout<<"NO SOLUTION"<<endl;
		else
		{
			for (int i=0;i<n2;i++)
			{
				for (int j=0;j<n2;j++)
				{
					cout<<rec[i][j];
					if (j<n2-1) cout<<" ";
					else cout<<endl;
				}
			}
		}
		getchar();
		getchar();
	}
	return 0;
}