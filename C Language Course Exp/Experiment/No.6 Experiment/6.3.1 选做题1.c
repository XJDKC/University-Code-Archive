#include<stdio.h>
#include<string.h>
#define N 506
char s1[N],s2[N];
int a[N]={0},b[N]={0},c[N]={0};
void exchange(char *s,int *f);
void add(int *a,int *b,int *c);
void output(int *f);
int main()
{
	scanf("%s %s",&s1,&s2);
	exchange(s1,a);
	exchange(s2,b);
	add(a,b,c);
	output(c); 
	return 0;
}
void exchange(char *s,int *f)
{
	int i;
	f[0]=strlen(s);
	for (i=1;i<=f[0];i++)
	{
		if (s[f[0]-i]!='.')
		f[i]=s[f[0]-i]-'0';
		else
		f[i]=-1;
	}
}
void add(int *a,int *b,int *c)
{
	int i=1;
	c[0]=a[0]>b[0]?a[0]:b[0];
	for (i=1;i<=c[0];i++)
	{
		if (a[i]!=-1)
		{
	       c[i]+=a[i]+b[i];
		   if (c[i+1]!=-1)
		   c[i+1]=c[i]/10;
		   else 
		   c[i+2]=c[i]/10;
		   c[i]%=10;	
	    }
	    else c[i]=-1;
	} 
	if (c[c[0]+1]) c[0]++; 
}
void output(int *f)
{
	int i;
	for (i=f[0];i>=1;i--)
	if (f[i]>=0)
	printf("%d",f[i]);
	else printf(".");
	printf("\n");
} 

