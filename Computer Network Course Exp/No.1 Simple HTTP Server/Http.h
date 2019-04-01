#pragma once
#include<string>
#include<list>
#include<map>

using namespace std;

class Http
{
	bool found;					//找到请求资源
	string method;				//请求方式
	string url;					//请求URL
	string file;				//请求文件
	string version;				//HTTP version
	string data;				//数据段
	string res;					//响应报文
	map<string, string> para;	//请求参数 

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