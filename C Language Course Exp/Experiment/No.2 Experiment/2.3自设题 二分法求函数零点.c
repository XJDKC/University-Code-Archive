/*���ַ����������
����

�к�����f(x) = x5 - 15 * x4+ 85 * x3- 225 * x2+ 274 * x - 121
��֪ f(1.5) > 0 , f(2.4) < 0 �ҷ��� f(x) = 0 ������ [1.5,2.4] ����ֻ��һ���������ö��ַ�����ø���

����:�ޡ�

���

�÷���������[1.5,2.4]�еĸ���Ҫ���������뵽С�����6λ��
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
	printf("%.6lf\n�������뺯�����ʽ��ֵΪ%lf\n",mid,ans);
	return 0;
}
