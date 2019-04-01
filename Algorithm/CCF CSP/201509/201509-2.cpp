//
// Created by xjdkc on 19-3-14.
//

#include <iostream>
#include <algorithm>
using namespace std;

int days[]={0,31,28,31,30,31,30,31,31,30,31,30,31};

int calDay(int year,int month)
{
    if ((year%4==0&&year%100!=0)||(year%400==0))
    {
        if (month==2)
            return 29;
        else
            return days[month];
    }
    else
        return days[month];
}

int main()
{
    int year,month=1,day;
    cin>>year>>day;
    while (day>calDay(year,month))
    {
        day-=calDay(year,month);
        month++;
    }
    cout<<month<<endl;
    cout<<day<<endl;
    return 0;
}