#include<stdio.h>
int no;
void hailstone(int n);
int main()
{
    int n;
	while (scanf("%d",&n)&&n)
	{
		no=0;
	    hailstone(n);	
	}	
	return 0;
} 
void hailstone(int n)
{
	if (n==1) 
	{
		printf("    1\n\n");
	}
	else 
	{
		printf("%5d",n);
		no++;
		if (!(no%6)) printf("\n");
		if (n&1) hailstone(3*n+1);
		else hailstone(n/2); 
	}
}
