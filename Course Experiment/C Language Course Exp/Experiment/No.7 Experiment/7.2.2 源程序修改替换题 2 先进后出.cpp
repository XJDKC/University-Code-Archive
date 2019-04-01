#include "stdio.h"
#include "stdlib.h"
struct s_list{ 
    int data;            /* ������ */
    struct s_list *next; /* ָ���� */ 
} ;
struct s_list *create_list (struct s_list **headp,int *p);
int main()
{
	struct s_list *head=NULL,*p;
	int s[]={1,2,3,4,5,6,7,8,0}; /* 0Ϊ������� */
	create_list(&head,s); /* ���������� */
	p=head; /*����ָ��pָ����ͷ */
	while(p){
		printf("%d\t",p->data); /* ����������ֵ */
		p=p->next; /*����ָ��pָ����һ��� */
	}
	printf("\n");
	return 0; 
}
struct s_list *create_list (struct s_list **headp,int *p)
{
	struct s_list * loc_head=NULL,*tail;
	if(p[0]==0) /* �൱��*p==0 */
		;
	else { /* loc_headָ��̬����ĵ�һ����� */
		tail=(struct s_list *)malloc(sizeof(struct s_list));
		tail->data=*p++; /* ��������ֵ */
		loc_head=tail; /* tailָ���һ����� */
		loc_head->next=NULL; 
		while(*p){ /* tail��ָ����ָ����ָ��̬�����Ľ�� */
			tail=(struct s_list *)malloc(sizeof(struct s_list));
			tail->data=*p++; /* ���´����Ľ���������ֵ */
			tail->next=loc_head;
			loc_head=tail;
		}
	}
	*headp=loc_head; /* ʹͷָ��headpָ���´��������� */
	return *headp; 
}

