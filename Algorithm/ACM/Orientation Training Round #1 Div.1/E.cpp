#include<iostream>
#include<string>
using namespace std;
int main()
{
	int temp;
	char c;
	string keyboard="qwertyuiopasdfghjkl;zxcvbnm,./";
	string s;
	cin>>c;
	cin>>s;
	c=c=='R'?-1:1;
	for (int i=0;i<s.size();i++)
	{
		temp=keyboard.find(s[i]);
		cout<<keyboard[temp+c];
	}
	cout<<endl;
	return 0;
}