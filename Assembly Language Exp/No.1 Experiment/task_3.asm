.386
STACK	SEGMENT	USE16	STACK			;堆栈段声明
	db	200	DUP(0)						;为堆栈段开辟200个字节的空间 并赋值为0
STACK	ENDS							;堆栈段声明结束
DATA	SEGMENT	USE16					;数据段声明
BUF1	DB	0,1,2,3,4,5,6,7,8,9			;声明一个数据存储区BUF1 初值分别为0H,1H,2H,3H,4H,5H,6H,7H,8H,9H
BUF2	DB	10	DUP(0)					;声明一个数据存储区BUF2 初值全部赋值成0
BUF3	DB	10	DUP(0)					;声明一个数据存储区BUF3 初值全部赋值成0
BUF4	DB	10	DUP(0)					;声明一个数据存储区BUF4 初值全部赋值成0
MENTION DB 'Press any key to begin! $'	;声明提示
DATA	ENDS							;数据段声明结束
CODE	SEGMENT USE16					;代码段声明
	ASSUME	CS:CODE,DS:DATA,SS:STACK	;假定
START:	MOV	AX,DATA
	MOV	DS,AX
	MOV	ESI,OFFSET BUF1
	MOV	CX,10
	MOV DX,OFFSET MENTION
	MOV AH,9
	INT 21H
	MOV AH,1
	INT 21H
LOPA:
	MOV	AL,[ESI]
	MOV	[ESI+10],AL
	INC	AL
	MOV	[ESI+20],AL
	ADD	AL,3
	MOV	[ESI+30],AL
	MOV BX,[ESI+10]
	CALL OUTPUT
	MOV BX,[ESI+20]
	CALL OUTPUT
	MOV BX,[ESI+30]
	CALL OUTPUT
	MOV DL,10
	MOV AH,2
	INT 21H
	INC	ESI
	DEC	CX
	JNZ	LOPA
	JMP	EXIT
OUTPUT	PROC
	PUSH AX
	MOV AX,0
	MOV DH,0			;计数 位数
	MOV BH,10			;记录对10 取余
LOPB:
	MOV AL,BL			;先将BL 的数字放入AL
	DIV BH				;将AX除以BH	余数存入AH,商存入AL
	MOV BL,AL			;将商存入AL 下一次继续除
	MOV AL,AH			;将余数存入AL
	CBW					;对AL进行扩充
	PUSH AX				;将余数压入栈中
	INC DH				;位数++
	CMP BL,0			;如果商不为0 继续除
	JNZ LOPB
LOPC:					
	POP AX				;将AX 出栈
	MOV DL,AL			;将第一位数字存入DL
	ADD DL,30H			;转换成ASCLL码
	MOV AH,2			;输出
	INT 21H				
	DEC DH				;位数--
	CMP DH,0
	JNZ LOPC			;如果位数不为0继续
	MOV DL,' '
	MOV AH,2
	INT 21H
	POP AX				;出栈结束
	RET
OUTPUT	ENDP
EXIT:
	MOV	AH,4CH
	INT	21H
CODE ENDS
	END	START