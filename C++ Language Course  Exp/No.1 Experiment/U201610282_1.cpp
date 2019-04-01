#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define true 1
#define false 0
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
struct STACK
{
    int *elems;
    int max;
    int pos;
};
int ERROR = false;
void initSTACK(STACK *const p,int m);               //初s始化p指向的栈：最多m个元素
void initSTACK(STACK *const p,const STACK &s);      //用s初始化p指向的栈
int size(const STACK *const p);                     //返回p指向的栈的最大元素个数max
int howMany(const STACK *const p);	                //返回p指向的栈的实际元素个数pos
int getelem(const STACK *const p, int x);	        //取下标x处的栈元素
STACK *const push(STACK *const p, int e); 	        //将e入栈，并返回p
STACK *const pop(STACK *const p, int &e); 	        //出栈到e，并返回p
STACK *const assign(STACK *const p, const STACK &s);//赋s给p指的栈,并返回p
void print(const STACK *const p);			        //打印p指向的栈
void destroySTACK(STACK *const p);		            //销毁p指向的栈

int main(int argc,char **argv)
{
    char curState=0;
    int num = 0,e=0;
    STACK *p=NULL;
    STACK *s=NULL;
    for (int i = 1;i<=argc&&argc!=1;i++)
    {
        if (i==argc||argv[i][0]=='-')
        {
            switch(curState)
            {
                case 0:break;
                case 'I':
                case 'O':
                case 'C':
                case 'A':if (howMany(p)!=0)
                             printf("  ");
                         print(p);break;
                case 'S':printf("  %d",size(p));break;
                case 'N':printf("  %d",howMany(p));break;
                case 'G':break;
                default:ERROR=true;
            }
            if (i!=argc)
            {
                curState = toupper(argv[i][1]);
                if (curState!='S')
                    printf("  ");
                printf("%c", curState);
            }
        }
        else if (!ERROR && (argv[i][0]!='-'||curState=='C'))
        {
            num = atoi(argv[i]);
            switch(curState)
            {
                case 'S':p=(STACK *)malloc(sizeof(STACK));
						 if (p == NULL)
							 ERROR = true;
						 else
	                         initSTACK(p, num);
						 break;
                case 'I':if (howMany(p)<size(p))
                            push(p, num);
                         else
                            ERROR = true;
                         break;
                case 'O':while (num--)
                        {
                            if (howMany(p)>0)
                                pop(p,e);
                            else
                            {
                                ERROR = true; 
                                break;
                            }                           
                        }
                        break;
                case 'C':s=(STACK *)malloc(sizeof(STACK));
						 if (s == NULL)
							 ERROR = true;
						 else
							initSTACK(s,*p);
                         break;
                case 'A':s=(STACK *)malloc(sizeof(STACK));
						 if (s == NULL)
							ERROR = true;
						 else
						 {
							 initSTACK(s, num);
							 assign(s, *p);
						 }
                         break;
                case 'N':printf("%d",howMany(p));break;
                case 'G':if (0<=num&&num<howMany(p))
                            printf("  %d", getelem(p, num));
                         else
                             ERROR = true;
                         break;
                default:ERROR=true;
            }    
        }
        if (ERROR)
            break;
        else if (s!=NULL)
        {
            destroySTACK(p);
            free(p);
            p = s;
            s = NULL;
        }
    }
    if (ERROR)
        printf("  E\n");
    else if (p)
    {
        destroySTACK(p);
        free(p);
    }
    return 0;
}

void initSTACK(STACK *const p,int m)
{
    p->pos = 0;
    p->max = m;
    p->elems = (int *)malloc(sizeof(int)*m);
	if (p->elems == NULL)
		ERROR = true;
}

void initSTACK(STACK *const p,const STACK &s)
{
    p->pos = s.pos;
	p->max = s.max;
	p->elems = (int *)malloc(sizeof(int)*p->max);
	if (p->elems == NULL)
	{
		ERROR = true;
		return;
	}
    for (int i=0;i<p->pos;i++)
        p->elems[i]=s.elems[i];
}

int size(const STACK *const p)
{
    return p->max;
}

int howMany(const STACK *const p)
{
    return p->pos;
}

int getelem(const STACK *const p, int x)
{
    if (0<=x&&x<p->pos)
        return p->elems[x];
    else
        return 0;
}

STACK *const push(STACK *const p, int e)
{
    if (p->pos<p->max)
        p->elems[p->pos++]=e;
    return p;
}

STACK *const pop(STACK *const p, int &e)
{
    if (p->pos)
        e = p->elems[--p->pos];
    return p;
}

STACK *const assign(STACK *const p, const STACK &s)
{
    destroySTACK(p);
    initSTACK(p, s);
    return p;
}

void print(const STACK *const p)
{
    for (int i = 0; i<p->pos;i++)
    {
        printf("%d",p->elems[i]);
        if (i<p->pos-1)
            printf("  ");
    }
}

void destroySTACK(STACK *const p)
{
    if (p->elems!=NULL)
        free(p->elems);
    p->max = 0;
    p->pos = 0;
}