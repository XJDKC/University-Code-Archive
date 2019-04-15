#include<stdio.h>
typedef struct student
{
	int num;
	char name[19];
	double score;
}Student;
Student s[3],*p;
int main()
{
	int n,i;
	scanf("%d",&n);
	while (n--)
	{
		for (i=0;i<3;i++)
		scanf("%d%s%lf",&s[i].num,s[i].name,&s[i].score);
		for (i=0;i<3;i++)
		printf("%d\t%-20s%lf\n",s[i].num,s[i].name,s[i].score);
		p=&s[0];
		for (i=0;i<3;i++,p++)
		printf("%d\t%-20s%lf\n",p->num,p->name,p->score);
		//printf("%d\t%-20s%lf\n",(*p).num,(*p).name,(*p).score);
	}
	return 0;
}
