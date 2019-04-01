//
// Created by xjdkc on 19-3-14.
//

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
vector<string> cur;

string trans(string s)
{
    string temp="";
    for (int i=0;i<s.size();i++)
    {
        if (i<s.size()-1&&s[i]=='/'&&s[i+1]=='/')
            continue;
        temp+=s[i];
    }
    //if (temp.size()>1&&temp[temp.size()-1]=='/')
    //    temp=temp.substr(0,temp.size()-1);
    return temp;
}

void Split(string s,vector<string> &sv,char c)
{
    string temp;
    stringstream ss;
    ss<<s;
    while (getline(ss,temp,c))
    {
        sv.push_back(temp);
    }
}
int main()
{
    int n;
    string path,s;
    cin>>n;
    cin>>path;cin.get();
    Split(trans(path),cur,'/');
    for (int i=0;i<n;i++)
    {
        getline(cin,s);
        if (s=="") s=path;
        if (s[0]!='/')
            s=path+'/'+s;

        vector<string> sv;
        s=trans(s.substr(1));
        Split(s,sv,'/');
        for (int j=0;j<sv.size();j++)
        {
            if (sv[j]==".") {
                sv.erase(sv.begin() + j);
                j--;
            }
            if (sv[j]=="..")
            {
                sv.erase(sv.begin()+j);
                if (j>0) {
                    sv.erase(sv.begin() + j - 1);
                    j--;
                }
                j--;
            }
        }
        cout<<'/';
        for (int j=0;j<sv.size();j++)
        {
            cout<<sv[j];
            if (j<sv.size()-1)
                cout<<"/";
        }
        cout<<endl;
    }
    return 0;
}

