#include<iostream>
#include<cstring>
using namespace std;
const int mod=10000;
struct matrax
{
	long long m[66][66];
};
matrax per,ans,base,cal,unit; 
matrax mul(matrax a,matrax b,int x,int y,int z)
{
	matrax c;
	for (int i=0;i<x;i++)
	for (int j=0;j<z;j++)
	{
		c.m[i][j]=0;
		for (int k=0;k<y;k++)
			c.m[i][j]=(c.m[i][j]+a.m[i][k]*b.m[k][j])%mod;
		c.m[i][j]=c.m[i][j]%mod;
	}
	return c;
}
matrax qpow(int n,int k)
{
	matrax p=per;
	int ci=n-k;
	while (ci)
	{
		if (ci&1) 
		{
		   unit=mul(unit,p,k,k,k);
		   ci--;
		}
		else 
		{
			p=mul(p,p,k,k,k);
			ci>>=1;
		}
	}
	return unit;
}
void init(int k)
{
	for (int i=0;i<50;i++) 
	for (int j=0;j<50;j++)
	{
		if (i==j&&i<k) per.m[i][j]=k-i;
		else if (j-1==i&&j<k) per.m[i][j]=1;
		else per.m[i][j]=0;
		if(i==j) unit.m[i][j]=1;
		else unit.m[i][j]=0;
	}
	for (int i=0;i<k;i++)
	base.m[i][0]=cal.m[k-1][k-1-i];
}
void calculation()
{
	for (int i=0;i<50;i++) cal.m[i][i]=cal.m[i][0]=1;
	for(int i=1;i<50;i++)
	for(int j=1;j<i;j++)
	cal.m[i][j]=(cal.m[i-1][j]*(j+1)+cal.m[i-1][j-1])%mod;
}
int main()
{
	int t,n,k;
	cin>>t;
	calculation();
	while (t--)
	{
		cin>>n>>k;
		init(k);
		matrax xi=qpow(n,k);
		ans=mul(xi,base,k,k,1);
		cout<<ans.m[0][0]<<endl;
	}
	return 0;
}
