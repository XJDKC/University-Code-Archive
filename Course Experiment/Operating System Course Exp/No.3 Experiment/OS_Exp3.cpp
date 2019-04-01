#include "mainwindow.h"
#include "OS_Exp3.h"
using namespace std;

MainWindow *GUI;
int GUI_LOCK;
pid_t p1,p2;

void *run(void *GUI)
{
    int shmid,semid;
    int status1,status2;
    sharedBuf *buf;

    ::GUI=(MainWindow *)GUI;
    ::GUI_LOCK=::GUI->GUI_LOCK;
    printInfo("mainThread starts!");

    //Set signal processing function!
    if (signal(SIGINT,signalProcess)==SIG_ERR)
        printInfo("Can't not catch SIGINT!\n");

    buf=static_cast<sharedBuf *>(createSHM(shmid));
    createSEM(semid);

    p1=fork();
    if (p1==0)
    {
        writebuf(shmid,semid);
    }
    else {
        printInfo("Sub 1 created!");

        p2=fork();
        if (p2==0)
        {
            readbuf(shmid,semid);
        }
        else {
            printInfo("Sub 2 created!");

            //Wait !
            waitpid(p1,&status1,0);
            waitpid(p2,&status2,0);

            deleteAll(shmid,semid);
            printInfo("mainThread ends!");
        }
    }
}

void *createSHM(int &shmid)
{
    key_t key;

    //Get the key according to the file path.
    if ((key=ftok(".",1))==-1)
    {
        printInfo("ftok error!");
        exit(1);
    }

    shmid=shmget(key,sizeof(sharedBuf)*LENGTH,IPC_CREAT|0666);
    if (shmid==-1)
    {
        printInfo("Creating shared memory failed!");
        exit(-1);
    }
    printInfo("Create shared memory successfully");

    void *shm=NULL;
    if ((shm=shmat(shmid,NULL,SHM_R|SHM_W))==(void *)-1)
    {
        printInfo("Error in allocating space!");
    }
    printInfo("Allocate space successfully!");
    return shm;
}

void createSEM(int &semid)
{
    key_t key;
    if ((key=ftok(".",2))==-1)
    {
        printInfo("ftok error!");
        exit(1);
    }

    semid=semget(key,2,IPC_CREAT|0666);
    if (semid==-1)
    {
        printInfo("Creating semaphore failed!");
        exit(-1);
    }
    printInfo("Create semaphore successfully!");

    //Initialize the semaphore
    if (semctl(semid, 0, SETVAL, LENGTH)>=0)
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
}

void readbuf(int shmid, int semid)
{
    bool mark = true;
    char *data;
    int next = 0;
    sharedBuf *head;

    data = static_cast<char *>(shmat(shmid, 0, 0));
    ofstream outFile;
    cout<<GUI->destination->text().toStdString()<<endl;
    outFile.open(GUI->destination->text().toStdString(), ios::binary);
    if (outFile.is_open())
    {
        while (mark)
        {
            head = (sharedBuf *)(data + next * sizeof(sharedBuf));
            P(semid, 1);
            mark = head->size>0;
            outFile.write(head->block,abs(head->size));
            V(semid, 0);
            next = (next + 1) % LENGTH;
        }
        outFile.close();
        printInfo("read ends");
    }
    else
    {
        printInfo("Cannot open the target file!");
        printProgress(-1);
    }
    getchar();
}

void writebuf(int shmid, int semid)
{
    if (signal(SIGUSR1, NULL) == SIG_ERR)
        cout << "error!" << endl;

    char *data;
    int next = 0;
    sharedBuf *head;
    ifstream inFile;
    cout<<GUI->source->text().toStdString()<<endl;
    inFile.open(GUI->source->text().toStdString(), ios::binary);

    unsigned long long count = 0;
    unsigned long long size = inFile.seekg(0, std::ios::end).tellg();
    cout << size << endl;
    inFile.seekg(ios::beg);

    data = static_cast<char *>(shmat(shmid, 0, 0));

    if (inFile.is_open())
    {
        while (!inFile.eof())
        {
            head = (sharedBuf *)(data+next*sizeof(sharedBuf));
            P(semid, 0);
            inFile.read(head->block, BLOCK_SIZE);
            V(semid, 1);

            head->size = inFile.gcount();
            if (inFile.eof() || !inFile.good())
                head->size = -head->size;
            count += inFile.gcount();
            printProgress(count*100/size);
            next = (next + 1) % LENGTH;
        }
        inFile.close();
        printInfo("write ends");
    }
    {
        printInfo("Cannot open the source file!");
        printProgress(-1);
    }
    getchar();
}

void printInfo(string s)
{
    QSharedMemory GUI_Shared(GUI_ID);
    GUI_Shared.attach();

    P(GUI_LOCK,0);

    char *data=static_cast<char *>(GUI_Shared.data());
    memcpy(data+1,s.c_str(),s.size()+1);

    V(GUI_LOCK,1);

    GUI_Shared.detach();
}

void printProgress(int per)
{
    QSharedMemory GUI_Shared(GUI_ID);
    GUI_Shared.attach();
    char *data=static_cast<char *>(GUI_Shared.data());

    GUI_Shared.lock();
    data[0]=per;
    GUI_Shared.unlock();

    GUI_Shared.detach();
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

void signalProcess(int sig_no)
{
    if (sig_no==SIGINT)
    {
        printf("Parent Process Receives SIGINT!\n");
        kill(p1,SIGUSR1);
        kill(p2,SIGUSR2);
    }
}

void deleteAll(int shmid,int semid)
{
    if (semctl(semid,0,IPC_RMID,0)>=0)
        printInfo("Remove the semaphore successfully!");
    else {
        printInfo("Removing the semaphore failed!");
        exit(1);
    }

    if (shmctl(shmid,IPC_RMID,0)>=0)
        printInfo("Remove the shared memory successfully!");
    else {
        printInfo("Removing the shared memory failed!");
        exit(1);
    }
}
