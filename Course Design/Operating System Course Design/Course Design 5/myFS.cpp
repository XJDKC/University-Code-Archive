//
// Created by xjdkc on 19-2-28.
//


#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "myFS.h"
using namespace std;

int myFS::init()
{
    ifstream inFile;
    inFile.open(fsPath,ios_base::binary);
    if (!inFile.is_open())
    {
        return format();
    }

    fs=new char[FS_BLCOKS_NUM*BLOCK_SIZE];
    inFile.read(fs,FS_BLCOKS_NUM*BLOCK_SIZE);
    superBegin=(superBlock *)fs;
    userBegin=(userBlock *)(fs+superBegin->userIndex*BLOCK_SIZE);
    bitmapBegin=(bitmapBlock *)(fs+superBegin->bitmapIndex*BLOCK_SIZE);
    inodeBegin=(inodeBlock *)(fs+superBegin->inodeIndex*BLOCK_SIZE);
    dataBegin=(dataBlock *)(fs+superBegin->dataIndex*BLOCK_SIZE);
    curPath="/";
    curUser=NULL;
    //curUser=(userInfo *)userBegin;
    curInode=(inode *)inodeBegin;

    inFile.close();
    return 0;
}

int myFS::exit()
{
    ofstream outFile;
    outFile.open(fsPath,ios_base::binary);
    if (!outFile.is_open())
    {
        cout<<"exit file system error!"<<endl;
    }
    outFile.write(fs,FS_BLCOKS_NUM*BLOCK_SIZE);
    outFile.close();
}
int myFS::format()
{
    ofstream outFile;
    outFile.open(fsPath,ios_base::binary);
    if (!outFile.is_open())
    {
        cout<<"format file system error!"<<endl;
        return -1;
    }

    //格式化超级快
    fs=new char [FS_BLCOKS_NUM*BLOCK_SIZE];
    superBegin=(superBlock *)fs;
    strcpy(superBegin->infomation,"Welcome to use XJDKC's file system!");
    superBegin->fsSize=FS_BLCOKS_NUM;
    superBegin->userSize=USER_BLCOKS_NUM;
    superBegin->bitmapSize=BITMAP_BLCOKS_NUM;
    superBegin->inodeSize=INODE_BLCOKS_NUM;
    superBegin->dataSize=DATA_BLCOKS_NUM;
    superBegin->userIndex=0+superBegin->userSize;
    superBegin->bitmapIndex=superBegin->userSize+superBegin->userIndex;
    superBegin->inodeIndex=superBegin->bitmapSize+superBegin->bitmapIndex;
    superBegin->dataIndex=superBegin->inodeSize+superBegin->inodeIndex;

    //初始化成员变量
    userBegin=(userBlock *)(fs+superBegin->userIndex*BLOCK_SIZE);
    bitmapBegin=(bitmapBlock *)(fs+superBegin->bitmapIndex*BLOCK_SIZE);
    inodeBegin=(inodeBlock *)(fs+superBegin->inodeIndex*BLOCK_SIZE);
    dataBegin=(dataBlock *)(fs+superBegin->dataIndex*BLOCK_SIZE);

    //初始化位图块
    for (unsigned int i=0;i<100;i++)
        bitmapBegin->tagBlock(i);

    //初始化用户块
    userInfo *root;
    for (unsigned int i=0;i<sizeof(userBegin->users)/sizeof(userInfo);i++)
        userBegin->users[i].userID=FREE;
    root=userBegin->mallocUser();
    root->registerUser("root","123456");

    //初始化索引块
    inode *pInode;
    directoryItem temp;
    pInode=inodeBegin->mallocInode();
    pInode->setInodeInfo(0,true);
    pInode->i_length=sizeof(directoryItem)*2;
    pInode->i_dataIndex[0]=bitmapBegin->mallocBlock();
    temp.setItemInfo(0,".");
    dataBegin->write(pInode->i_dataIndex[0],(char *)&temp,sizeof(directoryItem));
    temp.setItemInfo(0,"..");
    dataBegin->write(pInode->i_dataIndex[0],(char *)&temp,sizeof(directoryItem),sizeof(directoryItem));

    //初始化成员变量
    curPath="/";
    curUser=NULL;
    curInode=(inode *)inodeBegin;

    //写入文件
    outFile.write(fs,FS_BLCOKS_NUM*BLOCK_SIZE);
    outFile.close();
    return 0;
}

