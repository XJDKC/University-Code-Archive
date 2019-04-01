#pragma once
#ifndef MYVALUE_H_
#define MYVALUE_H_

typedef int ElemType;
typedef int status;

const int MinNo = 0x80000000;

HANDLE HANDLE_IN=GetStdHandle(STD_INPUT_HANDLE);
HANDLE HANDLE_OUT=GetStdHandle(STD_OUTPUT_HANDLE);


const char *select_interface[] = {"����������������������������������������������������������������������������������������������������\n",
								  "��             Menu for Select Function           ��\n",
								  "�� -----------------------------------------------��\n",
								  "��               1.����һ���µ���                 ��\n",
								  "��               2.ѡ��һ��������                 ��\n",
								  "��               3.���ļ��м�����                 ��\n",
							 	  "��               0.�˳�ϵͳ                       ��\n",
							 	  "�� -----------------------------------------------��\n",
								  "��             ��ѡ����Ĳ�����[0-3]:             ��\n",
								  "����������������������������������������������������������������������������������������������������\n"};

const char *Main_Interface[]={	"��������������������������������������������������������������������������������������������������������\n",
								"��      Menu for Binary Tree On Chain Structure     ��\n",
								"�� -------------------------------------------------��\n",
								"��       1. IntiaBiTree      13. LeftSibling        ��\n",
								"��       2. DestroyBiTree    14. RightSibling       ��\n",
								"��       3. CreateBiTree     15. InsertChild        ��\n",
								"��       4. ClearBiTree      16. DeleteChild        ��\n",
								"��       5. BiTreeEmpty      17. PreOrderTraverse   ��\n",
								"��       6. BiTreeDepth      18. InOrderTraverse    ��\n",
								"��       7. Root             19. PostOrderTraverse  ��\n",
								"��       8. Value            20. LevelOrderTraverse ��\n",
								"��       9. Assign           21. ChangeName         ��\n",
								"��      10. Parent           22. SaveInfo           ��\n",
								"��      11. LeftChild        23. ReloadInfo         ��\n",
								"��      12. RightChild        0. Exit               ��\n",
								"�� -------------------------------------------------��\n",
								"��               ��ѡ����Ĳ�����[0-22]:            ��\n",
								"��������������������������������������������������������������������������������������������������������\n"};

const char *Init_Interface[]={	"����������������������������������������������������������������������������������������������������\n",
								"��             Menu for Variable Type             ��\n",
								"�� -----------------------------------------------��\n",
								"��                1. bool   ������                ��\n",
								"��                2. char   �ַ���                ��\n",
								"��                3. int    ����                  ��\n",
								"��                4. float  �����ȸ�����          ��\n",
								"��                5. double ˫���ȸ�����          ��\n",
								"��                0. Exit                         ��\n",
								"�� -----------------------------------------------��\n",
								"��             ��ѡ����Ĳ�����[0-5]:             ��\n",
								"����������������������������������������������������������������������������������������������������\n"};

class Node;
class HEAD;
class Tree;

Tree *MultiHead=NULL;
Node *pget;
int tree_no = 0;
int untitile_no = 0;

std::stack<Node *> s;
std::queue<Node *> q;

std::vector<int> pre_order;
std::vector<ElemType> alldata;

COORD select_pos = { 15,7 };
COORD main_pos = { 14,4 };
COORD init_pos = { 15,5 };
COORD rec = { 15,7 };

SMALL_RECT windows_size = { 0,0,100,30 };

int select_string_num = 10; //ѡ������
int main_string_num = 18;   //����
int init_string_num = 12;	//������

char TreeMenu[] = "TreeMenu.txt";

void init();
void runsys(Tree *workon=NULL);
status LoadTree(Tree *workon=NULL);
void closesys();
void select_tree();
void select_function();
status InputTreeInfo();
Tree *findtree(std::string &name);
void remove(Tree *workon);
void Draw_Tree_Select(int mode=1);
void Deal_Mention(int interface_type,int op_type,int mentiontype,int info);
void Draw_Interface(const char **Interface_Info, COORD pos, int string_num);
#endif