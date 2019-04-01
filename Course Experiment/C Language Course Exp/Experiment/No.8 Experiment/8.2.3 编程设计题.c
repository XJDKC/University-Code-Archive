#include<stdio.h>
int main()
{
	char a='\0',b;
	freopen("test.txt","w",stdout);
	while (scanf("%c",&b)&&b!='\n')
	{
		if (a=='\0'||a==' ')
		{
			if (b>='a'&&b<='z')
			putchar(b-32);
			else putchar(b);
		}
		else putchar(b);
		a=b;
	}
	printf("\n");
	return 0;
}
