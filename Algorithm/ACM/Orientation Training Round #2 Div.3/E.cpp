#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
using namespace std;
int n;
int mod[101];
int getmod(int num)
{
    int temp=0,i=1;
    while (num)
    {
        if (num%2)
        {
            temp+=mod[i];
        }
        num/=2;
        i++;
    }
    return temp%n;
}
void output(int num)
{
    if (num)
    {
        output(num/2);
        cout<<num%2;
    }
}
int main()
{
    int num;
    int ans;
    while (scanf("%d",&n)&&n)
    {
        mod[1]=1%n;
        for (int i=2;i<=100;i++)
            mod[i]=(mod[i-1]*10)%n;
        for (int i=1;1;i++)
        {
            ans=getmod(i);
            if (!ans)
            {
                ans=i;
                break;
            }
        }
        output(ans);
        cout<<endl;
    }
    return 0;
}