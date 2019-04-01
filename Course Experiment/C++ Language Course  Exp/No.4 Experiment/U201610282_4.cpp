#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<cstdlib>
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
class QUEUE: public STACK{
    STACK s2;
public:
    QUEUE(int m);                               //每个栈最多m个元素，要求实现的队列最多能入2m个元素
    QUEUE(const QUEUE&s);                       //用队列s拷贝初始化队列
    virtual operator int () const;			    //返回队列的实际元素个数
    virtual int full() const;		            //返回队列是否已满，满返回1，否则返回0
    virtual int operator[](int x)const;         //取下标为x的元素，第1个元素下标为0
    virtual QUEUE& operator<<(int e);           //将e入队列,并返回队列
    virtual QUEUE& operator>>(int &e);	        //出队列到e,并返回队列
    virtual QUEUE& operator=(const QUEUE&s);    //赋s给队列,并返回被赋值的队列
    virtual void print() const; 			    //打印队列
    virtual ~QUEUE( );					        //销毁队列

};
int ERROR = false;
int main(int argc,char **argv)
{
    char curState=0;
    int num = 0,e=0;
    QUEUE *p = NULL;
    QUEUE *s = NULL;
    if (argc>1)
    {
        for (int i = 1; i <= argc; i++)
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
                    case 'S':p = new QUEUE(num);
                            break;
                    case 'I':if (!p->full())
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
                    case 'C':s = new QUEUE(*p);
                            break;
                    case 'A':s = new QUEUE(num);
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
    }
    else
    {
        int M, F, m, f, count, temp;
        cout << "输入男士人数和女士人数:" ;
        cin >> M >> F;
        cout << "输入想要跳舞的男士和女士的初始位置:";
        cin >> m >> f;
        p = new QUEUE(M);
        s = new QUEUE(F);
        count = 0;
        while (count++<M)
            *p << (count == m);
        count = 0;
        while (count++<F)
            *s << (count == f);
        count = 0;
        while (!((*p)[0]&&(*s)[0]))
        {
            *p >> temp; *p << temp;
            *s >> temp; *s << temp;
            count++;
        }
        cout << "在第" << count+1 << "支舞一起跳" << endl;
        delete p;
        delete s;
    }
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

QUEUE::QUEUE(int m):STACK(m),s2(m){}

QUEUE::QUEUE(const QUEUE&s):STACK(s),s2(s.s2){}

QUEUE::operator int() const
{
    return s2 + this->STACK::operator int();
}

int QUEUE::full() const
{
    return (s2 && (this->STACK::size() == this->STACK::operator int()));
}

int QUEUE::operator[](int x)const
{
    int num = s2;
	if (num > x)
		return this->s2[num - x - 1];
    else
		return this->STACK::operator[](x - num);
}

QUEUE& QUEUE::operator<<(int e)
{
    int temp;
    if (this->STACK::operator int()==this->STACK::size()&&!s2)
        while (this->STACK::operator int())
        {
            this->STACK::operator>>(temp);
            s2 << temp;
        }

    this->STACK::operator<<(e);
    return *this;
}

QUEUE& QUEUE::operator>>(int &e)
{
    int temp;
    if (!s2)
        while (this->STACK::operator int())
        {
            this->STACK::operator>>(temp);
            s2 << temp;
        }
    s2 >> e;
    return *this;
}

QUEUE& QUEUE::operator=(const QUEUE&s)
{
    this->STACK::operator=(s);
    this->s2 = s.s2;
    return *this;
}

void QUEUE::print() const
{
    int num = s2;
	int total = *this;
    for (int i = 0; i < total; i++)
    {
        if (i<num)
            cout << s2[num - i - 1];
        else
            cout << this->STACK::operator[](i - num);
        if (i< total-1)
            cout << "  ";
    }
}

QUEUE::~QUEUE( )
{
}
