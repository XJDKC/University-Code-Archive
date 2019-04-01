#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERRFLOW -2
#define NOTEXIST -3
#define EXIST -4

typedef int Status;

class NodeBase
{
	friend class ListBase;
	template <typename DataType>
	friend class List;
private:
	NodeBase *next;
public:
	virtual ~NodeBase() {}
	NodeBase()
	{
		next = NULL;
	}
};

class ListBase				//链表基类型
{
	friend class MainList;	//将多链表的主链类设置为友元 方便访问链表成员
public:
	bool saved;
	int type;
	std::string name;
	ListBase *next;			//指向下一条链表
	NodeBase *head;			//指向当前链表的头节点

	ListBase()
	{
		saved = false;
		next = NULL;
		head = NULL;
	}

	virtual Status InitList()=0;
	virtual	Status DestroyList()=0;
	virtual	Status ClearList()=0;
	virtual Status ListEmpty()=0;
	virtual Status ListLength()=0;
	virtual Status GetElem(int i)=0;
	virtual Status LocateElem()=0;
	virtual Status PriorElem()=0;
	virtual Status NextElem()=0;
	virtual Status ListInsert(int i)=0;
	virtual Status ListDelete(int i)=0;
	virtual Status ListTraverse()=0;

	virtual void set_e()=0;
	virtual void set_cur_e() = 0;
	virtual void get_e()=0;
	virtual void get_cur_e()=0;

	friend std::ifstream& operator>> (std::ifstream &fin, ListBase &mylist)
	{
		mylist.operator>>(fin);
		return fin;
	}
	friend std::ofstream& operator<< (std::ofstream &fout, ListBase &mylist)
	{
		mylist.operator<<(fout);
		return fout;
	}

	virtual void operator>>(std::ifstream &in) = 0;
	virtual void operator<<(std::ofstream &out) = 0;
};

template <typename DataType>
class Head :public NodeBase	//从节点基类派生出来 头节点派生类
{
	template <typename DataType>
	friend class List;		//将链表类设为友元方便访问
	friend NodeBase;		//将节点基类设为友元
private:
	int length;				//存储长度
public:
	Head()
	{
		length = 0;
	}
};

template <typename DataType>
class Node:public NodeBase
{
	friend NodeBase;
	friend class List<DataType>;
private:
	DataType data;
public:
	Node() {};
	Node(DataType &temp)
	{
		data = temp;
	}
};

template<typename DataType>			//模板类 支持 多类型链表
class List:public ListBase
{
	friend class MainList;			//将主链类设为友元
	friend class ListBase;			//将链表基类设为友元 
	private:
		DataType e, cur_e;			//设置两个变量作为存储单元 方便类内部与外界交换数据
		Head<DataType> *HEAD;
		Node<DataType> *pcur, *padja;
	public:
		List ()
		{
			head = NULL;
			saved = false;
			next = NULL;
			head = NULL;
		}
		~List()	{}

		Status InitList();
		Status DestroyList();
		Status ClearList();
		Status ListEmpty();
		Status ListLength();
		Status GetElem(int i);
		Status LocateElem();
		Status PriorElem();
		Status NextElem();
		Status ListInsert(int i);
		Status ListDelete(int i);
		Status ListTraverse();

		void set_e();
		void set_cur_e();
		void get_e();
		void get_cur_e();

		void getHEAD()
		{
			HEAD = dynamic_cast<Head<DataType> *>(head);
		}
		Node<DataType> *getCur(NodeBase *pp)
		{
			return dynamic_cast<Node<DataType> *>(pp);
		}

		void operator>>(std::ifstream &in)
		{
			InitList();
			in >> HEAD->length;
			in.get();
			NodeBase *pprev= head;
			for (int i = 1; i <= HEAD->length; i++)
			{
				pcur = new Node<DataType>;
				in>>pcur->data;
				pcur->next = pprev->next;
				pprev->next = pcur;
				pprev = pcur;
			}
		}
		void operator<<(std::ofstream &out)
		{
			out << HEAD->length<<std::endl;
			pcur = getCur(HEAD->next);
			while (pcur)
			{
				out << pcur->data;
				if (pcur->next) out << " ";
				else out << std::endl;
				pcur = getCur(pcur->next);
			}
		}
};

class MainList
{
public:
	int length;
	int count;
	ListBase *head;
	MainList() 
	{
		length = 0;
		count = 0;
		head = NULL;
	}

	bool allsaved();

	friend std::ifstream &operator>> (std::ifstream &fin,MainList &mainlist);
	friend std::ofstream &operator<< (std::ofstream &fout,MainList &mainlist);
};



template <typename DataType>
Status List<DataType>::InitList()
{
	if (head != NULL) return EXIST;
	head = new(Head<DataType>);
	getHEAD();	
	return OK;
}

template <typename DataType>
Status List<DataType>::DestroyList()
{
	if (head == NULL) return NOTEXIST;
	Head<DataType> *HEAD = dynamic_cast<Head<DataType> *>(head);
	NodeBase *pcur=HEAD->next,*pnext;
	while (pcur)
	{
		pnext = pcur->next;
		delete(pcur);
		pcur = pnext;
	}
	delete(head);
	head = NULL;
	return OK;
}

template <typename DataType>
Status List<DataType>::ClearList()
{
	if (head == NULL) return NOTEXIST;
	pcur = getCur(HEAD->next);
	while (pcur)
	{
		padja = getCur(pcur->next);
		delete(pcur);
		pcur = padja;
	}
	HEAD->length = 0;
	HEAD->next = NULL;
	return OK;
}

