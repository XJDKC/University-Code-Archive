#include<stdio.h>
#include<string.h>
int palindrome(char *x,char *y);
int main()
{
	int n;
	char c[1006];
	scanf("%d",&n);
	getchar();
	while (n--)
	{
		scanf("%[^\n]",c);
		getchar();
		if (palindrome(c,c+strlen(c)-1))
		    printf("Yes!\n");
		else
		    printf("No!\n");
    }
	return 0;
}
int palindrome(char *x,char *y)
{
	if (x>=y) return 1;
	else 
	{
		if (*x==*y) return palindrome(++x,--y);
		else return 0;
	}
}
