#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<cmath>
using namespace std;
int n,m;
int myq[10001],step[10001],head,tail;
bool isprime[10001];
void init()
{
    int temp;
    for (int i=1000;i<=10000;i++)
    {
        temp=sqrt((double)i)+1;
        isprime[i]=true;
        for (int j=2;j<=temp+1;j++)
        {
            if (i%j==0)
            {
                isprime[i]=false;
                break;
            }
        }
    }
}
void bfs()
{
    bool mark=false;
    int num,temp,a[4],i,tmp;
    while (head<=tail&&!mark)
    {
        num=myq[head];
        if (num==m) mark=true;
        else
        {
            i=0;
            temp=num;
            while (temp)
            {
                a[i++]=temp%10;
                temp/=10;
            }
            for (i=0;i<4;i++)
            {
                for (int j=0;j<10;j++)
                {
                    if (j!=a[i]&&!(i==3&&j==0)) //如果不等于原来的值 注意最高为为0
                    {
                        tmp=a[i];               
                        a[i]=j;
                        temp=a[3]*1000+a[2]*100+a[1]*10+a[0];
                        if (isprime[temp]&&!step[temp])
                        {
                            myq[++tail]=temp;
                            step[temp]=step[num]+1;
                        }
                        a[i]=tmp;
                    }
                }    
            }
        }
        head++;
    }
}
int main()
{
    int t;
    init();
    cin>>t;
    while (t--)
    {
        head=tail=0;
        memset(step,0,sizeof(step));
        cin>>n>>m;
        myq[0]=n;
        bfs();
        cout<<step[m]<<endl;
    }
    return 0;
}