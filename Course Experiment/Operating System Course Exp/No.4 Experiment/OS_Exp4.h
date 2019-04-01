#ifndef OS_EXP4_H
#define OS_EXP4_H

#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;

struct extraInfo
{
    bool end;
    int Total;
    int dirNum;
    int maxLength;
    int maxSizeNum;
    int maxDirNum;

    struct extraInfo &operator=(int num)
    {
        Total = dirNum = maxLength = maxSizeNum = maxDirNum = num;
    }
};

void *run(void *);
int utf8_strlen(const char *s);
int filter(const struct dirent *entry);
void getInfo(DIR *dp, int depth);
void printInfo(string s);
void printTree(int depth);
void printDir(char *dir, int depth);
void printStat(struct stat *statbuf, struct dirent *entry, int depth);

#endif // OS_EXP4_H
