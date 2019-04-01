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

#define Size_R 25					//�����Լ��������߶� ��������
#define Size_C 80					//�����Լ��������߶� ��������

/*�ṹ������*/
typedef struct Type					//ѧУ���� �ṹ��  type->����
{									//��Ϊ������Ϣ����ϵͳ������������
    char classes;					//ѧУ����
    int num;						//��ѧУ������ ����ѧУ���� �����������֧��ѧУ�Զ����㣩
    struct Type *next;				//�ṹָ�� ָ����һ��ѧУ���ͽṹ��
	struct Type *prev;				//�ṹָ�� ָ��ǰһ��ѧУ���ͽṹ�� ���������ݲ�ѯ����ͳ��ʱ�����������
    struct Basic *nextB;			//�ṹָ�� ָ���ѧУ������ѧУ������Ϣ������ͷ
}TYPE;								

typedef struct Basic				//ѧУ������Ϣ �ṹ�� basic->����
{									//��Ϊ������Ϣ����ϵͳ��������֧��
	char classes;					//ѧУ����
    char no[12];					//ѧУ���
    char name[30];					//ѧУ����
    char address[50];				//ѧУ��ַ
    char contacts[20];				//ѧУ��ϵ��
    char con_num[20];				//ѧУ��ϵ�绰
    struct Basic *next;				//�ṹָ�� ָ����һ��ѧУ������Ϣ�ṹ�� 
	struct Basic *prev;				//�ṹָ�� ָ��ǰһ��ѧУ�������ͽṹ�� ���������ݲ�ѯ����ͳ��ʱ�����������
    struct Recruit *nextR;			//�ṹָ�� ָ���ѧУ����������Ϣ������ͷ
}BASIC;

typedef struct Recruit				//ѧУ����������Ϣ �ṹ�� recruit->���� ¼ȡ
{									//��Ϊ������Ϣ����ϵͳ������������
	char classes;					//ѧУ����
    char no[12];					//ѧУ���
    char year[5];					//ѧУ������Ϣ��Ӧ���
    int index_num;					//¼ȡѧ��ָ����
    int enroll_num;					//ʵ��¼ȡѧ����
    float ad_score;					//¼ȡ������
    float high_score;				//¼ȡ��߷�
    float low_score;				//¼ȡ��ͷ�
	struct Recruit *next;			//�ṹָ�� ָ����һ��ѧУ������Ϣ�ṹ��
	struct Recruit *prev;			//�ṹָ�� ָ��ǰһ��ѧУ������Ϣ�ṹ�� ���������ݲ�ѯ����ͳ��ʱ�����������
}RECRUIT;

typedef struct layer_node			//ͼ����Ϣ �ṹ��
{									//���ڴ�Ż������ڸ���ͼ����Ϣ
    char no;                        //��ǰͼ����
    SMALL_RECT pop_area;            //��ǰͼ������
    CHAR_INFO *cur_info;            //��ǰͼ��������Ϣ��ascll�ַ�+��ɫ��
    unsigned short *cur_attr;		//��ǰͼ�����ԣ�ǰ��λ��ʾͼ���� �м���λ��ʾ���˵���� ����λ��ʾ������ţ�
	struct Hot_Area *cur_area;		//��ǰͼ��������Ϣ
    struct layer_node *next;		//�ṹָ�� ָ����һ��ͼ����Ϣ�ṹ��
}LAYER_NODE;


typedef union state_area						//״̬���� ����
{												//����ȡ����굱ǰλ�õ�ͼ������
    unsigned short info;						//���ڴ������ͼ��������Ϣ
    struct node									//�ֶνṹ
    {											//info �²�ͬ�ֶζ�Ӧ�Ų�ͬ����Ϣ �ֶνṹ���ڽ���ȡ��
		unsigned short layer_no     : 2;		//ͼ���
		unsigned short sel_main_num : 3;		//��ǰѡ�е����˵����
        unsigned short sel_sub_num  : 4;		//��ǰѡ�е��������
		unsigned short type         : 4;		//��������
    }comb;										//comb-> ����
}STATE_AREA;									

typedef struct Text_Bar					//������ �ṹ��
{										//���ڴ��ͼ���¸�������������Ϣ
	int no;                             //�������ĸ���
	COORD *pLPos;                       //ÿһ������������ʼλ��
	char **pTextInfo;                   //ÿһ����������������Ϣ�ַ����׵�ַ
}TEXT_BAR;								

