#include "OS_Exp2.h"
using namespace std;

int semid;
int a = 0;
MainWindow *GUI;

void *run(void *GUI)
{
    key_t key;
    pthread_t p1, p2;
    void *thread_ret;

    ::GUI=static_cast<MainWindow *>(GUI);

    printInfo("mainThread starts!");

    //Get the key according to the file path.
    if ((key=ftok(".",1))==-1)
    {
        printInfo("ftok error!");
        exit(1);
    }

    //Create the semaphore.
    semid = semget(key, 2, IPC_CREAT | 0660);
    printInfo("Create semaphore successfully!");

    //Initialize the semaphore
    if (semctl(semid, 0, SETVAL, 1)>=0)
        printInfo("Initialize the first semaphore successfully!");
    else {
        printInfo("Initializing the first semaphore failed!");
        exit(1);
    }
    if (semctl(semid, 1, SETVAL, 0)>=0)
        printInfo("Initialize the second semaphore successfully!");
    else {
        printInfo("Initializing the first semaphore failed!");
        exit(1);
    }

    //Create two threads;
    if (pthread_create(&p1, NULL, subp1, NULL) != 0)
    {
        printInfo("Create thread failed!");
        exit(1);
    }
    else
        printInfo("Create thread 1 successfully!");
    if (pthread_create(&p2, NULL, subp2, NULL) != 0)
    {
        printInfo("Create thread failed!");
        exit(1);
    }
    else
        printInfo("Create thread 2 successfully!");

    //Wait the two threads!
    pthread_join(p1, &thread_ret);
    printInfo("Thread 1 ends!");
    pthread_join(p2, &thread_ret);
    printInfo("Thread 2 ends!");

    if (semctl(semid,0,IPC_RMID,0)>=0)
        printInfo("Remove the semaphore successfully!");
    else {
        printInfo("Removing the semaphore failed!");
        exit(1);
    }

    printInfo("mainThread ends!");

    return 0;
}

void *subp1(void *arg)
{
    for (bool mark = true; mark;)
    {
        P(semid, 1);
        mark = a < 100;
        printInfo(to_string(a));
        V(semid, 0);
    }
    return NULL;
}

void *subp2(void *arg)
{
    for (int i = 1; i <= 100;i++)
    {
        P(semid, 0);
        if (i==1)
            a = 1;
        else
            a = a + 1;
        V(semid, 1);
    }
    return NULL;
}

void P(int semid, int index)
{
    struct sembuf sem;
    sem.sem_num = index;    //Location to be modified
    sem.sem_op = -1;        //add or sub
    sem.sem_flg = 0;
    semop(semid, &sem, (size_t)(1)); //number of array sem
}

void V(int semid, int index)
{
    struct sembuf sem;
    sem.sem_num = index;    //Location to be modified
    sem.sem_op = 1;         //add or sub
    sem.sem_flg = 0;
    semop(semid, &sem, (size_t)(1)); //number of array sem
}

void printInfo(string s)
{
    QString text=GUI->label->text();
    text+=QString::fromStdString(s+'\n');
    GUI->label->setText(text);
}
