#include<iostream>
#include<map>
#include<set>
#include<tuple>
#include<queue>
#include<stack>
#include<string>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<algorithm>
#include<functional>
#include<windows.h>
#include"mymap.h"
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
	ifstream inFile(MapMenu);
	if (!inFile.is_open())
	{
		Deal_Mention(0, -2, 0, 0);
		return ;
	}
	inFile >> MultiHead;
	inFile.close();
}

void runsys(Map *workon)
{
	int op = 1;
	int u, v, w;
	int Info = 0;
	int value = 0;
	ofstream outFile;
	status Status = 0;
	string map_name, new_name;
	pget = NULL;
	while (op)
	{
		Draw_Interface(Main_Interface, main_pos, main_string_num);
		cin >> op;
		Status = 0;
		switch (op)
		{
			case 0:Status = 0; break;
			case 1:DealInput();
					Status = workon->CreateGraph(V_map, E_map); break;
			case 2:Status = workon->DestroyGraph(); 
					MultiHead.DeleteMap(workon); op = 0; break;
			case 3:system("cls");
					cout << "请输入要查找的顶点编号:";
					cin >> u;
					pget = workon->LocateVex(u); break;
			case 4:system("cls");
					cout << "请输入要获取值的顶点的编号:";
					cin >> v;
					Info = workon->GetVex(v); break;
			case 5:system("cls");
					cout << "请分别输入待赋值顶点的编号以及要赋的值:";
					cin >> v >> value;
					Status = workon->PutVex(v, value); break;
			case 6:system("cls");
					cout << "请输入要获取第一个邻接顶点的顶点值:";
					cin >> v;
					pget = workon->FirstAdjVex(v); break;
			case 7:system("cls");
					cout << "请分别输入中心顶点值v和相对顶点值w:";
					cin >> v >> w;
					pget = workon->NextAdjVex(v, w); break;
			case 8:system("cls");
					cout << "请输入要插入的顶点编号:";
					cin >> v;
					Status = workon->InsertVex(v); break;
			case 9:system("cls");
					cout << "请输入待删除的顶点编号:" << endl;	
					cin >> v;
					Status = workon->DeleteVex(v); break;
			case 10:system("cls");
					cout << "请依次输入要插入边两端顶点编号(若为网请还输入边权):" << endl;
					cin >> v >> w;
					if (workon->map_type > 2) cin >> value;
					Status = workon->InsertArc(make_tuple(v, w, value)); break;
			case 11:system("cls");
					cout << "请依次输入待删除边两端顶点编号:" << endl;
					cin >> v >> w;
					if (workon->map_type > 2) cin >> value;
					Status = workon->DeleteArc(make_tuple(v, w, value)); break;
			case 12:system("cls"); workon->DFS(); system("pause"); break;

			case 13:system("cls"); workon->BFSTraverse(); system("pause"); break;
			case 14:system("cls");
					cout << "图当前名字为:" << workon->name << endl<<"请输入新的名字:";
					cin >> new_name;
					if (MultiHead.FindMap(new_name)) Status = EXIST;
					else {
						map_name=workon->name+".txt";
						workon->name = new_name;
						new_name += ".txt";
						if (workon->saved) 
							rename(map_name.c_str(),new_name.c_str());
						Status = OK;
					}break;
			case 15:outFile.open(workon->name+".txt");
					if (!outFile.is_open())	Status = ERROR;
					else {
						outFile << *workon;
						outFile.close();
						workon->saved=true;
						Status = OK;
					}break;
			case 16:Status=LoadMap(workon); break;
			default:op = -1; break;
		}
		if (op) Deal_Mention(1, op, Status, Info);
	}
}

void closesys()
{
	ofstream outFile;
	bool mark = true;
	int count = 0;
	Map *p = MultiHead.M_head;
	while (p)
	{
		if (!p->saved) { mark = false; }
		p = p->M_next;
	}
	if (!mark)
	{
		char op;
		ostringstream temp;
		Map *p = MultiHead.M_head;
		while (true)
		{
			system("cls");
			std::cout << "还有图未保存，需要保存吗？Y/N" << endl;
			cin >> op;
			if (op == 'Y' || op == 'N') break;
			else Deal_Mention(0, 0, -1, 0);
		}
		if (op == 'Y')
		{
			while (p)
			{
				outFile.open(p->name + ".txt");
				outFile << *p;
				outFile.close();
				p->saved = true;
				p = p->M_next;
			}
			Deal_Mention(0, 0, OK, 0);
		}
		else
		{
			while (p)
			{
				if (!p->saved)
				{
					MultiHead.num--;
				}
				p = p->M_next;
			}
		}
	}
	outFile.open(MapMenu);
	outFile << MultiHead;
	outFile.close();
	Deal_Mention(0, 0, 0, 0);
}

