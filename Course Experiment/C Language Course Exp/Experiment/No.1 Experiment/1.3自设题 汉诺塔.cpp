#include<stdio.h>                       //头文件输入输出 
#include<math.h>                        //数学头文件因为要用pow pow（a，b）意思是a^b  
int n;                                  //全局变量n 
void hanoi(int a,char x,char y,char z)  //声明一个叫hanoi的函数 该函数有四个参数a，x，y，z 
{                                       //意思是将a个圆盘从x号柱子经过y完全移动到z号柱子 
    if (a!=1){                          //如果圆盘数不为1（如果为1直接移动不需要经过y）  
        hanoi(a-1,x,z,y);               //那么就需要先把a个圆盘中上面a-1个圆盘经过z移动到y 
    }                                   //
    printf("%d from %d to %d\n",a,x,z); //然后将最后一个圆盘移动到z 
    if (a!=1)                           //同理 
    {                                   //
        hanoi(a-1,y,x,z);               //最后将原来的a-1从中转站y经过x移到z这样就完成了 
    }                                   //
}                                       //
                                        //就这样把最下面那块移到位置了 对于a-1块同理 
int main()                              //主函数 
{                                       //
    scanf("%d",&n);                     //输入n 
    printf("%d\n",int(pow(2.0,n)-1));   //输出完成游戏的最少步数 
    hanoi(n,'A','B','C');               //给hanoi函数提供初始参数让hanoi函数解决怎么走子（移动圆盘） 
    return 0;                           // 
}                                       //

