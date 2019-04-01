#ifndef OS_EXP3_H
#define OS_EXP3_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <QString>
#include <QSharedMemory>
//#include <linux/sem.h>

#define LENGTH 10
#define BLOCK_SIZE (4096*4)

struct sharedBuf
{
    int size;									//continue 1 stop 0
    char block[BLOCK_SIZE];		//assuming block size is 4kb
};

void *run(void *GUI);
void *createSHM(int &shmid);
void createSEM(int &semid);
void printInfo(std::string s);
void printProgress(int per);
void P(int semid, int index);
void V(int semid, int index);
void signalProcess(int sig_no);
void readbuf(int shmid,int semid);
void writebuf(int shmid,int semid);
void deleteAll(int shmid,int semid);

#endif // OS_EXP3_H
