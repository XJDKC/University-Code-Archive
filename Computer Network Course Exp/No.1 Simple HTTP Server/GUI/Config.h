#pragma once
#include <string>
#include <map>
#include <sys/timeb.h>
#include <winsock2.h>

using namespace std;

//����������Ϣ
class Config
{
public:
	static int MAXCONNECTION;					//���������
	static int BUFFERLENGTH;					//��������С
	static int PORT;							//�������˿�
	static string SERVERADDRESS;				//��������ַ
	static u_long BLOCKMODE;					//SOCKET����ģʽ
	static timeval TIMEOUT;					//��������ʱʱ��
	static string ROOTPATH;					//��������Ŀ¼
	static multimap<string, string> CONTENTTYPE;	//�ļ�����
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