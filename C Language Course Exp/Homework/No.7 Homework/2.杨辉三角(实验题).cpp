#include<stdio.h>
int C[15][15]={0};
void init();
void print(int x);
int main()
{
	int n,no=0;
	init();
	while (scanf("%d",&n)&&n)
	{
		print(n); 
		printf("\n");
	}
	return 0;
}
void init()
{
	int i,j;
	for (i=1;i<=12;i++)
	for (j=1;j<=i;j++)
	{
		if (j==1||j==i) 
		{
			C[i][j]=1;
			continue;
		}
		else 
		{
			C[i][j]=C[i-1][j]+C[i-1][j-1];
		}
	}
}
void print(int x)
{
	int i,j,wei;
	for (i=1;i<=x;i++)
	{
	    for (j=1;j<=x-i;j++)
		printf("  ");
		printf("%d",C[i][1]);
		for (j=2;j<=i;j++)
		{
			printf("%4d",C[i][j]);
		}	
		printf("\n");
	} 
}
