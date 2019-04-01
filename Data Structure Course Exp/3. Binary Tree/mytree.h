#pragma once

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERRFLOW -2
#define NOTEXIST -3
#define EXIST -4

class Node
{
	friend class Tree;
private:
	int no;
	ElemType data;
	Node *lchild, *rchild, *parent;
public:
	Node()
	{
		no = 0;
		data = 0;
		lchild = rchild = parent = NULL;
	}
	~Node()
	{
		delete(lchild);
		delete(rchild);
	}
	void GetNo()
	{
		std::cout << no;
	}
	void GetData()
	{
		std::cout << data;
	}

	friend std::ifstream&operator>>(std::ifstream &inFile, Tree &temp);
	friend std::ofstream&operator<<(std::ofstream &outFile, Tree &temp);
};

class HEAD
{
	friend class Tree;
private:
	int tsize;
	Node *ROOT;	
public:
	HEAD()
	{
		tsize = 0;
		ROOT = NULL;
	}
	~HEAD()
	{
	}
	
	friend std::ifstream&operator>>(std::ifstream &inFile, Tree &temp);
	friend std::ofstream&operator<<(std::ofstream &outFile, Tree &temp);
};

class Tree
{
private:
	HEAD *pRoot;
public:
	int e;
	bool saved;
	std::string name;
	Tree *next;
	Tree()
	{
		e = 0;
		saved = false;
		pRoot = NULL;
		next = NULL;
	}
	~Tree()
	{
		delete(pRoot->ROOT);
		delete(pRoot);
	}

	bool HasInit();
	int CalSize(Node *pcur,int L);
	status ShowInfo(Node *pcur);


	status InitBiTree();
	status DestroyBiTree();
	status CreateBiTree(std::vector<int> &pre_order,std::vector<ElemType> &alldata);
	status ClearBiTree();
	status BiTreeEmpty();
	status BiTreeDepth(Node *pcur=NULL);
	Node *Root();
	ElemType Value(Node *pcur=NULL);
	status Assign(ElemType value,Node *pcur=NULL);
	Node *Parent(Node *pcur=NULL);
	Node *GetNode(Node *pcur = NULL);
	Node *LeftChild(Node *pcur=NULL);
	Node *RightChild(Node *pcur=NULL);
	Node *LeftSibling(Node *pcur=NULL);
	Node *RightSibling(Node *pcur = NULL);
	status InsertChild(Node *p, int LR, Tree &c);
	status DeleteChild(Node *p, int LR);
	status PreOrderTraverse(Node *pcur=NULL);
	status InOrderTraverse(Node *pcur=NULL);
	status PostOrderTraverse(Node *pcur=NULL);
	status LevelOrderTraverse(Node *pcur=NULL);

	friend std::ifstream&operator>>(std::ifstream &inFile, Tree &temp);
	friend std::ofstream&operator<<(std::ofstream &outFile, Tree &temp);
};

bool Tree::HasInit()
{
	if (pRoot == NULL) return FALSE;
	else return TRUE;
}

int Tree::CalSize(Node *pcur,int L)
{
	if (pcur == NULL) return L;
	else
	{
		return CalSize(pcur->lchild,L) + CalSize(pcur->rchild,L) + 1;
	}
}

status Tree ::ShowInfo(Node *pcur)
{
	if (pcur == NULL) return NOTEXIST;
	else
	{
		std::cout << pcur->no << " " << pcur->data << std::endl;
		return OK;
	}
}

status Tree::InitBiTree()
{
	if (pRoot != NULL) return EXIST;
	pRoot = new(HEAD);
	return OK;
}

status Tree::DestroyBiTree()
{
	if (pRoot)	
		delete(pRoot->ROOT);
	delete(pRoot);
	pRoot = NULL;
	return OK;
}

status Tree::CreateBiTree(std::vector<int> &pre_order,std::vector<ElemType> &alldata)
{
	Node **pcur=&pRoot->ROOT, *pprev=NULL;
	e = 0;
	pRoot->tsize = alldata[0];
	for (int i = 1; i <= pre_order[0]; i++)
	{
		if (pre_order[i] == 0x80000000)
		{
			if (pcur == &pprev->lchild) pcur = &pprev->rchild;
			else
			{
				if (pprev)
				{
					do
					{
						pprev = pprev->parent;
					} while (pprev&&pprev->rchild != NULL);
					pcur = &pprev->rchild;
				}

			}
		}
		else
		{
			*pcur = new(Node);
			(*pcur)->no = pre_order[i];
			(*pcur)->data=alldata[++e];
			(*pcur)->parent = pprev;
			pprev = *pcur;
			pcur = &(*pcur)->lchild;
		}
	}
	return OK;
}