typedef struct Hot_Area					//���� �ṹ��
{										//���ڴ�ŵ�ǰͼ���¸���������Ϣ
	int no;                             //��������
	int bottom_no;                      //�ײ���ť����
	char *pHotType;                     //���������� 1��ʾѡ�� 2��ʾ��д 3��ʾֻ�� 4��ʾȷ�� 5��ʾȡ�� 6��ʾ��һҳ 7��ʾ��һҳ
	unsigned short *pHotNum;            //������Ӧ�ı�� ��1��ʼ 
	COORD size;                         //������Ӧ�Ĵ�С 
	SMALL_RECT *pArea;                  //ÿ��������λ�ã������α�ʾ��
}HOT_AREA;

typedef struct Back_Info				//������Ϣ �ṹ��
{										//���ڴ�Ÿ���������Ϣ ��ϵͳ���п�ʼ��ʱ���ӱ����б��ļ��н�������������Ϣ����
	char filename[30];					//��ǰ���ݵ�·��
	struct Back_info *next;				//�ṹָ�� ָ����һ��������Ϣ
}BACK_INFO;

/*������������Ϣ�洢*/
char title[]={"��У������Ϣ����ϵͳ"};    //ϵͳ����

const char *I_Main_Menu[]={				//���˵� ��ѡ��������Ϣ
       "    �ļ�(F)     ",
       "   ����ά��(M)  ",
       "   ���ݲ�ѯ(Q)  ",
       "   ����ͳ��(S)  ",
       "     ����(H)    "
};
const char *I_List_File[]={				//���˵� �ļ��Ӳ˵� ��ѡ��������Ϣ
     "[S] ���ݱ���",
     "[B] ���ݱ���",
     "[R] ���ݻָ�",
	 "[D] ����ɾ��",
     "[X] �˳�   Alt+X"
};
const char *I_Data_Maintain[]={			//���˵� ����ά���Ӳ˵� ��ѡ��������Ϣ
     "[T] ��У������Ϣ",
     "[B] ��У������Ϣ",
     "[R] ��У����������Ϣ"
};
const char *I_Data_Refer[]={			//���˵� ���ݲ�ѯ�Ӳ˵� ��ѡ��������Ϣ
     "[T] ��У������Ϣ",
     "[B] ��У������Ϣ",
     "[R] ��У����������Ϣ"
};
const char *I_Data_Statistics[]={		//���˵� ����ͳ���Ӳ˵� ��ѡ��������Ϣ
     "[Y] �����ͳ�Ƹ����Уʵ¼����",
     "[R] �����ͳ�Ƹ�Уʵ¼����",
     "[M] ����¼ȡ��������У",
     "[H] ¼ȡ��߷ָ߳�����������10��ѧУ",
     "[O] �����ͳ��¼ȡ��������ߵ�10��ѧУ"
};
const char *I_Help_Info[]={				//���˵� �����Ӳ˵� ��ѡ��������Ϣ
     "[T] ��������",
	 "",
     "[A] ����..."
};

const char **List_Of_All[]={			//�ö���ָ�����齫�����Ӳ˵��ַ��������������� ����һ����ά����
     I_List_File,						//�ļ��Ӳ˵�
     I_Data_Maintain,					//����ά���Ӳ˵�
     I_Data_Refer,						//���ݲ�ѯ�Ӳ˵�
     I_Data_Statistics,					//����ͳ���Ӳ˵�
     I_Help_Info						//�����Ӳ˵�
};

/*�����ⲿ��������*/
unsigned long ul;									//ul->unsigned long 
char back_list_filename[] = { "back_list.dat" };	//������Ϣ�б��ļ����ַ��� ���ڴ򿪸��ļ�
char type_data_filename[] = {"type.dat"};			//ѧУ������Ϣ�����ļ����ַ��� ���ڴ򿪷�����Ϣ�ļ�
char basic_data_filename[] = { "basic.dat" };		//ѧУ������Ϣ�����ļ����ַ��� ���ڴ򿪻�����Ϣ�ļ�
char recruit_data_filename[] = { "recruit.dat" };	//ѧУ������Ϣ�����ļ����ַ��� ���ڴ�������Ϣ�ļ�
unsigned long back_no = 0;							//���ڴ�ű����ļ�����
int mainmenu_num = 5;								//���˵�����
int sel_main_num = 0;								//ѡ�е����˵���� 0��ʾû��ѡ���κ����˵�
int sel_sub_num = 0;								//ѡ�е��Ӳ˵������������ 0��ʾû��ѡ���κ��Ӳ˵���������
int submenu_num[] = { 5,3,3,5,3 };					//��Ÿ����Ӳ˵���ѡ�����
BOOL Open_Sub = FALSE;								//bool ���� ��ʾ�Ƿ�����Ӳ˵� 1:��ʾ �� 2:��ʾû�д� 

