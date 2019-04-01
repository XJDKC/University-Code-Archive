#include<stdio.h>
#define N 10 
void isort(int f[]);
int main()
{
    int a[16];
    int i;
    while (scanf("%d",a+0)!=EOF)
    {
    	for (i=1;i<N;i++)
    	scanf("%d",a+i);
    	isort(a);
    	for (i=0;i<N;i++)
    	{
    		printf("%d",*(a+i));
    		if (i<N-1) printf("->");
    		else printf("\n");
		}
	}
	return 0;
} 
void isort(int f[])
{
	int temp;
	int i,j;
	for (i=0;i<N;i++)
	for (j=N-1;j>i;j--)
	{
        if (*(f+j)<*(f+j-1))
		{
		    temp=*(f+j);
			*(f+j)=*(f+j-1);
			*(f+j-1)=temp;	
		} 
    }
}
