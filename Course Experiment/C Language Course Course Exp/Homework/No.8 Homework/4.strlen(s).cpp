#include<stdio.h>
int istrlen(char *c);
int main()
{
	int n;
	char c[10005];
	scanf("%d",&n);
	getchar();
	while (n--)
	{
		fgets(c,10000,stdin);
		printf("%d\n",istrlen(c));
	}
	return 0;
}
int istrlen(char *c)
{
	int i;
	for (i=0;c[i]!='\n';i++) ;
	return i;
}
