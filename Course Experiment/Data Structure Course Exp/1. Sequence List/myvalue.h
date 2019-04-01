//myvalue.h 变量函数声明存储
#ifndef MYVALUE_H_
#define MYVALUE_H_

HANDLE HANDLE_IN=GetStdHandle(STD_INPUT_HANDLE);
HANDLE HANDLE_OUT=GetStdHandle(STD_OUTPUT_HANDLE);


const char *select_interface[] = {"┌────────────────────────────────────────────────┐\n",
								  "│             Menu for Select Function           │\n",
								  "│ -----------------------------------------------│\n",
								  "│               1.创建一个新的顺序表             │\n",
								  "│               2.从文件中加载顺序表             │\n",
							 	  "│               0.退出系统                       │\n",
							 	  "│ -----------------------------------------------│\n",
								  "│             请选择你的操作数[0-3]:             │\n",
								  "└────────────────────────────────────────────────┘\n"};

const char *Main_Interface[]={	"┌────────────────────────────────────────────────┐\n",
								"│  Menu for Linear Table On Sequence Structu1re  │\n",
								"│ -----------------------------------------------│\n",
								"│         1. IntiaList       8. PriorElem        │\n",
								"│         2. DestroyList     9. NextElem         │\n",
								"│         3. ClearList      10. ListInsert       │\n",
								"│         4. ListEmpty      11. ListDelete       │\n",
								"│         5. ListLength     12. ListTrabverse    │\n",
								"│         6. GetElem        13. SaveInfo         │\n",
								"│         7. LocateElem      0. Exit             │\n",
								"│ -----------------------------------------------│\n",
								"│             请选择你的操作数[0-14]:            │\n",
								"└────────────────────────────────────────────────┘\n"};

const char *Init_Interface[]={	"┌────────────────────────────────────────────────┐\n",
								"│             Menu for Variable Type             │\n",
								"│ -----------------------------------------------│\n",
								"│                1. char   字符型                │\n",
								"│                2. int    整形                  │\n",
								"│                3. float  单精度浮点型          │\n",
								"│                4. double 双精度浮点型          │\n",
								"│                5. bool   布尔型                │\n",
								"│                0. Exit                         │\n",
								"│ -----------------------------------------------│\n",
								"│             请选择你的操作数[0-5]:             │\n",
								"└────────────────────────────────────────────────┘\n"};
struct DATA
{
	char filename[31];
	DATA *next;
	friend std::ifstream &operator>>(std::ifstream &ifs, DATA &x);
	friend std::ofstream &operator<<(std::ofstream &ofs, const DATA &x);
};

std::ifstream &operator>>(std::ifstream &ifs, DATA &x)
{
	ifs >> x.filename;
	ifs.get();
	return ifs;
}

std::ofstream &operator<<(std::ofstream &ofs, DATA &x)
{
	ofs << x.filename << std::endl;
	return ofs;
}

DATA *data_head=NULL;

COORD select_pos = { 15,7 };
COORD main_pos = { 15,5 };
COORD init_pos = { 15,5 };
COORD rec = { 15,7 };

SMALL_RECT windows_size = { 0,0,100,30 };

char MultiList_Filename[] = "DataList.txt";

int select_string_num = 9;
int main_string_num = 13;
int init_string_num = 12;
int var_type=0;
int list_num = 0;
int list_no=0;


void init();
void select_function();
void select_type();
void loadlist();
void Draw_Interface(const char **Interface_Info, COORD pos, int string_num);
void Draw_List_Select();

template <class Type>
void deal_mention(int op_type, int mention_type, Type info);

template <class Type>
void runsys(List<Type> &LIST);

template <class Type>
int SaveList(List<Type> &LIST);

#endif