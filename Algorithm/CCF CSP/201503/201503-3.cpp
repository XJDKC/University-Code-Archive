//
// Created by xjdkc on 19-3-14.
//

#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

int monday[]={0,31,28,31,30,31,30,31,31,30,31,30,31};

bool isRuen(int year)
{
    return ((year%4==0&&year%100!=0)||(year%400==0));
}

int calWeek(int year,int month,int day)
{
    int sub=0;
    for (int i=1850;i<year;i++)
    {
        if (isRuen(i))
            sub+=366;
        else
            sub+=365;
    }
    for (int i=1;i<month;i++)
    {
        if (i==2&&isRuen(year))
            sub+=29;
        else
            sub+=monday[i];
    }
    sub+=day;
    return (sub)%7+1;
}
int main()
{
    bool flag=false;
    int a,b,c,y1,y2;
    cin>>a>>b>>c>>y1>>y2;

    for (int i=y1;i<=y2;i++)
    {
        int numd=(isRuen(i)&&a==2)?29:monday[a];
        int numw=0;
        flag=false;
        for (int j=1;j<=numd;j++)
        {
            if (calWeek(i,a,j)==c)
                numw++;
            if (numw==b) {
                flag=true;
                cout << setfill('0') << i << '/' << setw(2) << a << '/' << setw(2) << j << endl;
                break;
            }
        }
        if (!flag)
            cout<<"none"<<endl;
    }
    return 0;
}