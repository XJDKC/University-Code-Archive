#include<stdio.h>

int t[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};
int f[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
int year(int a)
{
	if(a%4==0&&a%100!=0||a%400==0) return 1;
	else return 0; 
}
int main()
{
	int a,b,c,i,j,temp=0,ti,T=10000;
	scanf("%d %d %d",&a,&b,&c);
	if(year(a)) 
	{
		for(i=1;i<b;i++)
		{
		temp+=t[i];	
		}
		temp+=c;
		temp=366-temp;
	    T-=temp;
	}
	else
	{
	for(i=1;i<b;i++)
		{
		temp+=f[i];	
		}
		temp+=c;
		temp=365-temp;
	    T-=temp;
	}
	while(1)
	{
		if(year(a+1)) T-=366;
		else T-=365;
		a++;
		if(T<=0) break;
	}
	if(year(a)) 
	{
	T+=366;
	   for(i=1;T>0;i++) 
	   {
	     	T-=t[i];
	   }
	   b=i-1;
	   c=T+t[i-1];
    }
	else 
	{
	    T+=365;
	    for(i=1;T>0;i++) 
	    {
	     	T-=f[i];
	    }
	    b=i-1;
	    c=T+f[i-1];
    }
    printf("%d-%d-%d\n",a,b,c);
    return 0;
}
