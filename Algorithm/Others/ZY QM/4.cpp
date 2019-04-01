#include<stdio.h>
#include<math.h> 
struct node
{
	int no,x,y;
};
struct node f[405];
int main()
{
	int n,m,i,j,k,num=0,t,temp,T=0,ans=0,temp1,temp2;
	scanf("%d %d %d",&n,&m,&t);
	for (i=1;i<=n;i++)
	for (j=1;j<=m;j++)
	{
		scanf("%d",&k);
		if (k!=0)
		{
			num++;
			f[num].no=k;
			f[num].x=i;
			f[num].y=j;
		}
	} 
	for (i=1;i<num;i++)
	for (j=num;j>i;j--)
	{
		if (f[j].no>f[j-1].no)
		{
			temp=f[j-1].no;f[j-1].no=f[j].no;f[j].no=temp;
			temp=f[j-1].x;f[j-1].x=f[j].x;f[j].x=temp;
			temp=f[j-1].y;f[j-1].y=f[j].y;f[j].y=temp;
		}
	}
	if (2*f[1].x+1<=t) 
	{
	T=f[1].x+1;ans+=f[1].no;
	for (i=2;i<=num;i++)
	{
		temp1=(f[i].x-f[i-1].x),temp2=f[i].y-f[i-1].y;
		if (temp1<0) temp1=-temp1;
		if (temp2<0) temp2=-temp2;
		if((T+temp1+temp2+1+f[i].x)<=t) 
		{
		  T+=temp1+temp2+1;
		  ans+=f[i].no;
		} 
		else break;
	} 
	}
	printf("%d\n",ans);
	return 0;
}

