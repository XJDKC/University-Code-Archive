.386
STACK SEGMENT USE16 STACK
	DB	200	DUP(0)
STACK ENDS
;-------------------------------
DATA SEGMENT USE16
BNAME	DB	'XING RULIN'					;系统登录名
BPASS	DB	'test',0,0						;系统登陆密码
IN_NAME	DB	10+1,?,11 DUP(0)				;为回车预留1位
IN_PWD	DB	6+1,?,7 DUP(0)					;为回车预留1位
IN_PRO	DB	10+1,?,11 DUP(0)				;为回车预留1位
NA_MEN	DB	'Please input the username: $'	;显示信息-输入姓名
PWD_MEN	DB	'Please input the password: $'	;显示信息-输入密码
FAIL	DB	'Login failed: Press any key to continue!',10,'$'	;显示信息-登录失败
PRO_MEN	DB	'Please enter the product name: $'	;显示信息-输入商品名称
AUTH	DB	?								;存放登陆状态
APR		DB	0								;存放平均收益
N		EQU	30								;存放商品类别数
;-------------------------------			;第一个网店信息
S1	DB	'SHOP1',0							;网店名称
GA1	DB	'PEN',7 DUP(0)						;第一个商品名称
	DW	35,56,70,25,?						;分别为第一个商品 进价,售价,进货量,已售量,利润率
GA2	DB	'BOOK',6 DUP(0)						;...
	DW	12,30,25,5,?
GAN	DB	N-2	DUP('Temp-Value',15,0,20,0,30,0,2,0,?,?)
;-------------------------------			;第二个网店信息
S2	DB	'SHOP2',0							;网店名称
GB1	DB	'BOOK',6 DUP(0)						;第一个商品名称
	DW	12,28,20,15,?						;分别为第一个商品 进价,售价,进货量,已售量,利润率
GB2	DB	'PEN',7 DUP(0)						;...
	DW	35,50,30,24,?
GBN	DB	N-2	DUP('Temp-Value',15,0,20,0,30,0,2,0,?,?)
DATA ENDS
;-------------------------------
CODE SEGMENT USE16
	ASSUME CS:CODE,DS:DATA,SS:STACK
START:
	MOV AX,DATA
	MOV DS,AX
INPUT:
	MOV BYTE PTR AUTH,0		;将AUTH赋初值为0
	LEA DX,NA_MEN			;输入名字
	MOV AH,9
	INT 21H
	LEA DX,IN_NAME
	MOV AH,10
	INT 21H
	MOV DL,10
	MOV AH,2
	INT 21H
	
	LEA BX,IN_NAME			;判断名字输入是否为回车或者q
	CMP	BYTE PTR [BX+1],1	;如果长度大于1那么为正常输入情况
	JA CONTINUE				;继续输入密码
	CMP	BYTE PTR [BX+2],13	;长度<=1与回车ASCLL码比较
	JZ	CAL					;是则直接跳转到功能三:计算利润 此时AUTH=0
	CMP BYTE PTR [BX+2],'q'	;不等与'q'比较
	JZ	EXIT				;相等则直接退出
CONTINUE:					;否则继续
	LEA DX,PWD_MEN			;输入密码
	MOV AH,9
	INT 21H
	LEA DX,IN_PWD
	MOV AH,10
	INT 21H
	MOV DL,10
	MOV AH,2
	INT 21H
	
	LEA BX,IN_NAME			;将名字不足位赋值为0
	CALL FILL_ZERO
	LEA BX,IN_PWD			;将密码不足位赋值为0
	CALL FILL_ZERO
	
LOG_IN:						;登陆
	PUSH OFFSET BNAME		;调用子程序比较用户名
	PUSH OFFSET IN_NAME
	CALL JUDGE
	CMP AX,0				;比较返回值AX 1表示相等 0表示不等
	JZ FAIL_LOG				;等于0就跳转到提示函数 否则继续

	PUSH OFFSET BPASS		;调用子程序比较密码
	PUSH OFFSET IN_PWD
	CALL JUDGE
	CMP AX,0				;比较返回值AX 1表示相等 0表示不等
	JZ FAIL_LOG				;等于0就跳转到提示函数 否则继续
	
	MOV BYTE PTR AUTH,1		;若之前没有跳转 说明成功登陆 将AUTH赋值为1
	
