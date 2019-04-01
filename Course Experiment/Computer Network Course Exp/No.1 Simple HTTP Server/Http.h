#pragma once
#include<string>
#include<list>
#include<map>

using namespace std;

class Http
{
	bool found;					//�ҵ�������Դ
	string method;				//����ʽ
	string url;					//����URL
	string file;				//�����ļ�
	string version;				//HTTP version
	string data;				//���ݶ�
	string res;					//��Ӧ����
	map<string, string> para;	//������� 

protected:
	void clearAll();
	void decodeURL();

public:
	void parseRequest(string req);
	int generateRespond();
	string &getRespond();
	string &getURL();
	string &getMethod();
};