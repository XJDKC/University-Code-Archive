//
// Created by xjdkc on 19-3-14.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;


int main()
{
    bool Type;
    int n;
    string s,x,temp;
    cin>>s;
    cin>>Type>>n;
    if (!Type)
        transform(s.begin(),s.end(),s.begin(),::tolower);
    for (int i=0;i<n;i++)
    {
        cin>>x;
        temp.resize(x.size());
        if (!Type)
        {
            transform(x.begin(),x.end(),temp.begin(),::tolower);
        }
        else
            temp=x;
        if (temp.find(s)!=temp.npos)
            cout<<x<<endl;
    }
    return 0;
}
/*
 *
Hello
0
5
HelloWorld
HiHiHelloHiHi
GrepIsAGreatTool
HELLO
HELLOisNOTHello
 */