CAL:
	LEA DX,PRO_MEN			;输入商品名称
	MOV AH,9
	INT 21H
	LEA DX,IN_PRO
	MOV AH,10
	INT 21H
	MOV DL,10
	MOV AH,2
	INT 21H
	LEA BX,IN_PRO			;将不足位补0
	CALL FILL_ZERO
	
	LEA SI,S1				;调用子程序查找输入的商品
	PUSH SI
	PUSH OFFSET IN_PRO
	CALL FIND_PROD
	MOV SI,AX
	
	CMP SI,0				;判断返回的商品所在位置偏移量是否等于0
	JZ CAL					;如果等于0说明没有找到重新输入
	
	CMP WORD PTR AUTH,0		;如果找到商品则查询登陆状态
	JZ SHOW_NAME			;如果等于0 表示没有登陆 则只用显示商品名称
	JMP SHOW_PROFIT			;否则需要计算利润率
	
SHOW_NAME:					;显示商品名称-先将商品名称下一个字节赋值为'$'表示字符串结束
	MOV BX,0				;BX表示商品名称的第BX个字节
LOOP4:						;循环查找 知道某个位置为0
	CMP BYTE PTR [SI+BX],0
	JZ J_L					;跳出循环
	INC BX
	JMP LOOP4
J_L:MOV BYTE PTR [SI+BX],'$';将对应位置赋值为'$' 表示字符串结束
	MOV DX,SI				;显示商品名称
	MOV AH,9
	INT 21H
	MOV DL,10
	MOV AH,2
	INT 21H
	JMP CAL					;继续输入下一个商品
	
	
SHOW_PROFIT:				;显示利润率评级
	LEA DI,S2				;第二个店铺地址偏移量
	PUSH DI					;传参-店铺地址偏移量
	PUSH OFFSET IN_PRO		;传参-查找的商品名称地址偏移量
	CALL FIND_PROD			;调用子程序查找
	MOV DI,AX				;将返回的偏移地址存入DI(由于默认商品种类相同故一定可以找到)
	
	PUSH SI					;计算一号商店该商品利润率
	CALL CAL_PROFIT
	PUSH DI					;计算二号商店该商品利润率
	CALL CAL_PROFIT

PRESENT:					;显示该商品平均利润率等级
	MOV AX,[SI+18]			;获得一号商店该商品利润率
	ADD AX,[DI+18]			;获得二号商店该商品利润率
	SAR AX,1				;除2
	CMP AX,90				;和90比较
	JGE	P_A					;如果比90大则显示A
	CMP AX,50				;与50比较
	JGE P_B					;如果比50大则显示B
	CMP AX,20				;与20比较
	JGE P_C					;如果比20大则显示C
	CMP AX,0				;与0比较
	JGE P_D					;如果比0大则显示D
							;否则显示E
P_E:MOV DL,'E'				;显示E
	JMP OUTPUT
P_D:MOV DL,'D'				;显示D
	JMP OUTPUT
P_C:MOV DL,'C'				;显示C
	JMP OUTPUT
P_B:MOV DL,'B'				;显示B
	JMP OUTPUT
P_A:MOV DL,'A'				;显示A
	
OUTPUT:						;输入显示信息
	MOV AH,2
	INT 21H
	MOV DL,10
	INT 21H
	JMP INPUT				;回到功能一

;子程序部分
;子程序名称:FILL_ZERO
;子程序功能:将字符串后面部分清0
;使用的寄存器:AX,SI
;传入参数:约定寄存器BX 存放字符串首地址
;传出参数:无
FILL_ZERO PROC				;子程序 填充0 约定BX存放传进来的字符串地址
	PUSH AX					;存放字符串总宽度
	PUSH SI					;存放当前下标
	MOVZX AX,BYTE PTR [BX]	;
	MOVZX SI,BYTE PTR [BX+1];指向最后一个不为0的
LOOP1:	
	INC SI					;增加
	CMP SI,AX
	JA	FILL_ZERO_RET		;如果比总宽度大就跳出
	MOV BYTE PTR [BX+SI+1],0;将BX+SI+1 也就是字符串的第SI个赋值为0
	JMP LOOP1				;进入下次循环
FILL_ZERO_RET:
	POP SI
	POP AX
	RET
FILL_ZERO ENDP

