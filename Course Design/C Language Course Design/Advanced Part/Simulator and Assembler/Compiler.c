#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX_COLUMN 200
#define OP_TOTAL (sizeof(mnemonic)/sizeof(mnemonic[0]))

typedef struct tap
{
	int addr;                 // 相对于 声明的内存空间首地址的偏移量 （以字节为单位）
	char name[9];             // 标号的名字 最长8位
	struct tap *next;         // 标号链表 下一个节点的地址
}TAP;

typedef struct var
{
	int type;                 // 1:表示变量为BYTE 意思是一个字节 2:表示变量名为WORD 意思是两个字节
	char name[9];             // 变量名称 最长8位
	int num;                  // 这个变量名下有多少个变量 （用于数组）
	short value[64];          // 各个变量的值 最多64个 也就是数组最多开到64
	struct var *next;         // 变量链表 下一个节点的首地址
}VAR;

TAP *tap_head = NULL;
VAR *var_head = NULL;
VAR *var_tail = NULL;

char *mnemonic[] = { "HLT","JMP","CJMP","OJMP","CALL",
                     "RET","PUSH","POP","LOADB","LOADW",
                     "STOREB","STOREW","LOADI","NOP","IN",
                     "OUT","ADD","ADDI","SUB","SUBI",
	                 "MUL","DIV","AND","OR","NOR",
	                 "NOTB","SAL","SAR","EQU","LT",
	                 "LTE","NOTC"};

int command_no = 0;
char *format = { "12222133444451667575777778778881" };
char cur_line[MAX_COLUMN + 1];
FILE *inFile, *outFile;

void DealFile(int argc, char **argv);
void DealTap_Var(char *op_name);
void DealOP(char *op_name);
void DealVarOutput();
int GetOPNum(char *op_name);
int GetTapAddr(char *addr_name);
int GetVarAddr(char *addr_name);
int GetRegNum(char *reg_name);

int main(int argc, char **argv)
{
	int num;
	char op_name[8];
	char *note_pos;
	DealFile(argc, argv);

	while (!feof(inFile))										//第一遍处理 处理掉 标号 变量 以及注释 以获取第二遍读取时所需信息
	{
		fgets(cur_line, MAX_COLUMN, inFile);					//读取一行数据
		if ((note_pos = strchr(cur_line, '#')) != NULL)			//处理注释
		{
			*note_pos = '\0';
		}
		num = sscanf(cur_line, "%s", op_name);					//从存当前行信息的字符串中读取一小节 即"助记符"
		if (num < 1) {											//如果当前行没有字符串 或者说 没有正确读取到字符串
			continue;											//进入下一行的处理
		}
		else 
		{
			DealTap_Var(op_name);								//否则处理标号和变量
		}
	}

	while (!feof(inFile))
	{
		fgets(cur_line, MAX_COLUMN, inFile);
		if ((note_pos = strchr(cur_line, '#')) != NULL)
		{
			*note_pos = '\0';
		}
		num=sscanf(cur_line, "%s", op_name);
		if (num < 1) {
			continue;
		}
		else {
			DealOP(op_name);
		}
	}
	fclose(inFile);

	inFile = fopen(argv[1], "r");
	while (!feof(inFile))										//第二遍 处理各种命令对应二进制转换 
	{
		fgets(cur_line, MAX_COLUMN, inFile);
		if ((note_pos = strchr(cur_line, '#')) != NULL)
		{
			*note_pos = '\0';
		}
		num = sscanf(cur_line, "%s", op_name);
		if (num < 1) {											//如果是空行 那么进行下一行的处理
			continue;
		}
		else if (!strcmp("BYTE", op_name) || !strcmp("WORD", op_name)) //否则进行下一次循环
		{
			continue;
		}
		else {
			if ((note_pos = strchr(cur_line, ':')) != NULL)
			{
				num = 0;
				while (cur_line[num] != ':')
				{
					cur_line[num++] = ' ';
				}
				cur_line[num] = ' ';
				sscanf(cur_line, "%s", op_name);
			}
			DealOP(op_name);
		}
	}
	DealVarOutput();

	fclose(inFile);
	fclose(outFile);
	return 0;
}

/****************************************
 * 函数名称：DealFile
 * 函数功能：处理文件操作
 * 输入参数：argc 命令行字符串数
			argv 命令行各个字符串
 * 输出参数：无
 * 返 回 值：无
 
 * 调用说明：无
 ****************************************/
void DealFile(int argc, char **argv)
{
	if (argc<3)
	{
		printf("ERROR: no enough command line arguments! \n");
		exit(0);
	}

	if ((inFile = fopen(argv[1], "r")) == NULL)
	{
		printf("ERROR: cannot open file %s for reading! \n", argv[1]);
		exit(0);
	}

	if ((outFile = fopen(argv[2], "w")) == NULL)
	{
		printf("ERROR: cannot open file %s for writing! \n", argv[2]);
		exit(0);
	}
}

