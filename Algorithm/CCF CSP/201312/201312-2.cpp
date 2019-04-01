//
// Created by xjdkc on 19-3-2.
//

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    int sum=0;
    char right;
    string s;
    string num;
    cin>>s;
    num=s.substr(0,1)+s.substr(2,3)+s.substr(6,5);
    for (int i=1;i<=9;i++)
        sum+=i*(num[i-1]-'0');
    sum%=11;
    right=sum<10?sum+'0':'X';
    if (s[12]==right)
        cout<<"Right"<<endl;
    else
        cout<<s.substr(0,12)<<right<<endl;

}