/*������Ϣ������ͷ����*/
TYPE *head = NULL;									//������Ϣ����ϵͳʮ������������ ����ͷ
BACK_INFO *back_list_head = NULL;					//������Ϣ�б�����������ͷ
LAYER_NODE *top_layer_head = NULL;					//ͼ����Ϣ������ͷ
CHAR_INFO *Buff_Menubar_Info = NULL;				//��Ų˵������������ַ���Ϣ (�ַ���ֵ �� ��ɫ)

/*����������Ϣ�����ʹ洢*/
unsigned short *scr_attr = NULL;					//������ ������Ϣ�ַ��� ���������� ���з���ռ�
HANDLE Handle_In;									//���������� ͨ�������ɸ�����Ϣ�������Ӧ���̵�����
HANDLE Handle_Out;									//���������� ͨ�������ɸ�����Ϣ�������Ӧ���̵����
COORD Interface_Size = { Size_C , Size_R };			//�����С
SMALL_RECT Win_Size = { 0,0,Size_C - 1,Size_R - 1 };//�����С ��С���� �ṹ�壩


//��ͬ�����������ɫ���� 
WORD Tag_Attr = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY; //�����ɫ��ѡ��ѡ��� ѡ���Ӧ��ɫ��
WORD Interface_Color = FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN;						 //������ɫ
WORD Rec_Attr= BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;		 //�߿���ɫ
WORD Hot_Attr = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;		 //������ɫ
WORD Fix_Input_Attr = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;					 //���������� 
WORD Input_Attr = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_INTENSITY;//����������ɫ


/*���ֺ�������*/
void SetRightConsoleMode();			//��ʼ������̨�������ģʽ
void LoadData();					//��������
void InitInterface();				//��ʼ������
void Clear_Buffer();				//��ջ�����(��Ȼ��ɫ�����)
void RunSys();						//����ϵͳ
void CloseSys();					//�ر�ϵͳ
void InitLayer();					//ͼ����Ϣ��ʼ��
int TagHotArea(int num);			//����Ӳ˵���Ӧ���
void TagMainMenu(int num);			//������˵���Ӧ���
void PopSubMenu(int num);			//�����Ӳ˵� ��Open_Sub=TRUE  
void WithdrewPopHot();				//�ջص�ǰ�Ӳ˵� ���� sel_sub_num ��Ϊ0 open_sub��Ϊfalse
void OpenNewMenu(int num);			//������˵� �����µ��Ӳ˵�
void PopHot(SMALL_RECT *,WORD ,TEXT_BAR *,HOT_AREA *);  //�ĸ������ֱ��Ӧ λ�� ��ɫ ������ ����
void ShutHot();						//�رյ��� ����
void DrawRec(SMALL_RECT *, WORD );	//���Ƶ����߿�
void CalSubArea(SMALL_RECT *);		//�����Ӳ˵���С
BOOL iFunction(int x_num,int y_num);//�Ӳ˵���Ӧ�������ܺ����� ���� 
void FreeList(TYPE *del_type,BASIC *del_basic,RECRUIT *del_recruit);		//�ͷ������� ��Ӧ�ڴ����� 
void PresentStatInfo(int mode, int total, int column_no, COORD *write_pos, RECRUIT *stat_ans);	//չ��ͳ����Ϣ ����ӡͳ�ƺ�������
void PrintStatInfo(int mode, int *present_type, int column_no, char **present_info, COORD *pos);//��ӡͳ����Ϣ 
void CalPopArea(SMALL_RECT *rec_pop, TEXT_BAR *cur_text, char **text_info, int *space_num, int bottom_no);//���㵯����С �����������������Ϣ
void PresentQueryInfo(BASIC *basic_query_ans, RECRUIT *recruit_query_ans, int *cur_char_num, int *space_num, int total);//չ�ֲ�ѯ��Ϣ
void InitHotInfo(SMALL_RECT *rec_pop, TEXT_BAR *cur_text, HOT_AREA *cur_area, char **text_info, int text_no, int *hot_type, int *space_num);//��ʼ��������Ϣ


void InsertType();					//����ά�� ���������Ϣ
void DeleteType();					//����ά�� ɾ��������Ϣ
void ModifyType();					//����ά�� �޸ķ�����Ϣ

void InsertBasic();					//����ά�� ����ѧУ������Ϣ		
void DeleteBasic();					//����ά�� ɾ��ѧУ������Ϣ
void ModifyBasic();					//����ά�� �޸�ѧУ������Ϣ

