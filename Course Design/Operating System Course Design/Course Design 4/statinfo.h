#ifndef STATINFO_H
#define STATINFO_H

#include <string>
#include <vector>
#include <queue>
#include <list>

using namespace std;

struct processStatInfo
{
    pid_t PID;
    string name;
    char state;
    bool showed;
    int priority;
    unsigned int totalProcessCPUTime[2];
    unsigned int usedProcessMemSize;

    void getProcessInfo(char *pid);
    bool updateProcessInfo();
};

struct sysCPUInfo
{
    int coresNum;
    int Cache[3];
    int logicalProcessorNum;
    double curSpeed;            // /proc/cpuinfo
    string modelName;           // /proc/cpuinfo
    vector<int>  totalCPUTime;
    vector<int>  idelCPUTime;

    void getCPUInfo();
    void updateCPUInfo();
};

struct sysRAMInfo
{
    int memTotal;
    int memFree;
    int memAvailable;
    int memBuffers;
    int memCached;      // Cached+SReclaimable
    int memSwapTotal;
    vector<int> memUsed;

    void getRAMInfo();
    void updateRAMInfo();
    int getSize(string &source);
};

struct sysDiskInfo
{
    void getDiskInfo();
};

struct sysNetInfo
{
    void getNetInfo();
};

struct OSInfo
{
    string kernelVersion;   // /proc/sys/kernel/ostype+osrelease
    string hostName;        // /proc/sys/kernel/hostname
    string osVersion;       // /proc/version

    void getOSInfo();
};

struct sysStatInfo
{
    OSInfo osInfo;
    sysCPUInfo cpuInfo;
    sysRAMInfo ramInfo;
    sysDiskInfo diskInfo;
    sysNetInfo netInfo;
    vector<processStatInfo> processInfo;

    void getSysStatInfo();
    void updateSysStatInfo();
    int findProcess(pid_t pid);
};


#endif // STATINFO_H
