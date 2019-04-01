#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<string>
#include<cstdlib>
#include<windows.h>
#include<cstring>
#include"mylist.h"
#include"myvalue.h"
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
	string temp;
	ifstream inFile;
	ListBase *p;
	inFile.open(ListMenu);
	if (!inFile.is_open())
	{
		deal_mention(-3, -1, 0);
		return;
	}
	inFile >> mainhead;
	inFile.close();
	p = mainhead.head;
	for (int i = 1; i <= mainhead.length; i++)
	{
		temp = (p->name)+".txt";
		inFile.open(temp);
		p->operator>>(inFile);
		inFile.close();
		p = p->next;
	}
}

void select_function()
{
	int op = 1;
	while (op)
	{
		Draw_Interface(select_interface, select_pos, select_string_num);
		scanf("%d", &op);
		switch (op)
		{
			case 1:select_type(); break;
			case 2:select_list(); break;
			case 3:LoadList(); break;
			case 0:closesys(); break;
			default:deal_mention(-2, 1, 0); op = 1; break;
		}
	}	
}

void select_type()
{
	int var_type=0;
	ostringstream temp;
	ListBase *newlist=NULL;
	while (!var_type)
	{
		Draw_Interface(Init_Interface, init_pos, init_string_num);
		scanf("%d", &var_type);
		if (var_type == 0) {var_type = 6; continue;}
		else if (var_type == 1) newlist = new(List<bool>);
		else if (var_type == 2) newlist = new(List<char>);
		else if (var_type == 3) newlist = new(List<int>);
		else if (var_type == 4) newlist = new(List<float>);
		else if (var_type == 5) newlist = new(List<double>);
		else { var_type = 0; deal_mention(-1, 0, 0); }
	}
	if (var_type > 0 && var_type < 6)
	{
		deal_mention(-1, var_type, 0);
		temp << "δ����" << ++mainhead.count;
		newlist->type = var_type;
		newlist->name = temp.str();
		newlist->next = mainhead.head;
		mainhead.head = newlist;
		mainhead.length++;
		runsys(newlist);
	}
}

void select_list()
{
	int op = 0;
	int no = 0;
	while (!op)
	{
		Draw_List_Select();
		cin >> op;
		if (op == 0) break;
		else if (op<0 || op>mainhead.length)
		{
			op = 0;
			deal_mention(-3, 1, 0);
		}
		else
		{
			no = op;
		}		
	}
	if (no)
	{
		ListBase *p=mainhead.head;
		while (--no)
		{
			p = p->next;
		}
		runsys(p);
	}
}

void remove(ListBase *workon)
{
	ListBase *p = mainhead.head;
	if (workon==mainhead.head)	mainhead.head = mainhead.head->next;
	else {
		while (p->next != workon) p = p->next;
		p->next = workon->next;
	}
	delete(workon);
	mainhead.length--;
}

void runsys(ListBase *workon)
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
		case 1:Status = workon->InitList(); break;
		case 2:Status = workon->DestroyList(); 
			   if (Status != NOTEXIST) {
			       remove(workon); op = 0;
			   } break;
		case 3:Status = workon->ClearList(); break;
		case 4:Status = workon->ListEmpty(); break;
		case 5:Status = workon->ListLength(); break;
		case 6:	system("cls");
			printf("������Ҫ��ȡ��Ԫ����ţ�");
			scanf("%d", &i);
			Status = workon->GetElem(i); break;
		case 7:	system("cls");
			printf("������Ҫ��λ��Ԫ��ֵ��");
			workon->set_e();
			Status = workon->LocateElem(); break;
		case 8:	system("cls");
			printf("�����뵱ǰλ��Ԫ��ֵ��");
			workon->set_cur_e();
			Status = workon->PriorElem(); break;
		case 9:	system("cls");
			printf("�����뵱ǰλ��Ԫ��ֵ��");
			workon->set_cur_e();
			Status = workon->NextElem(); break;
		case 10:system("cls");
			printf("�����������Ԫ�ص�λ��i��Ԫ��ֵe��");
			cin >> i;
			workon->set_e();
			Status = workon->ListInsert(i); break;
		case 11:system("cls");
				printf("�������ɾ��Ԫ�ص�λ��i��");
				cin >> i;
				Status = workon->ListDelete(i); break;
		case 12:system("cls");
				Status = workon->ListTraverse();
				break;
		case 13:Status = LoadList(workon); break;
		case 14:Status = SaveList(workon); break;
		case 15:Status = ChangeName(workon); break;
		}
		if (op) deal_mention(op, Status, workon);
	}
}

void closesys()
{
	ofstream outFile;	
	if (!mainhead.allsaved())
	{
		char op;			
		ostringstream temp;
		ListBase *p = mainhead.head;
		while (true)
		{
			system("cls");
			cout<<"��������δ���棬��Ҫ������Y/N" << endl;
			cin >> op;
			if (op == 'Y' || op == 'N') break;
			else deal_mention(-2, 1, 0);
		}
		if (op == 'Y')
		{
			while (p)
			{
				outFile.open(p->name + ".txt");
				p->operator<<(outFile);
				outFile.close();
				p->saved = true;
				p = p->next;
			}
			deal_mention(-2, 2, 0);
		}
		else
		{
			while (p)
			{
				if (!p->saved) mainhead.length--;
				p = p->next;
			}
		}
	}
	outFile.open(ListMenu);
	outFile << mainhead;
	outFile.close();
	deal_mention(-2, 0, 0);
}

