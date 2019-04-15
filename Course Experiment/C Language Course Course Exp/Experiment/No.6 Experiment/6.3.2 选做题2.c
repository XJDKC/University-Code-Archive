#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
	char *(*p[2])(char *,const char *);
	char a[10]="I Love ",b[10]="Program!",c[10],*p1,*p2;
	p[0]=strcpy;
	p[1]=strcat;
	p1=p[0](c,b);
	p2=p[1](a,b);
	printf("%s\n%s\n",p1,p2);
	return 0;
}
