#include<stdio.h>
#include<stdlib.h>
#define N 105 
double a[N][N],b[N][N],c[N][N];
double mul(double g[][N],int n)
{
	if (n==1) return g[1][1];
	double sum=0;
	double temp[N][N];
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<n;j++)
		for (int k=1;k<n;k++)
		if (k<i) temp[j][k]=g[j+1][k];
		else temp[j][k]=g[j+1][k+1];
		if (i&1) sum+=g[1][i]*mul(temp,n-1);
		else sum-=g[1][i]*mul(temp,n-1);
	}
    return sum;
}
void inv(double f[][N],int n)
{
	int xi;
	for (int i=1;i<=n;i++)
	for (int j=1;j<=n;j++)
	{
	    if ((i+j)%2==0) xi=1;
		else xi=-1;	
		for (int o=1,p=1;o<=n-1;o++,p++)
		{
		    if (p==i) p++;
			for (int q=1,r=1;q<=n-1;q++,r++)
			{
				if (r==j) r++;
				c[o][q]=f[p][r];
			}
		}
	    b[j][i]=xi*mul(c,n-1);
	}
}
int main()
{
    int n;
	double m;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			scanf("%lf",&a[i][j]);
	inv(a,n);
	m=mul(a,n);
	for (int i=1;i<=n;i++)
	    for (int j=1;j<=n;j++)
	    {
	    	printf("%lf",b[i][j]/m);
	    	if (j-n) printf(" ");
	    	else printf("\n");
		}
	system("pause"); 
	return 0;
}
