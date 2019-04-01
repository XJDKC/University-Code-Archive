#include<stdio.h>
#define PI 3.14159
int main(void)
{
    int f;
    short p,k,newint;
    double c ,r,s;
    /* for task 1 */
    printf("Input  Fahrenheit:");
    scanf("%d",&f);
    c = 5.0/9*(f-32);
    printf(" \n %d (F) = %.2f (C)\n\n ", f,c);
    /* for task 2 */
    printf("input the radius r:");
    scanf("%lf", &r);
    s = PI * r * r;
    printf("\nThe acreage is %.2lf\n\n",s);
    /* for task 3 */
    printf("input hex int k, p :");
    scanf("%hd %hd",&k,&p);
    newint=(p&0xff00)|((k>>8)&0xff);
    printf("\nnew int = %hd\n",newint);
    return 0;
}
