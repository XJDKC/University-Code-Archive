.386
.MODEL SMALL
PUBLIC SHOW_ALL
PUBLIC PRINT_NUM
PUBLIC SHOW_ICONS
PUBLIC CAL_PROFIT
PUBLIC SORT_PROFIT
PUBLIC CLEAR_SCREEN
PUBLIC S1,GA1,S2,GB1
PUBLIC ATTR_OFF,MEN_ATTR
STACK SEGMENT USE16 STACK 'STACK'
	DB	200	DUP(0)
STACK ENDS
;-------------------------------
DATA SEGMENT USE16	PUBLIC 'D'
BNAME	DW	'IX' xor 12788,'GN' xor 12788 ,'R ' xor 12788,'LU' xor 12788,'NI' xor 12788,77					;系统登录名
BPASS	DW	'ET' xor 12788,'TS' xor 12788 ,77,0						;系统登陆密码
IN_NAME	DB	10+1,?,11 DUP(0)				;为回车预留一位
IN_PWD	DB	6+1,?,7 DUP(0)					;为回车预留一位
IN_PRO	DB	10+1,?,11 DUP(0)				;为回车预留一位
NA_MEN	DB	'Please input the username: $'	;显示信息-输入姓名
PWD_MEN	DB	'Please input the password: $'	;显示信息-输入密码8
FAIL	DB	'Login failed: Press any key to continue! $'	;显示信息-登录失败
FAIL_TH DB	'Three failures in landing, You will be landing as a visitor! $'
PRO_MEN	DB	'Please enter the product name: $'	;显示信息-输入商品名称
AUTH	DB	?								;存放登陆状态
F_TIME	DB  0								;存放错误次数
N		EQU	30								;存放商品类别数
;-------------------------------			;第一个网店信息
S1	DB	'SHOP1',0							;网店名称
GA1	DB	'BOOK',6 DUP(0)						;第一个商品名称
	DW	35 xor 12788,56,70,25,?				;分别为第一个商品 进价,售价,进货量,已售量,利润率
GA2	DB	'PEN',7 DUP(0)						;...
	DW	12 xor 12788,30,25,5,?
GAN	DB	N-2	DUP('Temp-Value',15 xor 244,49,20,0,30,0,2,0,?,?)
;-------------------------------			;第二个网店信息
S2	DB	'SHOP2',0					;网店名称
GB1	DB	'BOOK',6 DUP(0)			;第一个商品名称
	DW	12 xor 12788,28,20,15,?						;分别为第一个商品 进价,售价,进货量,已售量,利润率
GB2	DB	'PEN',7 DUP(0)						;... 57
	DW	35 xor 12788,50,30,24,?
GBN	DB	N-2	DUP('Temp-Value',15 xor 244,49,20,0,30,0,2,0,?,?)
;-------------------------------
OUT_SHOP	EQU 1H
OUT_NAME	EQU 2H
OUT_INPRI	EQU 4H
OUT_OUTPRI	EQU 8H
OUT_INNUM	EQU 10H
OUT_OUTNUM	EQU 20H
OUT_RANK	EQU 40H	;既表示利润率信息 又表示rank信息
MEN_ATTR	DB	'Shop No.: $                   ',
				'Product Name: $               ',
				'Product Purchase Price: $     ',
				'Product Selling  Price: $     ',
				'Product Purchase Volume: $    ',
				'Product Sales    Volume: $    ',
				'Product Average  Profit: $    ',
				'Product Profit   Ranking: $   '
ATTR_OFF	DB	0,0,10,12,14,16,18

ICONS_FILE DB 'C:\ICONS.txt',0

FAIL_INQUIRED_GOODS_INFORM DB 'Wrong inquired goods input! Please try again ', 0AH, 0DH, '$'
FAIL_MODIFIED_GOODS_INFORM DB 'Wrong goods input! Please try again', 0AH, 0DH, '$'

INQ_INFORM DB 'Please enter the inquired goods name: $'
MOD_SHOP_INFORM	DB 'Please enter the shop name: $'
MOD_GOOD_INFORM DB 'Please enter the modified goods name: $'
PAGE_TRANS_INFORM DB 'Press page up/down to get more info  Press ESC to quit$'
POWED_BY_INFORM DB 'Powered by $'
MODE_INFORM DB 'Please enter the display mode [0-1]: $'
CAL_SUCCESS DB 'Succeed in calculating the profit rate! $'
RANK_SUCCESS DB 'Succeed in ranking the profit rate! $'

SHOW_MENU_TITLE DB 'SHOW MENU$'
SHOW_MENU_1 DB '1.INQUIRE GOODS INFO$'
SHOW_MENU_2 DB '2.MODIFY  GOODS INFO$'
SHOW_MENU_3 DB '3.CALCUL THE  PROFIT$'
SHOU_MENU_4 DB '4.RANK CALCUL PROFIT$'
SHOW_MENU_5 DB '5.SHOW ALL GOOD INFO$'
SHOW_MENU_6 DB '6.EXIT              $'

