.386
STACK SEGMENT USE16 STACK
	DB	200	DUP(0)
STACK ENDS
;-------------------------------
DATA SEGMENT USE16
BNAME	DB	'XING RULIN',0					;系统登录名
BPASS	DB	'TEST',0,0						;系统登陆密码
IN_NAME	DB	10+1,?,11 DUP(0)				;为回车预留一位
IN_PWD	DB	6+1,?,7 DUP(0)					;为回车预留一位
IN_PRO	DB	10+1,?,11 DUP(0)				;为回车预留一位
NA_MEN	DB	'Please input the username: $'	;显示信息-输入姓名
PWD_MEN	DB	'Please input the password: $'	;显示信息-输入密码
FAIL	DB	'Login failed: Press any key to continue! $'	;显示信息-登录失败
PRO_MEN	DB	'Please enter the product name: $'	;显示信息-输入商品名称
AUTH	DB	?								;存放登陆状态
N		EQU	30								;存放商品类别数
M		EQU 10000
;-------------------------------			;第一个网店信息
S1	DB	'SHOP1',0							;网店名称
GA1	DB	'PEN',7 DUP(0)						;第一个商品名称
	DW	35,56,70,25,?						;分别为第一个商品 进价,售价,进货量,已售量,利润率
GA2	DB	'BOOK',6 DUP(0)						;...
	DW	12,30,25,5,?
GA3	DB	'Bag',7 DUP(0)
	DW	15,25,M,0,?
GAN	DB	N-3	DUP('Temp-Value',15,0,20,0,30,0,2,0,?,?)
;-------------------------------			;第二个网店信息
S2	DB	'SHOP2',0							;网店名称
GB1	DB	'BOOK',6 DUP(0)						;第一个商品名称
	DW	12,28,20,15,?						;分别为第一个商品 进价,售价,进货量,已售量,利润率
GB2	DB	'PEN',7 DUP(0)						;... 57
	DW	35,50,30,24,?
GB3	DB	'Bag',7 DUP(0)
	DW	15,25,M,5000,?
GBN	DB	N-3	DUP('Temp-Value',15,0,20,0,30,0,2,0,?,?)

DATA ENDS
;-------------------------------
CODE SEGMENT USE16
	ASSUME CS:CODE,DS:DATA,ES:DATA,SS:STACK

IN_STRING MACRO A,B					;宏定义 输入字符串 A表示输入时的提示信息 B表示输入字符串的位置偏移量
	LEA DX,A						;将提示信息字符串偏移地址存入DX
	MOV AH,9						;将代表显示字符串的9号调用存入AH
	INT 21H							;执行中断
	LEA DX,B						;将存放输入信息的字符串偏移地址存入DX
	MOV AH,10						;将代表输入字符串的10号调用存入AH
	INT 21H							;执行中断
	MOV DL,10						;将换行符存入DL
	MOV AH,2						;将代表输出字符的2号调用存入AH
	INT 21H							;执行中断
ENDM								;结束宏定义

OUT_INFO MACRO A,B					;宏定义 输出信息 A表示输出信息(字符串偏移地址 或者 字符) B表示输出类型
	MOV	DX,A						;将待输出的 字符串偏移地址 或 字符 存入DX
	MOV AH,B						;将输出类型存入AH 可能为9or2 分别表示输出字符串 和 字符 
	INT 21H							;调用中断
	MOV DL,10						;将换行符存入DL
	MOV AH,2						;将代表输出字符的2号调用存入AH
	INT 21H							;执行中断
ENDM								;结束宏定义

CAL_PROFIT MACRO A					;计算商品利润率并保存到对应位置 参数--商品信息存放位置
	
	XOR EDX,EDX						;高位补0
	MOVZX EAX,WORD PTR DS:[A+10+2*1];计算总收入 EAX=售价
	MOVZX ECX,WORD PTR DS:[A+10+2*3];ECX=售货量
	MUL ECX							;EAX=总收入
	MOVSX ECX,WORD PTR DS:[A+10]	;计算成本 EBX=进价
	MOVSX EDI,WORD PTR DS:[A+10+2*2];ECX=进货量
	IMUL ECX,EDI					;EBX=总成本
	IMUL EAX,100					;将总收入乘以100 这样会获得百分比下的整数部分
	IDIV ECX						;除以成本
	SUB EAX,100						;减去成本
	MOV word ptr DS:[A+10+2*4],AX	;将计算得到的利润率百分之下的整数部分存入AX
	
