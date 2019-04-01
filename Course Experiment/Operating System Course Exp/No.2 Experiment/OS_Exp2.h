#ifndef OS_EXP2_H
#define OS_EXP2_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <QString>
#include "mainwindow.h"
//#include <linux/sem.h>
using namespace std;

void *run(void *GUI);
void *subp1(void *arg);
void *subp2(void *arg);
void printInfo(string s);
void P(int semid, int index);
void V(int semid, int index);

#endif // OS_EXP2_H
