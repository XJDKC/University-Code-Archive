//
// Created by xjdkc on 19-2-27.
//

#ifndef EXP5_BLOCKS_H
#define EXP5_BLOCKS_H

#include "FCB.h"
#include "user.h"

#define BLOCK_SIZE (1024)
#define FS_BLCOKS_NUM (100*1024)
#define SUPER_BLCOKS_NUM (1)
#define USER_BLCOKS_NUM (1)
#define BITMAP_BLCOKS_NUM (13)
#define INODE_BLCOKS_NUM (85)
#define MANAGE_BLOCKS_NUM (100)
#define DATA_BLCOKS_NUM (100*1024-100)

#define MAX_SIZE (13*1024)

#define NO_BLOCK 0xffffffff

/*
 * 磁盘块分配：   第0块 存放超级块：各种系统信息
 *              第1块 存放用户信息块：各种用户信息
 *              第2-14块 共13块 存放位图信息 即每个块的分配情况
 *              第15-99块 共85块 存放索引节点信息 即目录文件以及数据文件的索引节点
 *              共102400块
 */
struct superBlock
{
    char infomation[256];       //information
    unsigned int fsSize;        //per block
    unsigned int userSize;      //per block
    unsigned int bitmapSize;    //per block
    unsigned int inodeSize;     //per block
    unsigned int dataSize;      //per block
    unsigned int userIndex;
    unsigned int bitmapIndex;
    unsigned int inodeIndex;
    unsigned int dataIndex;     //data blocks' index
};

struct bitmapBlock
{
    unsigned char bitmap[BITMAP_BLCOKS_NUM*BLOCK_SIZE];

    void tagBlock(unsigned int blockNo);
    void untagBlock(unsigned int blockNo);
    bool isFree(unsigned int blockNo);
    unsigned int mallocBlock();                     //从空闲块中分配一个 将块号返回 为NO_BLOCK时表示已满
    void freeBlock(unsigned int blockNo);   //释放一个空闲块
};

struct userBlock
{
    struct userInfo users[USER_BLCOKS_NUM*BLOCK_SIZE/sizeof(userInfo)];

    userInfo *mallocUser();
    void freeUser(userInfo *pUser);
    userInfo *findUser(const char *userName);
};

struct inodeBlock
{
    struct inode inodes[INODE_BLCOKS_NUM*BLOCK_SIZE/sizeof(inode)];

    inode *mallocInode();
    void freeInode(inode *pInode);
    inode *findInode(unsigned int no);
    unsigned int getInodeNo(inode *pInode);
};

struct dataBlock
{
    unsigned char datas[DATA_BLCOKS_NUM][BLOCK_SIZE];

    unsigned char *getBlock(unsigned int blockNo);
    void read(unsigned int blockNo,char *recv,int length=BLOCK_SIZE,int index=0);
    void write(unsigned int blockNo,const char *source,int length=BLOCK_SIZE,int index=0);
};


#endif //EXP5_BLOCKS_H
