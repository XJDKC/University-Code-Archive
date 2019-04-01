#include<iostream>
#include<string>
#include<cstring>
#include<cctype>
#include<fstream>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
#include<sstream>
#include<limits>
#include<stdexcept>
#include<windows.h>
#include"myvalue.h"
#include"mytree.h"
using namespace std;
int main()
{
	SetConsoleOutputCP(936);
	SetConsoleWindowInfo(HANDLE_OUT, true, &windows_size);
	init();
	select_function();
	return 0;
}

void init()
{
	ifstream inFile(TreeMenu);
	ifstream inTree;
	Tree *p;
	if (!inFile.is_open())
	{
		Deal_Mention(0, -2, 0, 0);
		return ;
	}
	inFile >> tree_no>>untitile_no;
	inFile.get();
	for (int i = 1; i <= tree_no; i++)
	{
		p = new(Tree);
		p->InitBiTree();
		inFile >> p->name;
		p->saved = TRUE;
		inTree.open(p->name+".txt");
		if (!inTree.is_open())
		{
			Deal_Mention(0, -2, 1, 0);
			tree_no = i - 1;
			return;
		}
		inTree >> *p;
		inTree.close();
		p->next = MultiHead;
		MultiHead = p;
	}
	inFile.close();
}

void select_function()
{
	int op = 1;
	while (op)
	{
		Draw_Interface(select_interface, select_pos, select_string_num);
		cin >> op;
		switch (op)
		{
			case 1:runsys(); break;
			case 2:select_tree(); break;
			case 3:LoadTree(); break;
			case 0:closesys(); break;
			default:Deal_Mention(0,-1,ERROR,0); op = 1; break;
		}
	}	
}

void runsys(Tree *workon)
{
	int op=1;
	int LR=0;
	int Info=0;
	int value=0;
	string tree_name,new_name;
	status Status=0;
	Tree *insert=NULL;
	ofstream outFile;
	ostringstream temp;
	if (!workon)
	{
		workon = new(Tree);
		temp << "未命名" << ++untitile_no;
		workon->name = temp.str();
		tree_no++;
		workon->next = MultiHead;
		MultiHead = workon;
	}
	pget = NULL;
	while (op)
	{
		Draw_Interface(Main_Interface, main_pos, main_string_num);
		cin >> op;
		Status = 0;
		if (workon->HasInit() == FALSE&&op&&op != 1&&op!=2)
		{
			op = 1;
			Status = NOTEXIST;
		}
		else
		{
			switch (op)
			{
				case 0:Status = 0; break;
				case 1:Status = workon->InitBiTree(); break;
				case 2:Status = workon->DestroyBiTree();
					   remove(workon); op = 0;break;
				case 3:system("cls");
						Status = InputTreeInfo();
						Status = workon->CreateBiTree(pre_order,alldata); break;
				case 4:Status = workon->ClearBiTree(); break;
				case 5:Status = workon->BiTreeEmpty(); break;
				case 6:Info = workon->BiTreeDepth(); break;
				case 7:pget = workon->Root(); break;
				case 8:system("cls"); 
						cout << "请输入要获取值的节点的标识符:";
						cin >> workon->e;
						Info = workon->Value(); break;
				case 9:system("cls");
						cout << "请输入要赋值节点的标识符和元素值:";
						cin >> workon->e>>value;
						Status = workon->Assign(value); break;
				case 10:system("cls");
						cout << "请输入带操作节点的标识符:";
						cin >> workon->e;
						pget = workon->Parent();break;
				case 11:system("cls");
						cout << "请输入带操作节点的标识符:";
						cin >> workon->e;
						pget = workon->LeftChild();break;
				case 12:system("cls");
						cout << "请输入带操作节点的标识符:";
						cin >> workon->e;
						pget = workon->RightChild();break;
				case 13:system("cls");
						cout << "请输入带操作节点的标识符:";
						cin >> workon->e;
						pget = workon->LeftSibling();break;
				case 14:system("cls");
						cout << "请输入带操作节点的标识符:";
						cin >> workon->e;
						pget = workon->RightSibling();break;
				case 15:system("cls");
						cout << "请输入待插入树的名字:"; cin >> tree_name;
						cout << "请输入插入当前获取节点的子树类型(0:左 1:右):"; cin >> LR;
						if (LR==0||LR==1)
						{
							insert = findtree(tree_name);
							if (insert != NULL)
							{
								Status=workon->InsertChild(pget, LR, *insert);
								if (Status == OK)
								{
									remove(insert);
								}
							}
							else Status = NOTEXIST; break;
						}
						else{ Status = OVERRFLOW; break; }
				case 16:system("cls");
						cout << "请输入待删除子树的类型(0:左 1:右):"; cin >> LR;
						if (LR == 0 || LR == 1)
						{
							Status = workon->DeleteChild(pget, LR);
						}
						else Status = OVERRFLOW; break;
				case 17:system("cls");
						Status=workon->PreOrderTraverse();system("pause"); break;
				case 18:system("cls");
						Status=workon->InOrderTraverse();system("pause"); break;
				case 19:system("cls");
						Status=workon->PostOrderTraverse();system("pause"); break;
				case 20:system("cls");
						Status=workon->LevelOrderTraverse();system("pause"); break;
				case 21:system("cls");
						cout << "当前树的名字为:" << workon->name << endl<<"请输入新的名字:";
						cin >> new_name;
						if (findtree(new_name) != NULL) Status = ERROR;
						else {
							Status = OK; workon->name = new_name;
						}break;
				case 22:outFile.open(workon->name + ".txt");
						outFile << *workon; outFile.close();
						workon->saved = true;
						Status = OK; break;
				case 23:Status = LoadTree(workon);
						break;
			}
		}
		if (op) Deal_Mention(1, op, Status, Info);
	}
}

