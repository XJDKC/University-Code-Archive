#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wincon.h>
#include <string.h>
#include <conio.h>
#include <io.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <consoleapi.h>

#ifndef ISYSTEM_H_INCLUDED
#define ISYSTEM_H_INCLUDED

#define Size_R 25					//窗口以及缓冲区高度 （行数）
#define Size_C 80					//窗口以及缓冲区高度 （列数）

/*结构体声明*/
typedef struct Type					//学校类型 结构体  type->类型
{									//作为招生信息管理系统数据链的主链
    char classes;					//学校类型
    int num;						//该学校类型下 所有学校个数 （根据输入的支链学校自动计算）
    struct Type *next;				//结构指针 指向下一个学校类型结构体
	struct Type *prev;				//结构指针 指向前一个学校类型结构体 （用于数据查询数据统计时方便遍历链表）
    struct Basic *nextB;			//结构指针 指向该学校类型下学校基本信息链的链头
}TYPE;								

typedef struct Basic				//学校基本信息 结构体 basic->基本
{									//作为招生信息管理系统数据链的支链
	char classes;					//学校类型
    char no[12];					//学校编号
    char name[30];					//学校名称
    char address[50];				//学校地址
    char contacts[20];				//学校联系人
    char con_num[20];				//学校联系电话
    struct Basic *next;				//结构指针 指向下一个学校基本信息结构体 
	struct Basic *prev;				//结构指针 指向前一个学校基本类型结构体 （用于数据查询数据统计时方便遍历链表）
    struct Recruit *nextR;			//结构指针 指向该学校历年招生信息链的链头
}BASIC;

typedef struct Recruit				//学校招生基本信息 结构体 recruit->招生 录取
{									//作为招生信息管理系统数据链的旁链
	char classes;					//学校类型
    char no[12];					//学校编号
    char year[5];					//学校招生信息对应年份
    int index_num;					//录取学生指标数
    int enroll_num;					//实际录取学生数
    float ad_score;					//录取分数线
    float high_score;				//录取最高分
    float low_score;				//录取最低分
	struct Recruit *next;			//结构指针 指向下一个学校招生信息结构体
	struct Recruit *prev;			//结构指针 指向前一个学校招生信息结构体 （用于数据查询数据统计时方便遍历链表）
}RECRUIT;

typedef struct layer_node			//图层信息 结构体
{									//用于存放缓冲区内各个图层信息
    char no;                        //当前图层层号
    SMALL_RECT pop_area;            //当前图层区域
    CHAR_INFO *cur_info;            //当前图层文字信息（ascll字符+颜色）
    unsigned short *cur_attr;		//当前图层特性（前两位表示图层层号 中间三位表示主菜单编号 后四位表示热区编号）
	struct Hot_Area *cur_area;		//当前图层热区信息
    struct layer_node *next;		//结构指针 指向下一层图层信息结构体
}LAYER_NODE;


typedef union state_area						//状态区域 联合
{												//用于取出鼠标当前位置的图层特性
    unsigned short info;						//用于存放整个图层特性信息
    struct node									//字段结构
    {											//info 下不同字段对应着不同的信息 字段结构用于将其取出
		unsigned short layer_no     : 2;		//图层号
		unsigned short sel_main_num : 3;		//当前选中的主菜单编号
        unsigned short sel_sub_num  : 4;		//当前选中的热区编号
		unsigned short type         : 4;		//热区类型
    }comb;										//comb-> 联合
}STATE_AREA;									

typedef struct Text_Bar					//文字条 结构体
{										//用于存放图层下各个文字条的信息
	int no;                             //文字条的个数
	COORD *pLPos;                       //每一个文字条的起始位置
	char **pTextInfo;                   //每一个文字条的文字信息字符串首地址
}TEXT_BAR;								

