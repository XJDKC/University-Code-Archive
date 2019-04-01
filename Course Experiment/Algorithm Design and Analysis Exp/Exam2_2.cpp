#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
const int N = 100;
struct node
{
    float x, y;
};
node *P[N],*Px[N],*Py[N];
int n;
void input();
float dis(node *a, node *b);
void merge(int n, node *sx[], node *sy[], node *&q1, node *&q2);
bool comp1(const node *a, const node *b);
bool comp2(const node *a, const node *b);
int main()
{
    node *q1, *q2;
    input();
    sort(Px, Px+n, comp1);
    sort(Py, Py+n, comp2);
    merge(n,Px, Py, q1, q2);
    cout << q1->x << " " << q1->y << endl;
    cout << q2->x << " " << q2->y << endl;
    cout << dis(q1, q2) << endl;
}

bool comp1(const node *a,const node *b)
{
    return a->x < b->x;
}
bool comp2(const node *a,const node *b)
{
    return a->y < b->y;
}

void input()
{
    cin>>n;
    node *p;
    for (int i = 0; i < n; i++)
    {
        p = new node;
        cin >> p->x >> p->y;
        Px[i] = Py[i] = P[i] = p;
    }
}

void merge(int num,node *Px[],node *Py[],node *&s0,node *&s1)
{
    if (num<=3)
    {
        float minlength = 0x7fffffff;
        for (int i = 0; i < num; i++)
            for (int j = 0; j < i; j++)
            {
                if (dis(Px[i],Px[j])<minlength)
                {
                    s0 = Px[i];
                    s1 = Px[j];
                    minlength = dis(Px[i], Px[j]);
                }
            }
    }
    else
    {
        int qnum = 0, rnum = 0;
        float minq = 0x7fffffff, minr = 0x7fffffff, minqr;
        node *q0 = NULL, *q1 = NULL, *r0 = NULL, *r1 = NULL;
        node *Qx[N], *Qy[N], *Rx[N], *Ry[N];
        for (int i = 0; i < num; i++)
        {
            if (Py[i]->x<Px[num/2]->x)
                Qy[qnum++] = Py[i];
            else
                Ry[rnum++] = Py[i];

            if (i<num/2)
                Qx[i] = Px[i];
            else
                Rx[i-num/2] = Px[i];
        }
        if (num/2>=2)
        {
            merge(num / 2, Qx, Qy, q0, q1);
            minq = dis(q0, q1);
        }
        if (num-num/2>=2)
        {
            merge(num - num / 2, Rx, Ry, r0, r1);
            minr = dis(r0, r1);
        }
        minqr = min(minq, minr);
        s0 = minq < minr ? q0 : r0;
        s1 = minq < minr ? q1 : r1;

        int QxMax = Qx[num / 2 - 1]->x, snum = 0;
        node *Sx[N],*Sy[N];
        for (int i = 0,j=0; i < num; i++)
        {
            if (abs(Px[i]->x-QxMax)<=minqr)
                Sx[snum++] = Px[i];
            if (abs(Py[i]->x-QxMax)<=minqr)
                Sy[j++] = Py[i];
        }
        for (int i = 0; i < snum; i++)
        {
            for (int j = i + 1; j < min(snum, i + 15); j++)
            {
                if (dis(Sy[i],Sy[j])<minqr)
                {
                    s0 = Sy[i];
                    s1 = Sy[j];
                    minqr = dis(Sy[i], Sy[j]);
                }
            }
        }
    }
    
}

float dis(node *a,node *b)
{
    return sqrt((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
}
/*
TEST 1:
10
7 9
-8 -1
-3 -1
1 4
-3 9
6 -4
7 5
6 6
-6 10
0 8

ANS 1:
6 6
7 5
1.41421

10
43	67
82	35
81	37
70	98
71	94
24	61
21	34
5	2
67	29
42	76

3
-1	0
0	2
1	0


*/