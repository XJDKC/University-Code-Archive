//
// Created by xjdkc on 19-2-28.
//

#ifndef EXP5_MYFS_H
#define EXP5_MYFS_H

#include <string>
#include <vector>
#include "Blocks.h"
#include "FCB.h"
#include "user.h"
using namespace std;

const char fsPath[]="fs";

struct myFS
{
    char *fs;
    std::string curPath;
    superBlock *superBegin;
    bitmapBlock *bitmapBegin;
    userBlock *userBegin;
    inodeBlock *inodeBegin;
    dataBlock *dataBegin;

    userInfo *curUser;
    inode *curInode;

    int init();
    int exit();
    int format();
    int processCommand();

    int login();
    int cancelUser();
    int registering();

    int mkdir(vector<string> para);  //创建目录
    int rmdir(vector<string> para);  //删除目录
    int touch(vector<string> para);  //创建文件
    int rm(vector<string> para);     //删除文件
    int ls(vector<string> para);     //显示目录项
    int cd(vector<string> para);     //进入目录
    int cat(vector<string> para);    //显示内容 读
    int write(vector<string> para);  //写文件
    int open(vector<string> para);   //打开文件
    int close(vector<string> para);  //关闭文件
    int chmod(vector<string> para);  //改变文件权限


    int kbhit(void);
    inode *findInode(string path);                                          //根据输入路径查找inode
    unsigned char *readFile(inode *pInode);
    bool isItemExist(inode *pInode,string filename);
    string dealPath(string path,inode *&parent,bool create=false);
    bool writeFile(inode *pInode,const char *source,unsigned int length);
};

#endif //EXP5_MYFS_H