SHOW_MENU_CHOOSE DB 'Please enter the choice: $'

BUF DB 15 DUP(0)
ORDER DW N*2*2 DUP(0)
INQ_GA  DB 80,?,80 DUP(0)
MOD_SHOP	DB 80,?,80 DUP(0)
MOD_GA  DB 80,?,80 DUP(0)
MOD_DATA  DB 80,?,80 DUP(0)
CHOICE	DB 80,?,80 DUP(0)
;-------------------------------
KEY_LENTH	DB 2 xor 'B'
KEY			DB (244-34)/5,(49-34)/5
ORIGINAL_IP DW 0,?
ORIGINAL_CS DW 0,?
ANTI_ADDR	DW ANTI,?
EXIT_ADDR	DW EXIT
DATA ENDS
;-------------------------------
CODE SEGMENT USE16	PUBLIC 'C'
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

;-------------------------------
OUT_INFO MACRO A,B					;宏定义 输出信息 A表示输出信息(字符串偏移地址 或者 字符) B表示输出类型
	MOV	DX,A						;将待输出的 字符串偏移地址 或 字符 存入DX
	MOV AH,B						;将输出类型存入AH 可能为9or2 分别表示输出字符串 和 字符 
	INT 21H							;调用中断
ENDM								;结束宏定义

;-------------------------------
CAL_RATE MACRO A					;计算商品利润率并保存到对应位置 参数--商品信息存放位置
	
	XOR EDX,EDX						;高位补0
	MOVZX EAX,WORD PTR DS:[A+10];计算总收入 EAX=售价
	UNCHIFF
	MOVZX ECX,WORD PTR DS:[A+10+2*2];ECX=售货量
	MUL ECX							;EAX=总收入
	MOVZX ECX,WORD PTR DS:[A+10+2*1]	;计算成本 EBX=进价
	MOVZX EDI,WORD PTR DS:[A+10+2*3];ECX=进货量	
	IMUL ECX,EDI					;EBX=总成本
	XCHG EAX,ECX
	IMUL EAX,100					;将总收入乘以100 这样会获得百分比下的整数部分
	IDIV ECX						;除以成本
	SUB EAX,100						;减去成本
	MOV word ptr DS:[A+10+2*4],AX	;将计算得到的利润率百分之下的整数部分存入AX
	
ENDM

;-------------------------------
CHIFF MACRO A,B
	LOCAL CIRCLE,NTO0
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH DX
	PUSH SI
	PUSH DI
	PUSH BP

	MOV SI,A
	MOV CX,B
	MOVZX DX,BYTE PTR [KEY_LENTH]
	XOR DL,'B'
	PUSH DX
	MOV BX,0
	MOV BP,0
	LEA DI,KEY
CIRCLE:
	MOV DL,[SI+BX]
	MOV AL,DS:[DI+BP]
	MOV AH,5
	MUL AH
	ADD AL,34
	XOR DL,AL
	MOV [SI+BX],DL
	INC BX
	INC BP
	XCHG DI,[ESP]
	CMP BP,DI
	JNZ NTO0
	XOR BP,BP
NTO0:
	XCHG DI,[ESP]
	CMP BX,CX
	JNZ CIRCLE
	POP DX
	
	POP BP
	POP DI
	POP SI
	POP DX
	POP CX
	POP BX
	POP AX
ENDM

;-------------------------------
UNCHIFF MACRO
	LOCAL CIRCLE,NTO0
	PUSH CX
	PUSH DX
	PUSH DI

	MOV DX,AX
	LEA DI,KEY
	
	MOV AL,DS:[DI]
	MOV AH,5
	MUL AH
	ADD AL,34
	MOV CL,AL
	
	MOV AL,DS:[DI+1]
	MOV AH,5
	MUL AH
	ADD AL,34
	MOV AH,AL
	MOV AL,CL
	
	XOR AX,DX

	POP DI
	POP DX
	POP CX
ENDM

;-------------------------------
SHOW_INFO MACRO A,B,C
	LOCAL PRE_LPP4,LOOPP4,OUT_ATTR,OUT_NEXT,LP,P_NUM,NEXTP4,OUT_10,FINISH,J_P_N
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH DX
	PUSH SI
	PUSH DI
	PUSH BP
	MOV CX,A
	MOV SI,B
	MOV DI,C
	ADD CX,48
	
	SHR DI,1
	JNC	PRE_LPP4
	OUT_INFO <OFFSET MEN_ATTR>,9
	OUT_INFO CX,2
	MOV CH,1
PRE_LPP4:
	MOV BX,1
LOOPP4:
	SHR DI,1
	JNC NEXTP4
	CMP CH,0
	JE OUT_ATTR
	OUT_INFO 10,2
OUT_ATTR:
	INC CH	
	MOV BP,BX
	CMP BX,6
	JNE OUT_NEXT
	CMP CL,'2'
	JNE OUT_NEXT
	INC BP
