#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

#define OP        ((IR>>27)&0x1F)
#define REG0      (((IR)>>24)&0x07)
#define REG1      (((IR)>>20)&0x0F)
#define REG2      (((IR)>>16)&0x0F)
#define PORT      ((IR)&0xFF)
#define IMMEDIATE ((IR)&0xFFFF)
#define ADDRESS   ((IR)&0xFFFFFF)

typedef struct prog_state_word          //程序状态字逻辑单元
{
	unsigned short overflow_flag : 1;   //数据溢出标志 1代表溢出了 0代表没有
	unsigned short compare_flag  : 1;   //逻辑运算标志 1代表逻辑真 0代表逻辑假
	unsigned short reserver      : 14;  //保留字节
}PROG_STATE_WORD;

typedef struct extra                    //附加段 结构体
{
	short pre_reg[8];                   //之前的八个通用寄存器 存放的数据
	unsigned long *pre_PC;              //之前的指令计数器  （方便回到原来地方后读取下一条指令） 
	PROG_STATE_WORD pre_psw;            //之前的程序状态字 存放的数据
}EXTRA;

short REG[8];                           //register 八个通用寄存器 通用寄存器用一个机器字 即 两字节表示
unsigned char *Memory;                  //指向模拟内存的指针
unsigned long *PC;                      //指令计数器 用于存放下一条指令的内存地址 用两个机器字 四字节表示
unsigned long IR;						//中间代码 存放原指令
unsigned long *CS;                      //代码段寄存器 code segment  用于指向代码段 首地址
unsigned char *DS;                      //数据段寄存器 data segment  用于指向数据段 首地址
short *SS;                              //堆栈段寄存器 stock segment 用于存放子程序（函数）传递的参数 和 函数返回值
EXTRA *ES;                              //附加段寄存器 extra segment 用于存放调用函数之前 各个通用寄存器 指令计数器 和 程序状态字 方便返回时恢复

PROG_STATE_WORD PSW;                    //程序状态字 一个机器字 两字节表示 

int HLT(void); 
int JMP(void);    
int CJMP(void);
int OJMP(void);
int CALL(void);
int RET(void);
int PUSH(void);
int POP(void);
int LOADB(void);
int LOADW(void);
int STOREB(void);
int STOREW(void);
int LOADI(void);
int NOP(void);
int IN(void);
int OUT(void);
int ADD(void);
int ADDI(void);
int SUB(void);
int SUBI(void);
int MUL(void);
int DIV(void);
int AND(void);
int OR(void);
int NOR(void);
int NOTB(void);
int SAL(void);
int SAR(void);
int EQU(void);
int LT(void);
int LTE(void);
int NOTC(void);

int(*op_function[])(void) = { HLT,JMP,CJMP,OJMP,CALL,
							  RET,PUSH,POP,LOADB,LOADW,
							  STOREB,STOREW,LOADI,NOP,IN,
							  OUT,ADD,ADDI,SUB,SUBI,
							  MUL,DIV,AND,OR,NOR,
							  NOTB,SAL,SAR,EQU,LT,
							  LTE,NOTC };


int main(int argc,char **argv)
{
	int num = 0;
	int Mark = 1;
	unsigned long instruction;
	unsigned long mem_size;
	FILE *inFile;

	mem_size = 1 << 24;

	if ((Memory = (unsigned char *)malloc(mem_size)) == NULL)
	{
		printf("ERROR: fail to allocate memory! \n");
		exit(-1);
	}
    
	PC =(unsigned long *) Memory;
	if ((inFile = fopen(argv[1],"r")) == NULL)
	{
		printf("ERROR: cannot open file %s for reading! \n", argv[1]);
		exit(-1);
	}
	while (!feof(inFile))
	{
		fscanf(inFile, "%li", &instruction);
		*PC = instruction;
		PC++;
		num++;
	}
	

	SS = (short *)PC;
	PC--;
	DS = (unsigned char *)(PC - (*PC % 4 == 0 ? *PC / 4 : *PC / 4 + 1))-1;
	PC = (unsigned long *)Memory;
	CS = PC;
	ES = (EXTRA *)(Memory + mem_size - sizeof(EXTRA));

	while (Mark)
	{
		IR = *PC++;
		Mark = (*op_function[OP])();
	}

	free(Memory);
	fclose(inFile);
	return 0;
}

//由于每个助记符对应的功能都在综述里面已经提到了 
//所有函数均是对于功能的简单翻译就不再赘述
int HLT(void)
{
	return 0;
}

int JMP(void)
{
	PC = (unsigned long *)(Memory + ADDRESS);
	return 1;
}

int CJMP(void)
{
	if (PSW.compare_flag)
	{
		PC = (unsigned long *)(Memory + ADDRESS);
	}
	return 1;
}

int OJMP(void)
{
	if (PSW.overflow_flag)
	{
		PC = (unsigned long *)(Memory + ADDRESS);
	}
	return 1;
}

int CALL(void)
{
	for (int i = 0; i < 8; i++)
	{
		ES->pre_reg[i] = REG[i];
	}
	ES->pre_PC = PC;
	ES->pre_psw = PSW;
	ES--;
	PC = CS + ADDRESS / 4;
	return 1;
}

