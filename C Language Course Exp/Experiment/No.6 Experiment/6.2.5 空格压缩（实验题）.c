#include<stdio.h>
void compress(char c[]);
int main()
{
	int n,i;
	char c[86];
	while (scanf("%d",&n)&&n)
	{
		getchar();
		for (i=0;i<n;i++)
		{
			fgets(c,85,stdin);
			compress(c);
		}
		printf("\n");
	}
	return 0;
}
void compress(char c[])
{
	int j;
	for (j=0;*(c+j)!='\0';j++)
	{
		if (!j&&*(c+j)=='\n')
			break;
		if (j&&*(c+j)==' '&&*(c+j-1)==' ')
		continue;
		else printf("%c",*(c+j));
	}
}