status Tree::ClearBiTree()
{
	delete(pRoot->ROOT);
	pRoot->ROOT = NULL;
	pRoot->tsize = 0;
	return OK;
}

status Tree::BiTreeEmpty()
{
	if (pRoot->ROOT == NULL) return TRUE;
	else return FALSE;
}

status Tree::BiTreeDepth(Node *pcur)
{
	if (pcur == NULL) pcur = pRoot->ROOT;
	return pcur==NULL?0:max(pcur->lchild?BiTreeDepth(pcur->lchild):0,pcur->rchild?BiTreeDepth(pcur->rchild):0)+1;
}

Node *Tree::Root()
{
	return pRoot->ROOT;
}

ElemType Tree::Value(Node *pcur)
{
	if (pcur == NULL) pcur = pRoot->ROOT;
	if (pcur->no == e) return pcur->data;
	else {
		int finddata = 0x80000000;
		if (pcur->lchild) finddata = max(finddata, Value(pcur->lchild));
		if (pcur->rchild) finddata = max(finddata, Value(pcur->rchild));
		return finddata;
	}
}

status Tree::Assign(ElemType value,Node *pcur)
{
	if (pcur == NULL) pcur = pRoot->ROOT;
	if (pcur->no == e) {
		pcur->data = value; 
		return OK;
	}
	else
	{
		bool mark = ERROR;
		if (pcur->lchild) mark =mark ||Assign(value, pcur->lchild);
		if (!mark&&pcur->rchild) mark = mark||Assign(value, pcur->rchild);
		return mark;
	}
}

Node *Tree::Parent(Node *pcur)
{
	if (pcur == NULL) pcur = pRoot->ROOT;
	if (pcur->no == e) return pcur->parent;
	else
	{
		Node *re=NULL;
		if (pcur->lchild) re = Parent(pcur->lchild);
		if (pcur->rchild&&!re) re = Parent(pcur->rchild);
		return re;
	}
}

Node *Tree::GetNode(Node *pcur)
{
	if (pcur == NULL) pcur = pRoot->ROOT;
	if (pcur->no == e) return pcur;
	else
	{
		Node *re=NULL;
		if (pcur->lchild) re = GetNode(pcur->lchild);
		if (pcur->rchild&&!re) re = GetNode(pcur->rchild);
		return re;
	}
}

Node *Tree::LeftChild(Node *pcur)
{
	if (pcur == NULL) pcur = pRoot->ROOT;
	if (pcur->no == e) return pcur->lchild;
	else
	{
		Node *re=NULL;
		if (pcur->lchild) re = LeftChild(pcur->lchild);
		if (pcur->rchild&&!re) re = LeftChild(pcur->rchild);
		return re;
	}
}

Node *Tree::RightChild(Node *pcur)
{
	if (pcur == NULL) pcur = pRoot->ROOT;
	if (pcur->no == e) return pcur->rchild;
	else
	{
		Node *re=NULL;
		if (pcur->lchild) re = RightChild(pcur->lchild);
		if (pcur->rchild && !re) re = RightChild(pcur->rchild);
		return re;
	}
}

Node *Tree::LeftSibling(Node *pcur)
{
	if (pcur == NULL) pcur = pRoot->ROOT;
	if (pcur->no == e)
	{
		if (pcur->parent == NULL || pcur->parent->lchild == pcur)  return NULL;
		else return pcur->parent->lchild;
	}
	else
	{
		Node *re=NULL;
		if (pcur->lchild) re = LeftSibling(pcur->lchild);
		if (pcur->rchild&&!re) re = LeftSibling(pcur->rchild);
		return re;
	}
}

