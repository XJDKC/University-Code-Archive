#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
int toInt(string s)
{
    int temp;
    stringstream ss;
    ss<<s;
    ss>>temp;
    return temp;
}
void Split(string s,vector<int> &sv)
{
    int i,j;
    sv.clear();
    for (i=0,j=0;j<s.size();j++)
    {
        if (s[j]=='+'||s[j]=='-'||s[j]=='x'||s[j]=='/')
        {
            sv.push_back(toInt(s.substr(i,j-i)));
            switch (s[j])
            {
                case '+':sv.push_back(-4); break;
                case '-':sv.push_back(-3); break;
                case 'x':sv.push_back(-2); break;
                case '/':sv.push_back(-1); break;
            }
            i=j+1;
        }
    }
    sv.push_back(toInt(s.substr(i)));
}
int main()
{
    int n;
    vector<int> sv;
    string s;
    cin>>n;
    for (int j=0;j<n;j++)
    {
        cin>>s;
        Split(s,sv);
        for (int i=0;i<sv.size();i++)
        {
            if (sv[i]==-2)
            {
                sv[i-1]=sv[i-1]*sv[i+1];
                sv.erase(sv.begin()+i);
                sv.erase(sv.begin()+i);
                i--;
                continue;
            }
            if (sv[i]==-1)
            {
                sv[i-1]=sv[i-1]/sv[i+1];
                sv.erase(sv.begin()+i);
                sv.erase(sv.begin()+i);
                i--;
                continue;
            }
        }
        for (int i=0;i<sv.size();i++)
        {
            if (sv[i]==-4)
            {
                sv[i-1]=sv[i-1]+sv[i+1];
                sv.erase(sv.begin()+i);
                sv.erase(sv.begin()+i);
                i--;
                continue;
            }
            if (sv[i]==-3)
            {
                sv[i-1]=sv[i-1]-sv[i+1];
                sv.erase(sv.begin()+i);
                sv.erase(sv.begin()+i);
                i--;
                continue;
            }
        }
        if (sv[0]==24)
            cout<<"Yes"<<endl;
        else
            cout<<"No"<<endl;
        
    }
    
}
/*
10
9+3+4x3
5+4x5x5
7-9-9+8
5x6/5x4
3+5+7+9
1x1+9-9
1x9-5/9
8/5+6x9
6x7-3x6
6x4+4/5
*/
