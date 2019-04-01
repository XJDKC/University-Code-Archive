#include<iostream>
using namespace std;
int main()
{
	int a[55];
	int n,k,ans=0;
	cin>>n>>k;
	for (int i=1;i<=n;i++)
	{
		cin>>a[i];
		if (i<=k&&a[i]>0) ans++;
		else if (i>k&&a[i]==a[k]&&a[i]>0) ans++;
	}
	cout<<ans<<endl;
	return 0;
}