Status LoadList(ListBase *workon)
{
	if (workon == NULL)
	{
		int op = 0;
		int no = 0;
		int count = 0;
		ListBase *p=mainhead.head;
		while (p)
		{
			if (p->saved) count++;
			p = p->next;
		}
		while (!op)
		{
			Draw_List_Select(2);
			cin >> op;
			if (op == 0) break;
			else if (op<0 || op>count)
			{
				op = 0;
				deal_mention(-3, 1, 0);
			}
			else
			{
				no = op;
			}
		}
		if (no)
		{
			ListBase *p=mainhead.head;
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
			p->operator>>(inFile);
			runsys(p);
		}
		return OK;
	}
	else if (workon->head == NULL) return NOTEXIST;
	else if (workon->head!=NULL&&workon->saved)
	{
		ifstream inFile(workon->name+".txt");
		workon->operator>>(inFile);
		return OK;
	}
	return OK;
}

Status SaveList(ListBase *workon)
{
	if (workon->head == NULL) return NOTEXIST;
	string temp;
	if (!workon->saved)
	{
		system("cls");
		printf("�����뱣���ļ����ƣ�");
		cin >> workon->name;
	}
	temp = workon->name + ".txt";
	ofstream outFile(temp);
	if (!outFile.is_open())
	{
		return ERROR;
	}
	workon->operator<<(outFile);
	workon->saved = true;
	outFile.close();
	return OK;
}

Status ChangeName(ListBase *workon)
{
	if (workon->head == NULL) return NOTEXIST;
	string temp=workon->name;
	system("cls");
	cout << "��ǰ��������Ϊ:" << workon->name << endl;
	cout << "�������µ�����:";
	cin >> workon->name;
	ListBase *p = mainhead.head;
	while (p)
	{
		if (p!=workon&&p->name == workon->name)
		{
			workon->name = temp;
			return ERROR;
		}
		p = p->next;
	}
	return OK;
}

void deal_mention(int op_type, int mention_type, ListBase *workon)
{
	system("cls");
	if (op_type == -3)
	{
		switch (mention_type)
		{
			case -1:printf("�������б��ļ�ʧ�ܣ�"); break;
			case 1:printf("��������ȷָ�"); break;
			case 2:printf("������سɹ���"); break;
			case 3:printf("�������ʧ�ܣ�"); break;
		}
	}
	else if (op_type == -2)
	{
		switch (mention_type)
		{
			case 0:printf("��ӭ�´�ʹ�ã�"); break;
			case 1:printf("��������ȷָ�"); break;
			case 2:printf("����������ɹ���"); break;
		}
	}
	else if (op_type==-1)
	{
		switch (mention_type)
		{
			case 0:printf("��������ȷָ�"); break;
			case 1:printf("�ɹ�ѡ��������������Ϊbool�������ͣ�"); break;
			case 2:printf("�ɹ�ѡ��������������Ϊchar�ַ��ͣ�"); break;
			case 3:printf("�ɹ�ѡ��������������Ϊint���Σ�"); break;
			case 4:printf("�ɹ�ѡ��������������Ϊfloat�����ȸ����ͣ�"); break;
			case 5:printf("�ɹ�ѡ��������������Ϊdouble˫���ȸ����ͣ�"); break;
			default:break;
		}
	}
	else if (op_type)
	{
		switch (op_type)
		{
		case 1:	switch (mention_type)
				{
				case -2:printf("������ʧ�ܣ�"); break;
				case 1:printf("�������ɹ���"); break;
				case -4:printf("�Ѿ�����������,��Ҫ���´���,�������٣�"); break;
				}break;
		case 2:	switch (mention_type)
				{
				case -3:printf("�������ڣ�"); break;
				case 1:printf("�������ٳɹ���"); break;
				}break;
		case 3:	switch (mention_type)
				{
				case -3:printf("�������ڣ�"); break;
				case 1:printf("�������ɹ���"); break;
				}break;
		case 4:	switch (mention_type)
				{
				case -3:printf("�������ڣ�"); break;
				case 1:printf("��ǰ����Ϊ�ձ�"); break;
				case 0:printf("��ǰ����Ϊ�ձ�"); break;
				}break;
		case 5:	switch (mention_type)
				{
				case -3:printf("�������ڣ�"); break;
				default:printf("������Ϊ%d��", mention_type); break;
				}break;
		case 6:	switch (mention_type)
				{
				case -3:printf("�������ڣ�"); break;
				case 0:printf("�����i���Ϸ���"); break;
				case 1:cout << "�����е�i��λ�õ�ֵΪ:"; workon->get_e(); break;
				}break;
		case 7:	switch (mention_type)
				{
				case -3:printf("�������ڣ�"); break;
				case 0:printf("δ�ҵ���Ԫ�أ�"); break;
				default:cout << "����Ԫ���������е����Ϊ:" << mention_type; break;
				}break;
		case 8:	switch (mention_type)
				{
				case -3:printf("�������ڣ�"); break;
				case 0:printf("δ�ҵ�����ĵ�ǰԪ�أ�"); break;
				case 1:cout << "����Ԫ����������ǰ��Ԫ��Ϊ:"; workon->get_e(); break;
				case -4:printf("����Ԫ��û��ǰ��Ԫ�أ�"); break;
				}break;
		case 9:	switch (mention_type)
				{
				case -3:printf("�������ڣ�"); break;
				case 0:printf("δ�ҵ�����ĵ�ǰԪ�أ�"); break;
				case 1:cout << "����Ԫ���������к��Ԫ��:";workon->get_e(); break;
				case -4:printf("����Ԫ��û�к��Ԫ�أ�"); break;
				}break;
		case 10:switch (mention_type)
				{
				case -3:printf("�������ڣ�"); break;
				case -2:printf("Ԫ�ز���ʧ�ܣ�"); break;
				case 0:printf("�����λ����Ϣi���Ϸ���"); break;
				case 1:printf("Ԫ�ز���ɹ���"); break;
				}break;
		case 11:switch (mention_type)
				{
				case -3:printf("�������ڣ�"); break;
				case 0:printf("�����λ����Ϣi���Ϸ���"); break;
				case 1:cout << "Ԫ��ɾ���ɹ���  ɾ����Ԫ��ֵΪ:";workon->get_e(); break;
				}break;
		case 12:switch (mention_type)
				{
				case -3:printf("�������ڣ�"); break;
				default:return;
				}break;
		case 13:switch (mention_type)
				{
					case -3:printf("�������ڣ�"); break;
					case 0:printf("����ʧ�ܣ�"); break;
					case 1:printf("���سɹ���"); break;
				}break;
		case 14:switch (mention_type)
				{
					case -3:printf("�������ڣ�"); break;
					case 0:printf("����ʧ�ܣ�"); break;
					case 1:printf("����ɹ���"); break;
				}break;
		case 15:switch (mention_type)
				{
					case -3:printf("�������ڣ�"); break;
					case 0:printf("���������Ѵ��ڣ�"); break;
					case 1:printf("�޸ĳɹ���"); break;
				}break;
		default:cout << printf("��������ȷ�Ĳ�������"); break;
		}
	}
	printf("\n");
	system("pause");
}

