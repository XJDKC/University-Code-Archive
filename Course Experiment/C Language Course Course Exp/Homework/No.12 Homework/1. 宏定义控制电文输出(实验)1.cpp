#include<stdio.h>
#include<string.h>
#define CHANGE(c) ((c)%2)
int main()
{
	char c[10006],a;
	int i;
	while (scanf("%[^\n]",c)!=EOF)
	{
		getchar();
		a=c[0];
		if(CHANGE(a))
		{
			for (i=0;i<strlen(c);i++)
			{
			    if (c[i]>='a'&&c[i]<='z') 
					c[i]-=('a'-'A');
			    else if (c[i]>='A'&&c[i]<='Z')
			        c[i]+=('a'-'A');
			    printf("%c",c[i]);
			}
			printf("\n");
		}
		else printf("%s\n",c); 
	}
	return 0;
}

