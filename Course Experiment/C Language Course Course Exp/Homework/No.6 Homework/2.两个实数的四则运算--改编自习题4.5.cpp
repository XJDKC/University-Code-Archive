#include<stdio.h>
void swhprocess(double x,double y,char c)
{
	printf("After switch processing,the result is : ");
	switch(c)
	{
		case '+':printf("%.2lf\n",x+y);break;
		case '-':printf("%.2lf\n",x-y);break;
		case '/':printf("%.2lf\n",x/y);break;
		case '*':printf("%.2lf\n",x*y);break;
		default:break;
	}
}
void ieprocess(double x,double y,char c)
{
	printf("After if-else processing,the result is : ");
	if (c=='+')     printf("%.2lf\n",x+y);
    else if(c=='-') printf("%.2lf\n",x-y);
    else if(c=='/') printf("%.2lf\n",x/y);
	else            printf("%.2lf\n",x*y);
}
int main()
{
	int a,no=0;
	float x,y;
	char c;
	while (scanf("%d %f %f %c",&a,&x,&y,&c)!=EOF)
	{
		if (no==0) no=1;
		else printf("\n");
		if (a==1) swhprocess(x,y,c);
		if (a==0) ieprocess(x,y,c);
		if (a==2) {
			ieprocess(x,y,c);
			swhprocess(x,y,c);
		} 
	} 
	printf("\n");//修改后多加了一行 
	return 0;
}