OUT_NEXT:
	IMUL BP,30
	ADD BP,OFFSET MEN_ATTR
	OUT_INFO BP,9
	MOVZX BP,BYTE PTR [BX+ATTR_OFF]
	ADD BP,SI
	CMP BX,1
	JNE P_NUM
	MOV DH,10
LP:	CMP DH,0
	JE NEXTP4
	MOV DL,DS:[BP]
	MOV AH,2
	INT 21H
	INC BP
	DEC DH
	JMP LP
P_NUM:
	PUSH AX
	MOV AX,DS:[BP]
	CMP BX,2
	JNE J_P_N
	UNCHIFF
J_P_N:
	PUSH AX
	CALL PRINT_NUM
	POP AX
	CMP BX,6
	JNE NEXTP4
	CMP CL,'1'
	JNE NEXTP4
	OUT_INFO '%',2
NEXTP4:
	INC BX
	CMP BX,7
	JB	LOOPP4
	
OUT_10:
	CMP CH,1
	JE	FINISH
	OUT_INFO 10,2
	
FINISH:	
	POP BP
	POP DI
	POP SI
	POP DX
	POP CX
	POP BX
	POP AX
ENDM

;-------------------------------
START:
	MOV AX,DATA						;将DATA的段地址存入AX
	MOV DS,AX						;将数据段与DATA建立联系
	MOV ES,AX						;将附加数据段与DATA建立联系 (此时数据段和附加数据段重叠 均访问DATA 方便之后串操作 SI默认访问当前数据段 DI默认访问当前附加数据段)
	
	MOV AH,0
	MOV AL,12H
	INT 10H
	
	CLI
	MOV BP,WORD PTR ANTI_ADDR
	PUSH BP
	MOV AH,2ch
	POP BX
	MOV CX,[ESP-2]
	PUSH BX
	STI
	CALL CX
	CMP AX,1
	JZ EXIT
	CMP AX,0
	JNZ EXIT
	
	MOV WORD PTR ANTI_ADDR,0
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
		
	MOV BP,[ESP]
	MOV ANTI_ADDR,BP
CONTINUE:							;否则继续
	IN_STRING PWD_MEN,IN_PWD		;输入密码
	
	CALL BP
	CMP AX,1
	JZ EXIT
CMP_NAME_PAS:						;比较用户名密码是否正确
	PUSH OFFSET BNAME				;传参--将正确用户名入栈
	PUSH OFFSET IN_NAME				;传参--将输入的用户名入栈
	CALL JUDGE						;调用子程序比较用户名
	CMP AX,0						;比较返回值AX 1表示相等 0表示不等
	JNE CMP_PAS
	INC BYTE PTR F_TIME
	CMP BYTE PTR F_TIME,3
	JE IN_PRO_NAME
	JMP FAIL_LOG						;等于0就跳转到提示函数 否则继续

CMP_PAS:
	PUSH OFFSET BPASS				;传参--将正确密码入栈
	PUSH OFFSET IN_PWD				;传参--将输入的密码入栈
	CALL JUDGE						;调用子程序比较密码
	CMP AX,0						;比较返回值AX 1表示相等 0表示不等
	JNE SUCCESS
	INC BYTE PTR F_TIME
	CMP BYTE PTR F_TIME,3	
	JE IN_PRO_NAME
	JMP FAIL_LOG						;等于0就跳转到提示函数 否则继续
SUCCESS:
	MOV BYTE PTR AUTH,1				;若之前没有跳转 说明成功登陆 将AUTH赋值为1
IN_PRO_NAME:						;输入商品名称
	;IN_STRING PRO_MEN,IN_PRO		;使用宏输入商品名称
	CMP BYTE PTR AUTH,1
	JE JM
	OUT_INFO <OFFSET FAIL_TH>,9
	MOV AH,1
	INT 21H
JM:	JMP SHOW_MENU

FAIL_LOG:							;登陆失败
	OUT_INFO <OFFSET FAIL>,9		;调用宏输出登陆失败信息
	OUT_INFO 10,2
	MOV AH,1						;输入一个字符 -- 按任意键继续
	INT 21H							;执行中断
	JMP IN_NAME_PAS



