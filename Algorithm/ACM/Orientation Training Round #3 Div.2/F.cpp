#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cmath>
using namespace std;
int a[40005],dp[40005];
int find(int left,int right,int num)
{
    int mid;
    while (left<=right)
    {
        mid=left+(right-left)/2;
        if (dp[mid]>=num)
        {
            right=mid-1;
        }
        else 
        {
            left=mid+1;
        }
    }
    return right;
}
int main()
{
    int t,n,ans=0;
    scanf("%d",&t);
    while (t--)
    {
        ans=1;
        scanf("%d",&n);
        for (int i=0;i<n;i++)
        {
            scanf("%d",&a[i]);
        }
        dp[1]=a[0];
        for (int i=1,pos;i<n;i++)
        {
            pos=find(1,ans,a[i]);
            dp[pos+1]=a[i];
            if (pos==ans) ans++;
        }
        printf("%d\n",ans);
    }
    //system("pause");
    return 0;
}