void Draw_List_Select(int mode)
{
	int count = 0;
	system("cls");
	ListBase *p=mainhead.head;
	COORD pos=rec;
	CONSOLE_SCREEN_BUFFER_INFO cursor_pos;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	printf("����������������������������������������������������������������������������������������������������\n");	pos.Y++;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	printf("��               Menu for Existing Lists          ��\n");	pos.Y++;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	printf("�� -----------------------------------------------��\n");	pos.Y++;
	for (int i = 1; i <= mainhead.length; i++)
	{
		if (mode == 2)
		{
			if (p->saved)
			{
				count++;
				SetConsoleCursorPosition(HANDLE_OUT,pos);
				printf("��");
				for (int j=1,temp=16;j<temp;j++)
					printf(" ");
				cout << count << ":" << p->name;
				switch (p->type)
				{
				case 1:cout << "(bool)"; break;
				case 2:cout << "(char)"; break;
				case 3:cout << "(int)"; break;
				case 4:cout << "(float)"; break;
				case 5:cout << "(double)"; break;
				}
				GetConsoleScreenBufferInfo(HANDLE_OUT, &cursor_pos);
				while (cursor_pos.dwCursorPosition.X < 64) { printf(" "); cursor_pos.dwCursorPosition.X++; }
				printf("��\n");
				pos.Y++;
			}
			p = p->next;
		}
		else
		{
			SetConsoleCursorPosition(HANDLE_OUT,pos);
			printf("��");
			for (int j=1,temp=16;j<temp;j++)
				printf(" ");
			cout << i << ":" << p->name;
			switch (p->type)
			{
			case 1:cout << "(bool)"; break;
			case 2:cout << "(char)"; break;
			case 3:cout << "(int)"; break;
			case 4:cout << "(float)"; break;
			case 5:cout << "(double)"; break;
			}
			GetConsoleScreenBufferInfo(HANDLE_OUT, &cursor_pos);
			while (cursor_pos.dwCursorPosition.X < 64) { printf(" "); cursor_pos.dwCursorPosition.X++; }
			printf("��\n");
			pos.Y++;
			p = p->next;
		}

	}
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	printf("��               0:Exit                           ��\n");	pos.Y++;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	printf("�� -----------------------------------------------��\n");	pos.Y++;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	printf("��             ��ѡ����Ĳ�����[0-%d]:", mode==1?mainhead.length:count);
	GetConsoleScreenBufferInfo(HANDLE_OUT, &cursor_pos);
	while (cursor_pos.dwCursorPosition.X < 64) { printf(" "); cursor_pos.dwCursorPosition.X++; }
	printf("��\n");pos.Y++;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	printf("����������������������������������������������������������������������������������������������������\n");
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