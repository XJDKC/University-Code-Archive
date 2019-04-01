#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>

int pipefd[2];
pid_t p1,p2;


void signalProcess(int sig_no)
{
    if (sig_no==SIGINT)
    {
        printf("Parent Process Receives SIGINT!\n");
        kill(p1,SIGUSR1);
        kill(p2,SIGUSR2);
    }
}

void signalProcess1(int sig_no)
{
    if (sig_no==SIGINT)
    {
        printf("Child Process 1 discards SIGINT1!\n");
    }
    if (sig_no==SIGUSR1)
    {
        printf("Child Process 1 is Killed by Parent!\n");
        exit(0);
    }
}

void signalProcess2(int sig_no)
{
    if (sig_no==SIGINT)
    {
        printf("Child Process 1 discards SIGINT2!\n");
    }
    if (sig_no==SIGUSR2)
    {
        printf("Child Process 2 is Killed by Parent!\n");
        exit(0);
    }
}

void childProcess1()
{
    if (signal(SIGINT,signalProcess1)==SIG_ERR)
        printf("ChildProcess 1:Can't not catch SIGINT!\n");
    if (signal(SIGUSR1,signalProcess1)==SIG_ERR)
        printf("ChildProcess 1:Can't not catch SIGUSR1\n");

    int count=1;
    char buf[30];
    while (1)
    {
        close(pipefd[0]);
        sprintf(buf,"I send you %d times!",count);
        buf[strlen(buf)]='\0';
        write(pipefd[1],buf,strlen(buf));
        ++count;
        sleep(1);
    }
}

void childProcess2()
{
    if (signal(SIGINT,signalProcess2)==SIG_ERR)
        printf("ChildProcess 2:Can't not catch SIGINT!\n");
    if (signal(SIGUSR2,signalProcess2)==SIG_ERR)
        printf("ChildProcess 2:Can't not catch SIGUSR2\n");

    int length;
    char buf[30];
    while (1)
    {
        close(pipefd[1]);
        length=read(pipefd[0],buf,30);
        buf[length]='\0';
        printf("Child Process 2 Receives:%s\n",buf);
        sleep(1);
    }
}

int main()
{
    int status1,status2;

    //Create Pipe!
    pipe(pipefd);

    //Set signal processing function!
    if (signal(SIGINT,signalProcess)==SIG_ERR)
        printf("Can't not catch SIGINT!\n");

    //Create the first process!
    p1=fork();
    if (p1==0)
    {
        printf("Sub1 created!\n");
        childProcess1();
    }

    //Create the second process!
    p2=fork();
    if (p2==0)
    {
        printf("Sub2 created!\n");
        childProcess2();
    }

    //Wait !
    waitpid(p1,&status1,0);
    waitpid(p2,&status2,0);

    //
    close(pipefd[0]);
    close(pipefd[1]);

    printf("Parent Process is KIlled!\n");
    return 0;
}
