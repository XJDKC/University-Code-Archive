/*二分法求函数的零点
描述

有函数：f(x) = x5 - 15 * x4+ 85 * x3- 225 * x2+ 274 * x - 121
已知 f(1.5) > 0 , f(2.4) < 0 且方程 f(x) = 0 在区间 [1.5,2.4] 有且只有一个根，请用二分法求出该根。

输入:无。

输出

该方程在区间[1.5,2.4]中的根。要求四舍五入到小数点后6位。
*/
#include<stdio.h>
#define exp 1.0e-6
double c[10];
int main()
{
    double left=1.5,right=2.4,mid,zhi,ans;
    int i;
    while (right-left>exp)
    {
    	mid=(left+right)/2;c[1]=mid;
    	for (i=2;i<=5;i++)
		c[i]=c[i-1]*mid;
		zhi=c[5]-15*c[4]+85*c[3]-225*c[2]+274*c[1]-121;
		if (zhi<0) right=mid;
		else if (zhi>0) left=mid;
		ans=zhi;
    }
	printf("%.6lf\n该数带入函数表达式后值为%lf\n",mid,ans);
	return 0;
}
