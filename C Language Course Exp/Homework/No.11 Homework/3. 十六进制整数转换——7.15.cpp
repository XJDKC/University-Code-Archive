#include<stdio.h>
#include<string.h>
int main()
{
	int n,i,ans,temp;
	char c[1006];
	scanf("%d",&n);
	while (n--)
	{
		scanf("%s",c);
		for (ans=0,i=strlen(c)-1,temp=1;i>=2;i--)
		{
			if (c[i]>='0'&&c[i]<='9')
		    ans+=(c[i]-'0')*temp;
			else if (c[i]>='A'&&c[i]<='Z')
			ans+=(c[i]-'A'+10)*temp;
			else ans+=(c[i]-'a'+10)*temp;
			temp*=16;
		}
		printf("%d\n",ans);
	}
	return 0;
}
