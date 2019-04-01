#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <winsock2.h>
#include <algorithm>
#include <conio.h>
#include "Server.h"
#include "WinsockEnv.h"
#include "Config.h"
#include "Http.h"
#pragma comment(lib, "Ws2_32.lib")

#pragma warning(disable:4996)

Server::Server(void)
{
	this->threads = new list<thread>();
	this->fileOpened = new map<string,mutex *>();

	this->exit = false;

	this->timeout = Config::TIMEOUT;
}

Server::~Server(void)
{
	//�ر�server socket
	if (this->srvSocket != NULL) {
		closesocket(this->srvSocket);
		this->srvSocket = NULL;
	}

	if (this->threads != NULL) {
		for (list<thread>::iterator it = this->threads->begin(); it != this->threads->end(); it++)
			it->join();
		this->threads->clear();
		//delete this->threads;
		//this->threads = NULL;
	}
	
	if (this->fileOpened != NULL){
		for (map<string, mutex *>::iterator it = this->fileOpened->begin(); it != this->fileOpened->end(); it++)
			delete it->second;
		this->fileOpened->clear();
		//delete this->fileOpened;
		//this->fileOpened = NULL;
	}
	this->exit = false;
	WSACleanup(); //����winsock ���л���
}

//��ʼ��Winsock
int Server::WinsockStartup() {
	if (WinsockEnv::Startup() == -1) return -1;	//��ʼ��Winsock
	return 0;
}

//��ʼ��Server����������sockect���󶨵�IP��PORT
int Server::ServerStartup() {
	//���� TCP socket
	this->srvSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->srvSocket == INVALID_SOCKET) {
		this->stateInfo(0, 0, "");
		WSACleanup();
		return -1;
	}
	this->stateInfo(0, 1, "");

	//���÷�����IP��ַ�Ͷ˿ں�
	this->srvAddr.sin_family = AF_INET;
	this->srvAddr.sin_port = htons(Config::PORT);
	this->srvAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//���Զ��ҵ����������ʵ�IP��ַ
//	this->srvAddr.sin_addr.S_un.S_addr = inet_addr(Config::SERVERADDRESS.c_str()); //��������һ������IP��ַ�ķ���

	//�� socket to Server's IP and port
	int rtn = ::bind(this->srvSocket, (LPSOCKADDR)&(this->srvAddr), sizeof(this->srvAddr));
	if (rtn == SOCKET_ERROR) {
		this->stateInfo(0, 2, "");
		closesocket(this->srvSocket);
		WSACleanup();
		return -1;
	}

	this->stateInfo(0, 3, "");
	return 0;
}

//��ʼ����,�ȴ��ͻ�����������
int Server::ListenStartup() {
	int rtn = listen(this->srvSocket, Config::MAXCONNECTION);
	if (rtn == SOCKET_ERROR) {
		this->stateInfo(0, 4, "");
		closesocket(this->srvSocket);
		WSACleanup();
		return -1;
	}

	this->stateInfo(0, 5, "");
	return 0;
}

//��SOCKET s������Ϣ
int Server::recvMessage(SOCKET socket,string &recvBuf) {
	int receivedBytes = recv(socket, (char *)recvBuf.c_str(), Config::BUFFERLENGTH, 0);
	if (receivedBytes == SOCKET_ERROR || receivedBytes == 0) {
		this->stateInfo(socket, 14, "");
		return -1;
	}
	else {
		recvBuf[receivedBytes] = '\0';
		//this->stateInfo(socket, 15, "");
		return receivedBytes;
	}
}

//��SOCKET s������Ϣ
int Server::sendMessage(SOCKET socket, string &msg) {

	int rtn = send(socket, msg.c_str(), msg.length(), 0);
	if (rtn == SOCKET_ERROR)
	{
		this->stateInfo(socket, 16, "");
		return -1;
	}
	else {
		this->stateInfo(socket, 17, "");
		return 0;
	}

}

