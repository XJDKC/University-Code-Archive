#include<iostream>
#include<fstream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include<cmath>
#include<windows.h>
#include<cctype>
#include<typeinfo.h>
#include"mylist.h"
#include"myvalue.h"
using namespace std;

int main()
{
	//system("chcp 65001");
	SetConsoleOutputCP(936);								//设置代码页
	SetConsoleWindowInfo(HANDLE_OUT, true, &windows_size);	//设置窗口大小
	init();													//初始化文件链表信息
	select_function();										//选择功能界面
	return 0;
}

void init()													//从文件中加载链表 列表信息
{
	ifstream datalist;
	datalist.open(MultiList_Filename);
	if (!datalist.is_open())
	{
		deal_mention(-3, -1, 0);
		datalist.close();
		ofstream datalist;
		datalist.open(MultiList_Filename);
		datalist << "0" << endl;
		return;
	}
	DATA *p;
	datalist >> list_num;
	datalist.get();
	data_head = NULL;
	for (int i=0;i<list_num;i++)
	{
		p = new(DATA);
		datalist >> *p;
		p->next = data_head;
		data_head = p;
	}
	datalist.close();
}

void Draw_Interface(const char **Interface_Info, COORD pos, int string_num)			//画界面函数
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

void Draw_List_Select()																//画选择要操作的链表界面
{
	system("cls");
	DATA *p = data_head;
	COORD pos=rec;
	CONSOLE_SCREEN_BUFFER_INFO cursor_pos;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	printf("┌────────────────────────────────────────────────┐\n");	pos.Y++;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	printf("│               Menu for Saved Lists             │\n");	pos.Y++;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	printf("│ -----------------------------------------------│\n");	pos.Y++;
	for (int i = 1; i <= list_num; i++)
	{
		SetConsoleCursorPosition(HANDLE_OUT,pos);
		printf("│");
		for (int j=1,temp=16;j<temp;j++)
			printf(" ");
		printf("%d:%s", i, p->filename);
		GetConsoleScreenBufferInfo(HANDLE_OUT, &cursor_pos);
		while (cursor_pos.dwCursorPosition.X < 64) { printf(" "); cursor_pos.dwCursorPosition.X++; }
		printf("│\n");
		pos.Y++;
		p = p->next;
	}
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	printf("│               0:Exit                           │\n");	pos.Y++;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	printf("│ -----------------------------------------------│\n");	pos.Y++;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	printf("│             请选择你的操作数[0-%d]:", list_num);
	GetConsoleScreenBufferInfo(HANDLE_OUT, &cursor_pos);
	while (cursor_pos.dwCursorPosition.X < 64) { printf(" "); cursor_pos.dwCursorPosition.X++; }
	printf("│\n");pos.Y++;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	printf("└────────────────────────────────────────────────┘\n");
	pos.X += strchr(Init_Interface[init_string_num - 2], ':') - Init_Interface[init_string_num - 2]+1;
	pos.Y --;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
}

void select_function()	//选择功能函数 根据输入进入不同的功能
{
	int op=1;
	while (op)
	{
		Draw_Interface(select_interface, select_pos, select_string_num);
		scanf("%d", &op);
		switch (op)
		{
			case 1:select_type(); break;
			case 2:loadlist(); break;
			case 0:deal_mention(-2, 0, 0); break;
			default:deal_mention(-2, 1, 0); op = 1; break;
		}
	}
}

void select_type()		//选择创建列表的类型
{
	while (!var_type)
	{
		Draw_Interface(Init_Interface, init_pos, init_string_num);
		scanf("%d", &var_type);
		if (var_type == 0) { var_type = 1; continue; }
		else if (var_type == 1) { deal_mention(-1, var_type, 0); list_no=0; List<char> LIST; runsys(LIST); }
		else if (var_type == 2) { deal_mention(-1, var_type, 0); list_no=0; List<int> LIST; runsys(LIST); }
		else if (var_type == 3) { deal_mention(-1, var_type, 0); list_no=0; List<float> LIST; runsys(LIST); }
		else if (var_type == 4) { deal_mention(-1, var_type, 0); list_no=0; List<double> LIST; runsys(LIST); }
		else if (var_type == 5) { deal_mention(-1, var_type, 0); list_no=0; List<bool> LIST; runsys(LIST); }
		else { var_type = 0; deal_mention(-1, 0, 0); }
	}
	var_type = 0;
}

