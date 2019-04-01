//
// Created by xjdkc on 19-2-27.
//

#ifndef EXP5_FCB_H
#define EXP5_FCB_H

#include <string>
#include "user.h"

#define O_RD (0x4)
#define O_WR (0x2)
#define O_EX (0x1)

struct inode
{
    unsigned int i_owner;           //所有者 以userID表示
    unsigned int i_license;         //如果许可权为0 则表示该节点未分配
    unsigned int i_length;          //文件大小
    unsigned int i_dataIndex[13];   //文件数据块号

    bool isDir();
    bool Openable(userInfo *user);
    void setInodeInfo(unsigned int owner,bool type=false);
};

struct directoryItem
{
    unsigned int i_no;              //
    char i_filename[12];            //
    directoryItem() {}
    directoryItem(unsigned int no,const char *filename);
    void setItemInfo(unsigned int no,const char *filename);
};


#endif //EXP5_FCB_H