;-------------------------------
JUDGE PROC							;参数字符串原串 目的串 
	PUSH BP							;栈:原串(2) 目的串(2) 子程序返回地址(2) BP(2)    BP在栈中的位置也是BP指向的位置
	MOV BP,SP						;栈:原串(2) 目的串(2) 子程序返回地址(2) BP(2)
	PUSH BX							;栈:原串(2) 目的串(2) 子程序返回地址(2) BP(2)  BX(2)
	PUSH CX							;栈:原串(2) 目的串(2) 子程序返回地址(2) BP(2)  BX(2)  CX(2)
	PUSH DX
	XCHG DI,[BP+6]					;DI存储原串 方便等会串搜索 栈:DI(2) 目的串(2) 子程序返回地址(2) BP(2)  BX(2)  CX(2)
	XCHG SI,[BP+4]					;SI存储目的串	栈:DI(2) SI(2) 子程序返回地址(2) BP(2)  BX(2)  CX(2)

	cli
	MOV AH,2CH
	MOV BX,DI						;将原串的偏移量放在BX
	INT 21H
	MOV AL,77						;将搜索值0放在AL 即搜索结束标记
	PUSH DX
	MOVZX CX,BYTE PTR [SI]			;将搜索次数放在CX
	REPNE SCASB						;执行串搜索 执行完后DI为字符串结束标记0的偏移量
	SUB DI,BX						;获得原串长度 存放到DI
	DEC DI
	XCHG DI,BX						;交换DI,BX BX为长度 DI为原串起始地址
	
	MOV AH,2CH
	INT 21H
	STI	
	MOV AX,WORD PTR EXIT_ADDR
	CMP DX,[ESP]
	POP DX
	JE COMPARE
	JMP AX
COMPARE:
	MOVSX AX,BYTE PTR [SI+1]		;将目的串长度存入AX
	CMP BX,AX						;比较原串与目的串长度
	JNZ NO							;不相等则返回0
	
	ADD SI,2
	CHIFF SI,BX
	
	MOV CX,BX
	;POP CX							;否则开始比较各个位 将比较长度存入CX
	;ADD SI,2						;将SI变成目的串的起始地址
	REPE CMPSB						;开始比较
	JNZ NO							;如果不相等则返回0
YES:MOV AX,1						;否则返回1 将返回值放在AX中
	JMP JUDGE_RET					;跳转到返回处
NO:	MOV AX,0						;否则返回0
JUDGE_RET:							
	POP DX
	POP CX							;栈:DI(2) SI(2) 子程序返回地址(2) BP(2)  BX(2)
	POP BX							;栈:DI(2) SI(2) 子程序返回地址(2) BP(2)
	MOV SI,[BP+4]					;栈:DI(2) SI(2) 子程序返回地址(2) BP(2)
	MOV DI,[BP+6]					;栈:DI(2) SI(2) 子程序返回地址(2) BP(2)
	POP BP							;栈:DI(2) SI(2) 子程序返回地址(2)
	RET 4							;跳转到栈顶指向的IP 忽略4个字节
JUDGE ENDP


;-------------------------------
SHOW_MENU:
	CALL CLEAR_SCREEN

	CALL SHOW_ICONS
	
	MOV DH, 7
	MOV DL, 30
	MOV BH, 0
	MOV AH, 02H
	INT 10H

	LEA DX, SHOW_MENU_TITLE
	MOV AH, 9
	INT 21H

	MOV CL, 7
	MOV CH, 0
	LEA SI, SHOW_MENU_1
SHOW_MENU_CIR:
	INC CL
	INC CH
	MOV DH, CL
	MOV DL, 25
	MOV BH, 0
	MOV AH, 02H
	INT 10H
	MOV DX, SI
	MOV AH, 9
	INT 21H
	ADD SI, 21
	CMP BYTE PTR AUTH,0
	JNE CMP6
	ADD SI, 21*4
	ADD CH, 4
CMP6:
	CMP CH, 6
JNAE SHOW_MENU_CIR

	ADD CL, 2 					;行数
	MOV DH, CL
	MOV DL, 23
	MOV BH, 0
	MOV AH, 02H
	INT 10H
	LEA DX, SHOW_MENU_CHOOSE
	MOV AH, 9
	INT 21H

	LEA DX, CHOICE
	MOV AH, 10
	INT 21H
	
	CALL CLEAR_SCREEN


	CMP BYTE PTR[CHOICE + 2], '1'
	JZ SHOW_1
	CMP BYTE PTR AUTH,0
	JZ JUDGE_6
	CMP BYTE PTR[CHOICE + 2], '2'
	JZ SHOW_2
	CMP BYTE PTR[CHOICE + 2], '3'
	JZ SHOW_3
	CMP BYTE PTR[CHOICE + 2], '4'
	JZ SHOW_4
	CMP BYTE PTR[CHOICE + 2], '5'
	JZ SHOW_5
JUDGE_6:
	CMP BYTE PTR[CHOICE + 2], '6'
	JZ SHOW_6
	JMP SHOW_MENU

SHOW_1:
	CALL INQ_INFO
	MOV AH, 1
	INT 21H
	JMP SHOW_MENU

SHOW_2:
	CALL MOD_INFO
	JMP SHOW_MENU
	
SHOW_3:
	CALL CAL_PROFIT
	JMP SHOW_MENU
	
SHOW_4:
	CALL SORT_PROFIT
	JMP SHOW_MENU
	
SHOW_5:
	CALL SHOW_ALL
	JMP SHOW_MENU
	
SHOW_6:
	CALL EXIT
	JMP SHOW_MENU
		

