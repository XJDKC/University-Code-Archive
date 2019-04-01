#include<iostream>
using namespace std;
bool existed[200]={false};
int main()
{
	int ans=0;
	string s;
	cin>>s;
	for (int i=0;i<s.size();i++)
	{
		if (!existed[s[i]])
		{
			existed[s[i]]=true;
			ans++;
		}
	}
	if (ans%2)	cout<<"IGNORE HIM!"<<endl;
	else cout<<"CHAT WITH HER!"<<endl;
	return 0;
}