#include<stdio.h>
#include<string.h>
int a[6],f[6][6],g[6][6];
void change(int x,int y)
{
	g[x][y]^=1;
	if (x-1>=1) g[x-1][y]^=1;
	if (x+1<=5) g[x+1][y]^=1;
	if (y-1>=1) g[x][y-1]^=1;
	if (y+1<=5) g[x][y+1]^=1;
	return ; 
}
void cal()
{
	int a1,a2,a3,a4,a5,i,j,step=0,ans=10;
	for (a[1]=0;a[1]<2;a[1]++)
	for (a[2]=0;a[2]<2;a[2]++)
	for (a[3]=0;a[3]<2;a[3]++)
	for (a[4]=0;a[4]<2;a[4]++)
	for (a[5]=0;a[5]<2;a[5]++)
	{
		step=0;
		memcpy(g,f,sizeof(g));
		for (i=1;i<=5;i++)
			if (a[i]) 
			{
			    change(1,i);
			    step++;
		    }
		for (i=2;i<=5;i++)
		for (j=1;j<=5;j++)
		{
			if (!g[i-1][j]&&step<=6) 
			{
				change(i,j);step++;
			}
		}
		for (i=1;i<=5;i++)
		{
			if (!g[5][i]) step=7; 
		}
		if (step<=ans) ans=step;
		if (ans==1) printf("1\n"); 
	}
	if(ans<=6) printf("%d\n",ans);
	else printf("-1\n"); 
}
int main()
{
	int n,i,k,j,num;
	scanf("%d",&n);
	for (i=1;i<=n;i++)
	{
		memset(f,0,sizeof(f));
		for (j=1;j<=5;j++)
		{
			scanf("%d",&num);
			while (num)
			{
				f[j][5-f[j][0]++]=num%10;
				num/=10;
			}
		}
		cal();
	}
} 
