#include<stdio.h>
int main()
{
	int n,i,m,a[1006],temp;
	scanf("%d",&n);
	while (n--)
	{
		scanf("%d",&m);
		for (i=0;i<m;i++)
			scanf("%d",&a[i]);
		for (i=0;i<=(m-1)/2;i++)
		{
			temp=*(a+i);
			*(a+i)=*(a+m-i-1);
			*(a+m-i-1)=temp;
		}
		for (int i=0;i<m;i++)
		{
		    printf("%d",*(a+i));
	        if (i<m-1) printf(" ");
			else printf("\n");
		}
	}
	return 0;
}
