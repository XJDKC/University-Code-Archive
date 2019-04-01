#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
	pid_t pid;
	char wInfo[20];
	char rInfo[20];
	int fd=open("/dev/XRL_Module",O_RDWR|O_NONBLOCK);
	if (fd!=-1)
	{
		printf("input the info you want to write into the device:");
		scanf("%[^\n]",wInfo);
		write(fd,wInfo,sizeof(wInfo));
		printf("write info: %s\n",wInfo);
		
		read(fd,rInfo,sizeof(rInfo));
		printf("read info: %s\n",rInfo);
		close(fd);
	}
	else
	{
		printf("fail to open the device!\n");
	}
}
