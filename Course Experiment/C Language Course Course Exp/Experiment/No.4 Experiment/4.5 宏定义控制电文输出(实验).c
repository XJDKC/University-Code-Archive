#include<stdio.h>
#include<string.h>
#define CHANGE ((a)%2)
int main()
{
	char c[10006],a;
	int i;
	while (fgets(c,10000,stdin)!=NULL)
	{
		a=c[0];
		#ifdef CHANGE
		if (CHANGE==1)
			for (i=0;i<strlen(c);i++)
			{
			    if (c[i]>='a'&&c[i]<='z')
					putchar('A'+c[i]-'a');
			    else if (c[i]>='A'&&c[i]<='Z')
			        putchar('a'+c[i]-'A');
			    else putchar(c[i]);
			}
	    else 
		    printf("%s",c); 
		#endif
	}
	return 0;
}