status LoadTree(Tree *workon)
{
	if (workon == NULL)
	{
		int op = 0;
		int no = 0;
		int count = 0;
		Tree *p=MultiHead;
		while (p)
		{
			if (p->saved) count++;
			p = p->next;
		}
		while (!op)
		{
			Draw_Tree_Select(2);
			cin >> op;
			if (op == 0) break;
			else if (op<0 || op>count)
			{
				op = 0;
				Deal_Mention(-3, 1, 0,0);
			}
			else
			{
				no = op;
			}
		}
		if (no)
		{
			Tree *p=MultiHead;
			while (no)
			{
				if (p->saved) {
					no--;
					if (no == 0)
						break;
				}
				p = p->next;
			}
			ifstream inFile(p->name+".txt");
			inFile >> *p;
			runsys(p);
		}
		return OK;
	}
	else if (workon->HasInit() == FALSE) return NOTEXIST;
	else if (workon->HasInit() == TRUE&&workon->saved)
	{
		ifstream inFile(workon->name+".txt");
		if (!inFile.is_open())
		{
			return ERROR;
		}
		inFile>>*workon;
		pget = NULL;
		return OK;
	}
	return OK;
}

void select_tree()
{
	int op = 0;
	int no = 0;
	while (!op)
	{
		Draw_Tree_Select();
		cin >> op;
		if (op == 0) break;
		else if (op<0 || op>tree_no)
		{
			op = 0;
			Deal_Mention(2, -1, 0, 0);
		}
		else
		{
			no = op;
		}		
	}
	if (no)
	{
		Tree *p=MultiHead;
		while (--no)
		{
			p = p->next;
		}
		runsys(p);
	}
}

void closesys()
{
	ofstream outFile;
	bool mark = true;
	int count = 0;
	Tree *p=MultiHead;
	while (p)
	{
		if (!p->saved&&p->HasInit()==TRUE) { mark = false; break; }
		if (p->HasInit() == FALSE) count++;
		p = p->next;
	}
	tree_no -= count;
	if (!mark)
	{
		char op;			
		ostringstream temp;
		Tree *p = MultiHead;
		while (true)
		{
			system("cls");
			std::cout<<"还有链表未保存，需要保存吗(忽略未初始化树)？Y/N" << endl;
			cin >> op;
			if (op == 'Y' || op == 'N') break;
			else Deal_Mention(0, 0, -1, 0);
		}
		if (op == 'Y')
		{
			while (p)
			{
				if (p->HasInit() == TRUE)
				{
					outFile.open(p->name + ".txt");
					outFile << *p;
					outFile.close();
					p->saved = true;
					p = p->next;
				}
			}
			Deal_Mention(0, 0, OK, 0);
		}
		else
		{
			while (p)
			{
				if (!p->saved&&p->HasInit()==TRUE)
				{
					tree_no--;
				}
				p = p->next;
			}
		}
	}
	outFile.open(TreeMenu);
	outFile << tree_no << " " << untitile_no << endl;
	p = MultiHead;
	while (p)
	{
		if (p->saved&&p->HasInit()==TRUE)
		{
			outFile << p->name << endl;
		}
		p = p->next;
	}
	outFile.close();
	Deal_Mention(0, 0, 0,0);
}

void remove(Tree *workon)
{
	Tree *pcur = MultiHead, *pprev = NULL;
	while (pcur)
	{
		if (pcur == workon)
		{
			if (pprev == NULL)
			{
				MultiHead = pcur->next;
			}
			else
			{
				pprev->next = pcur->next;
			}
		}
		pprev = pcur;		
		pcur = pcur->next;
	}
	tree_no--;
}