ENDM

START:
	MOV AX,DATA						;将DATA的段地址存入AX
	MOV DS,AX						;将数据段与DATA建立联系
	MOV ES,AX						;将附加数据段与DATA建立联系 (此时数据段和附加数据段重叠 均访问DATA 方便之后串操作 SI默认访问当前数据段 DI默认访问当前附加数据段)
	
IN_NAME_PAS:						;功能一:输入账号 密码
	MOV BYTE PTR AUTH,0				;将登陆状态重置为0 (有可能之后会重新登陆)
	IN_STRING NA_MEN,IN_NAME		;输入账号
	
	LEA BX,IN_NAME					;判断名字输入是否为回车或者q
	CMP	BYTE PTR [BX+1],1			;如果长度大于1那么为正常输入情况
	JA CONTINUE						;继续输入密码
	CMP	BYTE PTR [BX+2],13			;长度<=1与回车ASCLL码比较
	JZ	IN_PRO_NAME					;是则直接跳转到功能三:计算利润的输入商品名 此时AUTH=0
	CMP BYTE PTR [BX+2],'q'			;不等与'q'比较
	JZ	EXIT						;相等则直接退出
	
CONTINUE:							;否则继续
	IN_STRING PWD_MEN,IN_PWD		;输入密码
	
CMP_NAME_PAS:						;比较用户名密码是否正确
	PUSH OFFSET BNAME				;传参--将正确用户名入栈
	PUSH OFFSET IN_NAME				;传参--将输入的用户名入栈
	CALL JUDGE						;调用子程序比较用户名
	CMP AX,0						;比较返回值AX 1表示相等 0表示不等
	JZ FAIL_LOG						;等于0就跳转到提示函数 否则继续

	PUSH OFFSET BPASS				;传参--将正确密码入栈
	PUSH OFFSET IN_PWD				;传参--将输入的密码入栈
	CALL JUDGE						;调用子程序比较密码
	CMP AX,0						;比较返回值AX 1表示相等 0表示不等
	JZ FAIL_LOG						;等于0就跳转到提示函数 否则继续
	
	MOV BYTE PTR AUTH,1				;若之前没有跳转 说明成功登陆 将AUTH赋值为1
	
IN_PRO_NAME:						;输入商品名称
	IN_STRING PRO_MEN,IN_PRO		;使用宏输入商品名称
	
	LEA SI,S1						;将1号商店信息偏移首地址存入SI 之后会用到
	PUSH SI							;传参--将1号商店信息偏移首地址入栈
	PUSH OFFSET IN_PRO				;传参--将要查找的输入商品名"指针"入栈
	CALL FIND_PROD					;调用子程序在1号商店查找输入的商品
	MOV SI,AX						;获得查找结果 存放要查找商品信息的"指针"
	
	CMP SI,0						;判断返回的商品所在位置偏移量是否等于0
	JZ IN_PRO_NAME					;如果等于0说明没有找到重新输入
	
	CMP BYTE PTR AUTH,0				;如果找到商品则查询登陆状态
	JZ SHOW_NAME					;如果等于0 表示没有登陆 则只用显示商品名称
	
	;LEA DI,S2						;第二个店铺地址偏移量
	;PUSH DI							;传参-店铺地址偏移量
	;PUSH OFFSET IN_PRO				;传参-查找的商品名称地址偏移量
	;CALL FIND_PROD					;调用子程序查找
	MOV DI,AX
	
	MOV EAX,0FFFFH
	AND ESI,EAX
	JMP CAL							;否则需要计算利润率

