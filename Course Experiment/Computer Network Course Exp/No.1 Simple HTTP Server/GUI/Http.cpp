#include "Http.h"
#include "Config.h"
#include <sys/stat.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <codecvt>
#include <vector>


void Http::clearAll()
{
	this->found = false;
	this->method.clear();
	this->url.clear();
	this->file.clear();
	this->version.clear();
	this->para.clear();
	this->data.clear();
	this->res.clear();
}

void Http::parseRequest(string req)
{
	int pos1, pos2, pos3, pos4;		//分别表示Http 第一个空格位置、url中？和#的位置、第二个空位置、第一行结束位置
	string key, value;

	pos1 = req.find(' ');
	pos2 = min(req.find('?', pos1 + 1), req.find('#', pos1 + 1));
	pos3 = req.find(' ', pos1 + 1);
	pos4 = req.find('\n', pos3 + 1);
	pos2 = pos2 != string::npos ? min(pos2, pos3) : pos3;
	
	this->clearAll();

	this->method = req.substr(0, pos1);						//获取 请求方法
	this->url = req.substr(pos1 + 1, pos2 - pos1 - 1);		//获取 请求URL
	this->version = req.substr(pos3 + 1, pos4 - pos3 - 2);	//获取 HTTP版本

	int head, colon, tail;
	head = pos4 + 1;
	while ((tail = req.find('\n', head)) - head > 1)
	{
		colon = req.find(':', head);
		key = req.substr(head, colon - head);
		value = req.substr(colon + 2, tail - colon - 3);
		this->para[key] = value;
		head = tail + 1;
	}

	if (tail + 1 != req.size())
	{
		this->data = req.substr(tail + 1);
	}

	this->file = this->url;

	struct stat sb;
	stat((Config::ROOTPATH + this->file).c_str(), &sb);
	if ((sb.st_mode&S_IFMT) == S_IFDIR)
	{
		if (this->file[this->file.size() - 1] == '/')
			this->file += "index.html";
		else
			this->file += "/index.html";
	}

	this->decodeURL();
}

void Http::decodeURL()			//解析URL
{
	//Stable%20Matching-%E7%A8%B3%E5%AE%9A%E5%8C%B9%E9%85%8D%E9%97%AE%E9%A2%98.html
	char c1, c2, c;
	int textLength;
	string temp;
	for (int i = 0; i < this->file.size(); i++)
	{
		if (this->file[i] == '%')
		{
			c1 = this->file[i + 1]; toupper(c1); c1 = isdigit(c1) ? c1 - '0' : c1 - 'A' + 10;
			c2 = this->file[i + 2]; toupper(c2); c2 = isdigit(c2) ? c2 - '0' : c2 - 'A' + 10;
			switch (c1 * 16 + c2)
			{
				case 0x20:c = ' '; break;
				case 0x22:c = '"'; break;
				case 0x23:c = '#'; break;
				case 0x25:c = '%'; break;
				case 0x26:c = '&'; break;
				case 0x28:c = '('; break;
				case 0x29:c = ')'; break;
				case 0x2B:c = '+'; break;
				case 0x2C:c = ','; break;
				case 0x2F:c = '/'; break;
				case 0x3A:c = ':'; break;
				case 0x3B:c = ';'; break;
				case 0x3C:c = '<'; break;
				case 0x3D:c = '='; break;
				case 0x3E:c = '>'; break;
				case 0x3F:c = '?'; break;
				case 0x40:c = '@'; break;
				case 0x5C:c = '\\'; break;
				case 0x7C:c = '|'; break;
				default:c = c1 * 16 + c2; break;
			}
			temp += c;
			i += 2;
		}
		else
			temp += this->file[i];
	}

	wstring_convert<codecvt_utf8<wchar_t>> conv;
	wstring wString = conv.from_bytes(temp);

	textLength = WideCharToMultiByte(CP_ACP, 0, wString.c_str(), -1, NULL, 0, NULL, NULL);
	vector<char> vecText(textLength, '\0');
	WideCharToMultiByte(CP_ACP, 0, wString.c_str(), -1, &(vecText[0]), textLength, NULL, NULL);
	
	this->file = &(vecText[0]);
}

int Http::generateRespond()
{
	int length=0;
	string extention;
	string content_type="";
	ifstream inFile;
	ostringstream temp;
	multimap<string,string>::iterator it;
	inFile.open(Config::ROOTPATH + this->file, ios::binary);
	if (this->found = inFile.is_open())
	{
		temp << inFile.rdbuf();
		length = temp.str().size();
	}

	if (this->para.find("Accept") != this->para.end()&&this->file.find('.')!=string::npos)
	{
		extention = this->file.substr(this->file.rfind('.'));
		it = Config::CONTENTTYPE.find(extention);

		while (it!=Config::CONTENTTYPE.end()&&it->first == extention)
		{
			if (this->para["Accept"].find(it->second) != string::npos)
			{
				content_type = it->second;
				break;
			}
			it++;
		}
	}
	if (content_type == "")
	{
		it = Config::CONTENTTYPE.find(".*");
		content_type = it->second;
	}
	
	this->res = string("HTTP/1.1 ") + (this->found ? string("200 OK") : string("404 Not Found")) + string("\r\n")
			  + string("Connection: Keep-Alive\r\n")
			  + string("Content-Type: ") + content_type + string("\r\n")
			  + string("Content-Length: ") + to_string(length) + string("\r\n\r\n")
			  + temp.str();
	return length;
}

bool Http::isFound()
{
	return this->found;
}

string &Http::getRespond()
{
	return this->res;
}

string &Http::getURL()
{
	return this->url;
}

string &Http::getMethod()
{
	return this->method;
}