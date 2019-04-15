#include<iostream>
#include<algorithm>
using namespace std;
const int N = 10005;
struct Interval
{
    int left, right;
    bool operator <(Interval &b)const
    {
        return right < b.right;
    }
    Interval()
    {
        left = 0;
        right = 0;
    }
};
struct Classroom
{
    int target;
    int course[N];
    Classroom()
    {
        target = 0;
        course[0] = 0;
    }
    Classroom(int target)
    {
        this->target = target;
        course[0] = 1;
        course[1] = target;
    }
};
int num = 0;
Interval f[N];
Classroom *g[N];
void solve(int n)
{
    bool mark = false;
    for (int i = 1; i <= n;i++)
    {
        mark = false;
        for (int j = 0; j < num; j++)
        {
            if (f[i].left >= f[g[j]->target].right)
            {
                g[j]->target = i;
                g[j]->course[++g[j]->course[0]] = i;
                mark = true;
                break;
            }
        }
        if (!mark)
            g[num++] = new Classroom(i);
    }
}
void output()
{
    cout << "至少需要" << num <<"间教室"<< endl;
    for (int i = 0; i < num; i++)
    {
        cout << "第" << i + 1 << "间教室上课情况:" << endl;
        for (int j = 1; j <= g[i]->course[0]; j++)
            cout << "\t"
                 << "序号:" << g[i]->course[j] << "\t [" << f[g[i]->course[j]].left << ", " << f[g[i]->course[j]].right << "]" << endl;
        cout << endl;
        //char('a'+g[i]->course[j]-1)
    }
}
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n;i++)
        cin >> f[i].left >> f[i].right;
    sort(f + 1, f + n + 1);
    solve(n);
    output();
    return 0;
}
/*
10
1 3
1 2
2 4
3 4
5 7
5 6
6 7
7 10
6 9
5 8
*/
/*
10
1 4
1 8
1 4
5 8
5 11
9 12
9 12
11 16
13 16
13 16
*/