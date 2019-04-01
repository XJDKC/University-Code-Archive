#include<stdio.h>
#define N 10006
int heap[N]={0};
void adjust(int f[],int i,int n)
{
	int no,temp;
	no=2*i+1<=n?f[2*i]>f[2*i+1]?2*i:2*i+1:2*i;
	if (f[no]>f[i]) 
		f[no]=f[i]^f[no],f[i]=f[i]^f[no],f[no]=f[i]^f[no];
}
void heap_sort(int f[],int n)
{
	if (n==1) return ;
	int i,j;
	for (i=n/2;i>=1;i--)
		adjust(f,i,n-1);
	for (i=n;i>1;i--)
	{
		f[i]=f[i]^f[1],f[1]=f[i]^f[1],f[i]=f[i]^f[1];
		for (j=(i-1)/2;j>=1;j--)
		adjust(f,j,i-1);
	}
}
int main()
{
	int n,i;
	scanf("%d",&n);
	for (i=1;i<=n;i++)
	    scanf("%d",&heap[i]);
	heap_sort(heap,n);
	for (i=1;i<=n;i++)
	{
	    printf("%d",heap[i]);
        if (i<n) printf(" ");
        else printf("\n");
	}
	return 0;
} 
