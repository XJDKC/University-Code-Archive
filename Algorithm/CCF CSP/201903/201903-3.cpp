#include <iostream>
#include <string>
#include <cctype>
using namespace std;
const int N = 1006;
const int BYTE = 40*1024+6;

unsigned int disk[N][BYTE];
bool existed[N];
int n,s,l;
int blkSize=0;
int missNo=-1;

unsigned int trans(char c)
{
    if (isdigit(c))
        return c-'0';
    else if (isalpha(c))
        return c-'A'+10;
    return 0;
}
char untrans(unsigned int a)
{
    if (a<10)
        return a+'0';
    else
        return a+'A'-10;
}

void loadData(int no,string &s)
{
    existed[no]=true;
    for (int i=0;i<s.size();i=i+8)
    {
        for (int j=0;j<8;j++)
        {
            disk[no][i/8]+=trans(s[i+j])<<(j*4);
        }
    }
}

void LocateData(int no,int &diskNo,int &BlkNo)
{
    int no1,no2;
    no1=no/s;       //条编号        4
    no2=no1/n;      //除去p后行号   1
    diskNo=no1%n;   //1
    BlkNo=(no2)/(n-1)*n*s+(no2%(n-1)>=(n-1-diskNo)?1:0)*s+(no2%(n-1)*s)+(no%s);
}

string Decode(unsigned int a)
{
    string temp="";
    for (int i=0;i<8;i++)
    {
        temp+=untrans((a>>(i*4))&0xf);
    }
    return temp;
}

string recover(int diskNo,int BlkNo)
{
    int ans=0;
    for (int i=0;i<n;i++)
    {
        if (existed[i])
            ans^=disk[i][BlkNo];
	}
    return Decode(ans);
}

int main()
{
    int m;
    unsigned int temp;
    int no,diskNo,BlkNo;
    string ss;
    cin>>n>>s>>l;
    for (int i=0;i<l;i++)
    {
        cin>>no>>ss;
        loadData(no,ss);
    }
    blkSize=(ss.size()/8-1);
    cin>>m;
    for (int i=0;i<m;i++)
    {
        cin>>no;
        LocateData(no,diskNo,BlkNo);
        if (BlkNo>blkSize)
        	cout<<"-"<<endl;
        
        else if (!existed[diskNo])
        {
            if (l+1<n)
                cout<<'-'<<endl;
            else
                cout<<recover(diskNo,BlkNo)<<endl;
        }
        else
        {
            temp=disk[diskNo][BlkNo];
            cout<<Decode(temp)<<endl;
        }
    }
    return 0;
}
/*
2 1 2
0 000102030405060710111213141516172021222324252627
1 000102030405060710111213141516172021222324252627
2
0
1

3 2 2
0 000102030405060710111213141516172021222324252627
1 A0A1A2A3A4A5A6A7B0B1B2B3B4B5B6B7C0C1C2C3C4C5C6C7
2
2
5
*/
