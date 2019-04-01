#include<stdio.h>

int ans=1,num=1,n;
int p[12]={1,2,3,5,7,11,13,17,19,23,29,31};

void ISS(int k,int now,int cnt,int last)
{
	if(k==12)
	{
		if(ans<=now&&num<=cnt)
		{
			ans=now;
			num=cnt;
		}
		if(ans>=now&&num>=cnt)
		{
			ans=now;
			num=cnt;
		}
	}
	else
	{
		
	}
 } 


int main()
{
	scanf("%d",&n);
	ISS(1,1,1,31);
	printf("%d",ans);
 } 