SOCKET Server::AcceptRequestionFromClient() {
	sockaddr_in clientAddr;		//�ͻ���IP��ַ
	int nAddrLen = sizeof(clientAddr);
	u_long blockMode = Config::BLOCKMODE;//��session socket��Ϊ������ģʽ�Լ����ͻ���������

	//�����Ựsocket
	SOCKET newSocket = accept(this->srvSocket, (LPSOCKADDR)&(clientAddr), &nAddrLen);
	if (newSocket == INVALID_SOCKET) {
		this->stateInfo(0, 6, "");
		return INVALID_SOCKET;
	}

	this->stateInfo(newSocket, 7, "");

	//���µĻỰsocket��Ϊ������ģʽ��
	if (ioctlsocket(newSocket, FIONBIO, &blockMode) == SOCKET_ERROR) {
		this->stateInfo(0, 8, "");
		return INVALID_SOCKET;
	}

	return newSocket;
}

//�õ��ͻ���IP��ַ
string  Server::GetClientAddress(SOCKET s) {
	string clientAddress; //clientAddress�Ǹ����ַ����� clientAddress.empty() is true
	sockaddr_in clientAddr;
	int nameLen, rtn;

	nameLen = sizeof(clientAddr);
	rtn = getpeername(s, (LPSOCKADDR)&clientAddr, &nameLen);
	if (rtn != SOCKET_ERROR) {
		clientAddress += inet_ntoa(clientAddr.sin_addr);
	}

	return clientAddress;
}

string  Server::GetClientPort(SOCKET s)
{
	string clientAddress; //clientAddress�Ǹ����ַ����� clientAddress.empty() is true
	sockaddr_in clientAddr;
	int nameLen, rtn;

	nameLen = sizeof(clientAddr);
	rtn = getpeername(s, (LPSOCKADDR)&clientAddr, &nameLen);
	if (rtn != SOCKET_ERROR) {
		clientAddress += to_string(clientAddr.sin_port);
	}

	return clientAddress;
}

//���ܿͻ��˷�������������ݲ�ת��
int Server::Loop() {
	int rtn;
	int hasConnecRequest;
	fd_set rfds;
	timeval zero = {0,0};
	SOCKET newSocket;
	u_long blockMode = Config::BLOCKMODE;//��srvSock��Ϊ������ģʽ�Լ����ͻ���������

	if ((rtn = ioctlsocket(this->srvSocket, FIONBIO, &blockMode) == SOCKET_ERROR)) { //FIONBIO��������ֹ�׽ӿ�s�ķ�����ģʽ��
		this->stateInfo(0, 9, "");
		return -1;
	}
	this->stateInfo(0, 10, "");

	while (true) { //�ȴ��ͻ�����������

		//Prepare the read and write socket sets for network I/O notification.
		FD_ZERO(&rfds);

		//��srvSocket���뵽rfds���ȴ��û���������
		FD_SET(this->srvSocket, &rfds);

		//�ȴ��û���������
		if ((hasConnecRequest = select(0, &rfds, NULL, NULL, &zero)) == SOCKET_ERROR) { //select���������пɶ����д��socket��������������rtn��.���һ�������趨�ȴ�ʱ�䣬��ΪNULL��Ϊ����ģʽ
			this->stateInfo(this->srvSocket, 13, "");
			return -1;
		}

		//���ȼ���Ƿ��пͻ��������ӵ���
		if (hasConnecRequest)
		{
			if ((newSocket = this->AcceptRequestionFromClient()) == INVALID_SOCKET)
				return -1;
			this->threads->push_back(thread(&Server::ThreadLoop, this, newSocket));
		}

		if (kbhit())
		{
			if (getch() == 27)
				this->exit = true;
		}
		if (this->exit)
			break;
	}
	cout << "�����˳�" << endl;
	return 0;
}

