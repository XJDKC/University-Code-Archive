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
	if((fp=fopen(argv[2],"r"))==NULL){        /* fp 指向 filename */
    	printf("Can't open %s file!\n",argv[2]);
		exit(-1);
	}
	freopen(argv[2],"r",stdin); 
	while((ch=getchar())!=EOF)          /* 从filename中读字符 */
	putchar(ch);                  /* 向显示器中写字符 */
	system("pause");
    return 0;	
}