SHOW_NAME:							;显示商品名称-先将商品名称下一个字节赋值为'$'表示字符串结束
	LEA SI,IN_PRO					;将输入的商品名称地址传入SI
	MOVSX BX,BYTE PTR [SI+1]		;获得输入的长度
	MOV BYTE PTR [SI+2+BX],'$'		;将其后一个字符编程 字符串结束符'$'
	ADD SI,2						;得到字符串首地址
	OUT_INFO SI,9					;调用宏输出商品名
	JMP IN_NAME_PAS					;回到功能一

CAL:
	MOV CX,M
	XOR AX,AX
	CALL TIMER
LOOP1:
	PUSH CX
	MOV AX,WORD PTR [ESI+14]
	CMP AX,WORD PTR [ESI+16]
	JBE IN_NAME_PAS
	INC WORD PTR [ESI+16]
;	MOV DI,AX						;将返回的偏移地址存入DI(由于默认商品种类相同故一定可以找到)
	
	PUSH SI
	
	LEA EBX,GA1
;	LEA BP,GB1
LOOP2:								;循环找到DI(输入的商品名称)对应的商品
	LEA EBP,GB1
LOOP3:
	MOV SI,BX
	MOV DI,BP
	MOV CX,5
	REPE CMPSW
	JZ REFRESH
	ADD BP,20
	CMP BP,OFFSET GB1+20*N
	JB LOOP3
	
REFRESH:
	CAL_PROFIT EBX
	CAL_PROFIT EBP
	MOV AX,DS:[EBX+18]					;获得一号商店该商品利润率
	ADD AX,DS:[EBP+18]					;获得二号商店该商品利润率
	SAR AX,1
	MOV [EBX+18],AX
	ADD BX,20
;	ADD BP,20
	CMP BX,OFFSET GA1+20*N
	JB LOOP2
	
	POP SI
	
	JMP SHOWTIME
	
PRESENT:							;显示该商品平均利润率等级
	MOV AX,[ESI+18]					;获得一号商店该商品利润率
	;PUSH AX
	MOV DL,'A'
	CMP AX,90						;和90比较
	JGE	OUTPUT							;如果比90大则显示A
	INC DL
	CMP AX,50						;与50比较
	JGE OUTPUT							;如果比50大则显示B
	INC DL
	CMP AX,20						;与20比较
	JGE OUTPUT							;如果比20大则显示C
	INC DL
	CMP AX,0						;与0比较
	JGE OUTPUT							;如果比0大则显示D
	ADD DL,2						;否则显示F
	
OUTPUT:								;输出评级
	;PUSH AX
	;CALL SHOW_NUM
	OUT_INFO DX,2					;调用宏输出计算得到的利润率评级
SHOWTIME:	
	POP CX
	DEC CX
	JNE LOOP1
	MOV AX,1
	CALL TIMER
	JMP	IN_NAME_PAS					;回到功能一

FAIL_LOG:							;登陆失败
	OUT_INFO <OFFSET FAIL>,9		;调用宏输出登陆失败信息
	MOV AH,1						;输入一个字符 -- 按任意键继续
	INT 21H							;执行中断
	JMP IN_NAME_PAS

EXIT:								;退出系统
	MOV AH,4CH
	INT 21H

