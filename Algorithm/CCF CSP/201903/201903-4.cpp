#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<queue>
#include<cstdlib> 
#include<cstring>
using namespace std;
const int N = 10006;

struct Process
{
    int cur,total;
    bool type[8];
    int no[8];
};

Process p[N];
bool waiting[N],finished[N];

int T,n;

int toInt(string s)
{
    int temp;
    stringstream ss;
    ss<<s;
    ss>>temp;
    return temp;
}

void Trans(int no,string s)
{
    string temp;
    stringstream ss;
    ss<<s;
    p[no].cur=p[no].total=0;
    while (getline(ss,temp,' '))
    {
        p[no].type[p[no].total]=temp[0]=='S'?0:1;
        p[no].no[p[no].total++]=toInt(temp.substr(1));
    }
}

bool isLock()
{
    int waitNo=0,finishedNo=0;
    while (finishedNo<n)
    {
        for (int i=0;i<n;i++)
        {
            if (!waiting[i]&&!finished[N])
            {
                int temp=p[i].no[p[i].cur];
                if (waiting[temp]&&!finished[temp]&&p[i].type[p[i].cur]!=p[temp].type[p[temp].cur])
                {
                    p[i].cur++;
                    if (p[i].cur==p[i].total)
                    {
                        finished[i]=true;
                        finishedNo++;
                    }
                    p[temp].cur++;
                    if (p[temp].cur==p[temp].total)
                    {
                        finished[temp]=true;
                        finishedNo++;
                    }
                    waiting[temp]=false;
                    waitNo--;
                }
                else
                {
                    waiting[i]=true;
                    waitNo++;
                }
            }            
        }
        if (waitNo==n)
            return true;
    }
    return false;
}

int main()
{
    string s;
	cin>>T>>n;cin.get();
	while (T--)
	{
        memset(waiting,0,sizeof(waiting));
        memset(finished,0,sizeof(finished));
		for (int i=0;i<n;i++)
        {
            getline(cin,s);
            Trans(i,s);
        }
        cout<<isLock()<<endl;
	}
    return 0;
}

/*
3 2
R1 S1
S0 R0
R1 S1
R0 S0
R1 R1 R1 R1 S1 S1 S1 S1
S0 S0 S0 S0 R0 R0 R0 R0

2 3
R1 S1
R2 S0 R0 S2
S1 R1
R1
R2 S0 R0
S1 R1 
*/ 
