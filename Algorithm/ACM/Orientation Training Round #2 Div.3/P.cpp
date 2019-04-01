#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cmath>
using namespace std;
long long gcd(long long a,long long b)
{
    if (b==0) return a;
    return gcd(b,a%b);
}
void exgcd(long long a,long long b,long long &x,long long &y)
{
    if (b==0)
    {
        x=1;y=0;
        return ;
    }
    exgcd(b,a%b,x,y);
    long long temp=x;
    x=y;y=temp-a/b*y;
}
int main()
{
    long long x,y,m,n,l;
    scanf("%lld%lld%lld%lld%lld",&x,&y,&m,&n,&l);
    long long a=n-m,b=l,c=x-y,d=gcd(a,b);
    if (c%d) printf("Impossible\n");
    else
    {
        long long ans1,ans2;
        a/=d;b/=d;c/=d;
        exgcd(a,b,ans1,ans2);
        ans1=((c*ans1)%b+b)%b; //x=x0*c+b*k
        if (!ans1) ans1+=b;    //ans1=0的情况
        printf("%lld\n",ans1);
    }
    system("pause");
    return 0;
}