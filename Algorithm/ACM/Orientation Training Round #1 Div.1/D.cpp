#include<iostream>
#include<cstdlib>
using namespace std;
int main()
{
	long long n;
	cout<<"please input n:";
	cin>>n;
	if (n%2==0)
	{
		cout<<n/2<<endl;
	}
	else 
	{
		cout<<(n-1)/2-n<<endl;
	}
	//system("pause");
	return 0;
}