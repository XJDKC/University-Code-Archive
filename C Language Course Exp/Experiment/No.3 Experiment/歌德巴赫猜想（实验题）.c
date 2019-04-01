#include<stdio.h>
#include<math.h> 
int isprime(int x); 
int main()
{
	int begin,end,i;
	while (scanf("%d%d",&begin,&end)&&begin!=0)
	{
		printf("GOLDBACH'S CONJECTURE:\n"
               "Every even number n>=4 is "
			   "the sum of two primes.\n");
		for (;begin<=end;begin++)
		{
			if (begin%2==0)
			{
				for (i=2;i<=begin;i++)
				if (isprime(i)&&isprime(begin-i))
				{
					printf("%d=%d+%d\n",begin,i,begin-i);
				    break;
				}
			} 
		}
		printf("\n");
	}
	return 0;
} 
int isprime(int x)
{
	if (x==1) return 0;
	else if (x==2) return 1;
	else {
		int temp=sqrt(x),i;
		for (i=2;i<=temp+1;i++)
		if (x%i==0) return 0;
		return 1;
	}
}
