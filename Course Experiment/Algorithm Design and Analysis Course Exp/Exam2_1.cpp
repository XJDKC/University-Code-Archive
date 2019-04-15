#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
const int N=105;
const int M=105;
int a[N],b[M],c[N][M],f[N][M];
string x, y;
string ansx="", ansy="";
void input1();
void input2();
void dp();
void output(int R,int C);
int main()
{
    input2();
    dp();
    for (int i = 1; i <= x.size(); i++)
    {
        for (int j = 1; j <= y.size(); j++)
            cout << f[i][j] << " ";
        cout << endl;
    }

    
    output(x.size(), y.size());
    return 0;
}

void input1()
{
    cin >> x >> y;
    f[0][0] = 0;
    for (int i = 1; i <= x.size(); i++)
    {
        cin >> a[i];
        f[i][0] = f[i - 1][0] + a[i];
    }
    for (int j = 1; j <= y.size(); j++)
    {
        cin >> b[j];
        f[0][j] = f[0][j - 1] + b[j];
    }
    for (int i = 1; i <= x.size(); i++)
        for (int j = 1; j <= y.size(); j++)
            cin >> c[i][j];
}

void dp()
{
    for (int i = 1; i <= x.size(); i++)
        for (int j = 1; j <= y.size(); j++)
            f[i][j] = min(f[i - 1][j - 1] + c[i][j], min(f[i - 1][j] + a[i], f[i][j - 1] + b[j]));
}

void output(int R,int C)
{
    if (R==0||C==0)
        return;
    else
    {
        if (f[R][C]==f[R-1][C-1]+c[R][C])
        {
            ansx.insert(0, 1, x[R - 1]);
            ansy.insert(0, 1, y[C - 1]);
            output(R - 1, C - 1);
        }
        else if (f[R][C]==f[R-1][C]+a[R])
        {
            ansx.insert(0, 1, x[R - 1]);
            ansy.insert(0, 1, ' ');
            output(R - 1, C);
        }
        else if (f[R][C]==f[R][C-1]+b[C])
        {
            ansx.insert(0, 1, ' ');
            ansy.insert(0, 1, y[C - 1]);
            output(R, C - 1);
        }
    }
    if (R==x.size()&&C==y.size())
    {
		cout<<"Minimum cost:"<< f[x.size()][y.size()] << endl;
        cout << ansx << endl;
        cout << ansy << endl;
    }
}

void input2()
{
    cin >> x >> y;
    f[0][0] = 0;
    for (int i = 1; i <= x.size(); i++)
    {
        a[i] = 2;
        f[i][0] = f[i - 1][0] + 2;
    }

    for (int j = 1; j <= y.size(); j++)
    {
        b[j] = 2;
        f[0][j] = f[0][j - 1] + 2;
    }
    for (int i = 1; i <= x.size(); i++)
        for (int j = 1; j <= y.size(); j++)
            c[i][j]=abs(x[i-1]-y[j-1]);
}
/*
abc
ac
1 1 1
1 1 
0 2
2 2
2 0



*/
