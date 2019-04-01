#include<stdio.h>
#include<stdlib.h>
#define N 10005 
typedef struct node
{
	int data;
	struct node *next; 
}Point;
Point *stack[N]={NULL};
Point *create_tail(int n);
Point *reverse(Point **head);
void output(Point *head); 
int main()
{
	int n;
	Point *head;
	scanf("%d",&n);
	head=create_tail(n);
	output(head);
	head=reverse(&head);
	output(head);
	return 0;
}
Point *create_tail(int n)
{
	int i;
	Point *head=NULL,*p1=NULL,*p2;
	for (i=0;i<n;i++)
	{
		if (!i)
		{
		    p1=(Point *)malloc(sizeof(Point));
			scanf("%d",&p1->data);
			head=p1;
		}
		else 
		{
			p2=(Point *)malloc(sizeof(Point));
			scanf("%d",&p2->data);
			p1->next=p2;
			p1=p2;
		}
	}
	if (p1!=NULL) p1->next=NULL;
	return head;
}
void output(Point *head)
{
	Point *p=head;
	while (p!=NULL)
	{
		printf("%d",p->data);
		if (p->next!=NULL) printf(" ");
		else printf("\n");
		p=p->next;
	}
}
Point *reverse(Point **head)
{
	int top=0;
	Point *p=*head,*p1=NULL,*p2;
	while (p!=NULL)
	{
		stack[top++]=p;
		p=p->next;
	}
	top=top==0?0:top-1;
	while (top>=0)
	{
	     if (p1==NULL)
		 {
		 	p1=stack[top--];
			*head=p1;
		 	if (top>=0) 
			{
			    p2=stack[top--];
		 	    p1->next=p2;
			    p1=p2;
		 	}
		 }
		 else 
		 {
		 	p2=stack[top--];
		 	p1->next=p2;
		 	p1=p2;
		 }
	}
	if (p1!=NULL) p1->next=NULL;
	return *head;
}