EXIT PROC
	MOV AH, 4CH
	INT 21H
EXIT ENDP


;-------------------------------
INQ_INFO PROC					;查询商品信息
F_3_1:
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH DX
	PUSH SI
	PUSH DI
	IN_STRING INQ_INFORM,INQ_GA	;输入查询商品信息
	LEA BX, INQ_GA + 2			;商品名称偏移地址
	CMP BYTE PTR[BX], 0DH
	JE F_3_1_BACK				;输入回车，回到功能三1
	LEA AX, GA1					;商品1的偏移地址
	MOV CL, N
F_3_1_1:						;循环网店中所有商品
	MOV DI, AX					;已有商品的偏移地址
	MOV SI, BX					;输入商品的偏移地址
	F_3_1_2:					;比较两个商品字节
		MOV CH, BYTE PTR[SI]
		CMP CH, BYTE PTR[DI]
		JNE F_3_1_3
		INC SI
		INC DI
		CMP BYTE PTR[DI], 0
		JNZ F_3_1_2
		CMP BYTE PTR[SI], 0DH
		JNZ F_3_1_2		
	JMP JUDGE_1					;成功找到匹配目标
	F_3_1_3:					;继续循环，比较下一件商品
	ADD AX, 20
	DEC CL
JNZ F_3_1_1
JMP FAIL_INQUIRED_GOODS 					;未找到，提示重新输入商品
JUDGE_1:
								;AX为当前商品的偏移地址
	;----------------------------输出商品信息

	SHOW_INFO 1, AX, OUT_SHOP+OUT_NAME+OUT_INPRI+OUT_INNUM+OUT_OUTNUM
	ADD AX,OFFSET GB1
	SUB AX,OFFSET GA1
	SHOW_INFO 2, AX, OUT_SHOP+OUT_NAME+OUT_INPRI+OUT_INNUM+OUT_OUTNUM


F_3_1_BACK:
	POP DI
	POP SI
	POP DX
	POP CX
	POP BX
	POP AX
	RET
INQ_INFO ENDP


;-------------------------------
MOD_INFO PROC					;修改商品信息
F_3_2:
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH DX
	PUSH SI
	PUSH DI
	IN_STRING MOD_SHOP_INFORM, MOD_SHOP 	;输入修改商品的商店信息
	IN_STRING MOD_GOOD_INFORM, MOD_GA		;输入修改商品信息
	LEA BX, MOD_GA + 2			;商品名称偏移地址
	CMP BYTE PTR[BX], 0DH
	JE F_3_2_BACK				;输入回车，回到功能三1
	MOV CL, N

	LEA AX, GA1					;待修改商品的商店偏移地址
	CMP BYTE PTR[MOD_SHOP + 2], '1'
	JZ F_3_2_1
	ADD AX,OFFSET GB1
	SUB AX,OFFSET GA1

F_3_2_1:						;循环网店中所有商品
	MOV DI, AX					;已有商品的偏移地址
	MOV SI, BX					;输入商品的偏移地址
	F_3_2_2:					;比较两个商品字节
		MOV CH, BYTE PTR[SI]
		CMP CH, BYTE PTR[DI]
		JNE F_3_2_3
		INC SI
		INC DI
		CMP BYTE PTR[DI], 0
		JNZ F_3_2_2
		CMP BYTE PTR[SI], 0DH
		JNZ F_3_2_2		
	JMP JUDGE_2					;成功找到匹配目标
	F_3_2_3:					;继续循环，比较下一件商品
	ADD AX, 20
	DEC CL
JNZ F_3_2_1
JMP FAIL_MODIFIED_GOODS 					;未找到，提示重新输入商品
JUDGE_2:
								;AX为当前商品的偏移地址
	;----------------------------输出商品信息

MOV BX, OUT_INPRI				;BX--输出哪项数据
MOV DI, 0
PUSH AX
F_3_2_4:
	POP AX
	SHOW_INFO 1, AX, BX
	PUSH AX
	MOV DL, '>'
	MOV AH, 2
	INT 21H
	LEA DX, MOD_DATA
	MOV AH, 10
	INT 21H

	LEA CX, MOD_DATA + 2
	PUSH BX
	MOV BX, CX
	CMP BYTE PTR[BX], 0DH		;输入回车
	POP BX
	JZ F_3_2_6
	
	MOV SI, CX

F_3_2_5:
	CMP BYTE PTR[SI], '0'
	JB FAIL_ILLEGAL_INPUT
	CMP BYTE PTR[SI], '9'
	JA FAIL_ILLEGAL_INPUT
	INC SI
	CMP BYTE PTR[SI], 0DH
JNZ F_3_2_5

	LEA SI, MOD_DATA + 2
	MOV DX, 0
F_3_2_IN:
	MOV CL, BYTE PTR[SI]
	SUB CL, 30H
	MOV CH, 0
	IMUL DX, 10
	ADD DX, CX
	INC SI
	CMP BYTE PTR[SI], 0DH
