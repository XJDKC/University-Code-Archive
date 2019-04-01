#include<stdio.h>
int main()
{
	int n;
	scanf("%d",&n);
	getchar();
	while (n--)
	{
		char a='0',b;
		while ((b=getchar())!='\n')
		{
			if (a!='0'&&a==' '&&b==' ') continue;
			a=b;
			printf("%c",a);
		}
		printf("\n");
	}
	return 0;
}
