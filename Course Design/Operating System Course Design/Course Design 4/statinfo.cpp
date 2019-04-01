#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include "statinfo.h"

bool isNumber(char *s)
{
    if (s==nullptr)
        return false;
    else {
        while (*s)
        {
            if (!isdigit(*s))
                return false;
            s++;
        }
        return true;
    }
}

void sysStatInfo::getSysStatInfo()
{
    //get info
    chdir("/proc");
    this->osInfo.getOSInfo();
    this->cpuInfo.getCPUInfo();
    this->ramInfo.getRAMInfo();

    this->processInfo.clear();

    DIR *dp;
    struct dirent *entry;
    struct processStatInfo pnew;


    if ((dp = opendir("/proc"))==nullptr)
    {
        cout<<"Fail to open the dir: /proc"<<endl;
        return;
    }
    while ((entry = readdir(dp)) != nullptr)
    {
        if (entry->d_type != DT_DIR)
            continue;
        if (isNumber(entry->d_name))
        {
            pnew.getProcessInfo(entry->d_name);
            this->processInfo.push_back(pnew);
        }
    }
    closedir(dp);
}

void OSInfo::getOSInfo()
{
    ifstream inFile;
    string temp;
    stringstream ss;
    vector<string> sv;

    /*get the kernel version*/
    inFile.open("version");
    if (!inFile.is_open())
    {
        cout<<"fail to open file version"<<endl;
        return ;
    }
    sv.clear();
    while (getline(inFile,temp,' '))
    {
        sv.push_back(temp);
    }
    this->kernelVersion=sv[0]+"-"+sv[2];
    inFile.close();

    /*get the os version*/
    inFile.open("/etc/lsb-release");
    if (!inFile.is_open())
    {
        cout<<"fail to open file lsb-release"<<endl;
        return ;
    }
    sv.clear();
    while (getline(inFile,temp,'\n'))
    {
        sv.push_back(temp);
    }
    this->osVersion=sv[3].substr(sv[3].find('=')+1);
    this->osVersion=this->osVersion.substr(1,this->osVersion.size()-2);
    inFile.close();

    /*get the hostname*/
    inFile.open("/proc/sys/kernel/hostname");
    if (!inFile.is_open())
    {
        cout<<"fail to open file hostname"<<endl;
        return ;
    }
    inFile>>this->hostName;
    inFile.close();
}

void sysCPUInfo::getCPUInfo()
{
    ifstream inFile;
    string temp;
    vector<string> sv;

    /*get the cpu info */
    inFile.open("cpuinfo");
    if (!inFile.is_open())
    {
        cout<<"fail to open file cpuinfo"<<endl;
        return ;
    }
    sv.clear();
    while (getline(inFile,temp,'\n'))
    {
        sv.push_back(temp);
    }

    this->coresNum=stoi(sv[12].substr(sv[12].find(':')+2));
    this->logicalProcessorNum=stoi(sv[10].substr(sv[10].find(':')+2));
    this->modelName=sv[4].substr(sv[4].find(':')+2);

    inFile.close();

    chdir("/sys/devices/system/cpu/cpu0/cache/");
    inFile.open("index1/size");
    inFile>>this->Cache[0];
    inFile.close();
    inFile.open("index2/size");
    inFile>>this->Cache[1];
    inFile.close();
    inFile.open("index3/size");
    inFile>>this->Cache[2];
    inFile.close();
    chdir("/proc");

    this->updateCPUInfo();
}

void sysRAMInfo::getRAMInfo()
{
    ifstream inFile;
    string temp;
    vector<string> sv;

    inFile.open("meminfo");
    if (!inFile.is_open())
    {
        cout<<"fail to open file meminfo"<<endl;
        return ;
    }
    sv.clear();
    while (getline(inFile,temp,'\n'))
    {
        sv.push_back(temp);
    }
    this->memTotal=this->getSize(sv[0]);
    this->memFree=this->getSize(sv[1]);
    this->memAvailable=this->getSize(sv[2]);
    this->memBuffers=this->getSize(sv[3]);
    this->memCached=this->getSize(sv[4])+this->getSize(sv[22]);     // Cached+SReclaimable
    this->memSwapTotal=this->getSize(sv[14]);
    this->memUsed.push_back(this->memTotal-this->memFree-this->memCached-this->memBuffers);
    if (this->memUsed.size()>61)
    {
        this->memUsed.erase(this->memUsed.begin());
    }

    inFile.close();
}

void sysDiskInfo::getDiskInfo()
{

}

void sysNetInfo::getNetInfo()
{

}