FAIL_LOG:					;提示登陆失败
	LEA	DX,FAIL
	MOV AH,9
	INT 21H
	MOV AH,1
	INT 21H
	JMP	INPUT

;子程序名称:JUDGE
;子程序功能:比较两个字符串是否相等
;使用的寄存器:BP,SI,DI,AX,CX,DX
;传入参数:原字符串   (无其他信息)
;		  目的字符串 (系统中断格式)
;传出参数:是否相等信息  0表示不想等 1表示相等
JUDGE PROC					;子程序 判断字符串是否相等 用了BP,SI,DI,CX,AX 参数顺序 正确string 错误string AX存返回
	PUSH BP
	MOV BP,SP
	XCHG SI,[BP+6]			;将正确赋值SI
	XCHG DI,[BP+4]			;将错误赋值给DI
	PUSH CX
	DEC SI					;为循环作准备
	INC DI					;为循环作准备
	MOVZX CX,BYTE PTR [DI]				;循环次数
CMP_BIT:
	INC SI					;原字符串"指针"往后移动一位
	INC DI					;目的字符串"指针"往后移动一位
	MOV AL,[SI]				
	CMP AL,[DI]				;比较
	LOOPE CMP_BIT			;相等且CX-1不等于0 继续
	JNZ	NO					;如果比较的最后一个数不相等 则返回0
YES:MOV AX,1				;将返回值放在AX中
	JMP JUDGE_RET
NO:	MOV AX,0				;否则返回0
JUDGE_RET:
	POP CX
	MOV DI,[BP+4]
	MOV SI,[BP+6]
	POP BP
	RET 4
JUDGE ENDP

;子程序名称:FIND_PROD
;子程序功能:在商店中查找对应的商品信息并返回偏移量
;使用的寄存器:BP,SI,DI,AX,BX,CX,DX
;传入参数:原字符串   (无其他信息)
;		  目的字符串 (系统中断格式)
;传出参数:约定寄存AX 是否相等信息  0表示不想等 1表示相等
FIND_PROD PROC
	PUSH BP
	MOV BP,SP
	XCHG DI,[BP+4]			;AX存放查找的商品名称偏移地址
	XCHG SI,[BP+6]			;BX存放店铺商品偏移地址
	PUSH CX
LOOP2:						;跳过店铺名称
	INC SI
	CMP BYTE PTR [SI],0
	JNZ LOOP2
	
	INC SI
	MOV CX,N
LOOP3:						;循环找到DI(输入的商品名称)对应的商品
	PUSH SI
	PUSH DI
	CALL JUDGE
	CMP AX,0
	JNZ FIND				;找到跳出循环
	ADD SI,20
	LOOP LOOP3
	MOV AX,0				;没找到则返回0
	JMP FIND_PROD_RET
FIND:MOV AX,SI				;将当前店铺与输入商品名称对应的商品信息偏移量返回
FIND_PROD_RET:
	POP CX
	MOV DI,[BP+4]
	MOV SI,[BP+6]
	POP BP
	RET 4
FIND_PROD ENDP

;子程序名称:CAL_PROFIT
;子程序功能:计算商品的利润率
;使用的寄存器:BP,SI,DI,AX,BX,DX
;传入参数:商品信息偏移量
;传出参数:无
CAL_PROFIT PROC
	PUSH BP
	MOV BP,SP
	XCHG SI,[BP+4]
	PUSH AX
	PUSH BX
	PUSH DX
	
	MOVSX EAX,WORD PTR [SI+10+2*1]	;计算总收入
	MOVSX EDX,WORD PTR [SI+10+2*3]
	IMUL EAX,EDX
	MOVSX EBX,WORD PTR [SI+10]		;计算成本
	MOVSX EDX,WORD PTR [SI+10+2*2]
	IMUL EBX,EDX
	IMUL EAX,100					;将总收入乘以100 这样会获得百分比下的整数部分
	MOV EDX,0						;双字除法高位补0
	DIV EBX							;除以成本
	SUB AX,100						;减去成本
	MOV [SI+10+2*4],AX				;将计算得到的利润率百分之下的整数部分存入AX
	
	POP DX
	POP BX
	POP AX
	MOV SI,[BP+4]
	POP BP
	RET 2
CAL_PROFIT ENDP

EXIT:								;退出系统
	MOV AH,4CH
	INT 21H
CODE ENDS
	END START