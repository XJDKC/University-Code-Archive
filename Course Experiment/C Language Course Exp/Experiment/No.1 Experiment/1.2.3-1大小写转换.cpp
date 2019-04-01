#include<stdio.h>
int main()
{
    char c;
	scanf("%c",&c);
	if (c-'A'>=0&&c-'A'<26) c+=32;//如果是大写 那么+32 32为a的ascll码与A的差值 
	printf("%c\n",c);
	return 0;	
} 
