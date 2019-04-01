#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct stu
{
	char ID[16];
	char Name[21];
	float English;
	float Math;
	float Physics;
	float C;
	float SUM;
	float AVG;
	struct stu *next;
}Stu;
void create_tail(Stu **head,int n);
void change(Stu *head,int m);
int comp(Stu *x,Stu *y);
void isort(Stu **head);
void swap1(Stu *x,Stu *y);
void swap2(Stu **x_pre,Stu *x,Stu *y); 
void output1(Stu *head);
void output2(Stu *head);
void output3(Stu *head);
int main()
{
	int n,i,m;
	Stu *head=NULL;
	scanf("%d",&n);
	create_tail(&head,n);
	output1(head);
	scanf("%d",&m);
	change(head,m);
	output1(head);
	output2(head);
	isort(&head);
	output3(head);
	return 0;
}
void create_tail(Stu **head,int n)
{
	int i;
	Stu *p1,*p2;
	for (i=0;i<n;i++)
	{
		if (!i)
		{
			p1=(Stu *)malloc(sizeof(Stu));
			scanf("%s%s%f%f%f%f",p1->ID,p1->Name,&p1->English,&p1->Math,&p1->Physics,&p1->C);
			p1->SUM=p1->English+p1->Math+p1->Physics+p1->C;
			p1->AVG=p1->SUM/4;
			p1->next=NULL;
			*head=p1;
		}
		else 
		{
			p2=(Stu *)malloc(sizeof(Stu));
			scanf("%s%s%f%f%f%f",p2->ID,p2->Name,&p2->English,&p2->Math,&p2->Physics,&p2->C);
			p2->SUM=p2->English+p2->Math+p2->Physics+p2->C;
			p2->AVG=p2->SUM/4;
			p1->next=p2;
			p2->next=NULL;
			p1=p2;
		}
	}
}
void change(Stu *head,int m)
{
	int i;
	Stu *p1;
	char id[16],course[21];
	for (i=0;i<m;i++)
	{
		scanf("%s%s",id,course);
		p1=head;
		while (p1!=NULL)
		{
			if (!strcmp(p1->ID,id)) break;
			p1=p1->next;
		}
		switch (course[0])
		{
			case 'E':scanf("%f",&p1->English);break;
			case 'M':scanf("%f",&p1->Math);break;
			case 'P':scanf("%f",&p1->Physics);break;
			case 'C':scanf("%f",&p1->C);break;
			default:break;
		}
		p1->SUM=p1->English+p1->Math+p1->Physics+p1->C;
		p1->AVG=p1->SUM/4;
	}
	printf("Alter:\n");
}
int cmp(Stu *x,Stu *y)
{
	return x->AVG>y->AVG;
}
void isort(Stu **head)
{
	Stu *p1,*p2,*p1_pre,*tail=NULL;
	while (tail!=*head)
	{
	     p1_pre=NULL;
	     for (p1=*head;p1->next!=tail;p1_pre=p1,p1=p1->next)
	     {
	     	if (cmp(p1,p1->next))
	     	{
	     		if (p1_pre==NULL) *head=p1->next;
				swap2(&p1_pre,p1,p1->next);
				p1=p1_pre;
			}
		 }
		 tail=p1;
    }
}
void swap1(Stu *x,Stu *y)
{
	Stu temp;
	temp=*x;
	*x=*y;
	x->next=temp.next;
	temp.next=y->next;
	*y=temp;
}
void swap2(Stu **x_pre,Stu *x,Stu *y)
{
	Stu *t;
	if (*x_pre==NULL)
	{
		x->next=y->next;
		y->next=x;
	}
	else 
	{
	    t=y->next;
		y->next=x;
		x->next=t;
		(*x_pre)->next=y;
    }
    *x_pre=y;
}
void output1(Stu *head)
{
	Stu *p=head;
    printf("ID             Name                English   Math      Physics   C         \n");
	while (p!=NULL)
	{
	    printf("%-15s%-20s%-10.2f%-10.2f%-10.2f%-10.2f\n",
	         p->ID,p->Name,p->English,p->Math,p->Physics,p->C); 
	    p=p->next;
	} 
	printf("\n");
}
void output2(Stu *head)
{
	Stu *p=head;
    printf("SumAndAvg:\nID             Name                SUM       AVG       \n");
	while (p!=NULL)
	{
	    printf("%-15s%-20s%-10.2f%-10.2f\n",
	         p->ID,p->Name,p->SUM,p->AVG); 
	    p=p->next;
	} 
	printf("\n");
}
void output3(Stu *head)
{
	Stu *p=head;
    printf("Sort:\nID             Name                AVG       \n");
	while (p!=NULL)
	{
	    printf("%-15s%-20s%-10.2f\n",
	         p->ID,p->Name,p->AVG); 
	    p=p->next;
	} 
	printf("\n");
}

