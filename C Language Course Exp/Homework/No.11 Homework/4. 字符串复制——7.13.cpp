#include<stdio.h>
#include<string.h>
void mycpy(char *s,char *t,int n);
int main()
{
	int N,n,i;
	char s[1006],t[1006];
    scanf("%d",&N);
    getchar();
    while (N--)
    {
    	scanf("%[^\n]%d",t,&n);
    	getchar();
		mycpy(s,t,n);
    	for (i=0;i<strlen(s);i++)
    	printf("%c",s[i]);
    	printf("\n");
	}
	return 0;
}
void mycpy(char *s,char *t,int n)
{
	int i;
	for (i=0;i<n;i++)
	s[i]=t[i];
	s[i]='\0';
}
