#pragma once
#include <string>
#include <map>
#include <sys/timeb.h>
#include <winsock2.h>

using namespace std;

//保存配置信息
class Config
{
public:
	static int MAXCONNECTION;					//最大连接数
	static int BUFFERLENGTH;					//缓冲区大小
	static int PORT;							//服务器端口
	static string SERVERADDRESS;				//服务器地址
	static u_long BLOCKMODE;					//SOCKET阻塞模式
	static timeval TIMEOUT;					//服务器超时时间
	static string ROOTPATH;					//服务器根目录
	static multimap<string, string> CONTENTTYPE;	//文件类型
private:
	Config(void);
	~Config(void);
public:
	static int clear();
	static int getConfig();
	static void setDefault();
	static int setIP(string s);
	static int setPORT(string s);
};