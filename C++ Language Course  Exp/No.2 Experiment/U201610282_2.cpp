#include<iostream>
#include<cstring>
#include<cctype>
using namespace std;
class STACK{
    int *const elems;
    const int max;
    int pos;
public:
    STACK(int m);
    STACK(const STACK &s);
    int size() const;
    int howMany() const;
    int getelem(int x) const;
    STACK &push(int e);
    STACK &pop(int &e);
    STACK &assign(const STACK &s);
    void print() const;
    ~STACK();
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
                    if (p->howMany()!=0)
                        cout << "  "; 
                        p->print();
                    break;
                case 'S':
                    cout << "  " << p->size();
                    break;
                case 'N':
                    cout << "  " << p->howMany();
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
                case 'I':if (p->howMany()<p->size())
                            p->push(num);
                         else
                            ERROR = true;
                         break;
                case 'O':while (num--)
                        {
                            if (p->howMany()>0)
                                p->pop(e);
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
                         s->assign(*p);
                         break;
                case 'N':cout << p->howMany();
                         break;
                case 'G':if (0<=num&&num<p->howMany())
                            cout << "  " << p->getelem(num);
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

int STACK::howMany() const
{
    return pos;
}

int STACK::getelem(int x) const
{
    return elems[x];
}

STACK &STACK::push(int e)
{
    if (pos<max)
        elems[pos++] = e;
    return *this;
}

STACK &STACK::pop(int &e)
{
    if (pos)
        e = elems[--pos];
    return *this;
}

STACK &STACK::assign(const STACK &s)
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