status InputTreeInfo()
{
	int value;
	char c;
	std::cout << "请输入待创建树带空格的前序遍历(以$截止 两个元素之间以空格隔开):" << endl;
	cin.clear();
	cin.ignore();
	pre_order.clear();
	pre_order.push_back(0);
	while (cin.get(c))
	{
		if (isdigit(c))
		{
			ungetc(c, stdin);
			cin >> value;
			pre_order.push_back(value);
			pre_order[0]++;
		}
		else if (c == ' ')
		{
			pre_order.push_back(MinNo);
			pre_order[0]++;
		}
		else break;
		cin.get(c);
		if (c == ' ') continue;
		else break;
	}
	std::cout << "请按照前序遍历顺序输入待创建树各个节点值(以$结尾):" << endl;
	alldata.clear();
	alldata.push_back(0);
	while (cin.get(c))
	{
		if (isdigit(c))
		{
			ungetc(c, stdin);
			cin >> value;
			alldata.push_back(value);
			alldata[0]++;
		}
		else if (c == ' ')
		{
			pre_order.push_back(MinNo);
			pre_order[0]++;
		}
		else break;
		cin.get(c);
		if (c == ' ') continue;
		else break;
	}
	return OK;
}

Tree *findtree(string &name)
{
	Tree *pcur = MultiHead;
	while (pcur)
	{
		if (pcur->name == name)
			return pcur;
		pcur = pcur->next;
	}
	return NULL;
}

void Draw_Tree_Select(int mode)
{
	int count = 0;
	system("cls");
	Tree *p=MultiHead;
	COORD pos=rec;
	CONSOLE_SCREEN_BUFFER_INFO cursor_pos;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	std::printf("┌────────────────────────────────────────────────┐\n");	pos.Y++;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	std::printf("│               Menu for Existing Lists          │\n");	pos.Y++;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	std::printf("│ -----------------------------------------------│\n");	pos.Y++;
	for (int i = 1; i <= tree_no; i++)
	{
		if (mode == 2)
		{
			if (p->saved)
			{
				count++;
				SetConsoleCursorPosition(HANDLE_OUT,pos);
				std::printf("│");
				for (int j=1,temp=16;j<temp;j++)
					std::printf(" ");
				std::cout << count << ":" << p->name;
				GetConsoleScreenBufferInfo(HANDLE_OUT, &cursor_pos);
				while (cursor_pos.dwCursorPosition.X < 64) { printf(" "); cursor_pos.dwCursorPosition.X++; }
				std::printf("│\n");
				pos.Y++;
			}
			p = p->next;
		}
		else
		{
			SetConsoleCursorPosition(HANDLE_OUT,pos);
			std::printf("│");
			for (int j=1,temp=16;j<temp;j++)
				std::printf(" ");
			std::cout << i << ":" << p->name;
			GetConsoleScreenBufferInfo(HANDLE_OUT, &cursor_pos);
			while (cursor_pos.dwCursorPosition.X < 64) { printf(" "); cursor_pos.dwCursorPosition.X++; }
			std::printf("│\n");
			pos.Y++;
			p = p->next;
		}

	}
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	std::printf("│               0:Exit                           │\n");	pos.Y++;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	std::printf("│ -----------------------------------------------│\n");	pos.Y++;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	std:: printf("│             请选择你的操作数[0-%d]:", mode == 1 ? tree_no : count);
	GetConsoleScreenBufferInfo(HANDLE_OUT, &cursor_pos);
	while (cursor_pos.dwCursorPosition.X < 64) { printf(" "); cursor_pos.dwCursorPosition.X++; }
	std::printf("│\n");pos.Y++;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	std::printf("└────────────────────────────────────────────────┘\n");
	pos.X += strchr(Init_Interface[init_string_num - 2], ':') - Init_Interface[init_string_num - 2]+1;
	pos.Y --;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
}

void Draw_Interface(const char **Interface_Info, COORD pos, int string_num)
{
	system("cls");
	for (int i = 0; i < string_num; i++)
	{
		SetConsoleCursorPosition(HANDLE_OUT, pos);
		printf("%s", Interface_Info[i]);
		pos.Y++;
	}
	pos.X += strchr(Interface_Info[string_num - 2], ':') - Interface_Info[string_num - 2];
	pos.Y -= 2;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
}

