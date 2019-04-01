#include "stdio.h"
long sum_fac(int n);
int main(void)
{
    int k;
    for(k=1;k<6;k++)
         printf("k=%d\tthe sum is %ld\n",k,sum_fac(k));
    return 0;
}
long sum_fac(int n)
{
    long s=0;
    int i;
	long fac=1;
	for(i=1;i<=n;i++)
	{   
	    fac*=i;
	    s+=fac;
    }
	return s;
}

