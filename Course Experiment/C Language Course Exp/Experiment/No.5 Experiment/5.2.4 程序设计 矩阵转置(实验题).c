#include<stdio.h>
int matrix[4][4]={0};
void transpose(int m[][4]);
int main()
{
	int i,j;
	for (i=0;i<3;i++)
	{
		for (j=0;j<4;j++)
		{
		    scanf("%d",&matrix[i][j]);
		    printf("%5d",matrix[i][j]);
        } 
		printf("\n");
    }
	transpose(matrix);
	printf("\n");
	for (i=0;i<4;i++)
	{
	    for (j=0;j<3;j++)
	    printf("%5d",matrix[i][j]);
		printf("\n"); 
	}
	return 0;
}
void transpose(int m[][4])
{
	int i,j,temp;
	for (i=0;i<3;i++)
	{
		for (j=i+1;j<4;j++)
		{
			temp=m[i][j];
			m[i][j]=m[j][i];
			m[j][i]=temp;
		}
	}
}
