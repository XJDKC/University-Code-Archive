#pragma once
#ifndef MYVALUE_H_
#define MYVALUE_H_

HANDLE HANDLE_IN = GetStdHandle(STD_INPUT_HANDLE);
HANDLE HANDLE_OUT = GetStdHandle(STD_OUTPUT_HANDLE);

const char *select_interface[] = { "����������������������������������������������������������������������������������������������������\n",
								  "��             Menu for Select Function           ��\n",
								  "�� -----------------------------------------------��\n",
								  "��               1.����һ���µ�ͼ                 ��\n",
								  "��               2.ѡ��һ������ͼ                 ��\n",
								  "��               3.���ļ��м���ͼ                 ��\n",
								  "��               0.�˳�ϵͳ                       ��\n",
								  "�� -----------------------------------------------��\n",
								  "��             ��ѡ����Ĳ�����[0-3]:             ��\n",
								  "����������������������������������������������������������������������������������������������������\n" };

const char *Main_Interface[] = { "��������������������������������������������������������������������������������������������������������\n",
								"��          Menu for Map On Chain Structure         ��\n",
								"�� -------------------------------------------------��\n",
								"��       1. CreateGraph      10. InsertArc          ��\n",
								"��       2. DestroyGraph     11. DeleteArc          ��\n",
								"��       3. LocateVex        12. DFSTraverse        ��\n",
								"��       4. GetVex           13. BFSTraverse        ��\n",
								"��       5. PutVex           14. ChangeName         ��\n",
								"��       6. FirstAdjVex      15. SaveInfo           ��\n",
								"��       7. NextAdjVex       16. ReloadInfo         ��\n",
								"��       8. InsertVex         0. Exit               ��\n",
								"��       9. DeleteVex                               ��\n",
								"�� -------------------------------------------------��\n",
								"��               ��ѡ����Ĳ�����[0-17]:            ��\n",
								"��������������������������������������������������������������������������������������������������������\n" };

const char *Init_Interface[] = { "����������������������������������������������������������������������������������������������������\n",
								"��                  Menu for Map Type             ��\n",
								"�� -----------------------------------------------��\n",
								"��                1. ����ͼ                       ��\n",
								"��                2. ����ͼ                       ��\n",
								"��                3. ������                       ��\n",
								"��                4. ������                       ��\n",
								"��                0. Exit                         ��\n",
								"�� -----------------------------------------------��\n",
								"��             ��ѡ����Ĳ�����[0-4]:             ��\n",
								"����������������������������������������������������������������������������������������������������\n" };


Vertax *pget;
Multimap MultiHead;

COORD rec = { 15,7 };
COORD main_pos = { 14,4 };		//��Ҫ��������
COORD init_pos = { 15,5 };		//��ʼ������ ѡ���ܽ���
COORD select_pos = { 15,7 };	//ѡ�����

SMALL_RECT windows_size = { 0,0,100,30 };	//���ڴ�С

int select_string_num = 10; //ѡ������
int main_string_num = 15;   //����
int init_string_num = 11;	//ѡ�����ͽ���

char MapMenu[] = "MapMenu.txt";		//��Ŷ�ͼ���ļ�Ŀ¼

void init();						//��ʼ��
void runsys(Map *workon = NULL);	//�����ͼ�ĸ��ֲ���
void closesys();					//�ر�ϵͳ
void DealInput();					//����ͼ����
void select_map();					//����
void select_type();
void select_function();
status LoadMap(Map *workon = NULL);
void Draw_Map_Select(int mode = 1);
void Deal_Mention(int interface_type, int op_type, int mention_type, int info);
void Draw_Interface(const char **Interface_Info, COORD pos, int string_num);

#endif