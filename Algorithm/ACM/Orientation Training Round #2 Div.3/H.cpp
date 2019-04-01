#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cmath>
using namespace std;
struct node{
    int lasta,lastb;
    int step;
    int oper;       //1 给a满上 2 给b满上 3 a干杯 4 b干杯 5 a向b劝酒 6 b向a劝酒 -1 初始状态
}visited[105][105];
node myq[10005];
int A,B,C;
int head,tail;
inline bool move(int &cura,int &curb,int &nexta,int &nextb,int i)
{
    switch(i)
    {
        case 1:if (cura<A)      {nexta=A;nextb=curb;return true;} break;
        case 2:if (curb<B)      {nextb=B;nexta=cura;return true;} break;
        case 3:if (cura)        {nexta=0;nextb=curb;return true;} break;
        case 4:if (curb)        {nextb=0;nexta=cura;return true;} break;
        case 5:if (cura&&curb<B){nexta=cura-min(B-curb,cura);
                                 nextb=curb+min(B-curb,cura);return true;} break;
        case 6:if (curb&&cura<A){nextb=curb-min(A-cura,curb);
                                 nexta=cura+min(A-cura,curb);return true;} break; 
    }
    return false;
}
bool bfs()
{
    bool mark=false;
    int cura,curb;
    int nexta,nextb;
    node cur;
    while (head<=tail)
    {
        cura=myq[head].lasta;
        curb=myq[head].lastb;
        if (cura==C||curb==C) 
        {
            mark=true;
            break;
        }
        for (int i=1;i<7;i++)
        {
            if (move(cura,curb,nexta,nextb,i))
            {
                if (!visited[nexta][nextb].step)
                {
                    visited[nexta][nextb].oper=i;
                    visited[nexta][nextb].lasta=cura;
                    visited[nexta][nextb].lastb=curb;
                    visited[nexta][nextb].step=visited[cura][curb].step+1;
                    myq[++tail].lasta=nexta;
                    myq[tail].lastb=nextb;
                }
            }
        }
        head++;
    }
    return mark;
}
void output(int cura,int curb)
{
    if (cura==-1&&curb==-1)   return ;
    else
    {
        output(visited[cura][curb].lasta,visited[cura][curb].lastb);
        switch(visited[cura][curb].oper)
        {
            case 1:printf("FILL(1)\n");break;
            case 2:printf("FILL(2)\n");break;
            case 3:printf("DROP(1)\n");break;
            case 4:printf("DROP(2)\n");break;
            case 5:printf("POUR(1,2)\n");break;
            case 6:printf("POUR(2,1)\n");break;       
        }
    }
}
int main()
{
    int tempa,tempb;
    scanf("%d%d%d",&A,&B,&C);
    visited[0][0].lasta=-1;
    visited[0][0].lastb=-1;
    visited[0][0].oper=-1;
    visited[0][0].step=1;
    myq[0].lasta=0;
    myq[0].lastb=0;
    if (bfs())
    {
        tempa=myq[head].lasta;
        tempb=myq[head].lastb;
        printf("%d\n",visited[tempa][tempb].step-1);
        output(tempa,tempb);
    }
    else
    {
        printf("impossible\n");
    }
    return 0;
}