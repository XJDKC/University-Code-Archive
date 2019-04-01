//
// Created by xjdkc on 19-2-28.
//

#include <cstring>
#include "user.h"

//明文保存 有安全隐患
void userInfo::registerUser(const char *name,const char *pwd)
{
    strcpy(userName,name);
    strcpy(userPwd,pwd);
}

void userInfo::cancelUser()
{
    this->userID=FREE;
    memset(this->userName,0,sizeof(this->userName));
    memset(this->userPwd,0,sizeof(this->userPwd));
}

bool userInfo::userLogin(const char *pwd)
{
    if (strcmp(this->userPwd,pwd)==0)
        return true;
    else
        return false;
}