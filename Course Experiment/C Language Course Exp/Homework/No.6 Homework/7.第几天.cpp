#include<stdio.h>
int main()
{
	int y,m,d,i,ans=0,n;
	int count[15]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	scanf("%d",&n);
	for (i=2;i<=12;i++)
	count[i]+=count[i-1];
	while (n--)
	{
	    scanf("%d%d%d",&y,&m,&d);
		ans=0;
		if ((y%4==0&&y%100|y%400==0)&&m>2) ans++;
		ans+=count[m-1]+d;
		printf("%d\n",ans);
	}
	return 0;
}
