#include<stdio.h>
int main()
{
	int n;
	char c;
	scanf("%d",&n);
	getchar();
	while (n--)
	{
		scanf("%c",&c);
		getchar();
		if (c>='0'&&c<='9')
		c-='0';
		else if (c>='a'&&c<='f')
		c-='a'-10;
		else if (c>='A'&&c<='F')
		c-='A'-10;
		printf("%d\n",c);
	}
	return 0;
}