int myFS::processCommand()
{
    bool flag=true;
    string temp;
    string command;
    stringstream ss;
    vector<string> commands;
    cout<<superBegin->infomation<<endl;
    while (flag)
    {
        if (curUser==NULL)
        {
            getline(cin,command);
            if (command=="exit")        { flag=false;   continue;}
            if (command=="login")       { login();      continue;}
            if (command=="cancel")      { cancelUser(); continue;}
            if (command=="register")    { registering();continue;}
            cout<<"Instruction error! Please input again!"<<endl;
        }
        else
        {
            cout<<curUser->userName<<"@fs "<<curPath<<" ";
            getline(cin,command);
            temp="";
            for (int i=0;i<command.size();i++)
                if (i&&command[i]==' '&&command[i-1]==' ')
                    continue;
                else
                    temp+=command[i];
            commands.clear();
            ss.clear();
            ss.str(temp);
            while (getline(ss,command,' '))
            {
                commands.push_back(command);
            }

            if (commands.size()<1)      continue;
            if (commands[0]=="logout")  { curUser=NULL;    continue;}
            if (commands[0]=="mkdir")   { mkdir(commands); continue;}
            if (commands[0]=="rmdir")   { rmdir(commands); continue;}
            if (commands[0]=="touch")   { touch(commands); continue;}
            if (commands[0]=="rm")      { rm(commands);    continue;}
            if (commands[0]=="ls")      { ls(commands);    continue;}
            if (commands[0]=="cd")      { cd(commands);    continue;}
            if (commands[0]=="cat")     { cat(commands);   continue;}
            if (commands[0]=="write")   { write(commands); continue;}
            if (commands[0]=="open")    { open(commands);  continue;}
            if (commands[0]=="close")   { close(commands); continue;}
            if (commands[0]=="chmod")   { chmod(commands); continue;}
        }
    }
}

int myFS::login()
{
    string username;
    string password;
    userInfo *user;
    for (int i=0;i<3;i++)
    {
        cout<<"Username: ";cin>>username;
        cout<<"Password: ";cin>>password;
        cin.get();
        user=userBegin->findUser(username.c_str());
        if (user==NULL)
            cout<<"Wrong Username or Password! Please input again!"<<endl;
        else if (user->userLogin(password.c_str()))
        {
            curUser=user;
            return 0;
        }
    }
    return -1;
}

int myFS::cancelUser()
{
    string username;
    string password;
    userInfo *user;
    cout<<"Username: ";cin>>username;
    cout<<"Password: ";cin>>password;
    cin.get();
    user=userBegin->findUser(username.c_str());
    if (user==NULL)
    {
        cout<<"Username not exists!"<<endl;
        return -1;
    }
    else if (user->userLogin(password.c_str()))
    {
        user->cancelUser();
        return 0;
    }
    else
    {
        cout<<"Wrong Username or Password!"<<endl;
        return -1;
    }
}

int myFS::registering()
{
    string username;
    string password;
    userInfo *user;
    cout<<"Please enter the registration information!"<<endl;
    cout<<"Username: ";cin>>username;
    cout<<"Password: ";cin>>password;
    cin.get();
    user=userBegin->findUser(username.c_str());
    if (user!=NULL)
    {
        cout<<"Username already exists!"<<endl;
        return -1;
    }
    else
    {
        curUser=userBegin->mallocUser();
        if (curUser==NULL)
        {
            cout<<"User information space is full!"<<endl;
            return -1;
        }
        else
        {
            curUser->registerUser(username.c_str(),password.c_str());
            return 0;
        }
    }
}


