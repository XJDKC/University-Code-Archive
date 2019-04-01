//
// Created by xjdkc on 19-2-27.
//

#ifndef EXP5_USER_H
#define EXP5_USER_H

#define FREE 0xffffffff

struct userInfo
{
    unsigned int userID;        //用户ID
    char userName[14];          //用户名称
    char userPwd[14];           //密码

    userInfo()
    {
        userID=FREE;
        userName[0]='\0';
        userPwd[0]='\0';
    }

    void registerUser(const char *name,const char *pwd);        //
    void cancelUser();                                          //
    bool userLogin(const char *pwd);           //
};


#endif //EXP5_USER_H