JUDGE PROC							;参数字符串原串 目的串 
	PUSH BP							;栈:原串(2) 目的串(2) 子程序返回地址(2) BP(2)    BP在栈中的位置也是BP指向的位置
	MOV BP,SP						;栈:原串(2) 目的串(2) 子程序返回地址(2) BP(2)
	PUSH BX							;栈:原串(2) 目的串(2) 子程序返回地址(2) BP(2)  BX(2)
	PUSH CX							;栈:原串(2) 目的串(2) 子程序返回地址(2) BP(2)  BX(2)  CX(2)
	XCHG DI,[BP+6]					;DI存储原串 方便等会串搜索 栈:DI(2) 目的串(2) 子程序返回地址(2) BP(2)  BX(2)  CX(2)
	XCHG SI,[BP+4]					;SI存储目的串	栈:DI(2) SI(2) 子程序返回地址(2) BP(2)  BX(2)  CX(2)

	MOV BX,DI						;将原串的偏移量放在BX
	MOV AL,0						;将搜索值0放在AL 即搜索结束标记
	MOVZX CX,BYTE PTR [SI]			;将搜索次数放在CX
	REPNE SCASB						;执行串搜索 执行完后DI为字符串结束标记0的偏移量
	SUB DI,BX						;获得原串长度 存放到DI
	DEC DI
	XCHG DI,BX						;交换DI,BX BX为长度 DI为原串起始地址

	MOVSX AX,BYTE PTR [SI+1]		;将目的串长度存入AX
	CMP BX,AX						;比较原串与目的串长度
	JNZ NO							;不相等则返回0
	MOV CX,BX						;否则开始比较各个位 将比较长度存入CX
	ADD SI,2						;将SI变成目的串的起始地址
	REPE CMPSB						;开始比较
	JNZ NO							;如果不相等则返回0
YES:MOV AX,1						;否则返回1 将返回值放在AX中
	JMP JUDGE_RET					;跳转到返回处
NO:	MOV AX,0						;否则返回0
JUDGE_RET:							
	POP CX							;栈:DI(2) SI(2) 子程序返回地址(2) BP(2)  BX(2)
	POP BX							;栈:DI(2) SI(2) 子程序返回地址(2) BP(2)
	MOV SI,[BP+4]					;栈:DI(2) SI(2) 子程序返回地址(2) BP(2)
	MOV DI,[BP+6]					;栈:DI(2) SI(2) 子程序返回地址(2) BP(2)
	POP BP							;栈:DI(2) SI(2) 子程序返回地址(2)
	RET 4							;跳转到栈顶指向的IP 忽略4个字节
JUDGE ENDP

FIND_PROD PROC						;参数商店信息偏移量 待查找商品名偏移量 返回值存在AX
	PUSH BP							;栈:商店(2) 商品名(2) 子程序返回地址(2) BP(2)
	MOV BP,SP						;栈:商店(2) 商品名(2) 子程序返回地址(2) BP(2)
	PUSH CX							;栈:商店(2) 商品名(2) 子程序返回地址(2) BP(2)  CX(2)
	XCHG SI,[BP+6]					;存放商店信息偏移量		栈:SI(2) 商品名(2) 子程序返回地址(2) BP(2)  CX(2)
	XCHG DI,[BP+4]					;存放待查找商品名偏移量	栈:SI(2) DI(2) 子程序返回地址(2) BP(2)  CX(2)
	
LOOPP1:								;跳过店铺名称 也可用串搜索跳过 但是需要用DI
	INC SI							;增加SI
	CMP BYTE PTR [SI],0				;与结束标记0比较
	JNZ LOOPP1						;不等则继续查看下一个

	INC SI							;增加1 SI变成第一个商品的商品名的偏移量
	MOV CX,N						;循环次数--商店商品数量
LOOPP2:								;循环找到DI(输入的商品名称)对应的商品
	PUSH SI							;传参--将当前商品名称入栈
	PUSH DI							;传参--将查找商品名称入栈
	CALL JUDGE						;调用子程序比较名称是否相等
	CMP AX,0						;比较返回结果是否相等
	JNZ FIND						;找到跳出循环
	ADD SI,20						;否则跳转到下一个商品位置 (一个商品占20个字节)
	LOOP LOOPP2						;如果还有商品就继续循环

	MOV AX,0						;没找到则返回0
	JMP FIND_PROD_RET				;跳转到返回处
FIND:MOV AX,SI						;将当前店铺与输入商品名称对应的商品信息偏移量返回
FIND_PROD_RET:						;返回子程序
	POP CX							;栈:SI(2) DI(2) 子程序返回地址(2) BP(2)
	MOV DI,[BP+4]					;栈:SI(2) DI(2) 子程序返回地址(2) BP(2)
	MOV SI,[BP+6]					;栈:SI(2) DI(2) 子程序返回地址(2) BP(2)
	POP BP							;栈:SI(2) DI(2) 子程序返回地址(2)
	RET 4							;跳转到栈顶指向的IP 忽略4个字节