void createlist(int no)		//根据文件名 从对应文件中加载链表
{
	DATA *p = data_head;
	for (int i = 1; i < no; i++) p = p->next;
	ifstream inFile;
	inFile.open(p->filename);
	if (!inFile.is_open())
	{
		deal_mention(-3, 3, 0);
	}
	deal_mention(-3, 2, 0);
	inFile >> var_type;
	if (var_type == 1) { List<char> LIST;	inFile >> LIST;inFile.close();	runsys(LIST); }
	else if (var_type == 2) {  List<int> LIST;	inFile >> LIST;inFile.close();	runsys(LIST); }
	else if (var_type == 3) {  List<float> LIST;inFile >> LIST;inFile.close();	runsys(LIST); }
	else if (var_type == 4) {  List<double> LIST;inFile >> LIST;inFile.close();runsys(LIST); }
	else if (var_type == 5) {  List<bool> LIST;	inFile >> LIST;inFile.close();	runsys(LIST); }
	
	var_type = 0;
}

void loadlist()				//从文件中加载链表
{
	ifstream datalist;
	datalist.open(MultiList_Filename);
	if (!datalist.is_open())
	{
		deal_mention(-3, -1, 0);
		exit(EXIT_FAILURE);
	}
	DATA *p;
	datalist >> list_num;
	datalist.get();
	data_head = NULL;
	for (int i=0;i<list_num;i++)
	{
		p = new(DATA);
		datalist >> *p;
		p->next = data_head;
		data_head = p;
	}
	datalist.close();
	int op = 1;
	while (op)
	{
		Draw_List_Select();
		scanf("%d",&op);
		if (op == 0) break;
		else if (op<0 || op>list_num)
		{
			op = 1;
			deal_mention(-3, 1, 0);
		}
		else
		{
			list_no = op;
			createlist(op);
			list_no = op;
			op = 0;
		}
	}
}

template <class Type>
void deal_mention(int op_type, int mention_type, Type info)		//处理各种提示信息
{
	system("cls");
	if (op_type == -3)
	{
		switch (mention_type)
		{
			case 0:printf("打开数据列表文件失败！"); break;
			case 1:printf("请输入正确指令！"); break;
			case 2:printf("顺序表加载成功！"); break;
			case 3:printf("顺序表加载失败！"); break;
		}
	}
	else if (op_type == -2)
	{
		switch (mention_type)
		{
			case 0:printf("欢迎下次使用！"); break;
			case 1:printf("请输入正确指令！"); break;
		}
	}
	else if (op_type==-1)
	{
		switch (mention_type)
		{
			case 0:printf("请输入正确指令！"); break;
			case 1:printf("成功选定建立线性表类型为char字符型！"); break;
			case 2:printf("成功选定建立线性表类型为int整形！"); break;
			case 3:printf("成功选定建立线性表类型为float单精度浮点型！"); break;
			case 4:printf("成功选定建立线性表类型为double双精度浮点型！"); break;
			case 5:printf("成功选定建立线性表类型为bool布尔类型！"); break;
			default:break;
		}
	}
	else if (op_type)
	{
		switch (op_type)
		{
		case 1:	switch (mention_type)
				{
				case -2:printf("线性表创建失败！"); break;
				case 1:printf("线性表创建成功！"); break;
				case -4:printf("已经创建了线性表,若要重新创建,请先销毁！"); break;
				}break;
		case 2:	switch (mention_type)
				{
				case -3:printf("线性表不存在！"); break;
				case 1:printf("线性表销毁成功！"); break;
				}break;
		case 3:	switch (mention_type)
				{
				case -3:printf("线性表不存在！"); break;
				case 1:printf("清空线性表成功！"); break;
				}break;
		case 4:	switch (mention_type)
				{
				case -3:printf("线性表不存在！"); break;
				case 1:printf("当前线性表为空表！"); break;
				case 0:printf("当前线性表不为空表！"); break;
				}break;
		case 5:	switch (mention_type)
				{
				case -3:printf("线性表不存在！"); break;
				default:printf("线性表长度为%d！", mention_type); break;
				}break;
		case 6:	switch (mention_type)
				{
				case -3:printf("线性表不存在！"); break;
				case 0:printf("输入的i不合法！"); break;
				case 1:cout << "线性表中第i个位置的值为:" << info; break;
				}break;
		case 7:	switch (mention_type)
				{
				case -3:printf("线性表不存在！"); break;
				case 0:printf("未找到该元素！"); break;
				default:cout << "输入元素在线性表中的序号为:" << mention_type; break;
				}break;
		case 8:	switch (mention_type)
				{
				case -3:printf("线性表不存在！"); break;
				case 0:printf("未找到输入的当前元素！"); break;
				case 1:cout << "输入元素在线性表中前驱元素为:" << info; break;
				case -4:printf("输入元素没有前驱元素！"); break;
				}break;
		case 9:	switch (mention_type)
				{
				case -3:printf("线性表不存在！"); break;
				case 0:printf("未找到输入的当前元素！"); break;
				case 1:cout << "输入元素在线性表中后继元素:" << info; break;
				case -4:printf("输入元素没有后继元素！"); break;
				}break;
		case 10:switch (mention_type)
				{
				case -3:printf("线性表不存在！"); break;
				case -2:printf("元素插入失败！"); break;
				case 0:printf("输入的位置信息i不合法！"); break;
				case 1:printf("元素插入成功！"); break;
				}break;
		case 11:switch (mention_type)
				{
				case -3:printf("线性表不存在！"); break;
				case 0:printf("输入的位置信息i不合法！"); break;
				case 1:cout << "元素删除成功！  删除的元素值为:" << info; break;
				}break;
		case 12:return;
		case 13:switch (mention_type)
				{
					case -3:printf("线性表不存在！"); break;
					case 0:printf("保存失败！"); break;
					case 1:printf("保存成功！"); break;
				}break;
		default:cout << printf("请输入正确的操作数！"); break;
		}
	}
	printf("\n");
	system("pause");
}