typedef struct Hot_Area					//热区 结构体
{										//用于存放当前图层下各个热区信息
	int no;                             //热区数量
	int bottom_no;                      //底部按钮数量
	char *pHotType;                     //热区的类型 1表示选项 2表示可写 3表示只读 4表示确认 5表示取消 6表示上一页 7表示下一页
	unsigned short *pHotNum;            //热区对应的编号 从1开始 
	COORD size;                         //热区对应的大小 
	SMALL_RECT *pArea;                  //每个热区的位置（长方形表示）
}HOT_AREA;

typedef struct Back_Info				//备份信息 结构体
{										//用于存放各个备份信息 在系统运行开始的时候会从备份列表文件中讲将各个备份信息读入
	char filename[30];					//当前备份的路径
	struct Back_info *next;				//结构指针 指向下一个备份信息
}BACK_INFO;

/*主界面文字信息存储*/
char title[]={"高校招生信息管理系统"};    //系统标题

const char *I_Main_Menu[]={				//主菜单 各选项文字信息
       "    文件(F)     ",
       "   数据维护(M)  ",
       "   数据查询(Q)  ",
       "   数据统计(S)  ",
       "     帮助(H)    "
};
const char *I_List_File[]={				//主菜单 文件子菜单 各选项文字信息
     "[S] 数据保存",
     "[B] 数据备份",
     "[R] 数据恢复",
	 "[D] 备份删除",
     "[X] 退出   Alt+X"
};
const char *I_Data_Maintain[]={			//主菜单 数据维护子菜单 各选项文字信息
     "[T] 高校分类信息",
     "[B] 高校基本信息",
     "[R] 高校招生基本信息"
};
const char *I_Data_Refer[]={			//主菜单 数据查询子菜单 各选项文字信息
     "[T] 高校分类信息",
     "[B] 高校基本信息",
     "[R] 高校招生基本信息"
};
const char *I_Data_Statistics[]={		//主菜单 数据统计子菜单 各选项文字信息
     "[Y] 按年度统计各类高校实录人数",
     "[R] 按年度统计高校实录人数",
     "[M] 历年录取人数最多高校",
     "[H] 录取最高分高出分数线最多的10所学校",
     "[O] 按年度统计录取分数线最高的10所学校"
};
const char *I_Help_Info[]={				//主菜单 帮助子菜单 各选项文字信息
     "[T] 帮助主题",
	 "",
     "[A] 关于..."
};

const char **List_Of_All[]={			//用二级指针数组将各个子菜单字符串数组连接起来 构成一个三维数组
     I_List_File,						//文件子菜单
     I_Data_Maintain,					//数据维护子菜单
     I_Data_Refer,						//数据查询子菜单
     I_Data_Statistics,					//数据统计子菜单
     I_Help_Info						//帮助子菜单
};

/*各种外部变量声明*/
unsigned long ul;									//ul->unsigned long 
char back_list_filename[] = { "back_list.dat" };	//备份信息列表文件名字符串 用于打开该文件
char type_data_filename[] = {"type.dat"};			//学校分类信息数据文件名字符串 用于打开分类信息文件
char basic_data_filename[] = { "basic.dat" };		//学校基本信息数据文件名字符串 用于打开基本信息文件
char recruit_data_filename[] = { "recruit.dat" };	//学校招生信息数据文件名字符串 用于打开招生信息文件
unsigned long back_no = 0;							//用于存放备份文件数量
int mainmenu_num = 5;								//主菜单数量
int sel_main_num = 0;								//选中的主菜单编号 0表示没有选中任何主菜单
int sel_sub_num = 0;								//选中的子菜单（热区）编号 0表示没有选中任何子菜单（热区）
int submenu_num[] = { 5,3,3,5,3 };					//存放各个子菜单的选项个数
BOOL Open_Sub = FALSE;								//bool 类型 表示是否打开了子菜单 1:表示 打开 2:表示没有打开 