int myFS::mkdir(vector<string> para)
{
    bool flag;
    inode *parent,*pnew;
    string filename;
    unsigned char *data,*buf;
    directoryItem directItem;

    if (para.size()<1)
        return -1;

    filename=dealPath(para[1],parent,true);
    //如果未找到 说明路径有误 则返回-1
    if (parent==NULL)
    {
        cout<<"Wrong file path!"<<endl;
        return -1;
    }

    if (isItemExist(parent,filename))
        return -1;

    //创建path对应索引节点
    pnew=inodeBegin->mallocInode();
    pnew->i_dataIndex[0]=bitmapBegin->mallocBlock();
    if (pnew->i_dataIndex[0]==NO_BLOCK)
    {
        pnew->i_length=0;
        inodeBegin->freeInode(pnew);
        return -1;
    }
    pnew->setInodeInfo(curUser->userID,true);

    //添加"."目录项 指向该索引节点
    pnew->i_length=sizeof(directoryItem)*2;
    directItem.setItemInfo(inodeBegin->getInodeNo(pnew),".");
    dataBegin->write(pnew->i_dataIndex[0],(char *)&directItem,sizeof(directoryItem));

    //添加".."目录项 指向父目录
    directItem.setItemInfo(inodeBegin->getInodeNo(parent),"..");
    dataBegin->write(pnew->i_dataIndex[0],(char *)&directItem,sizeof(directoryItem),sizeof(directoryItem));

    //在父目录中添加该文件夹的目录项
    directItem.setItemInfo(inodeBegin->getInodeNo(pnew),filename.c_str());
    buf=new unsigned char[parent->i_length+sizeof(directoryItem)];
    data=readFile(parent);
    memcpy(buf,data,parent->i_length);
    memcpy(buf+parent->i_length,(char *)&directItem,sizeof(directoryItem));
    flag=writeFile(parent,(char *)buf,parent->i_length+sizeof(directoryItem));

    delete []data;
    delete []buf;

    return flag?0:-1;
}

int myFS::rmdir(vector<string> para)
{
    int num;
    inode *parent,*pcur;
    string filename;
    directoryItem *directItem;
    //找到父目录以及当前目录的索引节点
    filename=dealPath(para[1],parent,true);
    dealPath(para[1],pcur,false);

    if (para.size()<2)
        return -1;

    //判断路径是否正确
    if (pcur==NULL)
    {
        cout<<"Wrong file path!"<<endl;
        return -1;
    }

    //判断该索引节点是否为目录文件
    if (!pcur->isDir()) {
        cout<<"Path does not have a corresponding folder!"<<endl;
        return -1;
    }
    //判断该目录下是否有文件
    if (pcur->i_length>32)
    {
        cout<<"The folder has other file!"<<endl;
        return -1;
    }
    if (pcur==inodeBegin->inodes)
    {
        cout<<"Could not remove the root directory!"<<endl;
        return -1;
    }

    //删除该目录索引节点以及数据块
    num=(pcur->i_length+BLOCK_SIZE-1)/BLOCK_SIZE;
    for (int i=0;i<num;i++)
        bitmapBegin->freeBlock(pcur->i_dataIndex[i]);

    inodeBegin->freeInode(pcur);

    //删除父亲索引节点对应数据块中存放的目录项
    num=parent->i_length/sizeof(directoryItem);
    directItem=(directoryItem *)readFile(parent);
    for (int i=0;i<num;i++)
    {
        if (strcmp(directItem[i].i_filename,filename.c_str())==0)
        {
            for (int j=i+1;j<num;j++)
                directItem[j-1]=directItem[j];
            break;
        }
    }
    writeFile(parent,(char *)directItem,parent->i_length-sizeof(directoryItem));
    delete[]directItem;
}

int myFS::touch(vector<string> para)
{
    bool flag;
    string filename;
    inode *parent,*pnew;
    directoryItem directItem;
    unsigned char *data,*buf;

    if (para.size()<1)
        return -1;

    filename=dealPath(para[1],parent,true);
    //如果未找到 说明路径有误 则返回-1
    if (parent==NULL)
    {
        cout<<"Wrong file path!"<<endl;
        return -1;
    }

    if (isItemExist(parent,filename))
        return -1;

    //创建path对应索引节点
    pnew=inodeBegin->mallocInode();
    pnew->i_length=0;
    pnew->setInodeInfo(curUser->userID,false);

    //在父目录中添加该文件夹的目录项
    directItem.setItemInfo(inodeBegin->getInodeNo(pnew),filename.c_str());
    buf=new unsigned char[parent->i_length+sizeof(directoryItem)];
    data=readFile(parent);
    memcpy(buf,data,parent->i_length);
    memcpy(buf+parent->i_length,(char *)&directItem,sizeof(directoryItem));
    flag=writeFile(parent,(char *)buf,parent->i_length+sizeof(directoryItem));

    delete []data;
    delete []buf;

    return flag?0:-1;
}

