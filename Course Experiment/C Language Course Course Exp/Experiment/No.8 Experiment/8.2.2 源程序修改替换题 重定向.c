#include<stdio.h>
#include<stdlib.h>
int main(int argc, char* argv[])
{
	char ch;
	FILE *fp;
	printf("%d\n",argc);
	if(argc!=3){
		printf("%d\n",argc);
		printf("%d\nArguments error!\n",argc);
		exit(-1);
	}
	if((fp=fopen(argv[2],"r"))==NULL){        /* fp ָ�� filename */
    	printf("Can't open %s file!\n",argv[2]);
		exit(-1);
	}
	freopen(argv[2],"r",stdin); 
	while((ch=getchar())!=EOF)          /* ��filename�ж��ַ� */
	putchar(ch);                  /* ����ʾ����д�ַ� */
	system("pause");
    return 0;	
}

