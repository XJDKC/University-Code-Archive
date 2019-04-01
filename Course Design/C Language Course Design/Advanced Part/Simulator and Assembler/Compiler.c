#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX_COLUMN 200
#define OP_TOTAL (sizeof(mnemonic)/sizeof(mnemonic[0]))

typedef struct tap
{
	int addr;                 // ����� �������ڴ�ռ��׵�ַ��ƫ���� �����ֽ�Ϊ��λ��
	char name[9];             // ��ŵ����� �8λ
	struct tap *next;         // ������� ��һ���ڵ�ĵ�ַ
}TAP;

typedef struct var
{
	int type;                 // 1:��ʾ����ΪBYTE ��˼��һ���ֽ� 2:��ʾ������ΪWORD ��˼�������ֽ�
	char name[9];             // �������� �8λ
	int num;                  // ������������ж��ٸ����� ���������飩
	short value[64];          // ����������ֵ ���64�� Ҳ����������࿪��64
	struct var *next;         // �������� ��һ���ڵ���׵�ַ
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

	while (!feof(inFile))										//��һ�鴦�� ����� ��� ���� �Լ�ע�� �Ի�ȡ�ڶ����ȡʱ������Ϣ
	{
		fgets(cur_line, MAX_COLUMN, inFile);					//��ȡһ������
		if ((note_pos = strchr(cur_line, '#')) != NULL)			//����ע��
		{
			*note_pos = '\0';
		}
		num = sscanf(cur_line, "%s", op_name);					//�Ӵ浱ǰ����Ϣ���ַ����ж�ȡһС�� ��"���Ƿ�"
		if (num < 1) {											//�����ǰ��û���ַ��� ����˵ û����ȷ��ȡ���ַ���
			continue;											//������һ�еĴ���
		}
		else 
		{
			DealTap_Var(op_name);								//�������źͱ���
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
	while (!feof(inFile))										//�ڶ��� ������������Ӧ������ת�� 
	{
		fgets(cur_line, MAX_COLUMN, inFile);
		if ((note_pos = strchr(cur_line, '#')) != NULL)
		{
			*note_pos = '\0';
		}
		num = sscanf(cur_line, "%s", op_name);
		if (num < 1) {											//����ǿ��� ��ô������һ�еĴ���
			continue;
		}
		else if (!strcmp("BYTE", op_name) || !strcmp("WORD", op_name)) //���������һ��ѭ��
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
 * �������ƣ�DealFile
 * �������ܣ������ļ�����
 * ���������argc �������ַ�����
			argv �����и����ַ���
 * �����������
 * �� �� ֵ����
 
 * ����˵������
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
 * �������ƣ�DealTap_Var
 * �������ܣ������źͱ�����
 * ���������op_name ��ʾҪ��������Ƿ��ַ���
 * �����������
 * �� �� ֵ����
 
 * ����˵������
 ****************************************/
void DealTap_Var(char *op_name)
{
	int cur_var_no=0;
	int no=0;
	char *mark;
	char temp[10];
	TAP *new_tap;
	VAR *new_var;
	if ((mark = strchr(op_name, ':')) != NULL)             //�����ǰ�еĵ�һС�ں���:�� ˵���Ǳ��
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
		if (strcmp("BYTE", op_name) == 0)                     //�����ʽ
		{
			new_var->type = 1;
		}             
		else
		{
			new_var->type = 2;
		}
		
		sscanf(cur_line, "%*s%*[ ]%[^ [\n]", new_var->name);      //��������
		if ((mark = strchr(cur_line, '[')) != NULL)           //�����������
		{
			sscanf(mark + 1, "%[0-9]", temp);
			sscanf(temp, "%d", &new_var->num);
		} 
		else
		{
			new_var->num = 1;
		}
		if ((mark = strchr(cur_line, '=')) != NULL)           //�����ʼ��
		{
			if ((mark = strchr(cur_line, '{')) != NULL)   //����Ǵ����ŵ� ��ֵ
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
 * �������ƣ�DealOP
 * �������ܣ������źͱ�����
 * ���������op_name ��ʾҪ��������Ƿ��ַ���
 * �����������
 * �� �� ֵ����
 
 * ����˵������
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
			case 2: total = 2; //addr �������ʾ���Ǳ�Ŷ�Ӧ�������
				    input_no = sscanf(cur_line, "%s %s", temp, addr_name); break;
			case 3: total = 2; 
					input_no = sscanf(cur_line, "%s %s", temp, reg0_name); break;
			case 4: total = 3; //addr �������ʾ���Ǳ�����Ӧ�ĵ�ַ 
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
 * �������ƣ�DealVarOutput
 * �������ܣ�����������������
 * �����������
 * �����������
 * �� �� ֵ����
 
 * ����˵������
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
 * �������ƣ�GetOPNum
 * �������ܣ���ȡ���Ƿ���Ӧ�����ֱ��
 * ���������op_name ���Ƿ�
 * �����������
 * �� �� ֵ�����Ƿ���Ӧ�����ֱ��
 
 * ����˵������
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
 * �������ƣ�GetTapAddr
 * �������ܣ���ȡ��ŵ����� 
 * ���������addr_name ��ַ���� �������
 * �����������
 * �� �� ֵ����ŵ����� 
 
 * ����˵������
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
 * �������ƣ�GetVarAddr
 * �������ܣ���ȡ������ַƫ����
 * ���������addr_name ��������
 * �����������
 * �� �� ֵ�����Ƿ���Ӧ�����ֱ��
 
 * ����˵�������ص������ݶ� ����ڵ�һ��������ƫ�������ֽ�Ϊ��λ��
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
 * �������ƣ�GetRegNum
 * �������ܣ���ȡ�Ĵ������
 * ���������reg_name �Ĵ�������
 * �����������
 * �� �� ֵ���Ĵ������
 
 * ����˵������
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
