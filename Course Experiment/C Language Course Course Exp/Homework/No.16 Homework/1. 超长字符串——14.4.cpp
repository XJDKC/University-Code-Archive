#include<stdio.h>
#include<stdlib.h>
struct node
{
	char c;
	struct node *next;
};
struct node *tail_create(struct node **head);
void print(struct node *head);
char *create_arr(struct node *head);
int main()
{
  struct node *head=NULL;
  char *ans;
  head=tail_create(&head);
  print(head);
  ans=create_arr(head);
  printf("%s\n",ans);
  return 0;
}
struct node *tail_create(struct node **head)
{
	char cc;
	struct node *p1,*p2;
	p1=(struct node *)malloc(sizeof(struct node)); 
	while (scanf("%c",&cc)!=EOF)
	{
		if (*head==NULL) 
		{
		    p1->c=cc;
			p1->next=NULL;
			*head=p1;
		} 
		else 
		{
		    p2=(struct node *)malloc(sizeof(struct node));
		    p2->c=cc;   p1->next=p2;  p2->next=NULL;
		    p1=p2;
	    }
	}
	return *head;
}
void print(struct node *head)
{
	while (head!=NULL)
	{
	    printf("%c",head->c);
		head=head->next;	
	} 
	printf("\n");
}
char *create_arr(struct node *head)
{
	int num=0,i=0;
	char *arr,*pc;
	struct node *p=head;
	while (p!=NULL)
	{
	    num++;
		p=p->next;	
	}
	arr=(char *)malloc(sizeof(char)*(num+1));
	p=head;
	pc=arr;
	while (p!=NULL)
	{
		*pc=p->c;
		p=p->next;
		pc++;
	}
	*pc='\0';
	return arr;
}