void InsertRecruit();				//����ά�� ����ѧУ������Ϣ
void DeleteRecruit();				//����ά�� ɾ��ѧУ������Ϣ
void ModifyRecruit();				//����ά�� �޸�ѧУ������Ϣ

void QueryType_Classes();			//���ݲ�ѯ ͨ��ѧУ���� ��ѯѧУ������Ϣ

void QueryBasic_No();				//���ݲ�ѯ ͨ����� ��ѯѧУ������Ϣ
void QueryBasic_Name();				//���ݲ�ѯ ͨ������ ��ѯѧУ������Ϣ ��֧��ģ����ѯ��

void QueryRecruit_NoYear();			//���ݲ�ѯ ͨ����ź����   ��ѯѧУ������Ϣ
void QueryRecruit_Score();			//���ݲ�ѯ ͨ��¼ȡ�������� ��ѯѧУ������Ϣ

BOOL SaveData(void);				//���ܺ��� �������� 
BOOL BackData(void);				//���ܺ��� ��������
BOOL RecoveryData(void);			//���ܺ��� �ָ�����
BOOL DeleteBack();					//���ܺ��� ɾ������
BOOL ExitSys(void);					//���ܺ��� �˳�ϵͳ

BOOL MaintainType(void);			//���ܺ��� ����ά�� ά��ѧУ������Ϣ ά������ѡ��
BOOL MaintainBasic(void);			//���ܺ��� ����ά�� ά��ѧУ������Ϣ ά������ѡ��
BOOL MaintainRecruit(void);			//���ܺ��� ����ά�� ά��ѧУ������Ϣ ά������ѡ��

BOOL QueryType(void);				//���ܺ��� ���ݲ�ѯ ��ѯѧУ������Ϣ ά������ѡ��
BOOL QueryBasic(void);				//���ܺ��� ���ݲ�ѯ ��ѯѧУ������Ϣ ά������ѡ��
BOOL QueryRecruit(void);			//���ܺ��� ���ݲ�ѯ ��ѯѧУ������Ϣ ά������ѡ��

BOOL StatTypePeople(void);			//���ܺ��� ����ͳ�� ͳ�Ʋ�ͬ��������¼ȡ����
BOOL StatAllPeople(void);			//���ܺ��� ����ͳ�� �����ͳ�Ƹ���Уʵ¼����
BOOL StatEnrollNum(void);			//���ܺ��� ����ͳ�� ͳ������¼ȡ��������У
BOOL StatHighScore(void);			//���ܺ��� ����ͳ�� ͳ����߷ָ߳�����������10��ѧУ
BOOL StatHighIndex(void);			//���ܺ��� ����ͳ�� �����ͳ��¼ȡ��������ߵ�10��ѧУ

BOOL HelpSys(void);					//���ܺ��� ������Ϣչʾ
BOOL AboutSys(void);				//���ܺ��� ������Ϣչʾ

int CreateList();					//�������� ��ȡ�ļ���Ϣ
int ErrorMention(int num);			//��Ϣ����
int DealEvent(int no);                                                       //���������������¼�
int DealIntput(HOT_AREA *cur_area, int *space_num,int *cur_char_num);        //���������͵����¼�
int InitHotArea(int mode,int bottom_no, int text_no, int area_no, int min_width, int *cur_char_num, int *space_num, int *hot_type, char **text_info); //��ʼ������

TYPE *FindTypePoint(char classes);								//Ѱ��ѧУ������Ϣ�ڵ�	
BASIC *FindBasicPoint(char classes, char *no);					//Ѱ��ѧУ������Ϣ�ڵ�
RECRUIT *FindRecruitPoint(char classes,char *no,char *year);	//Ѱ��ѧУ������Ϣ�ڵ�

TYPE *DealTypeInputInfo(TYPE *input_info, int mode,int command, int *space_num, int *cur_char_num);				//����ѧУ������Ϣ������
BASIC *DealBasicInputInfo(BASIC *input_info, int mode, int command, int *space_num, int *cur_char_num);			//����ѧУ������Ϣ������
RECRUIT *DealRecruitInputInfo(RECRUIT *input_info, int mode, int command, int *space_num, int *cur_char_num);	//����ѧУ������Ϣ������

RECRUIT *StatListCreate(int mode, int *total,RECRUIT *input_info);	//ͳ����Ϣ������
RECRUIT *StatListSort(int mode,RECRUIT *stat_head);					//ͳ����Ϣ���������
BOOL StatComp(int mode,RECRUIT *x,RECRUIT *y);						//ͳ����Ϣ����Ƚ� ��ͬ��ʽ 

#endif // ISYSTEM_H_INCLUDED
