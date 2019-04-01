#include<stdio.h>
void main(void)
{
    int i,n,s=1;
    printf("Please enter n:");
    scanf("%d",&n);
    i=n;
    while(i)
    {
        s*=i;
        i--;
    }
    printf("%d! = %d\n",n,s);
}