JNZ F_3_2_IN
	

	POP AX
	PUSH BX
	MOV BX, AX

	MOV WORD PTR[BX + DI + 10], DX
	POP BX
	PUSH AX
F_3_2_6:
	MOV DL, 0AH
	MOV AH, 2
	INT 21H
	MOV DL, 0DH
	MOV AH, 2
	INT 21H
	ADD DI, 2
	SAL BX, 1
	CMP BX, 20H
JNZ F_3_2_4
POP AX

F_3_2_BACK:
	POP DI
	POP SI
	POP DX
	POP CX
	POP BX
	POP AX
	RET
MOD_INFO ENDP

FAIL_ILLEGAL_INPUT:
	MOV DL, 0AH
	MOV AH, 2
	INT 21H
	MOV DL, 0DH
	MOV AH, 2
	INT 21H
JMP F_3_2_4

FAIL_MODIFIED_GOODS:
	LEA DX, FAIL_MODIFIED_GOODS_INFORM
	MOV AH, 9
	INT 21H
	MOV AH, 1
	INT 21H
	POP DI
	POP SI
	POP DX
	POP CX
	POP BX
	POP AX
JMP F_3_2


FAIL_INQUIRED_GOODS:
	LEA DX, FAIL_INQUIRED_GOODS_INFORM
	MOV AH, 9
	INT 21H
	MOV AH, 1
	INT 21H
	POP DI
	POP SI
	POP DX
	POP CX
	POP BX
	POP AX
JMP F_3_1


;-------------------------------
CAL_PROFIT PROC						;计算商品利润率并保存到对应位置 参数--商品信息存放位置
	PUSH ESI
	PUSH EDI
	PUSH EBP
	PUSH EAX						;栈:SI(2) 子程序返回地址(2) BP(2)  EAX(4) 
	PUSH EBX						;栈:SI(2) 子程序返回地址(2) BP(2)  EAX(4)  EBX(4)
	PUSH ECX						;栈:SI(2) 子程序返回地址(2) BP(2)  EAX(4)  EBX(4)  ECX(4) 
	PUSH EDX						;栈:SI(2) 子程序返回地址(2) BP(2)  EAX(4)  EBX(4)  ECX(4) EDX(4)
	
	
	LEA EBX,GA1
	LEA EBP,GB1
	SUB EBP,EBX
LOOPP5:							;循环找到DI(输入的商品名称)对应的商品
REFRESH:
	CAL_RATE EBX					;获得一号商店该商品利润率
	CAL_RATE EBX+EBP					;获得二号商店该商品利润率
	MOV AX,DS:[EBX+18]				
	ADD AX,DS:[EBP+EBX+18]				
	SAR AX,1
	MOV [EBX+18],AX
	ADD BX,20

	CMP BX,OFFSET GA1+20*N
	JB LOOPP5
	
	CALL CLEAR_SCREEN
	OUT_INFO <OFFSET CAL_SUCCESS>,9
	MOV AH,1
	INT 21H
	
	POP EDX							;栈:SI(2) 子程序返回地址(2) BP(2)  EAX(4)  EBX(4)  ECX(4)
	POP ECX							;栈:SI(2) 子程序返回地址(2) BP(2)  EAX(4)  EBX(4)
	POP EBX							;栈:SI(2) 子程序返回地址(2) BP(2)  EAX(4)  EBX(4)
	POP EAX							;栈:SI(2) 子程序返回地址(2) BP(2)  EAX(4)
	POP EBP
	POP EDI
	POP ESI
	RET 
CAL_PROFIT ENDP


;-------------------------------
SORT_PROFIT PROC
	PUSH AX
	PUSH EBX
	PUSH CX
	PUSH DX
	PUSH ESI
	PUSH DI
	PUSH BP
	
	MOV CX,1
	XOR DI,DI
	MOV BP,-101
S_RLP1:
	MOV AX,-101
	XOR EBX,EBX
S_RLP2:
	MOV DX,WORD PTR [EBX+GB1+18]
	CMP DX,AX
	JNG NEXT_LP2
	MOV AX,DX
	MOV ESI,EBX
NEXT_LP2:
	ADD EBX,20
	CMP EBX,N*20
	JB S_RLP2
	MOV DX,CX
	CMP BP,AX
	JZ SAME
	MOV BP,AX
	XOR DI,DI
	JMP ASSIGN
SAME:
	INC DI
ASSIGN:
	SUB DX,DI
	NEG DX
	SUB DX,100
	MOV WORD PTR [ESI+GB1+18],DX
	INC CX
	CMP CX,N
	JBE S_RLP1
	
	XOR EBX,EBX
