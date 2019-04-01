//
// Created by xjdkc on 19-3-14.
//

#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
const int N = 1006;

struct PAIR
{
    int key;
    int value;
    bool operator<(const PAIR &a)const {
        if (value==a.value) return key<a.key;
        return value>a.value;
    }
};

PAIR f[N];

int main()
{
    int n,x,num=0;
    cin>>n;
    for (int i=1;i<=n;i++)
    {
        cin>>x;
        f[x].key=x;
        if (!f[x].value) num++;
        f[x].value++;
    }
    sort(f,f+N);
    for (int i=0;i<num;i++)
        cout<<f[i].key<<" "<<f[i].value<<endl;

    return 0;
}