void DealInput()
{
	system("cls");
	int n, m;
	cout << "请输入要创建图的顶点数和边数:";
	cin >> n >> m;
	cout << "请输入各个顶点编号(可选择输入初值):"<<endl;
	V_map.clear();
	for (int i = 1,x,value,mark=false; i <= n; i++)
	{
		mark = false;
		do {
			if (mark) cout << "输入顶点已存在请重新输入!" << endl;
			else mark = true;
			cin >> x;
			if (cin.get() != '\n')
				cin >> value;
			else value = -1;
		} while (V_map.find(x) != V_map.end()); 
		V_map[x] = value;
	}
	cout << "请输入各个边两端顶点编号(若为网可选择输入边权):" << endl;
	E_map.clear();
	UD_M_MAP::iterator temp;
	UD_MAP *new_map;
	for (int i = 1, x, y, value,mark=false; i <= m; i++)
	{
		mark = false;
		do {
			if (mark) cout << "输入边已存在请重新输入!" << endl;
			else mark = true;
			cin >> x >> y;
			if (cin.get() != '\n')
				cin >> value;
			else value = -1;
		} while ((temp = E_map.find(x)) != E_map.end() && temp->second.find(y) != temp->second.end());
		if (E_map.find(x) == E_map.end())
		{
			new_map = new(UD_MAP);
			(*new_map)[y] = value;
			E_map[x] = *new_map;
		}
		else
			E_map[x][y] = value;
	}
}

status LoadMap(Map *workon)
{
	if (workon == NULL)
	{
		int op = 0;
		int no = 0;
		int count = 0;
		Map *p = MultiHead.M_head;
		while (p)
		{
			if (p->saved) count++;
			p = p->M_next;
		}
		while (!op)
		{
			Draw_Map_Select(2);
			cin >> op;
			if (op == 0) break;
			else if (op<0 || op>count)
			{
				op = 0;
				Deal_Mention(0, 1, 0, 0);
			}
			else
			{
				no = op;
			}
		}
		if (no)
		{
			Map *p = MultiHead.M_head;
			while (no)
			{
				if (p->saved) {
					no--;
					if (no == 0)
						break;
				}
				p = p->M_next;
			}
			ifstream inFile(p->name + ".txt");
			inFile >> *p;
			runsys(p);
		}
		return OK;
	}
	else if (workon->saved)
	{
		ifstream inFile(workon->name + ".txt");
		if (!inFile.is_open())
		{
			return ERROR;
		}
		inFile >> *workon;
		pget = NULL;
		return OK;
	}
	return OK;
}

void select_map()
{
	int op = 0;
	int no = 0;
	while (!op)
	{
		Draw_Map_Select();
		cin >> op;
		if (op == 0) break;
		else if (op<0 || op>MultiHead.num)
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
		Map *p = MultiHead.M_head;
		while (--no)
		{
			p = p->M_next;
		}
		runsys(p);
	}
}

void select_type()
{
	int map_type = 1;
	ostringstream temp;
	Map *pnew;
	while (map_type)
	{
		Draw_Interface(Init_Interface, init_pos, init_string_num);
		cin >>map_type;
		if (map_type < 0 || map_type>4) { map_type = 1; Deal_Mention(1, -1, 0, 0); }
		else break;
	}
	if (map_type)
	{
		temp << "未命名" << ++MultiHead.untitle_no;
		pnew = new(Map);
		pnew->name = temp.str();
		pnew->map_type = map_type;
		MultiHead.num++;
		pnew->M_next = MultiHead.M_head;
		MultiHead.M_head = pnew;
		runsys(pnew);
	}
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
			case 1:select_type(); break;
			case 2:select_map(); break;
			case 3:LoadMap(); break;
			case 0:closesys(); break;
			default:Deal_Mention(0, -1, ERROR, 0); op = 1; break;
		}
	}
}

