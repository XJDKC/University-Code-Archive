.386
.model flat,stdcall
option casemap:none
;------------------------------ ������Ŷ����ļ�
include windows.inc
include user32.inc
include kernel32.inc
include gdi32.inc
include msvcrt.inc
include gdi32.inc
;------------------------------ ������ļ�
includelib user32.lib
includelib kernel32.lib
includelib gdi32.lib
includelib msvcrt.lib
includelib gdi32.lib
;------------------------------ ����ԭ������
memset PROTO C :ptr sbyte, :DWORD, :DWORD
sprintf PROTO C :ptr sbyte, :ptr sbyte, :VARARG
strlen	PROTO C :ptr sbyte

WinMain PROTO hInst:DWORD, hPreInst:DWORD, IpCmdLine:DWORD, nCmdShow:DWORD
WndProc	PROTO hWin:DWORD, uMsg:DWORD, wParam:DWORD, IParam:DWORD
CalAverage PROTO
ShowInfo PROTO
AboutMe	PROTO
;------------------------------ �ṹ������
GOOD STRUCT					;��Ʒ�ṹ��
	GName DB 10 dup(0)		;'Temp-Value'	;��Ʒ����
	GPurPrice DW ?			;��Ʒ����
	GSelPrice DW ?			;��Ʒ�ۼ�
	GPurVol	DW ?			;��Ʒ������
	GSelVol DW ?			;��Ʒ�ۻ���
	GProRand DW 0			;��Ʒ������
GOOD ENDS
;------------------------------
.data
	WinClassName	DB		'MyFirstWinClass',0
	WinTitle		DB		'��Ʒ��Ϣ����ϵͳ',0
	AboutMsg		DB		'����CSEE1601 ������',0
	CalSuccess		DB		'����ƽ�������ʳɹ���',0
	CalFail			DB		'����ƽ��������ʧ�ܣ�',0
	ChangeMen		DB		'������ʾ��Ϣ���ܷ����˸���,ȷ��ˢ�£�',0
	hInstance		DD		0
	hWnd			DD		0
	hDC				DD		0
	CommandLine		DD		0
	Fht				DD		15
	Wwd				DD		560
	Wht				DD		350
	Wtx				DD		400
	Wty				DD		200
	CurState		DD		0
	N				EQU		5

	S1				DB		'SHOP1',0,0,0,0,0
	GA1				GOOD	<'BOOK',35,56,70,25,>
	GA2				GOOD	<'PEN',12,30,25,5,>
	GA3				GOOD	<'PENCIL',20,30,30,25,>
	GA4				GOOD	<'RULER',16,24,24,8,>
	GA5				GOOD	<'ERASER',12,50,24,10,>

	S2				DB		'SHOP2',0,0,0,0,0
	GB1				GOOD	<'BOOK',12,28,20,15,>
	GB2				GOOD	<'PEN',35,50,30,24,>
	GB3				GOOD	<'PENCIL',20,35,28,20,>
	GB4				GOOD	<'RULER',15,25,25,20,>
	GB5				GOOD	<'ERASER',10,40,20,10,>
.code
;----------------------------------------	�궨��
CAL_RATE MACRO A						;������Ʒ�����ʲ����浽��Ӧλ�� ����--��Ʒ��Ϣ���λ��
	PUSH EDI

	XOR EDX,EDX							;��λ��0
	MOVZX EAX,(GOOD PTR [ESI]).GSelPrice;���������� EAX=�ۼ�
	MOVZX ECX,(GOOD PTR [ESI]).GSelVol	;ECX=�ۻ���
	MUL ECX								;EAX=������
	MOVZX ECX,(GOOD PTR [ESI]).GPurPrice;����ɱ� EBX=����
	MOVZX EDI,(GOOD PTR [ESI]).GPurVol	;ECX=������	
	IMUL ECX,EDI						;EBX=�ܳɱ�
	IMUL EAX,100						;�����������100 �������ðٷֱ��µ���������
	IDIV ECX							;���Գɱ�
	SUB EAX,100							;��ȥ�ɱ�
	MOV (GOOD PTR [ESI]).GProRand,AX	;������õ��������ʰٷ�֮�µ��������ִ���AX

	POP EDI
