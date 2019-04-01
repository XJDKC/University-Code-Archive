#pragma once
#ifndef MYVALUE_H_
#define MYVALUE_H_

HANDLE HANDLE_IN = GetStdHandle(STD_INPUT_HANDLE);
HANDLE HANDLE_OUT = GetStdHandle(STD_OUTPUT_HANDLE);

const char *select_interface[] = { "┌────────────────────────────────────────────────┐\n",
								  "│             Menu for Select Function           │\n",
								  "│ -----------------------------------------------│\n",
								  "│               1.创建一个新的图                 │\n",
								  "│               2.选择一个已有图                 │\n",
								  "│               3.从文件中加载图                 │\n",
								  "│               0.退出系统                       │\n",
								  "│ -----------------------------------------------│\n",
								  "│             请选择你的操作数[0-3]:             │\n",
								  "└────────────────────────────────────────────────┘\n" };

const char *Main_Interface[] = { "┌──────────────────────────────────────────────────┐\n",
								"│          Menu for Map On Chain Structure         │\n",
								"│ -------------------------------------------------│\n",
								"│       1. CreateGraph      10. InsertArc          │\n",
								"│       2. DestroyGraph     11. DeleteArc          │\n",
								"│       3. LocateVex        12. DFSTraverse        │\n",
								"│       4. GetVex           13. BFSTraverse        │\n",
								"│       5. PutVex           14. ChangeName         │\n",
								"│       6. FirstAdjVex      15. SaveInfo           │\n",
								"│       7. NextAdjVex       16. ReloadInfo         │\n",
								"│       8. InsertVex         0. Exit               │\n",
								"│       9. DeleteVex                               │\n",
								"│ -------------------------------------------------│\n",
								"│               请选择你的操作数[0-17]:            │\n",
								"└──────────────────────────────────────────────────┘\n" };

const char *Init_Interface[] = { "┌────────────────────────────────────────────────┐\n",
								"│                  Menu for Map Type             │\n",
								"│ -----------------------------------------------│\n",
								"│                1. 有向图                       │\n",
								"│                2. 无向图                       │\n",
								"│                3. 有向网                       │\n",
								"│                4. 无向网                       │\n",
								"│                0. Exit                         │\n",
								"│ -----------------------------------------------│\n",
								"│             请选择你的操作数[0-4]:             │\n",
								"└────────────────────────────────────────────────┘\n" };


Vertax *pget;
Multimap MultiHead;

COORD rec = { 15,7 };
COORD main_pos = { 14,4 };		//主要操作界面
COORD init_pos = { 15,5 };		//初始主界面 选择功能界面
COORD select_pos = { 15,7 };	//选择界面

SMALL_RECT windows_size = { 0,0,100,30 };	//窗口大小

int select_string_num = 10; //选择类型
int main_string_num = 15;   //功能
int init_string_num = 11;	//选择类型界面

char MapMenu[] = "MapMenu.txt";		//存放多图的文件目录

void init();						//初始化
void runsys(Map *workon = NULL);	//处理对图的各种操作
void closesys();					//关闭系统
void DealInput();					//处理建图输入
void select_map();					//处理
void select_type();
void select_function();
status LoadMap(Map *workon = NULL);
void Draw_Map_Select(int mode = 1);
void Deal_Mention(int interface_type, int op_type, int mention_type, int info);
void Draw_Interface(const char **Interface_Info, COORD pos, int string_num);

#endif