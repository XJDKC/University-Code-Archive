.386
STACK	SEGMENT	USE16	STACK			;��ջ������
	db	200	DUP(0)						;Ϊ��ջ�ο���200���ֽڵĿռ� ����ֵΪ0
STACK	ENDS							;��ջ����������
DATA	SEGMENT	USE16					;���ݶ�����
BUF1	DB	0,1,2,3,4,5,6,7,8,9			;����һ�����ݴ洢��BUF1 ��ֵ�ֱ�Ϊ0H,1H,2H,3H,4H,5H,6H,7H,8H,9H
BUF2	DB	10	DUP(0)					;����һ�����ݴ洢��BUF2 ��ֵȫ����ֵ��0
BUF3	DB	10	DUP(0)					;����һ�����ݴ洢��BUF3 ��ֵȫ����ֵ��0
BUF4	DB	10	DUP(0)					;����һ�����ݴ洢��BUF4 ��ֵȫ����ֵ��0
MENTION DB 'Press any key to begin! $'
DATA	ENDS							;���ݶ���������
CODE	SEGMENT USE16					;���������
	ASSUME	CS:CODE,DS:DATA,SS:STACK	;�ٶ�
START:	MOV	AX,DATA
	MOV	DS,AX
	MOV	SI,OFFSET BUF1
	MOV	DI,OFFSET BUF2
	MOV	BX,OFFSET BUF3
	MOV	BP,OFFSET BUF4
	MOV	CX,10
	MOV AH,9
	INT 21H
	MOV AH,1
	INT 21H
LOPA:	MOV	AL,[SI]
	MOV	[DI],AL
	INC	AL
	MOV	[BX],AL
	ADD	AL,3
	MOV	DS:[BP],AL
	INC	SI
	INC	DI
	INC	BP
	INC	BX
	DEC	CX
	JNZ	LOPA
	MOV	AH,4CH
	INT	21H
CODE	ENDS
	END	START