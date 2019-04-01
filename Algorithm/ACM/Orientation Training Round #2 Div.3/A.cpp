#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,k,ans;
bool map[8][8],used[8];
void dfs(int row,int num)
{
    if (num==k)
    {
        ans++;
        return ;
    }
    else if (row>=n) return ;
    else if (num+n-row<k) return ;
    else
    {
        if (row+1<n) dfs(row+1,num);
        for (int i=0;i<n;i++)
        {
            if (map[row][i]&&!used[i])
            {
                used[i]=true;
                dfs(row+1,num+1);
                used[i]=false;
            }
        }
    }
}
int main()
{
    char c;
    while (cin>>n>>k&&n!=-1&&k!=-1)
    {
        getchar();
        ans=0;
        memset(map,0,sizeof(map));
        memset(used,0,sizeof(used));
        for (int i=0;i<n;i++)
        {
            for (int j=0;j<n;j++)
            {
                scanf("%c",&c);
                map[i][j]=c=='.'?false:true;
            }
            getchar();
        }
        dfs(0,0);
        printf("%d\n",ans);
    }
    return 0;
}