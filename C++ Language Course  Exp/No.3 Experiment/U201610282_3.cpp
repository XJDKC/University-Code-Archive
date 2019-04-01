#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<cctype>
using namespace std;
class STACK
{
    int *const elems; //申请内存用于存放栈的元素
    const int max;    //栈能存放的最大元素个数
    int pos;          //栈实际已有元素个数，栈空时pos=0;
public:
    STACK(int m);                             //初始化栈：最多m个元素
    STACK(const STACK &s);                    //用栈s拷贝初始化栈
    virtual int size() const;                 //返回栈的最大元素个数max
    virtual operator int() const;             //返回栈的实际元素个数pos
    virtual int operator[](int x) const;      //取下标x处的栈元素
    virtual STACK &operator<<(int e);         //将e入栈,并返回栈
    virtual STACK &operator>>(int &e);        //出栈到e,并返回栈
    virtual STACK &operator=(const STACK &s); //赋s给栈,并返回被赋值的栈
    virtual void print() const;               //打印栈
    virtual ~STACK();                         //销毁栈
};
int ERROR = false;
int main(int argc,char **argv)
{
    char curState=0;
    int num = 0,e=0;
    STACK *p = NULL;
    STACK *s = NULL;
    for (int i = 1; i <= argc && argc != 1; i++)
    {
        if (i==argc||argv[i][0]=='-')
        {
            switch(curState)
            {
                case 0:break;
                case 'I':
                case 'O':
                case 'C':
                case 'A':
                    if (*p!=0)
                        cout << "  "; 
                        p->print();
                    break;
                case 'S':
                    cout << "  " << p->size();
                    break;
                case 'N':
                    cout << "  " << *p;
                    break;
                case 'G':break;
                default:ERROR=true;
            }
            if (i!=argc)
            {
                curState = toupper(argv[i][1]);
                if (curState!='S')
                    cout << "  ";
                cout << curState;
            }
        }
        else if (!ERROR && (argv[i][0]!='-'||curState=='C'))
        {
            num = atoi(argv[i]);
            switch(curState)
            {
                case 'S':p = new STACK(num);
                         break;
                case 'I':if (*p<p->size())
                            *p << num;
                         else
                            ERROR = true;
                         break;
                case 'O':while (num--)
                        {
                            if (*p>0)
                                *p >> e;
                            else
                            {
                                ERROR = true; 
                                break;
                            }                           
                        }
                        break;
                case 'C':s = new STACK(*p);
                        break;
                case 'A':s = new STACK(num);
                        *s = *p;
                        break;
                case 'N':cout << *p;
                         break;
                case 'G':if (0<=num&&num<*p)
                            cout << "  " << (*p)[num];
                         else
                             ERROR = true;
                         break;
                default:ERROR=true;
            }    
        }
        if (ERROR)
            break;
        else if (s!=NULL)
        {
            delete p;
            p = s;
            s = NULL;
        }
    }
    if (ERROR)
        cout << "  E" << endl;
    else if (p)
        delete p;
    return 0;   
}

STACK::STACK(int m) : elems(new int[m]), max(m), pos(0){}

STACK::STACK(const STACK &s) : elems(new int[s.max]), max(s.max), pos(s.pos)
{
    for (int i = 0; i < s.pos; i++)
        elems[i] = s.elems[i];
}

int STACK::size() const
{
    return max;
}

STACK::operator int() const
{
    return pos;
}

int STACK::operator[](int x) const
{
    return elems[x];
}

STACK &STACK::operator<<(int e)
{
    if (pos<max)
        elems[pos++] = e;
    return *this;   
}

STACK &STACK::operator>>(int &e)
{
    if (pos)
        e = elems[--pos];
    return *this;   
}

STACK &STACK::operator=(const STACK &s)
{
    delete[] elems;
    *(int *)(&max) = s.max;
    *(int **)(&elems) = new int[s.max];
    pos = s.pos;
    for (int i = 0; i < pos; i++)
        elems[i] = s.elems[i];
    return *this;    
}

void STACK::print() const
{
    for (int i = 0; i < pos; i++)
    {
        cout << elems[i];
        if (i < pos - 1)
            cout << "  ";
    }
}

STACK::~STACK()
{
    delete[] elems; 
}
