#include<iostream>
using namespace std;
const int yu=10000;
long long f[2][55];
int cal(int n,int k)
{
	for (int i=0;i<=k;i++) f[0][i]=f[1][i]=0;
	f[0][1]=f[1][1]=1;
	for (int i=2;i<=n;i++)
	{
		for (int j=1;j<=i&&j<=k;j++)
		{
			f[1][j]=(f[0][j]*j+f[0][j-1])%yu;
		}
		if (i==n) return 1;
		i++;
		for (int j=1;j<=i&&j<=k;j++)
		{
			f[0][j]=(f[1][j]*j+f[1][j-1])%yu;
		}
		if (i==n) return 0;
	}
}
int main()
{
	int t,n,k,mark;
	cin>>t;
	for (int i=1;i<=t;i++)
	{
		cin>>n>>k;
		if (n==1) cout<<"1"<<endl;
		else 
		{
		    mark=cal(n,k);
		    cout<<f[mark][k]<<endl;
		}
	}
	return 0;
}