void processStatInfo::getProcessInfo(char *pid)
{
    ifstream inFile;
    string temp;
    vector<string> sv;
    this->PID=atoi(pid);
    this->showed=false;

    chdir(pid);

    inFile.open("stat");
    if (!inFile.is_open())
    {
        cout<<"fail to open file /proc/"<<this->PID<<"/stat"<<endl;
        return ;
    }
    sv.clear();
    while (getline(inFile,temp,' '))
    {
        sv.push_back(temp);
    }
    this->name=sv[1].substr(1,sv[1].size()-2);
    this->state=sv[2][0];
    this->priority=stoi(sv[17]);
    this->totalProcessCPUTime[0]=this->totalProcessCPUTime[1]=stoi(sv[13])+stoi(sv[14])+stoi(sv[15])+stoi(sv[16]);
    this->usedProcessMemSize=stoi(sv[23])*sysconf(_SC_PAGE_SIZE)/1024;
    inFile.close();

    chdir("..");
}

void sysStatInfo::updateSysStatInfo()
{
    this->cpuInfo.updateCPUInfo();
    this->ramInfo.updateRAMInfo();

    for (int i=0;i<this->processInfo.size();i++)
    {
        if (!this->processInfo[i].updateProcessInfo())
        {
            this->processInfo.erase(this->processInfo.begin()+i);
            i--;
        }
    }

    DIR *dp;
    struct dirent *entry;
    struct processStatInfo pnew;

    if ((dp = opendir("/proc"))==nullptr)
    {
        cout<<"Fail to open the dir: /proc"<<endl;
        return;
    }
    chdir("/proc");
    while ((entry = readdir(dp)) != nullptr)
    {
        if (entry->d_type != DT_DIR)
            continue;
        if (isNumber(entry->d_name))
        {
            int no=this->findProcess(atoi(entry->d_name));
            if (no<0)
            {
                pnew.getProcessInfo(entry->d_name);
                this->processInfo.push_back(pnew);
            }
        }
    }
    closedir(dp);

}

void sysCPUInfo::updateCPUInfo()
{
    ifstream inFile;
    string temp;
    stringstream ss;
    vector<string> sv;

    int count=0;

    inFile.open("stat");
    if (!inFile.is_open())
    {
        cout<<"fail to open file stat"<<endl;
        return ;
    }
    getline(inFile,temp,'\n');
    for (int i=0;i<temp.size();i++)
    {
        if (i&&temp[i]==' '&&temp[i-1]==' ')
            continue;
        ss<<temp[i];
    }
    sv.clear();
    while (getline(ss,temp,' '))
    {
        sv.push_back(temp);
    }

    for (int i=1;i<sv.size();i++)
        count+=stoi(sv[i]);
    this->totalCPUTime.push_back(count);
    this->idelCPUTime.push_back(stoi(sv[4]));

    if (this->totalCPUTime.size()>62)
    {
        this->totalCPUTime.erase(this->totalCPUTime.begin());
        this->idelCPUTime.erase(this->idelCPUTime.begin());
    }

    inFile.close();

    inFile.open("cpuinfo");
    if (!inFile.is_open())
    {
        cout<<"fail to open file cpuinfo"<<endl;
        return ;
    }
    sv.clear();
    while (getline(inFile,temp,'\n'))
    {
        sv.push_back(temp);
    }
    count=0;
    this->curSpeed=0;
    for (int i=0,num;i<sv.size();i+=27,count++)
    {
        this->curSpeed+=stod(sv[i+7].substr(sv[i+7].find(':')+2));
    }
    this->curSpeed/=count;

    inFile.close();
}

void sysRAMInfo::updateRAMInfo()
{
    this->getRAMInfo();
}

bool processStatInfo::updateProcessInfo()
{
    ifstream inFile;
    string temp;
    vector<string> sv;

    this->showed=false;

    chdir(to_string(this->PID).c_str());

    inFile.open("stat");
    if (!inFile.is_open())
    {
        cout<<"get:fail to open file /proc/"<<this->PID<<"/stat"<<endl;
        return false;
    }
    sv.clear();
    while (getline(inFile,temp,' '))
    {
        sv.push_back(temp);
    }
    this->totalProcessCPUTime[0]=this->totalProcessCPUTime[1];
    this->totalProcessCPUTime[1]=stoi(sv[13])+stoi(sv[14])+stoi(sv[15])+stoi(sv[16]);
    this->usedProcessMemSize=stoi(sv[23])*sysconf(_SC_PAGE_SIZE)/1024;
    inFile.close();

    chdir("..");

    return true;
}

int sysStatInfo::findProcess(pid_t pid)
{
    for (int i=0;i<this->processInfo.size();i++)
    {
        if (this->processInfo[i].PID==pid)
            return i;
    }
    return -1;
}

int sysRAMInfo::getSize(string &source)
{
    string temp;
    temp=source.substr(source.find(':')+1);
    temp=temp.substr(temp.find_first_not_of(' '));
    temp=temp.substr(0,temp.find(' '));
    return stoi(temp);
}
