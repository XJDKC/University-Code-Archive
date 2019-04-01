#include<stdio.h>
#include<string.h>
int main()
{
	char c[1006];
	while (scanf("%s",&c))
	{
		if (c[0]=='0') break;
		else 
		{
			int i=strlen(c);
			for (;i>=1;i--)
			printf("%c",c[i-1]);
		}
		printf("\n");
	}
	return 0;
}
