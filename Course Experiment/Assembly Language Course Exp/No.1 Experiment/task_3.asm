.386
STACK	SEGMENT	USE16	STACK			;��ջ������
	db	200	DUP(0)						;Ϊ��ջ�ο���200���ֽڵĿռ� ����ֵΪ0
STACK	ENDS							;��ջ����������
DATA	SEGMENT	USE16					;���ݶ�����
BUF1	DB	0,1,2,3,4,5,6,7,8,9			;����һ�����ݴ洢��BUF1 ��ֵ�ֱ�Ϊ0H,1H,2H,3H,4H,5H,6H,7H,8H,9H
BUF2	DB	10	DUP(0)					;����һ�����ݴ洢��BUF2 ��ֵȫ����ֵ��0
BUF3	DB	10	DUP(0)					;����һ�����ݴ洢��BUF3 ��ֵȫ����ֵ��0
BUF4	DB	10	DUP(0)					;����һ�����ݴ洢��BUF4 ��ֵȫ����ֵ��0
MENTION DB 'Press any key to begin! $'	;������ʾ
DATA	ENDS							;���ݶ���������
CODE	SEGMENT USE16					;���������
	ASSUME	CS:CODE,DS:DATA,SS:STACK	;�ٶ�
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
	MOV DH,0			;���� λ��
	MOV BH,10			;��¼��10 ȡ��
LOPB:
	MOV AL,BL			;�Ƚ�BL �����ַ���AL
	DIV BH				;��AX����BH	��������AH,�̴���AL
	MOV BL,AL			;���̴���AL ��һ�μ�����
	MOV AL,AH			;����������AL
	CBW					;��AL��������
	PUSH AX				;������ѹ��ջ��
	INC DH				;λ��++
	CMP BL,0			;����̲�Ϊ0 ������
	JNZ LOPB
LOPC:					
	POP AX				;��AX ��ջ
	MOV DL,AL			;����һλ���ִ���DL
	ADD DL,30H			;ת����ASCLL��
	MOV AH,2			;���
	INT 21H				
	DEC DH				;λ��--
	CMP DH,0
	JNZ LOPC			;���λ����Ϊ0����
	MOV DL,' '
	MOV AH,2
	INT 21H
	POP AX				;��ջ����
	RET
OUTPUT	ENDP
EXIT:
	MOV	AH,4CH
	INT	21H
CODE ENDS
	END	START