//�߳�ѭ��
void Server::ThreadLoop(SOCKET s)
{
	int hasRequest,state;
	fd_set rfds;
	fd_set wfds;
	Http process;
	string recvBuf(Config::BUFFERLENGTH, '\0');
	while (true)
	{
		//����д������� ������ǰ�̴߳����SOCKET���뼯��
		FD_ZERO(&rfds); FD_SET(s, &rfds);
		FD_ZERO(&wfds); FD_SET(s, &wfds);

		if ((hasRequest = select(0, &rfds, NULL, NULL, &this->timeout)) == SOCKET_ERROR) { 
			state = 0;
		}

		if ((hasRequest = select(0, NULL, &wfds, NULL, &this->timeout)) == SOCKET_ERROR) {
			this->stateInfo(s, 13, "");
		}

		if (this->exit)
			break;

		if (FD_ISSET(s, &rfds) && FD_ISSET(s, &wfds))
		{
			if (this->recvMessage(s, recvBuf) == SOCKET_ERROR)
				break;
			process.parseRequest(recvBuf);

			this->stateInfo(s, 19, process.getMethod()+" "+process.getURL());

			this->fileSetLock.lock();
			if (this->fileOpened->find(process.getURL()) == this->fileOpened->end())
				(*this->fileOpened)[process.getURL()] = new mutex();

			(*this->fileOpened)[process.getURL()]->lock();
			process.generateRespond();
			(*this->fileOpened)[process.getURL()]->unlock();
			
			this->stateInfo(s, 20, process.getURL());

			this->fileSetLock.unlock();
			if (this->sendMessage(s, process.getRespond()) == SOCKET_ERROR)
				break;

		}
		else
		{
			this->stateInfo(s, 18, "");
			break;
		}

		//sleep();
	}
	closesocket(s);
	return;
}

void Server::stateInfo(SOCKET s, int no,string info)
{
	string addr, port, comb;
	if (s)
	{
		addr = this->GetClientAddress(s);
		port = this->GetClientPort(s);
		comb = addr + ":" + port;
	}
	consoleLock.lock();
	switch (no)
	{
		case 0:cout << "Server socket create ERROR !" << endl;  break; 						//��ʾ����������socket����ʧ��
		case 1:cout << "Server socket create OK!" << endl; break; 							//��ʾ����������socket�����ɹ�
		case 2:cout << "Server socket bind ERROR!" << endl; break;							//��ʾ����������socket�󶨵�ַ�˿�ʧ��
		case 3:cout << "Server socket bind OK!" << endl; break;							//��ʾ����������socket�󶨵�ַ�˿ڳɹ�
		case 4:cout << "Server socket listen ERROR!" << endl; break;					//��ʾ����������socket��ʼ����
		case 5:cout << "Server socket listen OK!" << endl; break;						//��ʾ����������socket����ʧ��
		case 6:cout << "Server accept connection request ERROR!" << endl; break;		//��ʾ������������ʧ��
		case 7:cout << "Server accept connection request OK!" << endl; break;			//��ʾ������������ɹ�
		case 8:cout << "ioctlsocket() for new session failed with ERROR!" << endl;break;//ioctlsocket() for new session failed with ERROR!
		case 9:cout << "ioctlsocket() failed with ERROR!" << endl; break;				//ioctlsocket() failed with ERROR!
		case 10:cout << "ioctlsocket() for server socket OK!Waiting for client connection and data" << endl; break;//ioctlsocket() for server socket OK!Waiting for client connection and data
		case 11:cout << "\t" << comb << " New thread Create OK!" << endl; break;		//�������̳ɹ�
		case 12:cout << "\t" << comb << " New thread Create ERROR!" << endl; break;				//��������ʧ��
		case 13:cout << "select() failed with ERROR!" << endl; break;					//��ʾselectʧ��
		case 14:cout << "\t" << comb << " Server receive request ERROR !" << endl; break;		//��ʾ��������ʧ��
		case 15:cout << "\t" << comb << " Server receive request OK !" << endl; break;			//��ʾ�������ݳɹ�	
		case 16:cout << "\t" << comb << " Server send respond ERROR !" << endl; break;			//��ʾ��������ʧ��
		case 17:cout << "\t" << comb << " Server send respond OK !" << endl; break;				//��ʾ�������ݳɹ�
		case 18:cout << "\t" << comb << " Request Timeout" << endl; break;						//��ʾ���ӳ�ʱ
		case 19:cout << "\t" << comb << " Request Header:" << info << endl; break;				//��ʾ���ӳ�ʱ
		case 20:cout << "\t" << comb << " Can't find the file:" << info << endl; break;
	}
	consoleLock.unlock();
}