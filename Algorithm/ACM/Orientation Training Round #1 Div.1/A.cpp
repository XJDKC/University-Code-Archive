#include<iostream>
#include<string>
using namespace std;
int main()
{
	int n,x=0;
	int a[2]={0};
	string s;
	cin>>n;
	for (int i=0;i<n;i++)
	{
		cin>>s;
		if (s.find('+')!=s.npos)
		{
			a[0]++;
		}
		else if (s.find('-')!=s.npos)
		{
			a[1]++;
		}
	}
	x=a[0]-a[1];
	cout<<x<<endl;
	return 0;
}