template <class Type>	
void runsys(List<Type> &LIST)						//运行系统 主要功能（链表操作的各个功能）
{
	int i;
	int op = 1;
	int Status = 0;
	int info = 0;

	while (op) {
		Draw_Interface(Main_Interface, main_pos, main_string_num);
		scanf("%d", &op);
		Status = 0;
		switch (op)
		{
		case 1:Status = LIST.IniteList(); break;
		case 2:Status = LIST.DestroyList(); break;
		case 3:Status = LIST.ClearList(); break;
		case 4:Status = LIST.ListEmpty(); break;
		case 5:Status = LIST.ListLength(); break;
		case 6:	system("cls");
			printf("请输入要获取的元素序号：");
			scanf("%d", &i);
			Status = LIST.GetElem(i); break;
		case 7:	system("cls");
			printf("请输入要定位的元素值：");
			cin >> LIST.e;
			Status = LIST.LocateElem(); break;
		case 8:	system("cls");
			printf("请输入当前位置元素值：");
			cin >> LIST.cur_e;
			Status = LIST.PriorElem();
			LIST.e = LIST.pre_e; break;
		case 9:	system("cls");
			printf("请输入当前位置元素值：");
			cin >> LIST.cur_e;
			Status = LIST.NextElem();
			LIST.e = LIST.next_e; break;
		case 10:system("cls");
			printf("请输入待插入元素的位置i和元素值e：");
			cin >> i >> LIST.e;
			Status = LIST.ListInsert(i); break;
		case 11:system("cls");
				printf("请输入待删除元素的位置i：");
				cin >> i;
				Status = LIST.ListDelete(i); break;
		case 12:system("cls");
				Status = LIST.ListTraverse();
				system("pause"); break;
		case 13:Status = SaveList(LIST); break;
		}
		if (op) deal_mention(op, Status, LIST.e);
	}
}

template <class Type>
int SaveList(List<Type> &LIST)				//保存链表信息函数
{
	DATA *p,*pre=NULL;
	if (list_no == 0)
	{
		if (LIST.UnInite() == NOTEXIST) return NOTEXIST;
		p = new(DATA);
		system("cls");
		printf("请输入保存文件名称：");
		scanf("%s", p->filename);
		strcat(p->filename, ".txt");
		p->next = data_head;
		data_head = p;
		list_num++;
	}
	else
	{
		p = data_head;
		for (int i = 1; i < list_no; i++)
		{
			if (p != data_head) pre = p;			
			p = p->next;
		}
		if (LIST.UnInite() == NOTEXIST)
		{
			if (pre == NULL)
				data_head = p->next;
			else pre->next = p->next;
				free(p);
			list_num--;
			return NOTEXIST;
		}
	}
	ofstream outFile(p->filename);
	if (strcmp(LIST.GetType(), "char") == 0)
		outFile << "1"<<endl;
	else if (strcmp(LIST.GetType(), "int") == 0)
		outFile << "2"<<endl;
	else if (strcmp(LIST.GetType(), "float") == 0)
		outFile << "3"<<endl;
	else if (strcmp(LIST.GetType(), "double") == 0)
		outFile << "4"<<endl;
	else if (strcmp(LIST.GetType(), "bool") == 0)
		outFile << "5" << endl;
	outFile << LIST;
	outFile.close();
	outFile.open(MultiList_Filename);
	outFile << list_num << endl;
	p = data_head;
	while (p)
	{
		outFile << *p;
		p = p->next;
	}
	outFile.close();
	return OK;
}