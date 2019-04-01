#include "Config.h"
#include <iostream>
#include <fstream>

using namespace std;

Config::Config(void)
{
}

Config::~Config(void)
{
}

int Config::getConfig()
{
	int colon,tail;
	string ori,key,value;
	ifstream inFile("Config.yml");
	Config::setDefault();
	if (!inFile.is_open())
	{
		cout << "Fail to open the config file! The server will run as the default configuration!" << endl;
		return 0;
	}
	while (getline(inFile, ori))
	{
		ori = ori.substr(0, ori.find('#'));
		if (ori.size())
		{
			colon = ori.find(':');
			tail = min(ori.find('\r'), ori.find('\n'));
			tail = min(ori.find_last_not_of(' ')+1, tail);
			key = ori.substr(0, colon);
			if (colon+2<ori.size())
				value = ori.substr(colon + 2, tail - colon - 2);
			if (key == "SERVERADDRESS")
				Config::SERVERADDRESS = value;
			else if (key == "SERVERPORT")
				Config::PORT = stoi(value);
			else if (key == "MAXCONNECTION")
				Config::MAXCONNECTION = stoi(value);
			else if (key == "BLOCKMODE")
				Config::BLOCKMODE = stoi(value);
			else if (key == "BUFFERLENGTH")
				Config::BUFFERLENGTH = stoi(value);
			else if (key == "ROOTPATH")
				Config::ROOTPATH = value;
			else if (key == "TIMEOUT")
			{
				Config::TIMEOUT.tv_sec = stoi(value.substr(0, value.find('.')));
				Config::TIMEOUT.tv_usec = stoi(value.substr(value.find('.') + 1));
			}
			else if (key == "Content-type")
			{
				int pos1, pos2;
				while (getline(inFile, ori))
				{
					pos1 = ori.find(' ');
					pos2 = ori.find(' ', pos1 + 1);
					Config::CONTENTTYPE.insert(make_pair(ori.substr(pos1+1,pos2-pos1-1),ori.substr(pos2+1)));
				}
			}
		}
	}
	cout << "Server root path:"<<Config::ROOTPATH << endl;
	return 0;
}

void Config::setDefault()
{
	Config::SERVERADDRESS = "127.0.0.1";										//������IP��ַ
	Config::MAXCONNECTION = 50;													//���������50
	Config::BUFFERLENGTH = 4096;												//��������С4096�ֽ�
	Config::PORT = 5050;														//�������˿�5050
	Config::BLOCKMODE = 1;														//SOCKETΪ������ģʽ
	Config::ROOTPATH = "D:\\GitHub\\My Blog\\.deploy_git";						//�������ļ���Ŀ¼
	Config::TIMEOUT.tv_sec = 10;												//��������ʱʱ����λ
	Config::TIMEOUT.tv_usec = 0;												//��������ʱ�¼�����λ
	Config::CONTENTTYPE.insert(make_pair(".*","application/octet-stream"));		//������
}

int Config::clear()
{
	Config::CONTENTTYPE.clear();
	return 1;
}

int Config::setIP(string s)
{
	if (s!="")
		Config::SERVERADDRESS = s;
	return 1;
}
int Config::setPORT(string s)
{
	if (s!="")
		Config::PORT = stoi(s);
	return 1;
}


int Config::MAXCONNECTION;					//���������
int Config::BUFFERLENGTH;					//��������С
int Config::PORT;							//�������˿�
string Config::SERVERADDRESS;				//��������ַ
u_long Config::BLOCKMODE;					//SOCKET����ģʽ
timeval Config::TIMEOUT;					//��������ʱʱ��
string Config::ROOTPATH;					//��������Ŀ¼
multimap<string, string> Config::CONTENTTYPE;	//�ļ�����