int myFS::rm(vector<string> para)
{
    int num;
    inode *parent,*pcur;
    string filename;
    directoryItem *directItem;
    //找到父目录以及当前目录的索引节点
    filename=dealPath(para[1],parent,true);
    dealPath(para[1],pcur,false);

    if (para.size()<2)
        return -1;

    //判断路径是否正确
    if (pcur==NULL)
    {
        cout<<"Wrong file path!"<<endl;
        return -1;
    }

    //判断该索引节点是否为文件
    if (pcur->isDir()) {
        cout<<"The path corresponds to a folder!"<<endl;
        return -1;
    }

    if (filename=="."||filename=="..")
    {
        cout<<"Could not remove '.' or '..'"<<endl;
        return -1;
    }

    //删除该目录索引节点以及数据块
    num=(pcur->i_length+BLOCK_SIZE-1)/BLOCK_SIZE;
    for (int i=0;i<num;i++)
        bitmapBegin->freeBlock(pcur->i_dataIndex[i]);

    inodeBegin->freeInode(pcur);

    //删除父亲索引节点对应数据块中存放的目录项
    num=parent->i_length/sizeof(directoryItem);
    directItem=(directoryItem *)readFile(parent);
    for (int i=0;i<num;i++)
    {
        if (strcmp(directItem[i].i_filename,filename.c_str())==0)
        {
            for (int j=i+1;j<num;j++)
                directItem[j-1]=directItem[j];
            break;
        }
    }
    writeFile(parent,(char *)directItem,parent->i_length-sizeof(directoryItem));
    delete[]directItem;

    return 0;
}

int myFS::ls(vector<string> para)
{
    directoryItem *directItem;
    inode *parent;

    dealPath(para.size()>1?para[1]:"",parent,false);

    if (parent==NULL)
    {
        cout<<"Wrong file path!"<<endl;
        return -1;
    }

    if (!parent->isDir()){
        cout<<"Path does not have a corresponding folder!"<<endl;
        return -1;
    }

    directItem=(directoryItem *)readFile(parent);
    for (int i=0;i<parent->i_length/sizeof(directoryItem);i++)
    {
        cout<<directItem[i].i_filename<<"\t";
    }
    cout<<endl;
    delete []directItem;
    return 0;
}

int myFS::cd(vector<string> para)
{
    inode *pcur;

    if (para.size()<2)
        return -1;

    dealPath(para[1],pcur,false);

    if (pcur==NULL)
    {
        cout<<"Wrong file path!"<<endl;
        return -1;
    }
    if (!pcur->isDir()){
        cout<<"Path does not have a corresponding folder!"<<endl;
        return -1;
    }


    if (para[1][para[1].size()-1]=='/')
        para[1]=para[1].substr(0,para[1].size()-1);
    if (para[1].size()==0)
        curPath="/";
    else if (para[1][0]=='.'&&para[1].size()==1)
        curPath="/";
    else if (para[1][0]=='.')
        curPath=curPath+(curInode==inodeBegin->inodes?para[1].substr(2):para[1].substr(1));
    else
        curPath=curPath+"/"+para[1];

    curInode=pcur;
    return 0;
}

int myFS::cat(vector<string> para)
{
    inode *pcur;
    char *data;

    if (para.size()<2)
        return -1;

    dealPath(para[1],pcur,false);

    if (pcur==NULL)
    {
        cout<<"Wrong file path!"<<endl;
        return -1;
    }
    if (pcur->isDir()){
        cout<<"The path corresponds to a folder!"<<endl;
        return -1;
    }

    data=(char *)readFile(pcur);
    cout.write(data,pcur->i_length);
    cout<<endl;

    delete[]data;
    return 0;
}