void Draw_Map_Select(int mode)
{
	int count = 0;
	system("cls");
	Map *p = MultiHead.M_head;
	COORD pos = rec;
	CONSOLE_SCREEN_BUFFER_INFO cursor_pos;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	std::printf("┌────────────────────────────────────────────────┐\n");	pos.Y++;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	std::printf("│               Menu for Existing Lists          │\n");	pos.Y++;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	std::printf("│ -----------------------------------------------│\n");	pos.Y++;
	for (int i = 1; i <= MultiHead.num; i++)
	{
		SetConsoleCursorPosition(HANDLE_OUT, pos);
		std::printf("│");
		for (int j = 1, temp = 16; j < temp; j++)
			std::printf(" ");
		if (mode == 2)
		{
			if (p->saved)
				std::cout << ++count << ":" << p->name;
		}
		else 
			std::cout << i << ":" << p->name;
		GetConsoleScreenBufferInfo(HANDLE_OUT, &cursor_pos);
		while (cursor_pos.dwCursorPosition.X < 64) { printf(" "); cursor_pos.dwCursorPosition.X++; }
		if (!(mode == 2 && !p->saved)) {
			std::printf("│\n");
			pos.Y++;
		}
		p = p->M_next;
	}
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	std::printf("│               0:Exit                           │\n");	pos.Y++;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	std::printf("│ -----------------------------------------------│\n");	pos.Y++;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	std::printf("│             请选择你的操作数[0-%d]:", (mode == 1 ? MultiHead.num : count));
	GetConsoleScreenBufferInfo(HANDLE_OUT, &cursor_pos);
	while (cursor_pos.dwCursorPosition.X < 64) { printf(" "); cursor_pos.dwCursorPosition.X++; }
	std::printf("│\n"); pos.Y++;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	std::printf("└────────────────────────────────────────────────┘\n");
	pos.X += strchr(Init_Interface[init_string_num - 2], ':') - Init_Interface[init_string_num - 2] + 1;
	pos.Y--;
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
						case 0:cout << "打开多图列表文件失败！" << endl; break;
						case 1:cout << "打开图文件失败！" << endl; break;
					}break;
				case -1:cout << "请输入正确指令！" << endl; break;
				case 0:
					switch (mention_type)
					{
						case -1:cout << "请输入正确指令!" << endl; break;
						case 0:cout << "欢迎下次使用!" << endl; break;
						case 1:cout << "所有图保存成功!" << endl; break;
					}break;
			}break;
		case 1:
			switch (op_type)
			{
				case -1:cout << "请输入正确的操作数!" << endl; break;
				case 1:cout << "创建图成功!" << endl; break;
				case 3:if (pget == NULL)
							cout << "未找到输入编号对应顶点!" << endl;
					   else
					   {
						   cout << "顶点地址为:" << pget << endl;
						   cout << "顶点编号为:" <<pget->GetNo()<< endl;
						   cout << "与输入顶点相邻接的顶点依次为:" << endl;
						   pget->GetNextto();
					   }break;
				case 4:
					switch (mention_type)
					{
						case NOTEXIST:cout << "未找到输入顶点值对应顶点!" << endl; break;
						default:cout << "输入顶点对应值为:" << info << endl;
					}break;
				case 5:
					switch (mention_type)
					{
						case NOTEXIST:cout << "未找到输入顶点编号对应顶点!" << endl; break;
						case OK:cout << "赋值成功!" << endl;
					}break;
				case 6:cout << "第一个邻接顶点地址为:" << pget << endl;
						if (pget)
						{
							 cout << "顶点编号为:" <<pget->GetNo()<< endl;
						}break;
				case 7:cout << "下一邻接顶点地址为:" << pget << endl;
						if (pget)
						{
							cout << "顶点编号为:" << pget->GetNo() << endl;
						}break;
				case 8:
					switch (mention_type)
					{
						case EXIST:cout << "待插入顶点已存在!" << endl; break;
						case OK:cout << "插入成功!" << endl; break;
					}break;
				case 9:
					switch (mention_type)
					{
						case NOTEXIST:cout << "未找到输入顶点编号对应顶点!" << endl; break;
						case OK:cout << "删除成功!" << endl; break;
					}break;
				case 10:
					switch (mention_type)
					{
						case NOTEXIST:cout << "未找到输入顶点编号对应顶点!" << endl; break;
						case EXIST:cout << "待插入边已存在!" << endl; break;
						case OK:cout << "插入成功!" << endl; break;
					}break;
				case 11:
					switch (mention_type)
					{
						case NOTEXIST:cout << "未找到输入顶点编号对应顶点!" << endl; break;
						case ERROR:cout << "待删除边不存在!" << endl; break;
						case OK:cout << "删除成功!" << endl; break;
					}break;
				case 12:return;
				case 13:return;
				case 14:
					switch (mention_type)
					{
						case EXIST:cout << "输入图的名字已在!" << endl; break;
						case OK:cout << "修改成功!" << endl; break;
					}break;
				case 15:
					switch (mention_type)
					{
						case ERROR:cout << "写入失败!" << endl; break;
						case OK:cout << "保存成功!" << endl; break;
					}break;
				case 16:
					switch (mention_type)
					{
						case ERROR:cout << "重新加载失败!" << endl; break;
						case OK:cout << "重新加载成功!" << endl; break;
					}break;
			}break;
	}
	system("pause");
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