/*各个信息链的链头声明*/
TYPE *head = NULL;									//招生信息管理系统十字链表数据链 总链头
BACK_INFO *back_list_head = NULL;					//备份信息列表数据链的链头
LAYER_NODE *top_layer_head = NULL;					//图层信息链的链头
CHAR_INFO *Buff_Menubar_Info = NULL;				//存放菜单栏缓冲区的字符信息 (字符码值 和 颜色)

/*界面其他信息声明和存储*/
unsigned short *scr_attr = NULL;					//主界面 属性信息字符串 在主程序中 进行分配空间
HANDLE Handle_In;									//程序输入句柄 通过句柄完成各个信息到句柄对应进程的输入
HANDLE Handle_Out;									//程序输出句柄 通过句柄完成各个信息到句柄对应进程的输出
COORD Interface_Size = { Size_C , Size_R };			//界面大小
SMALL_RECT Win_Size = { 0,0,Size_C - 1,Size_R - 1 };//界面大小 （小矩形 结构体）


//不同类型区域的颜色设置 
WORD Tag_Attr = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY; //标记颜色（选中选项后 选项对应颜色）
WORD Interface_Color = FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN;						 //界面颜色
WORD Rec_Attr= BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;		 //边框颜色
WORD Hot_Attr = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;		 //热区颜色
WORD Fix_Input_Attr = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;					 //锁定输入区 
WORD Input_Attr = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_INTENSITY;//输入区域颜色


/*各种函数声明*/
void SetRightConsoleMode();			//初始化控制台输入输出模式
void LoadData();					//加载数据
void InitInterface();				//初始化界面
void Clear_Buffer();				//清空缓冲区(不然颜色不会变)
void RunSys();						//运行系统
void CloseSys();					//关闭系统
void InitLayer();					//图层信息初始化
int TagHotArea(int num);			//标记子菜单对应编号
void TagMainMenu(int num);			//标记主菜单对应编号
void PopSubMenu(int num);			//弹出子菜单 让Open_Sub=TRUE  
void WithdrewPopHot();				//收回当前子菜单 并让 sel_sub_num 置为0 open_sub置为false
void OpenNewMenu(int num);			//标记主菜单 并打开新的子菜单
void PopHot(SMALL_RECT *,WORD ,TEXT_BAR *,HOT_AREA *);  //四个变量分别对应 位置 颜色 文字条 热区
void ShutHot();						//关闭弹窗 热区
void DrawRec(SMALL_RECT *, WORD );	//绘制弹窗边框
void CalSubArea(SMALL_RECT *);		//计算子菜单大小
BOOL iFunction(int x_num,int y_num);//子菜单对应各个功能函数的 调用 
void FreeList(TYPE *del_type,BASIC *del_basic,RECRUIT *del_recruit);		//释放数据链 对应内存区域 
void PresentStatInfo(int mode, int total, int column_no, COORD *write_pos, RECRUIT *stat_ans);	//展现统计信息 被打印统计函数调用
void PrintStatInfo(int mode, int *present_type, int column_no, char **present_info, COORD *pos);//打印统计信息 
void CalPopArea(SMALL_RECT *rec_pop, TEXT_BAR *cur_text, char **text_info, int *space_num, int bottom_no);//计算弹窗大小 并计算各个文字条信息
void PresentQueryInfo(BASIC *basic_query_ans, RECRUIT *recruit_query_ans, int *cur_char_num, int *space_num, int total);//展现查询信息
void InitHotInfo(SMALL_RECT *rec_pop, TEXT_BAR *cur_text, HOT_AREA *cur_area, char **text_info, int text_no, int *hot_type, int *space_num);//初始化热区信息


void InsertType();					//数据维护 插入分类信息
void DeleteType();					//数据维护 删除分类信息
void ModifyType();					//数据维护 修改分类信息

void InsertBasic();					//数据维护 插入学校基本信息		
void DeleteBasic();					//数据维护 删除学校基本信息
void ModifyBasic();					//数据维护 修改学校基本信息

