#include "file2.c"
#include <stdio.h>
int x,y; /* �ⲿ�����Ķ�����˵�� */
char ch; /* �ⲿ�����Ķ�����˵�� */
void main(void)
{
    x=10;
    y=20;
    ch=getchar();
    printf("in file1 x=%d,y=%d,ch is %c\n",x,y,ch);
    func1();
}