/****************************************
 * 函数名称：DealTap_Var
 * 函数功能：处理标号和变量名
 * 输入参数：op_name 表示要处理的助记符字符串
 * 输出参数：无
 * 返 回 值：无
 
 * 调用说明：无
 ****************************************/
void DealTap_Var(char *op_name)
{
	int cur_var_no=0;
	int no=0;
	char *mark;
	char temp[10];
	TAP *new_tap;
	VAR *new_var;
	if ((mark = strchr(op_name, ':')) != NULL)             //如果当前行的第一小节含有:号 说明是标号
	{
		new_tap = (TAP *)calloc(1, sizeof(TAP));
		*mark = '\0';
		strcpy(new_tap->name, op_name);
		new_tap->addr = command_no * 4;
		new_tap->next = tap_head;
		tap_head = new_tap;
		command_no++;
	}
	else if (strcmp("BYTE", op_name) == 0 || strcmp("WORD", op_name) == 0)
	{
		new_var = (VAR *)calloc(1, sizeof(VAR));
		if (strcmp("BYTE", op_name) == 0)                     //处理格式
		{
			new_var->type = 1;
		}             
		else
		{
			new_var->type = 2;
		}
		
		sscanf(cur_line, "%*s%*[ ]%[^ [\n]", new_var->name);      //处理名字
		if ((mark = strchr(cur_line, '[')) != NULL)           //处理变量个数
		{
			sscanf(mark + 1, "%[0-9]", temp);
			sscanf(temp, "%d", &new_var->num);
		} 
		else
		{
			new_var->num = 1;
		}
		if ((mark = strchr(cur_line, '=')) != NULL)           //处理初始化
		{
			if ((mark = strchr(cur_line, '{')) != NULL)   //如果是带括号的 赋值
			{
				mark++;
				while (*mark != '}')
				{
					temp[no++] = *mark++;
					if (*mark == ',' || *mark =='}')
					{
						temp[no] = '\0';
						sscanf(temp, "%d", &new_var->value[cur_var_no++]);
						no = 0;
					}
				}
			}
			else if ((mark = strchr(cur_line, '"')) != NULL)
			{
				mark++;
				while (*mark != '"')
				{
					new_var->value[cur_var_no++] = *mark++;
				}
			}
			else
			{
				mark = strchr(cur_line, '=') + 1;
				sscanf(mark, "%d", &new_var->value[0]);
			}
		}
		if (var_tail == NULL)
		{
			var_head = new_var;
			var_tail = new_var;
		}
		else
		{
			var_tail->next = new_var;
			var_tail = new_var;
		}
	}
	else
	{
		command_no++;
	}
}

/****************************************
 * 函数名称：DealOP
 * 函数功能：处理标号和变量名
 * 输入参数：op_name 表示要处理的助记符字符串
 * 输出参数：无
 * 返 回 值：无
 
 * 调用说明：无
 ****************************************/
void DealOP(char *op_name)
{
	int total;
	int type;
	int input_no;
	unsigned long final_code = 0;
	unsigned long op = 0;
	unsigned long reg0 = 0, reg1 = 0, reg2 = 0;
	unsigned long addr = 0;
	int imme = 0, port = 0;
	char temp[8], reg0_name[8], reg1_name[8], reg2_name[8],addr_name[9];

	op = GetOPNum(op_name);
	if (op >= OP_TOTAL)                 
	{
		printf("ERROR: %s is a invalid instruction! \n", cur_line);
		exit(-1);
	}
	else
	{
		type = format[op] - '0';
		switch (type)
		{
			case 1: input_no = total = 1; break;
			case 2: total = 2; //addr 在这里表示的是标号对应函数入口
				    input_no = sscanf(cur_line, "%s %s", temp, addr_name); break;
			case 3: total = 2; 
					input_no = sscanf(cur_line, "%s %s", temp, reg0_name); break;
			case 4: total = 3; //addr 在这里表示的是变量对应的地址 
					input_no = sscanf(cur_line, "%s %s %s", temp, reg0_name, addr_name); break;
			case 5: total = 3; 
					input_no = sscanf(cur_line, "%s %s %i", temp, reg0_name,&imme); break;
			case 6: total = 3;
					input_no = sscanf(cur_line, "%s %s %i", temp, reg0_name, &port); break;
			case 7: total = 4;
					input_no = sscanf(cur_line, "%s %s %s %s", temp, reg0_name, reg1_name,reg2_name); break;
			case 8: total = 3;
				    input_no = sscanf(cur_line, "%s %s %s", temp, reg0_name, reg1_name); break;
		}
	}
	if (input_no < total)
	{
		printf("ERROR: bad instrument format! \n");
		exit(-1);
	}

	if (type != 1 && type != 2)
	{
		reg0 = GetRegNum(reg0_name);
	}
	switch (type)
	{
		case 2: addr = GetTapAddr(addr_name); break;
		case 4: addr = GetVarAddr(addr_name); break;
		case 7: reg1 = GetRegNum(reg1_name); reg2 = GetRegNum(reg2_name); break;
		case 8: reg1 = GetRegNum(reg1_name);
	}

	final_code = (op << 27) | (reg0 << 24) | (reg1 << 20) | (reg2 << 16) 
		       | (addr & 0x00ffffff) | (port & 0x000000ff) | (imme & 0x0000ffff);

	fprintf(outFile, "0x%08lx\n", final_code);
}