ENDM
;----------------------------------------	������
START:
	invoke GetModuleHandle,NULL
	MOV hInstance,EAX
	invoke GetCommandLine
	MOV CommandLine,EAX
	invoke WinMain,hInstance,NULL,CommandLine,SW_SHOWDEFAULT
	
	invoke ExitProcess,EAX
;----------------------------------------	����������
WinMain PROC hInst:DWORD, hPreInst:DWORD, IpCmdLine:DWORD, nCmdShow:DWORD
	local	wc			: WNDCLASSEX		;����������ʱ������Ϣ��ű���
	local	msg			: MSG				;��Ż�ȡ������Ϣ
	local	rectClient	: DWORD
	
	MOV wc.cbSize, sizeof WNDCLASSEX
	MOV wc.style, CS_HREDRAW or CS_VREDRAW or CS_BYTEALIGNWINDOW
	MOV wc.lpfnWndProc,offset WndProc
	MOV wc.cbClsExtra,NULL
	MOV wc.cbWndExtra,NULL
	PUSH hInst
	POP wc.hInstance
	MOV wc.hbrBackground,COLOR_WINDOW+1
	MOV wc.lpszMenuName,NULL
	MOV wc.lpszClassName,offset WinClassName
	MOV wc.hIcon,0
	invoke LoadCursor,NULL,IDC_ARROW
	MOV wc.hCursor,EAX
	MOV wc.hIconSm,0
	
	invoke RegisterClassEx,addr wc
	
	invoke CreateWindowEx,
			WS_EX_LEFT,
			ADDR WinClassName,
			ADDR WinTitle,
			WS_OVERLAPPEDWINDOW or WS_VISIBLE,
			Wtx,Wty,Wwd,Wht,
			NULL,NULL,hInst,NULL
	MOV hWnd,EAX
	
	invoke LoadMenu,hInst,500
	invoke SetMenu,hWnd,EAX
	invoke GetClientRect,hWnd,ADDR rectClient
	
	invoke ShowWindow,hWnd,SW_SHOWNORMAL
	invoke UpdateWindow,hWnd

	StartLoop:
		invoke GetMessage,ADDR msg,NULL,0,0
		CMP EAX,0
		JE ExitLoop
		invoke TranslateMessage,addr msg
		invoke DispatchMessage,addr msg
		jmp StartLoop
	ExitLoop:
		mov eax,msg.wParam
		ret
WinMain	ENDP

WndProc	PROC hWin:DWORD, uMsg:DWORD, wParam:DWORD, IParam:DWORD
	local	Ps   :PAINTSTRUCT	

	.if uMsg == WM_COMMAND												;�ж��ǲ��ǲ˵��¼�
		.if wParam == 510												;����ǰ�����Exit
			invoke PostQuitMessage,NULL									;�˳�
		.elseif wParam == 520											;��������˼���ƽ��������
			invoke CalAverage											;���ü��㺯��
			.if EAX == 1
				invoke MessageBox,hWin,ADDR CalSuccess,ADDR WinTitle,MB_OK
			.else
				invoke MessageBox,hWin,ADDR CalFail,ADDR WinTitle,MB_OK
			.endif
			.if CurState == 1
				invoke MessageBox,hWin,ADDR ChangeMen,ADDR WinTitle,MB_YESNO
				.if EAX == IDYES
					invoke InvalidateRect,hWnd,NULL,1
					invoke UpdateWindow,hWnd
					invoke BeginPaint,hWin,ADDR Ps
					mov hDC, eax
					invoke ShowInfo
					invoke EndPaint,hWin,ADDR Ps
				.else
					mov CurState,0
					invoke InvalidateRect,hWnd,NULL,1
					invoke UpdateWindow,hWnd
				.endif
			.endif 
		.elseif wParam == 521											;�����������ʾ��Ʒ��Ϣ��ť
			invoke ShowInfo												;������ʾ��Ϣ����
			MOV	CurState,1
		.elseif wParam == 530											;���������About
			invoke MessageBox,hWin,ADDR AboutMsg,ADDR WinTitle,MB_OK	;��ʾAbout��Ϣ
		.endif															;��������˵��¼���֧
	.elseif uMsg == WM_DESTROY											;������������Ͻ��˳�
		invoke PostQuitMessage,NULL										;�˳�
	.elseif	uMsg == WM_PAINT
		.if	CurState == 1
			invoke BeginPaint,hWin,ADDR Ps
				mov hDC, eax
				invoke ShowInfo
			invoke EndPaint,hWin,ADDR Ps
		.else
			invoke DefWindowProc,hWin,uMsg,wParam,IParam
			ret
		.endif
	.else																;�������
		invoke DefWindowProc,hWin,uMsg,wParam,IParam					;ȱʡ����
		ret																;������
	.endif
		mov eax,0														;�����˳� ����ֵΪ0
		ret
