#include<stdio.h>
#include<string.h>
int main()
{
	char n[16];
	int k;
	while (scanf("%s %d",n,&k)!=EOF)
	{
		if (k>strlen(n)) printf("-1\n");
		else printf("%d\n",n[strlen(n)-k]-'0');
	}
	return 0;
} 
