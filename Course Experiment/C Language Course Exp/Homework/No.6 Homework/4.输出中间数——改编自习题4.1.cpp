#include<stdio.h>
struct student
{
	char name;
	int grade;
}A,B,C;
int comp(struct student x,struct student y)
{
	if (x.grade!=y.grade)
	{
		return x.grade<y.grade;
	}
	else 
		return x.name>y.name;
}
void change(struct student *x,struct student *y)
{
	struct student temp; 
	temp=*x;
	*x=*y;
	*y=temp;
}
int main()
{
	int i;
	while (scanf("%d%d%d",&A.grade,&B.grade,&C.grade)!=EOF)
	{
		A.name='A';B.name='B';C.name='C';
		if (comp(A,B)) change(&A,&B);
		if (comp(A,C)) change(&A,&C);
		if (comp(B,C)) change(&B,&C);
		if (A.grade-C.grade&&A.grade-B.grade) printf("%c:%d\n",B.name,B.grade); 
	    else printf("%c:%d\n",A.name,A.grade); 
	} 
	return 0;
}
