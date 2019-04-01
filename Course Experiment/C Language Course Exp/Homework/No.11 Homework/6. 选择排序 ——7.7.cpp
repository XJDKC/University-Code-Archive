#include<stdio.h>
int main()
{
	int a[25],n,i,j,max,pos;
	while (scanf("%d",&n)&&n)
	{
		for (i=1;i<=n;i++)
		scanf("%d",&a[i]);
		for (j=n;j>=2;j--)
		{
			for (max=a[1],i=1,pos=1;i<=j;i++)
				if (a[i]>max) max=a[i],pos=i;
			a[pos]=a[j],a[j]=max;
		}
		for (i=1;i<=n;i++)//本题也可以取最小数然后中途输出 
		{
		    printf("%d",a[i]);
	        if (i<n) printf(" ");
	        else printf("\n");
		}
	}
	return 0;
}
