#include<stdio.h>
#define Swap(x,y) x=x+y,y=x-y,x=x-y
int main()
{
    int n,x,y;
    scanf("%d",&n);
    while (n--)
    {
    	scanf("%d%d",&x,&y); 
        Swap(x,y);
        printf("%d %d\n",x,y);
	}
	return 0;
} 