Node *Tree::RightSibling(Node *pcur)
{
	if (pcur == NULL) pcur = pRoot->ROOT;
	if (pcur->no == e)
	{
		if (pcur->parent == NULL || pcur->parent->rchild == pcur)  return NULL;
		else return pcur->parent->rchild;
	}
	else
	{
		Node *re=NULL;
		if (pcur->lchild) re = RightSibling(pcur->lchild);
		if (pcur->rchild&&!re) re = RightSibling(pcur->rchild);
		return re;
	}
}

status Tree::InsertChild(Node *p, int LR, Tree &c)
{
	if (p == NULL) return NOTEXIST;							//如果获取的节点为空 证明没有获取 则返回NOTEXIST
	else if (c.pRoot->ROOT->rchild != NULL) return ERROR;	//若果插入子树根节点右子树不为空 把么不符合要求 返回错误
	if (LR == 0)
	{
		c.pRoot->ROOT->rchild = p->lchild;
		p->lchild = c.pRoot->ROOT;
		p->lchild->parent = p;
		pRoot->tsize += c.pRoot->tsize;
	}
	else
	{
		c.pRoot->ROOT->rchild = p->rchild;
		p->rchild = c.pRoot->ROOT;
		p->rchild->parent = p;
		pRoot->tsize += c.pRoot->tsize;
	}
	return OK;
}

status Tree::DeleteChild(Node *p, int LR)
{
	if (p == NULL) return NOTEXIST;
	if (LR == 0)
	{
		pRoot->tsize -= CalSize(p->lchild,0);
		delete(p->lchild);
		p->lchild = NULL;
	}
	else
	{
		pRoot->tsize -= CalSize(p->rchild,0);
		delete(p->rchild);
		p->rchild = NULL;
	}
	return OK;
}

status Tree::PreOrderTraverse(Node *pcur)
{
/*
	if (pcur == NULL) pcur = pRoot->ROOT;
	if (pcur == pRoot->ROOT)
		std::cout << "\n---------------PreOrderTraverse-------------------\n";
	std::cout << pcur->data << "\t";
	CONSOLE_SCREEN_BUFFER_INFO cursor_pos;
	GetConsoleScreenBufferInfo(HANDLE_OUT, &cursor_pos);
	if (cursor_pos.dwCursorPosition.X >= 40) std::cout << std::endl;
	if (pcur->lchild) PreOrderTraverse(pcur->lchild);
	if (pcur->rchild) PreOrderTraverse(pcur->rchild);
	if (pcur == pRoot->ROOT)
		std::cout << "\n-------------------- end -------------------------\n";
	return OK;
*/
	std::cout << "\n---------------PreOrderTraverse-------------------\n";
	int count = 0;
	pcur = pRoot->ROOT;
	while (pcur||!s.empty())
	{
		if (pcur)
		{
			if (count&&count % 5==0) std::cout << std::endl;
			std::cout << pcur->data << "\t";
			count++;
			s.push(pcur);
			pcur = pcur->lchild;
		}
		else
		{
			pcur = s.top();
			s.pop();
			pcur = pcur->rchild;
		}
	}
	std::cout << "\n-------------------- end -------------------------\n";
	return OK;
}

status Tree::InOrderTraverse(Node *pcur)
{
/*
	if (pcur == NULL) pcur = pRoot->ROOT;
	if (pcur == pRoot->ROOT)
		std::cout << "\n---------------InOrderTraverse-------------------\n";
	
	CONSOLE_SCREEN_BUFFER_INFO cursor_pos;
	GetConsoleScreenBufferInfo(HANDLE_OUT, &cursor_pos);
	if (cursor_pos.dwCursorPosition.X >= 40) std::cout << std::endl;
	if (pcur->lchild)	InOrderTraverse(pcur->lchild);
	std::cout << pcur->data << "\t";
	if (pcur->rchild) InOrderTraverse(pcur->rchild);
	if (pcur == pRoot->ROOT)
		std::cout << "\n------------------- end -------------------------\n";
	return OK;
*/
	std::cout << "\n---------------InOrderTraverse-------------------\n";
	int count = 0;
	pcur = pRoot->ROOT;
	while (pcur||!s.empty())
	{
		if (pcur)
		{
			s.push(pcur);
			pcur = pcur->lchild;
		}
		else
		{
			pcur = s.top();
			s.pop();
			if (count&&count % 5==0) std::cout << std::endl;
			std::cout << pcur->data << "\t";
			count++;
			pcur = pcur->rchild;
		}
	}
	std::cout << "\n-------------------- end -------------------------\n";
	return OK;
}

