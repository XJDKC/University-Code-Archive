#include<iostream>
#include<algorithm>
using namespace std;
int a[1000005]={0},maxnum=0;
unsigned int cal(unsigned int num)
{
	if (num<1000001&&num>1&&a[num])
	{
		return a[num];
	}
	else if (num==1)
	{
		return 1;
	}
	else 
	{
		if (num%2)
		{
			return 1 + cal(num * 3 + 1);
		}
		else 
		{
			return (1 + cal(num / 2));
		}
	}
}
int main()
{
	bool mark=false;
	int x, y,maxn=0;
	for (int i=1;i<1000001;i++)
	{
		if (!a[i])
		{
			a[i]=cal(i);
		}
	}
	while (cin >> x >> y)
	{
		maxn = 0;
		mark=false;
		if (x>y)
		{
			swap(x,y);
			mark=true;
		}
 		for (int i = x; i <= y; i++)
		{
			maxn = max(a[i], maxn);
		}
		if (!mark) cout << x << " " << y << " " << maxn << endl;
		else cout << y << " " << x << " " << maxn << endl;
	}
	return 0;
}