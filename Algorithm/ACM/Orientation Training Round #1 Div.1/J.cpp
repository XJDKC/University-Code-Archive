#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	long long n,x,y,maxk=0,ansi=1,ansj=2;
	cin>>n;
	cin>>x;
	for (int i=2;i<=n;i++)
	{
		cin>>y;
		if (abs(y-x)>maxk)
		{
			maxk=abs(y-x);
			ansi=i-1;
			ansj=i;
		}
		x=y;
	}
	cout<<ansi<<" "<<ansj<<endl;
	return 0;
}