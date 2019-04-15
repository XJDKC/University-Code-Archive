#include<stdio.h>
#define N 5
#define M 5
struct student
{
    char name[16];
    int grade[M];
	double aver;		
}f[N];
struct subject
{
	char name[16];
	double aver;
	int num,high,low;
}g[M];
void output();
int main()
{
	int i,j,num[5],x;
	double gra_aver[M];
	for (i=0;i<M;i++)
	    scanf("%s",(*(g+i)).name);
	for (i=0;i<N;i++)
	{
		scanf("%s",(*(f+i)).name);
		for (j=0;j<M;j++)
		{
		    scanf("%d",&x);
		    *((*(f+i)).grade+j)=x;
	        (*(f+i)).aver+=x;
	        (*(g+j)).aver+=x;
	        if (x>=90) (*(g+j)).high++;
	        else if (x<60) (*(g+j)).low++;
	    }
	    (*(f+i)).aver/=(double)N;
    }
    for (i=0;i<M;i++)
    {
        (*(g+i)).aver/=(double)M;
        for (j=0;j<N;j++)
        if (*((*(f+j)).grade+i)<(*(g+i)).aver) 
        (*(g+i)).num++;
    }
    output(); 
    return 0;
}
void output()
{
	int i; 
	for (i=0;i<N;i++)
    	printf("Average score of %s is %.2lf\n",(*(f+i)).name,(*(f+i)).aver);
    for (i=0;i<M;i++)
        printf("Average score of %s is %.2lf\n",(*(g+i)).name,(*(g+i)).aver); 
    for (i=0;i<M;i++)
        printf("Number of students lower than avg of %s is %d\n",(*(g+i)).name,(*(g+i)).num);
    for (i=0;i<M;i++)
        printf("Number of students %s fail is %d\n",(*(g+i)).name,(*(g+i)).low);
    for (i=0;i<M;i++)
        printf("Number of students %s perfect is %d\n",(*(g+i)).name,(*(g+i)).high);
}
