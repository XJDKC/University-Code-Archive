#include<stdio.h>
typedef struct date
{
	int year;
	int month;
	int day;
}Date;
Date data;
int num[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
int main()
{
	int n,i;
	scanf("%d",&n);
	while (n--)
	{
		scanf("%d%d%d",&data.year,&data.month,&data.day);
		for (i=1;i<data.month;i++)
		data.day+=num[i];
		if (data.month>2&&!(data.year%4)&&data.year%100||!(data.year%400))
		data.day++;
		printf("%d\n",data.day);
	}
	return 0;
}
