#include<stdio.h>
#include<string.h>
#define N 506
char s1[N],s2[N];
int a[N]={0},b[N]={0},c[2*N]={0};
void exchange(char *s,int *f);
void multi(int *a,int *b,int *c);
void output(int *f);
int main()
{
	scanf("%s %s",&s1,&s2);
	exchange(s1,a);
	exchange(s2,b);
	multi(a,b,c);
	output(c);
}
void exchange(char *s,int *f)
{
	int i;
	f[0]=strlen(s);
	for (i=1;i<=f[0];i++)
	{
		f[i]=s[f[0]-i]-'0';
	}
}
void multi(int *a,int *b,int *c)
{
	int i,j;
	c[0]=a[0]+b[0]-1;
	for (i=1;i<=a[0];i++)
	for (j=1;j<=b[0];j++)
	{
		c[i+j-1]+=a[i]*b[j];
		c[i+j]+=c[i+j-1]/10;
		c[i+j-1]%=10;
	}
	if (c[c[0]+1]) c[0]++;
}
void output(int *f)
{
	int i;
	for (i=f[0];i>=1;i--)
	printf("%d",f[i]);
	printf("\n");
} 