int myFS::write(vector<string> para)
{
    int pos=0;
    bool flag=true;
    inode *pcur;
    string s;
    string temp;

    if (para.size()<2)
        return -1;

    dealPath(para[1],pcur,false);

    if (pcur==NULL)
    {
        cout<<"Wrong file path!"<<endl;
        return -1;
    }
    if (pcur->isDir()){
        cout<<"The path corresponds to a folder!"<<endl;
        return -1;
    }

    while (flag)
    {
        if (kbhit())
        {
            char c=getchar();
            switch (c)
            {
                case 127:s.erase(--pos,1);
                        temp=s.substr(pos,s.find('\n',pos))+" ";
                        printf("\033[1D%s\033[1D",temp.c_str());
                        break;
                //case 10:break;
                case 27:flag=false;break;
                case 37:if (pos>0) {pos-=1;printf("\033[1D");}break;
                case 39:if (pos<s.size()) {pos+=1;printf("\033[1C");}break;
                default:s.insert(pos++,1,c);
                        printf("%s",s.c_str()+pos-1);
            }
        }
    }

    flag=writeFile(pcur, s.c_str(),s.size());

    return flag;
}

int myFS::open(vector<string> para)
{

}

int myFS::close(vector<string> para)
{

}

int myFS::chmod(vector<string> para)
{
    if (curUser->userID==0)
    {

    }
}

inode *myFS::findInode(string path)
{
    directoryItem *direcItem;
    inode *pcur;
    stringstream ss;
    vector<string> sv;

    if (path[0]=='/')
    {
        pcur=inodeBegin->inodes;
        path=path.substr(1);
    }
    else
        pcur=curInode;

    sv.clear();
    ss<<path;
    while (getline(ss,path,'/'))
    {
        sv.push_back(path);
    }

    for (int i=0;i<sv.size();i++)
    {
        direcItem=(directoryItem *)readFile(pcur);
        for (int j=0;j<pcur->i_length/sizeof(direcItem);j+=1)
            if (strcmp(direcItem[j].i_filename,sv[i].c_str())==0)
            {
                pcur=inodeBegin->findInode(direcItem[j].i_no);
                break;
            }
            else if (j==pcur->i_length/sizeof(direcItem)-1)
                return NULL;
        delete []direcItem;
    }
    return pcur;
}

unsigned char *myFS::readFile(inode *pInode)
{
    int i=0;
    unsigned char *start;
    unsigned int count=0,length;
    unsigned char *ret=new unsigned char[pInode->i_length];

    while (count<pInode->i_length)
    {
        start=dataBegin->getBlock(pInode->i_dataIndex[i++]);
        length=min((pInode->i_length-count),(unsigned int)BLOCK_SIZE);
        memcpy(ret+count,start,length);
        count+=length;
    }
    return ret;
}

bool myFS::writeFile(inode *pInode,const char *source,unsigned int length)
{
    int i=0;
    unsigned char *start;
    unsigned int count=0,size;

    if (length>MAX_SIZE)
        return false;

    while (count<length)
    {
        //内存空间不足就先获取内存空间
        if (count>=pInode->i_length)
        {
            pInode->i_dataIndex[i]=bitmapBegin->mallocBlock();
            if (pInode->i_dataIndex[i]==NO_BLOCK)
                return false;
        }

        size=min((length-count),(unsigned int)BLOCK_SIZE);
        start=dataBegin->getBlock(pInode->i_dataIndex[i++]);
        memcpy(start,source+count,length);
        count+=length;
    }
    pInode->i_length=length;
    return true;
}

string myFS::dealPath(string path,inode *&parent,bool create)
{
    string filename;

    if (path.size()<1)
    {
        parent=curInode;
        return filename;
    }

    if (path[path.size()-1]=='/'&&path.size()>1)
        path=path.substr(0,path.size()-1);

    //判断路径名是否就是新文件夹名
    if (path.find('/')==string::npos&&create)
    {
        parent=curInode;
        return path;
    }

    filename=path.substr(path.find_last_of('/')+1);

    if (create)
    {
        path=path.substr(0,path.find_last_of('/'));
    }
    parent=findInode(path);
    return filename;
}

bool myFS::isItemExist(inode *pInode,string filename)
{
    int num;
    bool flag=false;
    directoryItem *directItem;

    num=pInode->i_length/sizeof(directoryItem);
    directItem=(directoryItem *)readFile(pInode);

    for (int i=0;i<num;i++)
        if (strcmp(directItem[i].i_filename,filename.c_str())==0)
        {
            flag=true;
            break;
        }

    delete[]directItem;
    return flag;
}

int myFS::kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}
