//
// Created by xjdkc on 19-3-14.
//

#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <cctype>
using namespace std;
vector<string> sv;
map<string,string> sm;
int main()
{
    int m,n;
    string s1,s2;
    cin>>m>>n;
    getchar();
    for (int i=0;i<m;i++)
    {
        getline(cin,s1);
        sv.push_back(s1);
    }
    for (int i=0;i<n;i++)
    {
        cin>>s1;
        getchar();
        getline(cin,s2);
        s1=s1;
        s2=s2.substr(1,s2.size()-2);
        sm[s1]=s2;
    }
    for (int i=0;i<sv.size();i++)
    {
        for (int j=0;j<sv[i].size();)
        {
            bool flag=false;
            int pos1=sv[i].find("{{ ",j),pos2;
            if (pos1!=-1)
            {
                pos2 = sv[i].find(" }}",pos1+3);
                if (pos2!=-1)
                {
                    flag=true;
                    string temp=sv[i].substr(pos1+3,pos2-pos1-3);
                    for (int k=0;k<temp.size();k++)
                    {
                        if (!(isdigit(temp[k])||isalpha(temp[k])||temp[k]=='_'))
                        {
                            flag=false;
                            break;
                        }
                    }
                    if (flag)
                    {
                        cout<<sv[i].substr(j,pos1-j);
                        for (auto it=sm.begin();it!=sm.end();it++)
                        {
                            if (temp==it->first)
                            {
                                cout<<it->second;
                                break;
                            }
                        }
                    }
                }
            }
            if (flag)
            {
                j=pos2+3;
            }
            else
            {
                if (pos1==-1)
                {
                    cout<<sv[i].substr(j);
                    j=sv[i].size();
                }
                else
                {
                    cout<<s2.substr(j,pos1+3-j);
                    j=pos1+3;
                }
            }
        }
        cout<<endl;
    }
    return 0;
}