FIND_PROD ENDP

SHOW_NUM PROC						;显示利润率在屏幕上
	PUSH BP
	MOV BP,SP
	XCHG AX,[BP+4]
	PUSH BX
	PUSH CX
	PUSH DX
	MOV BX,10
	MOV CX,0
	CMP AX,0
	JGE LOOPP3
	MOV BX,AX
	MOV DL,'-'
	MOV AH,2
	INT 21H
	NEG BX
	MOV AX,10
	XCHG AX,BX
	
LOOPP3:
	CMP AX,0
	JZ CONTINUEP
	MOV DX,0
	DIV BX
	ADD DX,48
	PUSH DX
	INC CX
	JMP LOOPP3
CONTINUEP:
	
	MOV AH,2
LOOPP4:
	POP DX
	INT 21H
	LOOP LOOPP4
	OUT_INFO '%',2
	MOV DL,10
	MOV AH,2
	INT 21H
	
	POP DX
	POP CX
	POP AX
	MOV BX,[BP+4]
	POP BP
	RET 2
SHOW_NUM ENDP

disptime proc        ;显示秒和百分秒，精度为55ms。(未保护ax寄存器)
         local timestr[8]:byte     ;0,0,'"',0,0,0dh,0ah,'$'
         push cx
         push dx         
         push ds
         push ss
         pop  ds
         mov  ah,2ch 
         int  21h
         xor  ax,ax
         mov  al,dh
         mov  cl,10
         div  cl
         add  ax,3030h
         mov  word ptr timestr,ax
         mov  timestr+2,'"'
         xor  ax,ax
         mov  al,dl
         div  cl
         add  ax,3030h
         mov  word ptr timestr+3,ax
         mov  word ptr timestr+5,0a0dh
         mov  timestr+7,'$'
         lea  dx,timestr  
         mov  ah,9
         int  21h    
         pop  ds 
         pop  dx
         pop  cx
         ret
disptime endp

TIMER	PROC
	PUSH  DX
	PUSH  CX
	PUSH  BX
	MOV   BX, AX
	MOV   AH, 2CH
	INT   21H	     ;CH=hour(0-23),CL=minute(0-59),DH=second(0-59),DL=centisecond(0-100)
	MOV   AL, DH
	MOV   AH, 0
	IMUL  AX,AX,1000
	MOV   DH, 0
	IMUL  DX,DX,10
	ADD   AX, DX
	CMP   BX, 0
	JNZ   _T1
	MOV   CS:_TS, AX
_T0:	POP   BX
	POP   CX
	POP   DX
	RET
_T1:	SUB   AX, CS:_TS
	JNC   _T2
	ADD   AX, 60000
_T2:	MOV   CX, 0
	MOV   BX, 10
_T3:	MOV   DX, 0
	DIV   BX
	PUSH  DX
	INC   CX
	CMP   AX, 0
	JNZ   _T3
	MOV   BX, 0
_T4:	POP   AX
	ADD   AL, '0'
	MOV   CS:_TMSG[BX], AL
	INC   BX
	LOOP  _T4
	PUSH  DS
	MOV   CS:_TMSG[BX+0], 0AH
	MOV   CS:_TMSG[BX+1], 0DH
	MOV   CS:_TMSG[BX+2], '$'
	LEA   DX, _TS+2
	PUSH  CS
	POP   DS
	MOV   AH, 9
	INT   21H
	POP   DS
	JMP   _T0
_TS	DW    ?
 	DB    'Time elapsed in ms is '
_TMSG	DB    12 DUP(0)
TIMER   ENDP

CODE ENDS							;
	END START						;结束程序 指定程序入口 
	
;主要功能列表
;1.显示字符串
;2.输入字符串
;3.输入字符
;4.输出字符
;5.比较字符串
;6.查找商品
;7.计算利润率
;time 10110->7800->7080->7030->6370->6310->6150