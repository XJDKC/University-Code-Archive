#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>
#include<iomanip>
using namespace std;
const int N = 100006;
int f[N];
int main()
{
	int n,sum;
	cin>>n;
	for (int i=1;i<=n;i++)
		cin>>f[i];
	cout<<max(f[1],f[n])<<" ";
	if ((n+1)%2==1)
	{
		sum=f[(n+1)/2]+f[(n+1)/2+1];
        if (sum/2*2!=sum)
			printf("%.1lf ",sum/2.0);
		else
			cout<<sum/2<<" ";
	}
	else
        cout<<f[(n+1)/2]<<" ";
    cout<<min(f[1],f[n])<<endl;	
	return 0;
}
