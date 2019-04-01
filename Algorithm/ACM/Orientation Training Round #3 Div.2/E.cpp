#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cmath>
using namespace std;
int dp[1005][1005],last[1005];
string s1,s2;
void output(int x,int y)
{
    if (x==0||y==0)
    {
        return ;
    }
    else
    {
        if (s1[x-1]==s2[y-1])
        {
            output(x-1,y-1);
            printf("%c",s1[x-1]); 
        }
        else if (dp[x-1][y]>dp[x][y-1])  
            output(x-1,y);
        else 
            output(x,y-1);   
    }
}
int main()
{
    int n,ans=1,tail=1;
    cin>>s1>>s2;
    for (int i=1;i<=s1.size();i++)
    {
        for (int j=1;j<=s2.size();j++)
        {
            if (s1[i-1]==s2[j-1])
            {
                dp[i][j]=dp[i-1][j-1]+1;
            }
            else
            {
                dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            }
        }
    }
    output(s1.size(),s2.size());
    printf("\n");
    system("pause");
    return 0;
}