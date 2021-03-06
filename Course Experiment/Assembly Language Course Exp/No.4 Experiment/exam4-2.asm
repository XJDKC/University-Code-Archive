.386
CODE SEGMENT USE16
	ASSUME CS:CODE,SS:STACK

ORIGINAL_IP	DW 0
ORIGINAL_CS DW 0
BEGIN:
	CMP AH,0
	JZ U0_10
	CMP AH,10H
	JZ U0_10
	PUSHF
	CALL DWORD PTR CS:ORIGINAL_IP	
	IRET
	
U0_10:
	PUSHF
	CALL DWORD PTR CS:ORIGINAL_IP
	CMP AL,'a'
	JNAE TO_UPPER_RET
	CMP AL,'z'
	JNBE TO_UPPER_RET
	SUB AL,'a'-'A'
	JMP TO_UPPER_RET
	
TO_UPPER_RET:
	IRET
TO_UPPER_END: NOP
START:
	;取原终端地址
	PUSH CS
	POP DS
	MOV AL,16H
	MOV AH,35H
	INT 21H
	;保存原中断地址
	MOV CS:ORIGINAL_CS,ES
	MOV CS:ORIGINAL_IP,BX
	;设置新的中断地址
	MOV DX,OFFSET BEGIN
	MOV AL,16H
	MOV AH,25H
	INT 21H
	;驻留新中断程序
	PUSH CS
	POP DS
	MOV DX,OFFSET START
	SHR DX,4
	ADD DX,1000H
	MOV AL,0
	MOV AH,31H
	INT 21H
CODE ENDS
STACK SEGMENT USE16 STACK
	DB 200 DUP(0)
STACK ENDS
;------------------------
	END START