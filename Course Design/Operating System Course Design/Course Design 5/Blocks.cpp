//
// Created by xjdkc on 19-2-28.
//
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "Blocks.h"
using namespace std;

void bitmapBlock::tagBlock(unsigned int blockNo)
{
    bitmap[blockNo/8] |=(unsigned char)1<<(blockNo%8);
}

void bitmapBlock::untagBlock(unsigned int blockNo)
{
    bitmap[blockNo/8] &=~((unsigned char)1<<(blockNo%8));
}

bool bitmapBlock::isFree(unsigned int blockNo)
{
    return !(bitmap[blockNo/8]&((unsigned char)1<<(blockNo%8)));
}

unsigned int bitmapBlock::mallocBlock()
{
    for (unsigned int i=FS_BLCOKS_NUM-DATA_BLCOKS_NUM;i<FS_BLCOKS_NUM;i++)
        if (isFree(i))
        {
            tagBlock(i);
            return i;
        }
    return NO_BLOCK;
}

void bitmapBlock::freeBlock(unsigned int blockNo)
{
    untagBlock(blockNo);
}


userInfo *userBlock::mallocUser()
{
    for (unsigned int i=0;i<sizeof(users)/sizeof(userInfo);i++)
        if (users[i].userID==FREE)
        {
            users[i].userID=i;
            return users+i;
        }
    return NULL;
}


void userBlock::freeUser(userInfo *pUser)
{
    pUser->cancelUser();
}

userInfo *userBlock::findUser(const char *userName)
{
    for (unsigned int i=0;i<sizeof(users)/sizeof(userInfo);i++)
        if (strcmp(users[i].userName,userName)==0)
            return users+i;
    return NULL;
}

inode *inodeBlock::mallocInode()
{
    for (unsigned int i=0;i<sizeof(inodes)/sizeof(inode);i++)
        if (inodes[i].i_license==0)
            return inodes+i;
    return NULL;
}

void inodeBlock::freeInode(inode *pInode)
{
    pInode->i_license=0;
    pInode->i_owner=0;
    pInode->i_length=0;
    memset(pInode->i_dataIndex,0,sizeof(pInode->i_dataIndex));
}

inode *inodeBlock::findInode(unsigned int no)
{
    if (inodes[no].i_license)
        return inodes+no;
    else
        return NULL;
}

unsigned int inodeBlock::getInodeNo(inode *pInode)
{
    return (pInode-(inode *)inodes);
}

unsigned char *dataBlock::getBlock(unsigned int blockNo)
{
    blockNo-=MANAGE_BLOCKS_NUM;
    return *(datas+blockNo);
}

void dataBlock::read(unsigned int blockNo,char *recv,int length,int index)
{
    blockNo-=MANAGE_BLOCKS_NUM;
    memcpy(recv,*(datas+blockNo)+index,length);
}

void dataBlock::write(unsigned int blockNo,const char *source,int length,int index)
{
    blockNo-=MANAGE_BLOCKS_NUM;
    memcpy(*(datas+blockNo)+index,source,length);
}
