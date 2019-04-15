#include<stdio.h>
int main()
{
	int y,m,d,i,ans=0;
	int count[15]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	for (i=2;i<=12;i++)
	count[i]+=count[i-1];
	while (scanf("%d%d%d",&y,&m,&d)!=EOF)
	{
		ans=0;
		if ((y%4==0&&y%100|y%400==0)&&m>2) ans++;
		ans+=count[m-1]+d;
		printf("该日期是这一年中的第%d天\n",ans);
	}
	return 0;
}
