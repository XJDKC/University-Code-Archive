#include<stdio.h>
#define Swap(x,y) x=x+y,y=x-y,x=x-y
int main()
{
    int i=1,x,y;
    while (scanf("%d%d",&x,&y)!=EOF)
    {
        printf("Case %d:\nBefore Swap:a=%d b=%d\n",i,x,y);
        Swap(x,y);
        printf("After Swap:a=%d b=%d\n\n",x,y);
        i++; 
	}
	return 0;
} 
