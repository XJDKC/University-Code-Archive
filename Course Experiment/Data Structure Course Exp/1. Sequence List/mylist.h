//mylist.h -- a list template
#ifndef MYLIST_H_
#define MYLIST_H_


#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERRFLOW -2
#define NOTEXIST -3
#define EXIST -4

typedef int status;

template <class Type>
class List;

template <class Type>
class List
{
    private:
        enum {LIST_INIT_SIZE = 100 , LISTINCREAMENT = 10};
        typedef struct{
            Type *elem;
            int length;
            int listsize;
        }SqList;
		SqList L;
    public:
        Type e,cur_e,pre_e,next_e;
        List(void)
        {
            L.elem=NULL;
            L.length=0;
            L.listsize=0;
        }
		const char *GetType();
		status UnInite();

		status IniteList();
		status DestroyList();
		status ClearList();
		status ListEmpty();
		int ListLength();
		status GetElem(int i);
		status LocateElem();
		status PriorElem();
		status NextElem();
		status ListInsert(int i);
		status ListDelete(int i);
		status ListTraverse();

		template <class Type>
		friend std::ifstream &operator>> (std::ifstream &ifs, List<Type> &x);
		template <class Type>
		friend std::ofstream &operator<< (std::ofstream &ofs, List<Type> &x);
};

template <class Type>
const char *List<Type>::GetType()
{
	return typeid(e).name();
}

template <class Type>
status List<Type>::UnInite()
{
	if (L.elem == NULL) return NOTEXIST;
	else return EXIST;
}

template <class Type>
status List<Type>::IniteList()
{
    if (L.elem) return EXIST;
    L.elem = (Type *)malloc(LIST_INIT_SIZE * sizeof(Type));
    if (!L.elem) return OVERRFLOW;
    L.length=0;
    L.listsize=LIST_INIT_SIZE;
    return OK;
}

template <class Type>
status List<Type>::DestroyList()
{
    if (L.elem==NULL) return NOTEXIST;
    free(L.elem);
	L.elem = NULL;
    L.length=0;
    L.listsize=0;
    return OK;
}

template <class Type>
status List<Type>::ClearList()
{
    if (L.elem==NULL) return NOTEXIST;
    L.length=0;
    return OK;
}

template <class Type>
status List<Type>::ListEmpty()
{
    if (L.elem==NULL) return NOTEXIST;
    if (L.length==0) return TRUE;
    else return FALSE;
}

template <class Type>
int List<Type>::ListLength()
{
    if (L.elem==NULL) return NOTEXIST;
    return L.length;
}

template <class Type>
status List<Type>::GetElem(int i)
{
    if (L.elem==NULL) return NOTEXIST;
    if (1>i||i>L.length) return ERROR;
    e=L.elem[i-1];
    return OK;
}

template <class Type>
status List<Type>::LocateElem()
{
    if (L.elem==NULL) return NOTEXIST;
    for (int i=0;i<L.length;i++)
    {
        if (L.elem[i]==e) return i+1;
    }
    return ERROR;
}

template <class Type>
status List<Type>::PriorElem()
{
    if (L.elem==NULL) return NOTEXIST;
	if (L.length&&cur_e == L.elem[0]) return EXIST;
    for (int i=1;i<L.length;i++)
    {
        if (L.elem[i]==cur_e)
        {
            pre_e=L.elem[i-1];
            return OK;
        }
    }
    return ERROR;
}

template <class Type>
status List<Type>::NextElem()
{
    if (L.elem==NULL) return NOTEXIST;
	if (L.length&&cur_e == L.elem[L.length-1]) return EXIST;
    for (int i=0;i<L.length-1;i++)
    {
        if (L.elem[i]==cur_e)
        {
            next_e=L.elem[i+1];
            return OK;
        }
    }  
    return ERROR;
}

template <class Type>
status List<Type>::ListInsert(int i)
{
    if (L.elem==NULL) return NOTEXIST;
    if (1>i||i>L.length+1) return ERROR;
    if (1+L.length>L.listsize)
    {
        Type *newlist;
        newlist=(Type *)realloc(L.elem,(L.listsize+LISTINCREAMENT)*sizeof(Type));
        if (newlist==NULL) return OVERRFLOW;
        L.elem=newlist;
        L.listsize+=LISTINCREAMENT;
    }
    for (int j=L.length-1;j>=i-1;j--)
    {
        L.elem[j+1]=L.elem[j];
    }
    L.elem[i-1]=e;
    L.length++;
    return OK;
}

template <class Type>
status List<Type>::ListDelete(int i)
{
    if (L.elem==NULL) return NOTEXIST;
    if (1>i||i>L.length) return ERROR;
    e=L.elem[i-1];
    for (int j=i;j<L.length;j++)
    {
        L.elem[j-1]=L.elem[j];
    }
    L.length--;
    return OK;
}

template <class Type>
status List<Type>::ListTraverse()
{
    int i;
    printf("\n---------------all elements -------------------\n");
	for (i = 0; i < L.length; i++)
	{
		cout << i+1 << " " << L.elem[i] << " \t ";
		if ((i+1) % 5 == 0) cout << endl;
	}
    printf("\n------------------ end ------------------------\n");
    return L.length;
}


template <class Type>
std::ifstream &operator>> (std::ifstream &ifs, List<Type> &x)
{
	ifs >> x.L.length; ifs.get();
	ifs >> x.L.listsize; ifs.get();
	x.L.elem=(Type *)realloc(x.L.elem,(x.L.listsize)*sizeof(Type));
	for (int i = 0; i < x.L.length; i++)
	{
		ifs >> x.L.elem[i];
	}
	return ifs;
}

template <class Type>
std::ofstream &operator<< (std::ofstream &ofs, List<Type> &x)
{
	ofs << x.L.length<<endl;
	ofs << x.L.listsize<<endl;
	for (int i = 0; i < x.L.length; i++)
	{
		ofs << x.L.elem[i]<<" ";
	}
	return ofs;
}

#endif