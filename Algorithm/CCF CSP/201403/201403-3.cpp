//
// Created by xjdkc on 19-3-1.
//

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <stack>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cctype>

using namespace std;

int n;
string formatString;
map<char,bool> format;

void trans();
void process();

int main()
{
    cin>>formatString;
    trans();
    process();
    return 0;
}

void trans()
{
    int length=formatString.size();
    for(int i=0;i<length;i++)
    {
        if (i!=length-1&&formatString[i+1]==':')
            format[formatString[i++]]=true;
        else
            format[formatString[i]]=false;
    }
}

void process()
{
    string temp;
    stringstream ss;
    vector<string> sv;
    map<string,string> linemap;
    map<char,bool>::iterator it;

    cin>>n;cin.get();
    for (int i=0;i<n;i++)
    {
        getline(cin,temp);
        sv.clear();
        ss.clear();
        ss.str(temp);
        while (getline(ss,temp,' '))
        {
            sv.push_back(temp);
        }

        linemap.clear();
        for (int j=1;j<sv.size();j++)
        {
            if (sv[j].size()==2&&sv[j][0]=='-')
            {
                it=format.find(sv[j][1]);
                if (it!=format.end())
                {
                    if (it->second)
                    {
                        if (j!=sv.size()-1)
                        {
                            linemap[sv[j]]=sv[j+1];
                            j++;
                        }
                        else
                            break;
                    }
                    else
                        linemap[sv[j]]="";
                }
                else
                    break;
            }
            else
                break;
        }
        cout<<"Case "<<i+1<<":";
        for (map<string,string>::iterator it=linemap.begin();it!=linemap.end();it++)
        {
            cout<<" "<<it->first;
            if (it->second!="")
                cout<<" "<<it->second;
        }
        cout<<endl;
    }
}
/*

albw:x
4
ls -a -l -a documents -b
ls
ls -w 10 -x -w 15
ls -a -b -c -d -e -l

 */