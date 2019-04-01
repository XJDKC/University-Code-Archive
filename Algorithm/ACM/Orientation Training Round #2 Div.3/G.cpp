#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<cmath>
using namespace std;
int t,c;
char s1[105],s2[105],s[210];
char f1[105],f2[105],f[210];
void shuffle()
{
    int i;
    for (i=0;i<2*c;i++)
    {
        if (i%2)
        {
            s[i]=s1[i/2];
        }
        else
        {
            s[i]=s2[i/2];
        }
    }
    s[i]='\0';
    for (i=0;i<c;i++)
    {
        s1[i]=s[i];
    }
    for (;i<2*c;i++)
    {
        s2[i-c]=s[i];
    }
}
int solve()
{
    bool mark=false;
    int step=0;
    do 
    {
        shuffle();
        step++;
        if (!strcmp(s1,f1)&&!strcmp(s2,f2))
        {
            step=-1;
            break;
        }
    }while (strcmp(s,f)!=0);
    return step;
}
int main()
{
    int ans;
    cin>>t;
    for (int i=1;i<=t;i++)
    {
        cin>>c;
        scanf("%s%s%s",s1,s2,s);
        strcpy(f1,s1);
        strcpy(f2,s2);
        strcpy(f,s);
        ans=solve();
        cout<<i<<" "<<ans<<endl;
    }
    return 0;
}