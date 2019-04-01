#include<stdio.h>
void jiami();
void jiemi();
int main()
{
//	freopen("A.txt","r",stdin);
//	freopen("B.txt","w",stdout);
//    jiami();
    freopen("B.txt","r",stdin); 
    freopen("C.txt","w",stdout); 
	jiemi();	
    return 0;
}
void jiami()
{
	int c;
	while (scanf("%c",&c)!=EOF)
	{
		if (c>='a'&&c<='z')
		{
		    c=(c-'a')+788;
		    c=c%26+'a';
		    putchar(c);
	    }
	    else if (c>='A'&&c<='Z') 
	    {
	    	c=(c-'A')+788;
	    	c=c%26+'A';
	    	putchar(c);
		}
	}
}
void jiemi()
{
	int c,d;
	while (scanf("%c",&c)!=EOF)
	{
		if (c>='a'&&c<='z')
		{
		    c=c-'a';
		    c=(c+26-8)%26;
		    putchar(c+'a');
	    }
	    else if (c>='A'&&c<='Z') 
	    {
	    	c=c-'A';
	    	c=(c+26-8)%26;
	    	putchar(c+'A');
		}
	}
}
