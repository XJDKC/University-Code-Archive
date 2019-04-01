#include<iostream>
#include<cmath>
using namespace std;
const int oo=0x7fffffff;
int main()
{
	int k,l;
	int edge;
	cin>>k;
	l=oo;
	edge=sqrt(k)+1;
	for (int i=1;i<=edge;i++)
	{
		if (k%i==0)
		{
			if (i>2&&i-1<l)
			{
				l=i-1;
			}
			if (k/i>2&&k/i-1<l)
			{
				l=k/i-1;
			}
		}
	}
	if (l==oo) cout<<"0"<<endl;
	else cout<<l<<endl;
	return 0;
}