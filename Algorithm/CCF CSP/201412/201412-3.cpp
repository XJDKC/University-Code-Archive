//
// Created by xjdkc on 19-3-14.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

const int N = 5006;

struct action
{
    int type;
    double price;
    long long num;
    bool operator <(const action &b)const {
        if (type<0||b.type<0) return type>b.type;
        if (price==b.price) return type>b.type;
        return price<b.price;
    }
};

long long buy[N],sell[N];

action total[N];

int main()
{
    double ansp=0;
    long long anss=0;
    int line=0,no,num=0;
    string s;
    while (cin>>s)
    {
        if (s=="buy")
        {
            num++;
            total[++line].type=0;
            cin>>total[line].price>>total[line].num;
        }
        else if (s=="sell")
        {
            num++;
            total[++line].type=1;
            cin>>total[line].price>>total[line].num;
        }
        else
        {
            cin>>no;
            total[++line].type=-1;
            if (total[no].type>=0)
            {
                total[no].type=-1;
                num--;
            }
        }
    }
    sort(total+1,total+line+1);
    sell[0]=0;
    for (int i=1;i<=num;i++)
    {
        sell[i]=sell[i-1];
        if (total[i].type==1)
            sell[i]+=total[i].num;
    }

    buy[num+1]=0;
    for (int i=num;i>=1;i--)
    {
        buy[i]=buy[i+1];
        if (total[i].type==0)
            buy[i]+=total[i].num;
    }


    for (int i=1;i<=num;i++)
    {
        long long temp=min(buy[i],sell[i]);
        if (temp>=anss)
        {
            ansp=total[i].price;
            anss=temp;
        }
    }
    cout<<setiosflags(ios::fixed)<<setprecision(2)<<ansp<<" "<<anss<<endl;
    return 0;
}