WndProc ENDP

CalAverage PROC
	LEA ESI,GA1
	LEA EDI,GB1
	SUB EDI,ESI

LOOP1:	
	CAL_RATE ESI						;���һ���̵����Ʒ������
	CAL_RATE ESI+EDI					;��ö����̵����Ʒ������
	MOV AX,(GOOD PTR [ESI]).GProRand				
	ADD AX,(GOOD PTR [ESI+EDI]).GProRand				
	SAR AX,1
	MOV (GOOD PTR [ESI]).GProRand,AX
	ADD ESI,20
	CMP ESI,OFFSET GA1+sizeof(GOOD)*N
	JB LOOP1
	
	MOV EAX,1
	ret
CalAverage ENDP

ShowInfo PROC
	local	hFont	:	DWORD
	local	logfont	:	LOGFONT
	local	BUF[50]	:	BYTE
	local	curline	:	DWORD
	local	ctime	:	DWORD
	JMP	pbegin		
	sh_instr		DB		'%hd',0
	s_instr			DB		'%s',0
	List			DB		'List',0
	Col				DB		'��Ʒ����',4 DUP(' '),'������',4 DUP(' '),'���ۼ�',4 DUP(' '),'��������',4 DUP(' '),'��������',4 DUP(' '),'ƽ��������(%)',0

pbegin:
	invoke memset,ADDR logfont,0,sizeof(LOGFONT)
	push Fht
	pop logfont.lfHeight
	mov logfont.lfWeight,400
	mov logfont.lfCharSet,1
	invoke CreateFontIndirect,addr logfont
	MOV hFont,EAX

	.if	CurState == 0
	invoke GetDC,hWnd
	MOV hDC,EAX
	.endif	

	invoke SelectObject,hDC,hFont

	invoke TextOut,hDC,10,10,ADDR List,4
	invoke strlen,ADDR Col
	invoke TextOut,hDC,10,28,ADDR Col,EAX
	invoke MoveToEx,hDC,10,45,NULL
	invoke LineTo,hDC,540,45

	MOV curline,50
	MOV ctime,0
	LEA ESI,GA1
Show:
	invoke strlen,ESI
	
	invoke TextOut,hDC,10,curline,ADDR (GOOD PTR [ESI]).GName,EAX

	invoke sprintf,ADDR BUF,ADDR sh_instr,(GOOD PTR [ESI]).GPurPrice
	invoke strlen,ADDR BUF
	invoke TextOut,hDC,115,curline,ADDR BUF,EAX

	invoke sprintf,ADDR BUF,ADDR sh_instr,(GOOD PTR [ESI]).GSelPrice
	invoke strlen,ADDR BUF
	invoke TextOut,hDC,195,curline,ADDR BUF,EAX

	invoke sprintf,ADDR BUF,ADDR sh_instr,(GOOD PTR [ESI]).GPurVol
	invoke strlen,ADDR BUF
	invoke TextOut,hDC,280,curline,ADDR BUF,EAX

	invoke sprintf,ADDR BUF,ADDR sh_instr,(GOOD PTR [ESI]).GSelVol
	invoke strlen,ADDR BUF
	invoke TextOut,hDC,370,curline,ADDR BUF,EAX

	invoke sprintf,ADDR BUF,ADDR sh_instr,(GOOD PTR [ESI]).GProRand
	invoke strlen,ADDR BUF
	invoke TextOut,hDC,470,curline,ADDR BUF,EAX

	ADD ESI,sizeof(GOOD)
	ADD curline,15
	INC ctime
	CMP ctime,N
	JNE Show

	ret
ShowInfo ENDP

end START