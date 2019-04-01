#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdlib>
using namespace std;
const int N =3;
const int N2=9;
int rec[10][10];
bool used[3][10][10];
bool find()
{
	bool mark=false,found=false;
	int i,j,k;
	for (i=0;i<N2;i++)
	{
		for (j=0;j<N2;j++)
		{
			if (rec[i][j]==0)
			{
				break;
			}
		}
		if (j<N2) break;
	}
	if (i==N2&j==N2) return true;
	else 
	{
		for (k=1;k<=9;k++)
		{
			if (!used[0][i][k]&&!used[1][j][k]&&!used[2][i/N*N+j/N][k])
			{
				mark=true;
				rec[i][j]=k;
				used[0][i][k]=used[1][j][k]=used[2][i/N*N+j/N][k]=true;
				found=find();
				if (found) return true;
				else 
				{
					rec[i][j] = 0;
					used[0][i][k]=used[1][j][k]=used[2][i/N*N+j/N][k]=false;
				}
			}
		}
		return false;
	}

}
int main()
{
	int t;
	char c;
	cin>>t;
	getchar();
	while (t--)
	{
		memset(used,0,sizeof(used));
		for (int i=0;i<N2;i++)
		{
			for (int j=0;j<N2;j++)
			{
				cin>>c;
				rec[i][j]=c-'0';
				if (rec[i][j])
				{
					used[0][i][rec[i][j]]=true;
					used[1][j][rec[i][j]]=true;
					used[2][i/N*N+j/N][rec[i][j]]=true;
				}

			}
			getchar();
		}
		if (!find()) cout<<"NO SOLUTION"<<endl;
		else
		{
			for (int i=0;i<N2;i++)
			{
				for (int j=0;j<N2;j++)
				{
					cout<<rec[i][j];
					if (j==N2-1) cout<<endl;
				}
			}
		}
	}
	return 0;
}