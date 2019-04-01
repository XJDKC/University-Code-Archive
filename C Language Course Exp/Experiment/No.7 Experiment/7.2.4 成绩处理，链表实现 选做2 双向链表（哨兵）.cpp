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
void swap1(Stu *x,Stu *y)//交换指针域 
{
	Stu temp;
	temp=*x;             //temp存放x节点所有信息 
	*x=*y;               //将y赋值给x节点  此时x节点指向的是y周围节点 
	x->next=temp.next;   //将x节点原来的指针域变回来（单向链表只用一个赋值） 
	temp.next=y->next;   //将temp改装成正确的y节点位置的节点 
	*y=temp;            
}
void swap3(Stu *x,Stu *y)//交换两个元素数据域 
{
	Stu *t;
	if (x->next!=y)       //如果两者不相邻 
	{
	    x->last->next=y;  //交换两者周围节点的指针域 
	    x->next->last=y;  //让周围节点指向正确的位置 
	    y->last->next=x;
	    y->next->last=x;
	    
	    t=x->last;        //让x，y节点指针域指向正确的节点 
	    x->last=y->last;  //由于x的指针域被赋值成y的指针域后会造成x指针域指向对象的丢失 
		y->last=t;        //所以要先保存起来 
		
		t=x->next;        //同理 
		x->next=y->next;
		y->next=t;
	 
    }
    else                  //如果两者相邻 
    {
    	x->last->next=y;  //那么就让x前一个节点的后一个节点变为y  
        y->next->last=x;  //让y后一个节点的前一个节点变成x 
        x->next=y->next;  //x的下一个变成y的下一个 
        y->last=x->last;  //y的前一个变成x的前一个 
        x->last=y;        //x的前一个变成y 
        y->next=x;        //y的后一个变成x 
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