void Deal_Mention(int interface_type, int op_type, int mention_type, int info)
{
	system("cls");
	switch (interface_type)
	{
		case 0:
			switch (op_type)
			{
				case -2: 
					switch (mention_type)
					{
						case 0:cout << "打开多树列表文件失败！" << endl; break;
						case 1:cout << "打开树文件失败！" << endl; break;
					}break;
				case -1:cout << "请输入正确指令！" << endl; break;
				case 0:
					switch (mention_type)
					{
						case -1:cout << "请输入正确指令!" << endl; break;
						case 0:cout << "欢迎下次使用!" << endl; break;
						case 1:cout << "所有树保存成功!" << endl; break;
					}break;
			}break;
		case 1:
			switch (op_type)
			{
				case -1:cout << "请输入正确的操作数" << endl; break;
				case 1:
					switch (mention_type)
					{
						case NOTEXIST:cout << "当前树还未初始化！" << endl; break;
						case EXIST:cout << "当前树已初始化！" << endl; break;
						case OK:cout << "初始化成功！" << endl; break;
					}break;
				case 2:
					switch (mention_type)
					{
						case OK:cout << "销毁成功！" << endl; break;
					}break;
				case 3:
					switch (mention_type)
					{
						case OK:cout << "创建树成功！" << endl; break;
					}break;
				case 4:
					switch (mention_type)
					{
						case OK:cout << "清空树成功！" << endl; break;
					}break;
				case 5:
					switch (mention_type)
					{
						case TRUE:cout << "当前树为空树！" << endl; break;
						case FALSE:cout << "当前树不为空树！" << endl; break;							
					}break;
				case 6:cout << "当前树的深度为:" << info << endl; break;
				case 7:cout << "获取根节点地址为:" << pget << endl;
					   if (pget)
					   {
						   cout << "节点的标识符为:"; pget->GetNo(); cout << endl;
						   cout << "节点的值为:"; pget->GetData(); cout << endl;
					   }break;
				case 8:if (info == MinNo) cout << "未找到输入标识符对应的节点值！" << endl;
					   else cout << "输入标识符对应的节点值为:" << info << endl; break;
				case 9:
					switch (mention_type)
					{
						case ERROR:cout << "未找到输入标识符对应节点！" << endl; break;
						case OK:cout << "赋值成功！" << endl; break;
					}break;
				case 10:cout << "获取双亲节点地址为:" << pget << endl;
						if (pget)
						{
							cout << "节点的标识符为:"; pget->GetNo(); cout << endl;
							cout << "节点的值为:"; pget->GetData(); cout << endl;
						}break;
				case 11:cout << "获取左孩子节点地址为:" << pget << endl;
						if (pget)
						{
							cout << "节点的标识符为:"; pget->GetNo(); cout << endl;
							cout << "节点的值为:"; pget->GetData(); cout << endl;
						}break;
				case 12:cout << "获取右孩子节点地址为:" << pget << endl;
						if (pget)
						{
							cout << "节点的标识符为:"; pget->GetNo(); cout << endl;
							cout << "节点的值为:"; pget->GetData(); cout << endl;
						}break;
				case 13:cout << "获取左兄弟节点地址为:" << pget << endl;
						if (pget)
						{
							cout << "节点的标识符为:"; pget->GetNo(); cout << endl;
							cout << "节点的值为:"; pget->GetData(); cout << endl;
						}break;
				case 14:cout << "获取右兄弟节点地址为:" << pget << endl;
						if (pget)
						{
							cout << "节点的标识符为:"; pget->GetNo(); cout << endl;
							cout << "节点的值为:"; pget->GetData(); cout << endl;
						}break;
				case 15:
					switch (mention_type)
					{
						case NOTEXIST:cout << "未找到输入名字对应的树！" << endl; break;
						case OVERRFLOW:cout << "当前获取节点为空！" << endl; break;
						case ERROR:cout << "待插入子树根节点右子树非空！" << endl; break;
						case OK:cout << "插入成功！" << endl; break;
					}break;
				case 16:
					switch (mention_type)
					{
						case NOTEXIST:cout << "当前获取节点为空！" << endl; break;
						case OVERRFLOW:cout << "当前节点为空！" << endl; break;
						case OK:cout << "删除成功！" << endl; break;
					}break;
				case 17:return;
				case 18:return;
				case 19:return;
				case 20:return;
				case 21:
					switch (mention_type)
					{
						case ERROR:cout << "输入名字与已有树名字重复！" << endl; break;
						case OK:cout << "修改成功" << endl; break;
					}break;
				case 22:
					switch (mention_type)
					{
						case OK:cout << "保存成功！" << endl; break;
					}break;
				case 23:
					switch (mention_type)
					{
						case ERROR:cout << "打开当前树保存文件失败！" << endl; break;
						case OK:cout << "加载成功！" << endl; break;
					}break;
			}break;
	}
	system("pause");
}