#include<iostream>
#include<iomanip>
#include<algorithm>
using namespace std;
const int N = 10005;
struct Time
{
    int hour;
    int minute;
    Time(){
        hour = minute = 0;
    }
    bool operator <=(Time &b)const{         //����<= ���ڱȽ�
        if (hour!=b.hour)
            return hour <= b.hour;
        return minute <= b.minute;
    }
    bool operator <(Time &b)const{          //����< ����֮��sort ����
        if (hour!=b.hour)
            return hour < b.hour;
        return minute < b.minute;
    }
    friend ostream &operator<<(ostream &out,Time &cur){     //������������<< �������ʱ���������
        out << setw(2) << setfill('0') << cur.hour << 
        ":" << setw(2) << setfill('0') << cur.minute;
        return out;
    }
    friend istream &operator>>(istream &in,Time &cur){      //�������������>> �������ʱ����������
        string temp;
        in >> temp;
        cur.hour=stoi(temp.substr(0, temp.find(':')));
        cur.minute=stoi(temp.substr(temp.find(':')+1));
        return in;
    }
};
struct Class
{
    string name;
    Time begin, end;
    bool operator <(Class &b)const{                         //����<�����
        return end < b.end;
    }
    Class():begin(),end(){}
    friend istream &operator>>(istream &in,Class &cur){     //������������� �������Class��������
        in >> cur.name;
        in >> cur.begin >> cur.end;
        return in;
    }
    friend ostream &operator<<(ostream &out,Class &cur){   //������������ �������Class�������
        out << cur.name;
        out << "\t[" << cur.begin << ", " << cur.end << "]";
        return out;
    }
};
struct Classroom
{
    int target;
    int course[N];
    Classroom(){
        target = course[0] = 0;
    }
    Classroom(int target){
        course[0] = 1;
        this->target =course[1]= target;
    }
};

int num = 0;
Class f[N];
Classroom *g[N];
void solve(int n)
{
    bool mark = false;
    for (int i = 1; i <= n;i++)
    {
        mark = false;
        for (int j = 0; j < num; j++)
        {
            if (f[g[j]->target].end<=f[i].begin)
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
    cout << "������Ҫ" << num <<"�����"<< endl;
    for (int i = 0; i < num; i++)
    {
        cout << "��" << i + 1 << "������Ͽ����:" << endl;
        for (int j = 1; j <= g[i]->course[0]; j++)
            cout << "\t" << "���:" << f[g[i]->course[j]] << endl;
        cout << endl;
    }
}
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n;i++)
        cin >> f[i];
    sort(f + 1, f + n + 1);
    solve(n);
    output();
    return 0;
}
/*
10
a 9:00 10:30
b 9:00 12:30
c 9:00 10:30
d 11:00 12:30
e 11:00 14:00
f 13:00 14:30
g 13:00 14:30
h 14:00 16:30
i 15:00 16:30
j 15:00 16:30
*/