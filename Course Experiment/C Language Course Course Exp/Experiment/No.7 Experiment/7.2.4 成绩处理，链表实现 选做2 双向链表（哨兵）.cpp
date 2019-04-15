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
	struct stu *last;
	struct stu *next;
}Stu;
void create(Stu **head,int n);
void change(Stu *head,int m);
int comp(Stu *x,Stu *y);
void isort(Stu **head);
void swap1(Stu *x,Stu *y);
void swap3(Stu *x,Stu *y);
void output1(Stu *head);
void output2(Stu *head);
void output3(Stu *head);
int main()
{
	int n,i,m;
	Stu *head=NULL;
	scanf("%d",&n);
	create(&head,n);
	output1(head);
	scanf("%d",&m);
	change(head,m);
	output1(head);
	output2(head);
	isort(&head);
	output3(head);
	return 0;
}
void create(Stu **head,int n)
{
	int i;
	Stu *p1,*p2;
	*head=(Stu *)malloc(sizeof(Stu));
	p1=*head;
	p1->last=NULL;
	for (i=0;i<n;i++)
	{
			p2=(Stu *)malloc(sizeof(Stu));
			scanf("%s%s%f%f%f%f",p2->ID,p2->Name,&p2->English,&p2->Math,&p2->Physics,&p2->C);
			p2->SUM=p2->English+p2->Math+p2->Physics+p2->C;
			p2->AVG=p2->SUM/4;
			p1->next=p2;
			p2->last=p1;
			p2->next=NULL;
			p1=p2;
	}
	p1->next=(Stu *)malloc(sizeof(Stu));
	p1->next->last=p1;
	p1->next->next=NULL;
	*head=(*head)->next; 
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
	Stu *p1,*p2,*p3;
	for (p1=*head;p1->next!=NULL;p1=p1->next)
	{
	    for (p3=p1,p2=p1->next;p2->next!=NULL;p2=p2->next)
	        if (cmp(p3,p2))
               p3=p2;
	    if (p1!=p3) 
		{
		   if (p1==*head) *head=p3; 
		   swap3(p1,p3);
		   p1=p3;
	    }
	}
}
void swap1(Stu *x,Stu *y)//����ָ���� 
{
	Stu temp;
	temp=*x;             //temp���x�ڵ�������Ϣ 
	*x=*y;               //��y��ֵ��x�ڵ�  ��ʱx�ڵ�ָ�����y��Χ�ڵ� 
	x->next=temp.next;   //��x�ڵ�ԭ����ָ������������������ֻ��һ����ֵ�� 
	temp.next=y->next;   //��temp��װ����ȷ��y�ڵ�λ�õĽڵ� 
	*y=temp;            
}
void swap3(Stu *x,Stu *y)//��������Ԫ�������� 
{
	Stu *t;
	if (x->next!=y)       //������߲����� 
	{
	    x->last->next=y;  //����������Χ�ڵ��ָ���� 
	    x->next->last=y;  //����Χ�ڵ�ָ����ȷ��λ�� 
	    y->last->next=x;
	    y->next->last=x;
	    
	    t=x->last;        //��x��y�ڵ�ָ����ָ����ȷ�Ľڵ� 
	    x->last=y->last;  //����x��ָ���򱻸�ֵ��y��ָ���������xָ����ָ�����Ķ�ʧ 
		y->last=t;        //����Ҫ�ȱ������� 
		
		t=x->next;        //ͬ�� 
		x->next=y->next;
		y->next=t;
	 
    }
    else                  //����������� 
    {
    	x->last->next=y;  //��ô����xǰһ���ڵ�ĺ�һ���ڵ��Ϊy  
        y->next->last=x;  //��y��һ���ڵ��ǰһ���ڵ���x 
        x->next=y->next;  //x����һ�����y����һ�� 
        y->last=x->last;  //y��ǰһ�����x��ǰһ�� 
        x->last=y;        //x��ǰһ�����y 
        y->next=x;        //y�ĺ�һ�����x 
	}
}
void output1(Stu *head)
{
	Stu *p=head;
    printf("ID             Name                English   Math      Physics   C         \n");
	while (p->next!=NULL)
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
	while (p->next!=NULL)
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
	while (p->next!=NULL)
	{
	    printf("%-15s%-20s%-10.2f\n",
	         p->ID,p->Name,p->AVG); 
	    p=p->next;
	} 
	printf("\n");
}

