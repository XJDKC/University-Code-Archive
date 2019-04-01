#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cctype>
#include<string>
#include<cmath>
#include<queue>
#include<stack>
#include<set>
#include<map>
using namespace std;
#define ll long long
const int oo=0x7fffffff;
const ll loo=0x7fffffffffffffff;

int main()
{
    int n,x,num,time;
    while (scanf("%d",&n)!=EOF)
    {
        time=1;
        scanf("%d",&num);
        for (int i=1;i<n;i++)
        {
            scanf("%d",&x);
            if (x!=num)
            {
                if (time==1)
                    num=x;
                else
                    time--; 
            }
            else
            {
                time++;
            }
        }
        printf("%d\n",num);
    }
    system("pause");
    return 0;
}