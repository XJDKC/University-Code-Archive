#include<stdio.h>
int main()
{
    char c;
	scanf("%c",&c);
	if (c-'A'>=0&&c-'A'<26) c+=32;//����Ǵ�д ��ô+32 32Ϊa��ascll����A�Ĳ�ֵ 
	printf("%c\n",c);
	return 0;	
} 