S_RLP3:
	MOV DX,WORD PTR [EBX+GB1+18]
	ADD DX,100
	NEG DX
	MOV WORD PTR [EBX+GB1+18],DX
	ADD EBX,20
	CMP EBX,N*20
	JB S_RLP3
	
	CALL CLEAR_SCREEN
	OUT_INFO <OFFSET RANK_SUCCESS>,9
	MOV AH,1
	INT 21H
	
	POP BP
	POP DI
	POP ESI
	POP DX
	POP CX
	POP EBX
	POP AX
	RET 
SORT_PROFIT ENDP


;-------------------------------
SHOW_ALL PROC
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH DX
	PUSH SI	
	PUSH DI

SELECT:
	CALL CLEAR_SCREEN
	OUT_INFO <OFFSET MODE_INFORM>,9
	LEA DX,CHOICE
	MOV AH,10
	INT 21H
	CALL CLEAR_SCREEN
	CMP CHOICE[2],'0'
	JE TYPE1
	CMP CHOICE[2],'1'
	JE TYPE2
	CMP CHOICE[2],13
	JE S_W_RET
	JMP SELECT
	
TYPE1:
	LEA DI,ORDER
	LEA SI,GA1
SP1:MOV [DI],SI
	MOV WORD PTR [DI+2],1
	ADD DI,4
	ADD SI,20
	CMP SI,OFFSET GA1+N*20
	JB SP1
	LEA SI,GB1
SP2:MOV [DI],SI
	MOV WORD PTR [DI+2],2
	ADD DI,4
	ADD SI,20
	CMP SI,OFFSET GB1+N*20
	JB SP2
	JMP DISPLAY

TYPE2:
	LEA DI,ORDER
	MOV CX,1
	MOV SI,1
SP3:MOV BX,0
SP4:CMP WORD PTR [BX+GB1+18],SI
	JNE N_SP4
	INC CX
	MOV AX,OFFSET GA1
	ADD AX,BX
	MOV [DI],AX
	MOV WORD PTR [DI+2],1
	ADD AX,OFFSET GB1-OFFSET GA1
	MOV [DI+4],AX
	MOV WORD PTR [DI+6],2
	ADD DI,8
N_SP4:
	ADD BX,20
	CMP BX,N*20
	JB SP4
	INC SI
	CMP CX,N
	JB SP3
	
DISPLAY:
	MOV DI,0
PRINT4:
	MOV SI,DI
	IMUL SI,16 
	ADD SI,OFFSET ORDER
	
	CALL CLEAR_SCREEN
	
	MOV CX,4
S_WLP1:
	SHOW_INFO [SI+2],[SI],127
	ADD SI,4
	CMP SI,OFFSET ORDER+N*2*4
	JAE H_I
	DEC CX
	JNE S_WLP1
H_I:OUT_INFO 10,2
	OUT_INFO <OFFSET PAGE_TRANS_INFORM>,9
DIRECT:	
	MOV AH,0
	INT 16H
	CMP AH,48H
	JE PAGE_UP
	CMP AH,50H
	JE PAGE_DOWN
	CMP AH,01H
	JE S_W_RET
	JMP DIRECT
PAGE_UP:
	CMP DI,0
	JE PRINT4
	DEC DI
	JMP PRINT4
PAGE_DOWN:
	CMP DI,N/2-1
	JAE PRINT4
	INC DI
	JMP PRINT4

S_W_RET:
	POP DI
	POP SI
	POP DX
	POP CX
	POP BX
	POP AX
	RET	
SHOW_ALL ENDP


;-------------------------------
CLEAR_SCREEN PROC
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH DX
	
	XOR BH,BH
	XOR CH,CH
C_SLP1:
	XOR CL,CL
	MOV DX,CX
	MOV AH,02H
	INT 10H
	PUSH CX
	XOR BH,BH
	MOV CX,80
	MOV AL,' '
	MOV BL,0FH
	MOV AH,09H
	INT 10H
	POP CX
	INC CH
	CMP CH,30
	JB C_SLP1
	XOR DX,DX
	XOR BH,BH
	MOV AH,02H
	INT 10H
	
	POP DX
	POP CX
	POP BX
	POP AX
	RET
CLEAR_SCREEN ENDP


;-------------------------------
SHOW_ICONS PROC
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH DX
	PUSH SI
	PUSH DI
	
	MOV BH,0
	MOV DH,28
	MOV DL,61
	MOV AH,02H
	INT 10H
	LEA DX,POWED_BY_INFORM
	MOV AH,9
	INT 21H
	
	LEA DX,ICONS_FILE
	MOV AL,0
	MOV AH,3DH
	INT 21H
	MOV SI,AX

	MOV BX,0
S_ILP1:
	MOV DI,0
S_ILP2:	
	PUSH BX
	MOV BX,SI
	MOV CX,1
	LEA DX,BUF
	MOV AH,3FH
	INT 21H
	POP BX
	
	CMP BYTE PTR BUF,'0'
	JZ NS_ILP2
	MOV DX,430
	MOV CX,580
	ADD DX,BX
	ADD CX,DI
	MOV AL,3
	MOV AH,0CH
	INT 10H
