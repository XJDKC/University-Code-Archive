#include<stdio.h>
enum mouth{
	jan=1,feb,mar,apr,may,jun,jul,aug,sept,oct,nov,dec
}mm;
int main()
{
	int year,i;
	scanf("%d",&year);
	for (i=1;i<=12;i++)
	{
		switch(i)
		{
			case jan:printf("January,31\n");break;
			case feb:if (!(year%4)&&year%100||!(year%400))
			            printf("February,29\n");
					 else printf("February,28\n");break;
			case mar:printf("March,31\n");break; 
			case apr:printf("April,30\n");break;
			case may:printf("May,31\n");break;
			case jun:printf("June,30\n");break;
			case jul:printf("July,31\n");break;
			case aug:printf("August,31\n");break;
			case sept:printf("September,30\n");break;
			case oct:printf("October,31\n");break;
			case nov:printf("November,30\n");break;
			case dec:printf("December,31\n");break;
			default:break;
			
		}
	}
	return 0;
}
