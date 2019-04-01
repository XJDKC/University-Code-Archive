#include<stdio.h>
int divisor(int x,int y);
int main()
{
    int x,y;
	while (scanf("%d%d",&x,&y)&&x!=0)
	printf("%d\n",divisor(x,y));
	return 0;	
} 
int divisor(int x,int y)
{
	if (y==0)
	{
		return x;
	}
	else 
	{
		int z;
		z=x%y;
		return divisor(y,z);
	}
}
