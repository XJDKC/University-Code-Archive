#include<stdio.h>
void flip(int *a,int x,int y);
int main()
{
	int n,k,a[60],i;
	while (scanf("%d%d",&n,&k)!=EOF)
	{
		for (i=0;i<n;i++)
		scanf("%d",&a[i]);
		flip(a,0,k-1);
		flip(a,k,n-1);
		flip(a,0,n-1);
		for (i=0;i<n;i++)
		{
		    printf("%d",a[i]);
		    if (i<n-1) printf(" ");
		    else printf("\n");
		}
	}
	return 0;
}
void flip(int *a,int x,int y)
{
	int i;
	for (i=x;i<y+x-i;i++)
	a[i]=a[i]+a[y+x-i],
	a[y+x-i]=a[i]-a[y+x-i],
	a[i]=a[i]-a[y+x-i]; 
}
