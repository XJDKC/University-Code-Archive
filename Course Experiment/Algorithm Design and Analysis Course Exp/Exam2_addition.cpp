#include<iostream>
using namespace std;
const int N = 105;
const int MaxW = 1005;
struct item
{
    int weight;
    int value;
};
item f[N];
int dp[MaxW];
int main()
{
    int n,w;
    cin>>n>>w;
    for (int i =0;i<n;i++)
        cin >> f[i].weight >> f[i].value;
    for (int i = 0; i < n; i++)
        for (int j = w; j >= f[i].weight;j--)
        {
            if ()
        }
}