NS_ILP2:
	INC DI
	CMP DI,60
	JB S_ILP2
	PUSH BX
	MOV BX,SI
	MOV CX,2
	LEA DX,BUF
	MOV AH,3FH
	INT 21H
	POP BX
	
	INC BX
	CMP BX,40
	JB S_ILP1
	
	MOV BX,SI
	MOV AH,3EH
	INT 21H
	
	POP DI
	POP SI
	POP DX
	POP CX
	POP BX
	POP AX
	RET 
SHOW_ICONS ENDP


;-------------------------------
;功能：讲AX中的有符号二进制数以十进制形式在显示器上输出
;入口参数：AX - 存放待转换的有符号二进制数
;出口参数：转换后的带符号十进制数载显示器上输出
;所用寄存器: EBX--用来存放基数10
;	        SI---用来作10进制数ASCLL码存储区的指针
;调用子程序: RADIX
PRINT_NUM PROC
	PUSH BP
	MOV BP,SP
	PUSH EAX
	PUSH EBX
	PUSH DX
	PUSH SI 					;保存现场
	LEA SI, BUF
	MOVSX EAX,WORD PTR [BP+4]
B:	
	OR EAX, EAX
	JNS PLUS
	NEG EAX
	MOV BYTE PTR[SI], '-'
	INC SI
PLUS:
	MOV EBX, 10
	CALL RADIX
	MOV BYTE PTR[SI], '$'
	LEA DX, BUF
	MOV AH, 9
	INT 21H
	POP SI
	POP DX
	POP EBX
	POP EAX
	POP BP
	RET 2
PRINT_NUM ENDP


;-------------------------------
;功能：将EAX中的32位无符号二进制数转换为10进制
;入口参数：
;		 EAX -- 存放带转换的32位无符号二进制数
;		 EBX -- 存放要转换进制的基数
;		 SI -- 存放转换后的P进制ASCII码数字串的字节缓冲区首址
;出口参数:
;		所求10进制ASCII码数字串按高位在前、低位在后的顺序存放在以SI为指针的字节缓冲区中
;		SI--指向字节缓冲区最后一个ASCII码的下一个字节处
;所使用寄存器:
;CX--P进制数字入栈、出栈时的计数器
;EDX--做除法时存放被除数高位或余数
RADIX PROC
	PUSH CX
	PUSH EDX
	XOR CX, CX 			;计数器清零
	LOP1:
		XOR EDX, EDX
		DIV EBX
		PUSH DX
		INC CX
		OR EAX, EAX
		JNZ LOP1		;EAX!=0, 转LOP1继续循环
	LOP2:
		POP AX
		ADD AL, 30H
		MOV [SI], AL
		INC SI
	LOOP LOP2
	POP EDX
	POP CX
	RET
RADIX ENDP

ANTI PROC
	PUSH ES
	PUSH BX
	PUSH DX
	PUSH SI

ANTI_BEGIN:
	MOV AX,1
	MOV SI,AX
	IMUL SI,4
	
	;获取原来的中断地址
	XOR BX,BX
	MOV ES,BX
	MOV BX,ES:[SI]
	MOV ORIGINAL_IP,BX
	
	MOV BX,ES:[SI+2]
	MOV ORIGINAL_CS,BX
	;用35H号中断获取原来地址
	MOV AL,1
	MOV AH,35H
	INT 21H
	;比较35H号中断获取的地址与寄存器寻址获得的是否相等
	CMP BX,WORD PTR ORIGINAL_IP
	JE J_G_ES					;相等说明正常继续
	JMP R_EXIT
	db 88 DUP(?)
J_G_ES:
	MOV BX,ES
	CMP BX,WORD PTR ORIGINAL_CS
	JE RESET
	JMP R_EXIT
	db 66 DUP(?)
	;设置新的值
RESET:
	PUSH DS
	MOV DS,AX
	MOV DX,AX
	MOV AH,25H
	INT 21H
	POP DS
	;获得的新的值是否和原来值相等
	MOV AH,35H
	INT 21H
	CMP ORIGINAL_IP,BX
	JNE J_O_CS
	JMP R_EXIT				;相等说明没改 直接退出
	db 44 DUP(?)
J_O_CS:
	MOV DX,ES
	CMP ORIGINAL_CS,DX
	JNE RECOVER
	JMP R_EXIT
	db 22 DUP(?)
	
RECOVER:
	PUSH DS
	MOV BX,ORIGINAL_CS
	MOV DX,ORIGINAL_IP
	MOV DS,BX
	MOV AH,25H
	INT 21H
	POP DS
	
	ADD AX,2
	CMP AX,4
	JB ANTI_BEGIN
	
	MOV AX,0
RET_ANTI:
	POP SI
	POP DX
	POP BX
	POP ES
	RET
R_EXIT:
	MOV AX,1
	JMP RET_ANTI
ANTI ENDP

CODE ENDS							;
	END START						;结束程序 指定程序入口 