int RET(void)
{
	ES++;
	for (int i = 0; i < 8; i++)
	{
		REG[i] = ES->pre_reg[i];
	}
	PC = ES->pre_PC;
	PSW = ES->pre_psw;
	return 1;
}

int PUSH(void)
{
	*SS = REG[REG0];
	SS++;
	return 1;
}

int POP(void)//修改
{
	if (REG0 == 0)
	{
		printf("ERROR: \n");
		exit(-1);
	}
	SS--;
	REG[REG0] = *SS;
	return 1;
}

int LOADB(void)
{
	REG[REG0] = *(char *)(DS + ADDRESS+REG[7]); 
	return 1;
}

int LOADW(void)
{
	REG[REG0] = *(short *)(DS + ADDRESS + REG[7]);
	return 1;
}

int STOREB(void)
{
	*(char *)(DS + ADDRESS + REG[7]) = (char)REG[REG0];
	return 1;
}

int STOREW(void)
{
	*(short *)(DS + ADDRESS + REG[7]) = (short)REG[REG0];
	return 1;
}

int LOADI(void)
{
	REG[REG0]=(short)IMMEDIATE;
	return 1;
}

int NOP(void)
{
	return 1;
}

int IN(void)
{
	read(0,(char *)(REG+REG0),1);
	return 1;
}

int OUT(void)
{
	write(1, (char *)(REG + REG0), 1);
	return 1;
}

int ADD(void)
{
	REG[REG0] = REG[REG1] + REG[REG2];
	if (REG[REG2] > 0 && (REG[REG1] - REG[REG0]) > 0 
	 || REG[REG2] < 0 && (REG[REG1] - REG[REG0]) < 0)
	{
		PSW.overflow_flag = 1;
	}
	else
	{
		PSW.overflow_flag = 0;
	}
	return 1;
}

int ADDI(void)
{
	short pre_value = REG[REG0];
	REG[REG0] = REG[REG0] + IMMEDIATE;
	if (IMMEDIATE > 0 && (pre_value - REG[REG0]) > 0
	 || IMMEDIATE < 0 && (pre_value - REG[REG0]) < 0)
	{
		PSW.overflow_flag = 1;
	}
	else
	{
		PSW.overflow_flag = 0;
	}
	return 1;
}

int SUB(void)
{
	REG[REG0] = REG[REG1] - REG[REG2];
	if (REG[REG2] > 0 && (REG[REG1] - REG[REG0]) < 0
	 || REG[REG2] < 0 && (REG[REG1] - REG[REG0]) > 0)
	{
		PSW.overflow_flag = 1;
	}
	else
	{
		PSW.overflow_flag = 0;
	}
	return 1;
}

int SUBI(void)
{
	short pre_value = REG[REG0];
	REG[REG0] = REG[REG0] - IMMEDIATE;
	if (IMMEDIATE > 0 && (pre_value - REG[REG0]) < 0
	 || IMMEDIATE < 0 && (pre_value - REG[REG0]) > 0)
	{
		PSW.overflow_flag = 1;
	}
	else
	{
		PSW.overflow_flag = 0;
	}
	return 1;
}

int MUL(void)
{
	REG[REG0] = REG[REG1] * REG[REG2];
	if (REG[REG2] && REG[REG1] * REG[REG2] / REG[REG2] != REG[REG1])
	{
		PSW.overflow_flag = 1;
	}
	else
	{
		PSW.overflow_flag = 0;
	}
	return 1;
}

int DIV(void)
{
	if (REG[REG2] == 0)
	{
		printf("ERROR: the divisor is zero! \n");
		exit(-1);
	}
	REG[REG0] = REG[REG1] / REG[REG2];
	return 1;
}

int AND(void)
{
	REG[REG0] = REG[REG1] & REG[REG2];
	return 1;
}

int OR(void)
{
	REG[REG0] = REG[REG1] | REG[REG2];
	return 1;
}

int NOR(void)
{
	REG[REG0] = REG[REG1] ^ REG[REG2];
	return 1;
}

int NOTB(void)
{
	REG[REG0] = ~REG[REG1];
	return 1;
}

int SAL(void)
{
	REG[REG0] = REG[REG1] << REG[REG2];
	return 1;
}

int SAR(void)
{
	REG[REG0] = REG[REG1] >> REG[REG2];
	return 1;
}

int EQU(void)
{
	if (REG[REG0] == REG[REG1])
	{
		PSW.compare_flag = 1;
	}
	else
	{
		PSW.compare_flag = 0;
	}
	return 1;
}

int LT(void)
{
	if (REG[REG0] < REG[REG1])
	{
		PSW.compare_flag = 1;
	}
	else
	{
		PSW.compare_flag = 0;
	}
	return 1;
}

int LTE(void)
{
	if (REG[REG0] <= REG[REG1])
	{
		PSW.compare_flag = 1;
	}
	else
	{
		PSW.compare_flag = 0;
	}
	return 1;
}

int NOTC(void)
{
	PSW.compare_flag = !PSW.compare_flag;
	return 1;
}
