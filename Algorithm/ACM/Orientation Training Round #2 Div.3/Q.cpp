#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cmath>
using namespace std;
int n,c;
int pos[100005],ans;
bool judge(int dis)
{
    int cal=1;
    for (int i=1,last=0;i<n;i++)
    {
        if (pos[i]-pos[last]>=dis)
        {
            last=i;
            cal++;
        }
        if (cal>=c) return true;
    }
    return false;
}
void search()
{
    int low=1,high=pos[n-1]-pos[0],mid;
    while (low<=high)
    {
        mid=low+(high-low)/2;
        if (judge(mid))
        {
            low=mid+1;
        }
        else
        {
            high=mid-1;
        }
    }
    ans=high;
}
int main()
{
    scanf("%d%d",&n,&c);
    for (int i=0;i<n;i++)
        scanf("%d",&pos[i]);
    sort(pos,pos+n);
    search();
    printf("%d\n",ans);
    system("pause");
    return 0;
}