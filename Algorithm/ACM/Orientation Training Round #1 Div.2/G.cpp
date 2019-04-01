#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
/*
      1     2
      3     4 
5  6  7  8  9  10 11
      12    13 
14 15 16 17 18 19 20
      21    22
      23    24
*/
int well[25],deep,len=0;
int back[]={5,4,7,6,1,0,3,2},rec[]={7,8,9,12,13,16,17,18};
int direct[][7]={{ 1, 3, 7,12,16,21,23}, 
				 { 2, 4, 9,13,18,22,24},
				 {11,10, 9, 8, 7, 6, 5},
				 {20,19,18,17,16,15,14},
				 {24,22,18,13, 9, 4, 2},
				 {23,21,16,12, 7, 3, 1},
				 {14,15,16,17,18,19,20},
				 { 5, 6, 7, 8, 9,10,11}};
string s;
bool judge()
{
	for (int i=1;i<8;i++) 
		if (well[rec[i]]!=well[rec[0]]) 
			return false;
	return true;
}
int predict()
{
	int num[4];
	memset(num,0,sizeof(num));
	for (int i = 0; i < 8; i++)
	{
		num[well[rec[i]]]++;
	}
	return (8-max(max(num[1], num[2]), num[3]));
}
void rot(int dir)
{
	int temp=well[direct[dir][0]];
	for (int i=0;i<6;i++)
		well[direct[dir][i]]=well[direct[dir][i+1]];
	well[direct[dir][6]]=temp;
}
bool solve(int step)
{
	if (judge()) return true;
	else if (step==deep) return false;
	else if (step+predict()>deep) return false;
	else 
	{
		if (step+1>len) {len++;s+='A'-1;};
		for (int i=0;i<8;i++)
		{
			s[step]='A'+i;
			rot(i);
			if (solve(step+1)) return true;
			rot(back[i]);
		}
		return false;
	}
}
int main()
{
	int first;
	while (cin>>first&&first)
	{
		well[1]=first;
		for (int i=2;i<25;i++)
			cin>>well[i];
		
		if (judge()) cout << "No moves needed" << endl;//No 不是NO。。。
		else
		{
			deep=1;
			do
			{
				if (solve(0)) break;
			}while(deep++);

			for (int i=0;i<deep;i++)
			{
				cout<<s[i];
			}
			cout<<endl;
		}
		cout<<well[rec[0]]<<endl;
	}
	return 0;
}