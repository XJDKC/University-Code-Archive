#include<stdio.h>
#include<string.h>
int main()
{
	int a[16]={0},i;
	char c[1006];
	while (scanf("%[^\n]",c))
	{
		getchar();
		for(i=0;i<strlen(c);i++)
		if(c[i]>='0'&&c[i]<='9')
		a[c[i]-'0']++;
		else if (c[i]>='A'&&c[i]<='Z'
		         ||c[i]>='a'&&c[i]<='z')
		a[10]++;
		else a[11]++;
		a[11]++;
		if (c[i-1]=='#') break;
	}
	for (i=0;i<=9;i++)
	printf("Number %d: %d\n",i,a[i]);
	printf("characters: %d\n",a[10]);
	printf("other: %d\n",a[11]-2);
	return 0;
}
