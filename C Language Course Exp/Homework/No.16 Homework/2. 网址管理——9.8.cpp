#include<stdio.h>
#include<stdlib.h>
typedef struct Web
{
    char shtage[21];
	char fulln[41];
	char url[41];	
}web;
void isort(web *inf,int n);
int comp(web x,web y);
int main()
{
	int n,i;
	web *inf;
	scanf("%d",&n);
	inf=(web *)malloc(sizeof(web)*n);
	for (i=0;i<n;i++)
	{
	    scanf("%s%s%s",inf[i].shtage,inf[i].fulln,inf[i].url);
        printf("%-20s%-40s%s\n",inf[i].shtage,inf[i].fulln,inf[i].url);
	}
	printf("\n");
	isort(inf,n);
	for (i=0;i<n;i++)
	    printf("%-20s%-40s%s\n",inf[i].shtage,inf[i].fulln,inf[i].url);
	return 0;
}
void isort(web *inf,int n)
{
	int i,j;
	web temp;
	for (i=0;i<n-1;i++)
	    for (j=i+1;j<n;j++)
            if (comp(inf[i],inf[j]))
            {
                temp=inf[i];
			    inf[i]=inf[j];
			    inf[j]=temp;	
		    }
}
int comp(web x,web y)
{
	char *p1=x.shtage,*p2=y.shtage;
	while ((*p1-*p2)==0&&*p2)
	{
		p1++;
		p2++;
	}
	return *p1>*p2;
}
