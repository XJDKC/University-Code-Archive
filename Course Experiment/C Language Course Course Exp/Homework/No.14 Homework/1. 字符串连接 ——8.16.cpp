#include<stdio.h>
int main()
{
	int n,i,j;
	char f[106][1006],*pos;
	while (scanf("%d",&n)&&n)
	{
		getchar(); 
		for (i=0;i<n;i++)
		fgets(f[i],1000,stdin);
        pos=f[0];
		while (*pos!='\n') pos++;
		pos--;
		for (i=1;i<n;i++)
			for (j=0;f[i][j]!='\n';j++)
			    *(++pos)=f[i][j];
		*(++pos)='\0';
		printf("%s\n",f[0]); 
	}
	return 0;
}
