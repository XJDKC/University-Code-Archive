#include<stdio.h>
int main()
{
	int t,temp,i;
	unsigned int x;                             //注意无符号 
	scanf("%d",&t);
	while (t--)
	{
		scanf("%u",&x);
	    for (i=1;i<=4;i++)
	    {
	    	temp=x%0x100;                        //对0x100取余得到最低的八位 
	    	x>>=8;                               //将x右移八位 
			if (i!=4) printf("%d.",temp);        //判断是否要加. 
			else printf("%d\n",temp);            //否则最后面输出换行 
		}
	}
	return 0;
}