void InsertRecruit();				//数据维护 插入学校招生信息
void DeleteRecruit();				//数据维护 删除学校招生信息
void ModifyRecruit();				//数据维护 修改学校招生信息

void QueryType_Classes();			//数据查询 通过学校类型 查询学校分类信息

void QueryBasic_No();				//数据查询 通过编号 查询学校基本信息
void QueryBasic_Name();				//数据查询 通过名字 查询学校基本信息 （支持模糊查询）

void QueryRecruit_NoYear();			//数据查询 通过编号和年份   查询学校基本信息
void QueryRecruit_Score();			//数据查询 通过录取分数区间 查询学校基本信息

BOOL SaveData(void);				//功能函数 保存数据 
BOOL BackData(void);				//功能函数 备份数据
BOOL RecoveryData(void);			//功能函数 恢复数据
BOOL DeleteBack();					//功能函数 删除备份
BOOL ExitSys(void);					//功能函数 退出系统

BOOL MaintainType(void);			//功能函数 数据维护 维护学校分类信息 维护类型选项
BOOL MaintainBasic(void);			//功能函数 数据维护 维护学校基本信息 维护类型选项
BOOL MaintainRecruit(void);			//功能函数 数据维护 维护学校招生信息 维护类型选项

BOOL QueryType(void);				//功能函数 数据查询 查询学校分类信息 维护类型选项
BOOL QueryBasic(void);				//功能函数 数据查询 查询学校基本信息 维护类型选项
BOOL QueryRecruit(void);			//功能函数 数据查询 查询学校招生信息 维护类型选项

BOOL StatTypePeople(void);			//功能函数 数据统计 统计不同分类下总录取人数
BOOL StatAllPeople(void);			//功能函数 数据统计 按年度统计各高校实录人数
BOOL StatEnrollNum(void);			//功能函数 数据统计 统计历年录取人数最多高校
BOOL StatHighScore(void);			//功能函数 数据统计 统计最高分高出分数线最多的10所学校
BOOL StatHighIndex(void);			//功能函数 数据统计 按年度统计录取分数线最高的10所学校

BOOL HelpSys(void);					//功能函数 帮助信息展示
BOOL AboutSys(void);				//功能函数 关于信息展示

int CreateList();					//创建链表 读取文件信息
int ErrorMention(int num);			//信息提醒
int DealEvent(int no);                                                       //处理弹窗的鼠标键盘事件
int DealIntput(HOT_AREA *cur_area, int *space_num,int *cur_char_num);        //处理输入型弹窗事件
int InitHotArea(int mode,int bottom_no, int text_no, int area_no, int min_width, int *cur_char_num, int *space_num, int *hot_type, char **text_info); //初始化热区

TYPE *FindTypePoint(char classes);								//寻找学校分类信息节点	
BASIC *FindBasicPoint(char classes, char *no);					//寻找学校基本信息节点
RECRUIT *FindRecruitPoint(char classes,char *no,char *year);	//寻找学校招生信息节点

TYPE *DealTypeInputInfo(TYPE *input_info, int mode,int command, int *space_num, int *cur_char_num);				//处理学校分类信息的输入
BASIC *DealBasicInputInfo(BASIC *input_info, int mode, int command, int *space_num, int *cur_char_num);			//处理学校基本信息的输入
RECRUIT *DealRecruitInputInfo(RECRUIT *input_info, int mode, int command, int *space_num, int *cur_char_num);	//处理学校招生信息的输入

RECRUIT *StatListCreate(int mode, int *total,RECRUIT *input_info);	//统计信息链表创建
RECRUIT *StatListSort(int mode,RECRUIT *stat_head);					//统计信息链表的排序
BOOL StatComp(int mode,RECRUIT *x,RECRUIT *y);						//统计信息排序比较 不同方式 

#endif // ISYSTEM_H_INCLUDED
