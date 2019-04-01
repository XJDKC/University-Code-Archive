#include<iostream>
#include<algorithm>
#include<iomanip>
using namespace std;
const int N = 10005;
struct Person
{
    int num;                    //表示学生已经尝试匹配医院数 或 医院容纳量
    int pri[N];
    int match[N];
    Person ()
    {
        num = 0;
        fill(pri, pri + N, 0);
        fill(match, match + N, 0);
    }
};
Person H[N], S[N];
int n, m;           //n表示学生数，m表示医院数

void getPri();
void G_S();
void output();
int lovemore(int ,int );

int main()
{
	cin>>n>>m;
	getPri();
	G_S();
	output();
	return 0;
}

void getPri()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> S[i].pri[j];

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> H[i].pri[j];

    for (int i = 0; i < m;i++)
        cin >> H[i].num;
}

int lovemore(int h,int s)
{
    int minpri,spri,rtn;
    for (int i = 0; i < n; i++)
    {
        if (H[h].pri[i]==s+1)
            spri = i;
        for (int j = 1; j <= H[h].match[0]; j++)
            if (H[h].pri[i]==H[h].match[j]+1)
            {
                minpri = i;
                rtn = j;
            }
    }
    if (spri<minpri)
        return rtn;
    else
        return -1;
}

void G_S()
{
	int h,s;                            //分别表示当前判断医院 和 学生下标
    int temp;                           //表示当前医院最低优先级学生
    int s_count = 0;                    //分别表示医院已经匹配数 学生已经匹配数
    while (s_count!=n)                  //如果还有学生没有匹配到
	{
        h = s = -1;
        while (S[++s].match[0]!=0) ;    //获取一个还没有匹配的学生
        h = S[s].pri[S[s].num++] - 1;   //获取该学生还没有尝试匹配过的医院 下标少1
        if (H[h].match[0]==H[h].num)   	        //如果该医院已经有学生选了并且医院已经满了
		{
            if ((temp=lovemore(h,s))!=-1) //如果医院更喜欢当前学生
            {
                S[H[h].match[temp]].match[0] = 0;  //医院之前匹配的学生 恢复自由
                H[h].match[temp] = s;   //医院重新匹配当前学生
            }
            else                        //否则继续找
                continue;
		}
		else //如果医院处于无学生选或者未选满的情况
		{
            s_count++;                  //学生匹配数++
            H[h].match[++H[h].match[0]] = s;
            S[s].match[++S[s].match[0]] = h;
        }
	}
}

void output()
{
    for (int i = 0; i < m; i++)
    {
        cout << "第" <<setw(2)<< i + 1 << "号医院匹配学生:" ;
        for (int j = 1; j <= H[i].match[0]; j++)
            cout << H[i].match[j] + 1 << "\t";
        cout << endl;
    }
}

/*
10 10

2 5 4 7 3 6 9 8 10 1  
3 2 1 4 5 9 6 10 8 7 
5 4 9 10 1 3 2 8 7 6 
3 8 7 2 5 4 9 1 10 6 
6 4 9 5 3 1 8 7 2 10 
6 1 2 8 3 9 10 5 7 4 
7 3 10 9 1 8 6 2 5 4  
10 8 2 9 1 3 6 7 4 5  
9 1 6 10 7 8 2 3 5 4  
8 10 2 7 3 1 6 9 5 4 

4 6 1 7 10 5 9 8 3 2  
1 2 4 3 8 9 6 10 5 7 
2 1 8 10 4 3 6 9 7 5 
3 1 7 4 5 2 6 8 10 9 
6 7 9 4 3 1 10 5 2 8 
4 1 2 8 10 9 3 5 7 6 
7 3 8 9 1 10 5 2 6 4  
10 4 2 3 1 8 6 7 9 5  
5 2 6 10 7 8 1 3 9 4  
7 1 2 8 3 10 6 9 5 4

3 3 4 2 2 3 3 2 3 1


answer：
(1,6)
(2,1)
(3,2)
(4,3)
(5,4)
(6,5)
(7,7)
(8,10)
(9,9)
(10,8)
---------------------
*/
/*
6 3

3 2 1
1 2 3
2 3 1
3 1 2
1 2 3
2 1 3

6 5 4 3 2 1
1 2 3 4 5 6
4 6 5 3 2 1

2 3 2



*/
