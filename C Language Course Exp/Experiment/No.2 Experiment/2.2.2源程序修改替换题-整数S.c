#include<stdio.h>
void main(void)
{
    int n=0,s=1,S;
    printf("Please enter S:");
    scanf("%d",&S);
    while(s<S)
        s*=++n;
    printf("����n����S����С����n=%d\n",n);
}