template <typename DataType>
Status List<DataType>::ListEmpty()
{
	if (head == NULL) return NOTEXIST;
	if (HEAD->length == 0) return TRUE;
	else return FALSE;
}

template <typename DataType>
Status List<DataType>::ListLength()
{
	if (head == NULL) return NOTEXIST;
	return HEAD->length;
}

template <typename DataType>
Status List<DataType>::GetElem(int i)
{
	if (head == NULL) return NOTEXIST;
	if (1 > i || i > HEAD->length) return ERROR;
	pcur = getCur(HEAD->next);
	for (int count = 1; count < i; count++)
		pcur = getCur(pcur->next);
	e = pcur->data;
	return OK;
}

template <typename DataType>
Status List<DataType>::LocateElem()
{
	if (head == NULL) return NOTEXIST;
	pcur=getCur(HEAD->next);
	for (int i=1;pcur!=NULL;pcur = getCur(pcur->next),i++)
	{
		if (pcur->data == e)
		{
			return i;
		}
	}
	return ERROR;
}

template <typename DataType>
Status List<DataType>::PriorElem()
{
	if (head == NULL) return NOTEXIST;
	NodeBase *pprev=head;
	pcur = getCur(HEAD->next);
	while (pcur)
	{
		if (pcur->data == cur_e)
		{
			if (pprev == head)
				return EXIST;
			else
			{
				e = getCur(pprev)->data;
				return OK;
			}
		}
		pcur = getCur(pcur->next);
		pprev = pprev->next;
	}
	return ERROR;
}

template <typename DataType>
Status List<DataType>::NextElem()
{
	if (head == NULL) return NOTEXIST;
	pcur=getCur(HEAD->next);
	while (pcur)
	{
		if (pcur->data == cur_e)
		{
			if (pcur->next == NULL)
				return EXIST;
			else
			{
				e = getCur(pcur->next)->data;
				return OK;
			}
		}
		pcur = getCur(pcur->next);
	}
	return ERROR;
}

template <typename DataType>
Status List<DataType>::ListInsert(int i)
{
	if (head == NULL) return NOTEXIST;
	if (1 > i || i > HEAD->length + 1) return ERROR;
	NodeBase *pprev=head;
	for (int j = 1; j < i; j++)
		pprev = pprev->next;
	NodeBase *newnode = new(Node<DataType>)(e);
	newnode->next = pprev->next;
	pprev->next = newnode;
	HEAD->length++;
	return OK;
}

template <typename DataType>
Status List<DataType>::ListDelete(int i)
{
	if (head == NULL) return NOTEXIST;
	if (1 > i || i > HEAD->length) return ERROR;
	NodeBase *pprev=head;
	pcur = getCur(HEAD->next);
	for (int j = 1; j < i; j++)
	{
		pcur=getCur(pcur->next);
		pprev = pprev->next;
	}
	e = pcur->data;
	pprev->next = pcur->next;
	delete(pcur);
	HEAD->length--;
	return OK;
}

template <typename DataType>
Status List<DataType>::ListTraverse()
{
	if (head == NULL) return NOTEXIST;
	pcur=getCur(HEAD->next);
	cout << "\n---------------all elements -------------------\n";
	for (int i = 0; i < HEAD->length; i++)
	{
		cout << pcur->data << " \t ";
		if ((i + 1) % 5 == 0) cout << endl;
		pcur = getCur(pcur->next);
	}
	cout<<"\n------------------ end ------------------------\n";
	system("pause"); 
	return HEAD->length;
}



template <typename DataType>
void List<DataType>::set_e()
{
	cin >> e;
}

template <typename DataType>
void List<DataType>::set_cur_e()
{
	cin >> cur_e;
}

template <typename DataType>
void List<DataType>::get_e()
{
	cout << e;
}

template<typename DataType>
void List<DataType>::get_cur_e()
{
	cout<<cur_e<<endl;
}


bool MainList::allsaved()
{
	ListBase *p=head;
	bool mark = true;
	while (p)
	{
		if (!p->saved)
		{
			mark = false;
			break;
		}
		p = p->next;
	}
	return mark;
}

std::ifstream& operator>> (std::ifstream &fin, MainList &mainlist)
{
	fin >> mainlist.length; fin.get();
	fin >> mainlist.count; fin.get();
	ListBase *p=NULL;
	int type;
	for (int i = 1; i <= mainlist.length; i++,p=p->next)
	{
		fin >> type;		
		fin.get();
		switch (type)
		{
		case 1:p = new(List<bool>); break;
		case 2:p = new(List<char>); break;
		case 3:p = new(List<int>); break;
		case 4:p = new(List<float>); break;
		case 5:p = new(List<double>); break;
		}
		p->type = type;
		fin >> p->saved;
		fin.get();
		if (p->saved)
		{
			fin >> p->name;
			fin.get();
		}
		p->next=mainlist.head;
		mainlist.head = p;
	}
	return fin;
}

std::ofstream& operator<< (std::ofstream &fout, MainList &mainlist)
{
	fout << mainlist.length<<" "<<mainlist.count << std::endl;
	ListBase *p=mainlist.head;
	while (p)
	{
		if (p->saved)
		{
			fout << p->type << " " << p->saved<< " " << p->name<<std::endl;
		}
		p = p->next;
	}
	return fout;
}
