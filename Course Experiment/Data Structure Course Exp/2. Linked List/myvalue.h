#pragma once
#ifndef MYVALUE_H_
#define MYVALUE_H_

HANDLE HANDLE_IN=GetStdHandle(STD_INPUT_HANDLE);
HANDLE HANDLE_OUT=GetStdHandle(STD_OUTPUT_HANDLE);


const char *select_interface[] = {"┌────────────────────────────────────────────────┐\n",
								  "│             Menu for Select Function           │\n",
								  "│ -----------------------------------------------│\n",
								  "│               1.创建一个新的链表               │\n",
								  "│               2.选择一个已有链表               │\n",
								  "│               3.从文件中加载链表               │\n",
							 	  "│               0.退出系统                       │\n",
							 	  "│ -----------------------------------------------│\n",
								  "│             请选择你的操作数[0-3]:             │\n",
								  "└────────────────────────────────────────────────┘\n"};

const char *Main_Interface[]={	"┌────────────────────────────────────────────────┐\n",
								"│    Menu for Linear Table On Chain Structure    │\n",
								"│ -----------------------------------------------│\n",
								"│         1. IntiaList       9. NextElem         │\n",
								"│         2. DestroyList    10. ListInsert       │\n",
								"│         3. ClearList      11. ListDelete       │\n",
								"│         4. ListEmpty      12. ListTrabverse    │\n",
								"│         5. ListLength     13. LoadInfo         │\n",
								"│         6. GetElem        14. SaveInfo         │\n",
								"│         7. LocateElem     15. ChangeName       │\n",
								"│         8. PriorElem       0. Exit             │\n",
								"│ -----------------------------------------------│\n",
								"│             请选择你的操作数[0-13]:            │\n",
								"└────────────────────────────────────────────────┘\n"};

const char *Init_Interface[]={	"┌────────────────────────────────────────────────┐\n",
								"│             Menu for Variable Type             │\n",
								"│ -----------------------------------------------│\n",
								"│                1. bool   布尔型                │\n",
								"│                2. char   字符型                │\n",
								"│                3. int    整形                  │\n",
								"│                4. float  单精度浮点型          │\n",
								"│                5. double 双精度浮点型          │\n",
								"│                0. Exit                         │\n",
								"│ -----------------------------------------------│\n",
								"│             请选择你的操作数[0-5]:             │\n",
								"└────────────────────────────────────────────────┘\n"};

MainList mainhead;

COORD select_pos = { 15,7 };
COORD main_pos = { 15,5 };
COORD init_pos = { 15,5 };
COORD rec = { 15,7 };

SMALL_RECT windows_size = { 0,0,100,30 };

int select_string_num = 10;
int main_string_num = 14;
int init_string_num = 12;

char ListMenu[] = "ListMenu.txt";

void init();
void select_function();
void select_type();
void select_list();
void remove(ListBase *workon);
void runsys(ListBase *workon);
void closesys();
Status SaveList(ListBase *workon);
Status LoadList(ListBase *workon=NULL);
Status ChangeName(ListBase *workon);
void deal_mention(int op_type, int mention_type, ListBase *workon);
void Draw_List_Select(int mode=1);
void Draw_Interface(const char **Interface_Info, COORD pos, int string_num);
#endif