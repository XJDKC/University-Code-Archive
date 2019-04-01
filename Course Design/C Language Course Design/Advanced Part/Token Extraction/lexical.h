#pragma once

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>


typedef struct Token_Node
{
	int type;                //1:标识符 2:关键字 3:整型常量 4:浮点型 5:字符型常量 6:字符串常量 7:操作符 8:分隔符
	int appear_no;
	char token[81];
	struct Token_Node *next;
}TOKEN_NODE;

FILE *original;
FILE *lexical;
TOKEN_NODE *head = NULL;
int token_no = 0;
int cur_row = 0;
int keyword_no = 44;
int operator_no = 44;
char info[1026];
char filename[81];
char *type_list[] = { "","标识符","关键字","整型常量","浮点型常量","字符型常量","字符串常量","操作符","分隔符" };

char *operator_list[] = { "(",")","[","]","->",".","!","~","++","--",
						  "+","-","*","&","/","%","<<",">>","<","<=",
						  ">",">=","==","!=","&","^","|","&&","||","?",
						  ":","=","+=","-=","*=","/=","%=","&=","^=","|=",
	                      "<<=",">>=",",","#" };

char *keyword[] = { "auto","break","case","char","const","continue","default","do",
				    "double","else","enum","extern","float","for","goto","if",
	                "inline","int","long","register","restrict","return","short","signed",
	                "sizeof","static","struct","switch","typedef","union","unsigned","void",
	                "volative","while","_Alignas","_Alignof","_Atomic","_Bool","_Complex","_Generic",
	                "_Imaginary","_Noreturn","_Static_assert","_Thread_local"};



void ReadInfo();
void AnalysisInfo();
int kind(char ch);
int getmore(int i, char *token);
void DealOutput(int tail_pos, int type, char *token);

int ConstantType(char *token);
bool FindKeyword(char *token);
bool FindOperator(char *token);
TOKEN_NODE *FindToken(char *token);