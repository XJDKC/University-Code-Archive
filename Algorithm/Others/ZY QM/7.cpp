#include<stdio.h>
#include<math.h>

int N,M,maxn,i,j;
int ans=0x7fffffff;

void cake(int m,int r,int h,int v,int s)
{
	if (m==1)
	{
	   if(v==N&&s<ans) ans=s;
	   else return ; 	
	}
	for (i=m-1;i<r;i++)
	for (j=m-1;j<h;j++)
	{
		if (v+i*i*j<=N) cake(m-1,i,j,v+i*i*j,s+2*i*j);
	}
	return ;
}
int main()
{
	scanf("%d%d",&N,&M);
	maxn=N;
	for (i=M;i<=maxn;i++)
	for (j=M;j<=maxn;j++)
	{
		if (i*i*j<=N)
		cake(M,i,j,i*i*j,i*i+2*i*j);
	}
	if (ans==0x7fffffff) printf("0\n");
	else printf("%d\n",ans);
	return 0;
}
