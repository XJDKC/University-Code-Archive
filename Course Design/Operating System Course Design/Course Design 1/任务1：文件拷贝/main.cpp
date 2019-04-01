#include<stdio.h>
#include<stdlib.h>
int main(int argc,char **argv)
{
    char *data;
    unsigned int size=0;
    FILE *inFile,*outFile;
    getchar();
    if (argc<3)
        printf("Too fewer arguments!");
    else
    {
        inFile=fopen(argv[1],"r");
        if (inFile==NULL) {
            printf("Cannot find the source file!");
            return -1;
        }
        else{
            fseek(inFile,0,SEEK_END);
            size=(unsigned int)ftell(inFile);
            fseek(inFile,0,SEEK_SET);

            data=(char *)malloc(sizeof(char)*size);
            if (data==NULL)
            {
                printf("Allocating memory error!");
                return -1;
            }

            fread(data,sizeof(char),size,inFile);
            outFile=fopen(argv[2],"w");
            fwrite(data,sizeof(char),size,outFile);

            fclose(inFile);
            fclose(outFile);

            printf("Copy successfully!");
        }
    }
    getchar();
    return 0;
}