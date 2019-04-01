#pragma once
#include <winsock2.h>
#include <string>
#include <thread>
#include <mutex>
#include <list>
#include <map>
#include <set>

using namespace std;

//������

class Server
{
private:
	bool exit;						//�˳�״̬
	SOCKET srvSocket;				//������socket
	sockaddr_in srvAddr;			//��������IP��ַ
	timeval timeout;				//�������Ͽ�����ʱ��
	list<thread> *threads;			//����ÿ��HTTP�Ự���̶߳���
	map<string,mutex *> *fileOpened;	//��ǰ�򿪵��ļ�����
	mutex consoleLock;				//���߳̿���̨�����
	mutex fileLock;					//���߳��ļ�������
	mutex fileSetLock;				//���߳��ļ�������

protected:
	virtual SOCKET AcceptRequestionFromClient();							//�ӿͻ��˽�����������
	virtual string  GetClientAddress(SOCKET s);								//�õ��ͻ���IP��ַ
	virtual string  GetClientPort(SOCKET s);								//�õ��ͻ���PORT�˿�
	virtual int recvMessage(SOCKET s, string &recvBuf);						//��SOCKET s������Ϣ
	virtual int sendMessage(SOCKET s, string &msg);							//��SOCKET s������Ϣ
	virtual void ThreadLoop(SOCKET s);										//ÿ���̵߳�ѭ��
	virtual void stateInfo(SOCKET s, int no,string info);								//״̬��Ϣ���
	
public:
	Server(void);
	virtual ~Server(void);
	virtual int WinsockStartup();		//��ʼ��Winsock
	virtual int ServerStartup();		//��ʼ��Server����������SOCKET���󶨵�IP��PORT
	virtual int ListenStartup();		//��ʼ�����ͻ�������
	virtual int Loop();					//ѭ��ִ��"�ȴ�HTTP����"->������HTTP����->"��ӦHTTP"->"��HTTP��Ϣ"
};

/*
ÿ���߳� 
	��Ҫһ��HTTP�ദ����
	��Ҫһ��������ձ���
	��Ҫ��ʱ����¼ʱ��
*/

