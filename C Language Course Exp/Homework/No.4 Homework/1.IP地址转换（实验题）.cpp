#include<stdio.h>
int main()
{
	int t,temp,i;
	unsigned int x;                             //ע���޷��� 
	scanf("%d",&t);
	while (t--)
	{
		scanf("%u",&x);
	    for (i=1;i<=4;i++)
	    {
	    	temp=x%0x100;                        //��0x100ȡ��õ���͵İ�λ 
	    	x>>=8;                               //��x���ư�λ 
			if (i!=4) printf("%d.",temp);        //�ж��Ƿ�Ҫ��. 
			else printf("%d\n",temp);            //���������������� 
		}
	}
	return 0;
}
