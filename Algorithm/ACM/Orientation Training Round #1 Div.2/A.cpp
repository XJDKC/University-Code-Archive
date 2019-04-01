#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int n,L,len,maxlen=0,rate=0;
string s;
bool judge(int lenth)
{
	bool same=true;
	for (int i=1;i<=lenth/2;i++)
	{
		same=true;
		for (int j=lenth-1;j>=lenth-i;j--)
		{
			if (s[j]!=s[j-i])
			{
				same=false;
				break;
			}
		}
		if (same==true) return true;
	}
	return false;
}

void find(int lenth)
{
	if (rate==n)
	{
		len=lenth;
		return ;
	}
	else 
	{
		if (lenth == maxlen)
		{
			s += 'A' - 1;
			maxlen++;
		}
		else
		{
			s[lenth] = 'A' - 1;
		}
		for (int j=0;j<L&&rate<n;j++)
		{
			s[lenth]++;
			if (!judge(lenth+1))
			{
				rate++;
				find(lenth+1);
			}
		}
	}
}

int main()
{
	while (cin>>n>>L&&n&&L)
	{
		rate=0;
		find(0);
		for (int i=0;i<len;i++)
		{
			cout<<s[i];
			if (i%64==63)
			{
				cout<<endl;
			}
			else if (i%4==3&&i<len-1)
			{
				cout<<" ";
			}
		}
		if (len%64)
		{
			cout<<endl;
		}
		cout<<len<<endl;
	}
	return 0;
}