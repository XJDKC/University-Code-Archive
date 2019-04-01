//
// Created by xjdkc on 19-2-28.
//

#include <cstring>
#include "FCB.h"

bool inode::isDir()
{
    return i_license&(1<<9);
}

/*
 * @TODO judge the user could or not could open the file
 */
bool inode::Openable(userInfo *user) {

}

void inode::setInodeInfo(unsigned int owner,bool type)
{
    i_owner=owner;
    i_length=0;
    if (type)
        i_license=0x3ff;
    else
        i_license=0x1ff;
}


directoryItem::directoryItem(unsigned int no,const char *filename)
{
    i_no=no;
    memset(i_filename,0,sizeof(i_filename));
    strcpy(i_filename,filename);
}

void directoryItem::setItemInfo(unsigned int no,const char *filename)
{
    i_no=no;
    memset(i_filename,0,sizeof(i_filename));
    strcpy(i_filename,filename);
}