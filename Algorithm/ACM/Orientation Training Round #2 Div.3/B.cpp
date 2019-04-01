#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
const int oo=0x7fffffff;
const int N=31;
struct node{
    int l;
    int r;
    int c;
}q[30000];
int L,R,C,LL,RR,CC;
int ans=oo,direct[6][3]={{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};
int step[30000],head=0,tail=0;
bool visited[N][N][N];
char map[N][N][N];
void bfs()
{
    int l,r,c;
    bool mark=false;
    while (head<=tail&&!mark)
    {
        l=q[head].l;r=q[head].r;c=q[head].c;
        for (int i=0;i<6;i++)
        {
            l+=direct[i][0];
            r+=direct[i][1];
            c+=direct[i][2];
            if (l>=0&&l<L&&r>=0&&r<R&&c>=0&&c<C&&
                !visited[l][r][c]&&map[l][r][c]=='.')
            {
                visited[l][r][c]=true;
                if (l==LL&&r==RR&&c==CC) 
                {
                    mark=true;
                    ans=step[head]+1;
                    break;
                }
                q[++tail].l=l;q[tail].r=r;q[tail].c=c;
                step[tail]=step[head]+1;
            }
            l-=direct[i][0];
            r-=direct[i][1];
            c-=direct[i][2];
        }
        head++;
    }
}
int main()
{
    int l,r,c;
    while (scanf("%d%d%d",&L,&R,&C)!=EOF&&L)
    {
        getchar();
        ans=oo;
        head=tail=0;
        memset(map,0,sizeof(map));
        memset(step,0,sizeof(step));
        memset(visited,0,sizeof(visited));
        for (int i=0;i<L;i++)
        {
            for (int j=0;j<R;j++)
            {
                for (int k=0;k<C;k++)
                {
                    scanf("%c",&map[i][j][k]);
                    if (map[i][j][k]=='S')
                    {
                        l=i;r=j;c=k;
                    }
                    else if (map[i][j][k]=='E')
                    {
                        LL=i;RR=j;CC=k;
                        map[i][j][k]='.';
                    }
                }
                getchar();
            }
            getchar();
        }
        visited[l][r][c]=true;
        q[0].l=l;q[0].r=r;q[0].c=c;
        bfs();
        if (ans==oo) printf("Trapped!\n");
        else printf("Escaped in %d minute(s).\n",ans);
    }
    return 0;
}