status Tree::PostOrderTraverse(Node *pcur)
{
/*
	if (pcur == NULL) pcur = pRoot->ROOT;
	if (pcur == pRoot->ROOT)
		std::cout << "\n---------------PostOrderTraverse-------------------\n";
	
	CONSOLE_SCREEN_BUFFER_INFO cursor_pos;
	GetConsoleScreenBufferInfo(HANDLE_OUT, &cursor_pos);
	if (cursor_pos.dwCursorPosition.X >= 40) std::cout << std::endl;
	if (pcur->lchild) PostOrderTraverse(pcur->lchild);
	if (pcur->rchild) PostOrderTraverse(pcur->rchild);	
	std::cout << pcur->data << "\t";
	if (pcur == pRoot->ROOT)
		std::cout << "\n--------------------- end -------------------------\n";
	return OK;
*/
	std::cout << "\n---------------PostOrderTraverse-------------------\n";
	int count = 0;
	pcur = pRoot->ROOT;
	Node *pprev=NULL;
	s.push(pcur);
	while (!s.empty())
	{
		pcur = s.top();
		if (pcur->lchild == NULL&&pcur->rchild == NULL || pprev&&(pcur->rchild == pprev || pcur->lchild == pprev&&pcur->rchild == NULL))
		{
			if (count&&count % 5==0) std::cout << std::endl;
			std::cout << pcur->data << "\t";
			count++;
			s.pop();
			pprev = pcur;
		}
		else
		{
			if (pcur->lchild&&pcur->lchild!= pprev)
			{
				s.push(pcur->lchild);
			}
			else if (pcur->rchild&&pcur->rchild!=pprev)
			{
				s.push(pcur->rchild);
			}
		}
	}
	std::cout << "\n-------------------- end -------------------------\n";
	return OK;
}

status Tree::LevelOrderTraverse(Node *pcur)
{
	if (pcur == NULL) pcur = pRoot->ROOT;
	std::cout << "\n---------------LevelOrderTraverse-------------------\n";
	int last=1,count = 0;
	Node *p;
	q.push(pcur);
	while (!q.empty())
	{
		p=q.front();
		q.pop();
		if (p) std::cout << p->data << "\t";
		//if (count&&count % 5==0) std::cout << std::endl;
		if (!p) std::cout << " \t";
		count++;
		if (count == last) { count = 0; last *= 2;std::cout << std::endl; }
		if (p) q.push(p->lchild);
		if (p) q.push(p->rchild);
	}
	std::cout << "\n---------------------- end -------------------------\n";
	return OK;
}

std::ifstream&operator>>(std::ifstream &inFile, Tree &temp)
{
	int num;
	pre_order.clear();
	alldata.clear();
	inFile >> num;
	pre_order.resize(num + 1);
	pre_order[0] = num;
	for (int i = 1; i <= pre_order[0]; i++)
		inFile >> pre_order[i];
	inFile >> num;
	alldata.resize(num + 1);
	alldata[0] = num;
	for (int i = 1; i <= alldata[0]; i++)
		inFile >> alldata[i];
	temp.InitBiTree();
	temp.CreateBiTree(pre_order,alldata);
	return inFile;
}

std::ofstream&operator<<(std::ofstream &outFile, Tree &temp)
{
	outFile << temp.CalSize(temp.pRoot->ROOT, 1) << " ";
	Node *pcur = temp.pRoot->ROOT;
	while (pcur||!s.empty())
	{
		if (pcur)
		{
			outFile << pcur->no << " ";
			s.push(pcur);
			pcur = pcur->lchild;
		}
		else
		{
			outFile << MinNo << " ";
			pcur = s.top();
			s.pop();
			pcur = pcur->rchild;
		}
	}
	outFile <<MinNo<<" "<< std::endl;
	outFile << temp.pRoot->tsize << " ";
	pcur = temp.pRoot->ROOT;
	while (pcur||!s.empty())
	{
		if (pcur)
		{
			outFile << pcur->data << " ";
			s.push(pcur);
			pcur = pcur->lchild;
		}
		else
		{
			pcur = s.top();
			s.pop();
			pcur = pcur->rchild;
		}
	}
	return outFile;
}