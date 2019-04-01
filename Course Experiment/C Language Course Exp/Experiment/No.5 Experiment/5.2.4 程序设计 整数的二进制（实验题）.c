#include<stdio.h>
#include<limits.h> 
char num[36];
void transform(int x);
void output();
int main()
{
	int n,x,i;
	scanf("%d",&n);
	for (i=0;i<n;i++)
	{
		scanf("%d",&x);
		transform(x);
		output();
	}
	return 0;
}
void transform(int x)
{
	int i,len=sizeof(int)*CHAR_BIT;
	for (i=len-1;i>=0;i--)
	{
		num[i]='0'+(x&1);
		x>>=1;
	}
}
void output()
{
	int i,len=sizeof(int)*CHAR_BIT;
	for (i=0;i<len;i++)
	printf("%c",num[i]);
	printf("\n");
}
