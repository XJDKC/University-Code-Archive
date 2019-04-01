#include<stdio.h>
int irandom(int x);
int main()
{
	int n,a,b,no,sum,temp;
	scanf("%d",&n);
	while (n--)
	{
		scanf("%d%d",&a,&b);
		for (no=1;;no++)
	    {
		   sum=0;
		   if (no==1)
	       {
		      sum=irandom(a+no-1)+irandom(b+no-1);
		      if (sum==7||sum==11) 
			  {
		         printf("success!\n");
		         break;
		      }
		      else if (sum==2||sum==3||sum==12)
			  {
		         printf("fail!\n");
		         break;  
			  }
			  else temp=sum;
	       }
	       else 
		   {
	       	  sum=irandom(a+no-1)+irandom(b+no-1);
	       	  if (sum==temp) 
			  {
			  	printf("success!\n");
			  	break;
	       	  } 
	       	  else if (sum==7)
	       	  {
	       	  	 printf("fail!\n");
		         break; 
	       	  }
	       }
	   }
	} 
	return 0;
} 
int irandom(int x)
{
	int cal=0;
	while (x)
	{
		cal+=x%10;
		x/=10;
	}
	return cal%6+1;
} 
