#include<stdio.h>
int main()
{
    int x,y,m,n,temp;
	while (scanf("%d%d",&x,&y)&&x&&y)
	{
	    if (x>y) m=x,n=y;
	    else m=y,n=x;
	    while (n)
	    {
	        temp=m%n;
	        m=n;
	        n=temp;
		}
		n=x*y/m;
		printf("%d %d\n",m,n);
	}	
	return 0;
} 