/****************************************
 * 函数名称：DealVarOutput
 * 函数功能：处理各个变量的输出
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：无
 
 * 调用说明：无
 ****************************************/
void DealVarOutput()
{
	int mod = 0;
	unsigned long data_size = 0;
	VAR *cur_var_node = NULL;
	cur_var_node = var_head;
	while (cur_var_node != NULL)
	{
		if (cur_var_node->type == 1)
		{
			data_size += cur_var_node->num*cur_var_node->type;
			for (int i = 0; i < cur_var_node->num; i++)
			{
				if (mod % 4 == 0)
				{
					fprintf(outFile, "0x%02lx", cur_var_node->value[i]);
				}
				else if (mod % 4 == 3)
				{
					fprintf(outFile, "%02lx\n", cur_var_node->value[i]);
				}
				else {
					fprintf(outFile, "%02lx", cur_var_node->value[i]);
				}
				mod = (mod + 1) % 4;
			}
		}
		else if (cur_var_node->type == 2)
		{
			data_size += cur_var_node->num*cur_var_node->type;
			for (int i = 0; i < cur_var_node->num; i++)
			{
				if (mod % 4 == 0)
				{
					fprintf(outFile, "0x%04lx", cur_var_node->value[i]);
				}
				else if ((mod + 2) > 4)
				{
					fprintf(outFile, "%02lx\n", (cur_var_node->value[i] >> 8) & 0xff);
					fprintf(outFile, "0x%02lx", cur_var_node->value[i] & 0xff);
				}
				else {
					fprintf(outFile, "%04lx", cur_var_node->value[i]);
					if (mod + 2 == 4)
					{
						fprintf(outFile, "\n");
					}
				}
				mod = (mod + 2) % 4;
			}
		}
		cur_var_node = cur_var_node->next;
	}
	for (;mod>0&&mod < 4; mod++)
	{
		fprintf(outFile, "00");
		if (mod % 4 == 3)
		{
			fprintf(outFile, "\n");
		}
	}
	fprintf(outFile, "0x%08lx\n", data_size);
}


/****************************************
 * 函数名称：GetOPNum
 * 函数功能：获取助记符对应的数字编号
 * 输入参数：op_name 助记符
 * 输出参数：无
 * 返 回 值：助记符对应的数字编号
 
 * 调用说明：无
 ****************************************/
int GetOPNum(char *op_name)
{
	int i;
	for (i = 0; i < OP_TOTAL; i++)
	{
		if (strcmp(mnemonic[i], op_name) == 0)
			break;
	}
	return i;
}

/****************************************
 * 函数名称：GetTapAddr
 * 函数功能：获取标号的行数 
 * 输入参数：addr_name 地址名称 标号名称
 * 输出参数：无
 * 返 回 值：标号的行数 
 
 * 调用说明：无
 ****************************************/
int GetTapAddr(char *addr_name)
{
	TAP *cur_tap_node = tap_head;
	while (cur_tap_node != NULL)
	{
		if (strcmp(cur_tap_node->name, addr_name) == 0)
		{
			return cur_tap_node->addr;
		}
		cur_tap_node = cur_tap_node->next;
	}
	printf("ERROR: %f is not declared! \n");
	exit(-1);
}

/****************************************
 * 函数名称：GetVarAddr
 * 函数功能：获取变量地址偏移量
 * 输入参数：addr_name 变量名称
 * 输出参数：无
 * 返 回 值：助记符对应的数字编号
 
 * 调用说明：返回的是数据段 相对于第一个变量的偏移量（字节为单位）
 ****************************************/
int GetVarAddr(char *addr_name)
{
	int addr_no=0;
	VAR *cur_var_node = var_head;
	while (cur_var_node != NULL)
	{
		if (strcmp(cur_var_node->name, addr_name) == 0)
		{
			return addr_no;
		}
		addr_no += cur_var_node->num*cur_var_node->type;
		cur_var_node = cur_var_node->next;
	}

	printf("ERROR: %f is not declared! \n");
	exit(-1);
}

/****************************************
 * 函数名称：GetRegNum
 * 函数功能：获取寄存器编号
 * 输入参数：reg_name 寄存器名称
 * 输出参数：无
 * 返 回 值：寄存器编号
 
 * 调用说明：无
 ****************************************/
int GetRegNum(char *reg_name)
{
	if (tolower(*reg_name) == 'z')
	{
		return 0;
	}
	else if (tolower(*reg_name) >= 'a'&&tolower(*reg_name) <= 'g')
	{
		return tolower(*reg_name) - 'a' + 1;
	}
	else
	{
		printf("ERROR: bad register name in %s! \n", cur_line);
		exit(-1);
	}
}
