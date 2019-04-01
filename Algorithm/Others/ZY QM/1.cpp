#include<stdio.h>
int a[1005][1005]={0};
int ans=0;

int max(int x,int y)
{
	if(x>=y) return x;
	else return y;
}
int min(int y,int x)
{
	if(y>=x) return x;
	else return y;
}
void search(int x1,int x2,int y1,int y2);

int main()
{
	int n,m,i,j;
	scanf("%d %d",&n,&m);
	for(i=1;i<=n;i++)
	for(j=1;j<=m;j++)
	scanf("%d",&a[i][j]);
	search(1,m,1,n);
	printf("%d",ans); 
}

void search(int x1,int x2,int y1,int y2)
{
	if(x1<=x2&&y1<=y2)
	{
		int i,j,m;
		bool p=true;
		for(i=y1;i<=y2;i++)
		for(j=x1;j<=x2;j++)
		if(a[i][j]==0) 
		{
			search(x1,j-1,y1,y2);
			search(x1,x2,i+1,y2);
			search(j+1,x2,y1,y2);
			search(x1,x2,y1,i-1);
			p=false;
		}
		if(p)
		{
		  m=min(x2-x1+1,y2-y1+1);
		  ans=max(ans,m);
		}	
	}
	return;
}


