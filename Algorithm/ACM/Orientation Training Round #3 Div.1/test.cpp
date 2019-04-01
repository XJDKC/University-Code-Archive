//2017-04-04
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct node
{
    int w, s, pos;
    bool operator<(node x)const
    {
        return w < x.w;
    }
}mice[1005];
int dp[1005], pre[1005];//dp[i]表示前i只老鼠的最长下降子序列

void print(int pos)
{
    if(pos == -1)return ;
    print(pre[pos]);
    printf("%d\n", mice[pos].pos);
}

int main()
{
    int n = 0, w, s;
    memset(pre, -1, sizeof(pre));
    while(scanf("%d%d", &w, &s)!=EOF)
    {
        mice[n].w = w;
        mice[n].s = s;
        mice[n].pos = n+1;
        n++;
    }
    sort(mice, mice+n);
    int pos = -1, mx = 0;
    for(int i = 0; i < n; i++){
        dp[i] = 1;
        for(int j = 0; j < i; j++){
            if(mice[j].w < mice[i].w && mice[j].s > mice[i].s){
                if(dp[j]+1 > dp[i]){
                    dp[i] = dp[j]+1;
                    pre[i] = j;
                }
            }
        }
        if(dp[i] > mx){
            mx = dp[i];
            pos = i;
        }
    }
    printf("%d\n", mx);
    print(pos);
    system("pause");
    return 0;
}