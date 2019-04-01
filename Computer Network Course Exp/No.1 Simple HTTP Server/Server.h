#pragma once
#include <winsock2.h>
#include <string>
#include <thread>
#include <mutex>
#include <list>
#include <map>
#include <set>

using namespace std;

//服务器

class Server
{
private:
	bool exit;						//退出状态
	SOCKET srvSocket;				//服务器socket
	sockaddr_in srvAddr;			//服务器端IP地址
	timeval timeout;				//服务器断开连接时延
	list<thread> *threads;			//处理每个HTTP会话的线程队列
	map<string,mutex *> *fileOpened;	//当前打开的文件集合
	mutex consoleLock;				//多线程控制台输出锁
	mutex fileLock;					//多线程文件访问锁
	mutex fileSetLock;				//多线程文件集合锁

protected:
	virtual SOCKET AcceptRequestionFromClient();							//从客户端接受连接请求
	virtual string  GetClientAddress(SOCKET s);								//得到客户端IP地址
	virtual string  GetClientPort(SOCKET s);								//得到客户端PORT端口
	virtual int recvMessage(SOCKET s, string &recvBuf);						//从SOCKET s接受消息
	virtual int sendMessage(SOCKET s, string &msg);							//向SOCKET s发送消息
	virtual void ThreadLoop(SOCKET s);										//每个线程的循环
	virtual void stateInfo(SOCKET s, int no,string info);								//状态信息输出
	
public:
	Server(void);
	virtual ~Server(void);
	virtual int WinsockStartup();		//初始化Winsock
	virtual int ServerStartup();		//初始化Server，包括创建SOCKET，绑定到IP和PORT
	virtual int ListenStartup();		//开始监听客户端请求
	virtual int Loop();					//循环执行"等待HTTP请求"->“解析HTTP请求”->"响应HTTP"->"等HTTP消息"
};

/*
每个线程 
	需要一个HTTP类处理报文
	需要一个缓冲接收报文
	需要计时器记录时间
*/

