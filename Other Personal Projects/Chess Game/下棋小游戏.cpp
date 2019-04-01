#include <afxwin.h>                                                         //����CRect ��
#include <stdafx.h>  
#include "����С��Ϸ.h"
#include <fstream>
#include <iostream>
#include<iomanip>
using namespace std;
CMyApp myApp;                                                               //����һ��CMyApp���� ����InitInstance �麯��������ʼ������

BOOL CMyApp::InitInstance ()                                                //��ʼ������ �궨��
{                                                                           
    m_pMainWnd = new CMainWindow;                                           //����һ��CMainWindow���ಢ��ǰ��ָ�����
    m_pMainWnd->ShowWindow (m_nCmdShow);                                    //��ʾ����
    m_pMainWnd->UpdateWindow ();                                            //���´���
    return TRUE;                                                            //�����ɹ�
}

BEGIN_MESSAGE_MAP (CMainWindow, CWnd)                                       //�꿪ʼ����Ϣӳ��
    ON_WM_PAINT ()                                                          //��ͼ�ź�
    ON_WM_LBUTTONDOWN ()                                                    //����������
    ON_WM_LBUTTONDBLCLK ()                                                  //������˫��
    ON_WM_RBUTTONDOWN ()                                                    //����Ҽ�����
END_MESSAGE_MAP ()                                                          //ֹͣ

const CRect CMainWindow::m_rcSquares[9] = {                                 //����9���������� �����ж�����Ƿ���ĳһ����
    CRect ( 16,  16, 112, 112),                                             //���Ͻ����� �����½�����ȷ������������������
    CRect (128,  16, 224, 112),
    CRect (240,  16, 336, 112),
    CRect ( 16, 128, 112, 224),
    CRect (128, 128, 224, 224),
    CRect (240, 128, 336, 224),
    CRect ( 16, 240, 112, 336),
    CRect (128, 240, 224, 336),
    CRect (240, 240, 336, 336)
};

CMainWindow::CMainWindow ()
{
    InitGame();                                                                 //��ʼ����Ϸ
    CString strWndClass = AfxRegisterWndClass (                                 //ע��һ�� WNDCLASS ������.
        CS_DBLCLKS,                                                             // Class style����˫��ʱ�䷢���Ĵ������ͣ�
        AfxGetApp ()->LoadStandardCursor (IDC_ARROW),                           // Class cursor������һ��ϵͳ��꣩
        (HBRUSH) (COLOR_3DFACE + 1),                                            // Background brush��ÿ�Σ���BeginPaintʱ������տͻ�������COLOR_3DFACE+1��ָ�����ھ����밴ť�Ի���һ�µı���ɫ������һЩ3D���ԣ�Ĭ��Ϊ����ɫ
        AfxGetApp ()->LoadStandardIcon (IDI_WINLOGO)                            // Class icon������ϵͳͼ�꣩
    );
    //����CWnd::CreateEx()����������
    CreateEx (0, strWndClass, _T ("������"),                                    //��һ��������ʾ0�����Ƕ��WS_EX��־��ϣ�2��AfxRegisterWndClass�������ص�WNDCLASS���ƣ�3�����⣻//4��������ʽ
        WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,               //WS_THICKFRAME���ڿɵ���С���ԣ����ﲻ�ã�
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,             //��ʼλ�úʹ�С��������CW_USEDEFAULT��Windowsʰȡ���ںʹ�С
        NULL, NULL);                                                            //������λ�úͳߴ�
    CRect rect (0, 0, 352, 352);                                                //����ͻ������ھ�����״ �������봰�ڼ���16�ļ�϶
    CalcWindowRect (&rect);                                                     //���ݷֱ��ʡ��˵�...���㴰�ھ��δ�С�������ڴ��ڴ�������ã�
    SetWindowPos (NULL, 0, 0, rect.Width (), rect.Height (),
    SWP_NOZORDER | SWP_NOMOVE | SWP_NOREDRAW);
}

void CMainWindow::PostNcDestroy ()                                              //�ڳ������֮ǰ���ٴ�����CMainWindow����
{
    delete this;
}

void CMainWindow::OnPaint ()                                                    //OnPaint()��Ӧÿ���ػ�����
{
    CPaintDC dc (this);
    DrawBoard (&dc);    
}

void CMainWindow::OnLButtonDown (UINT nFlags, CPoint point)                     //������������Ӧ
{
    CClientDC dc (this);                                                    
    if (m_nNextChar != EX){                                                     //������������Ӧ������������£����أ�
        return ;
    }
	if (Pos1==0)
    {
		Pos1 = GetRectID (point);   
        if ((Pos1 == -1) || (m_nGameGrid[Pos1] != 1))                           //-1��ʾδ����
        {
			Pos1=0;
		}
		if (cannotmove()){ Pos1=0;}
		return ;
    }
    else 
	{
		Pos2 = GetRectID (point); 
        if ((Pos2 == -1) || (m_nGameGrid[Pos2] != 0)||!can())                   //-1��ʾδ����
        {
			Pos2=0;return ;
		}
	}
    m_nGameGrid[Pos1] = 0;                                                      //������²��ı���һ�����״̬
	m_nGameGrid[Pos2] = EX;
    m_nNextChar = OH;
    Draw (&dc, Pos1);                                                           //����ͼ���ж���Ϸ�Ƿ����
    DrawX (&dc, Pos2);
    if(CheckForGameOver ())return;                                              //�����ı�ʤ����͸��ˡ�����ʤ����ϵ�������
    static int nPattern[2][3] = {
        0, 4, 8,
        2, 4, 6
    };
	for (int i=0;i<2;i++)
	{
		for (int j=0;j<3;j++)
		{
			if (Pos1==nPattern[i][j]) 
			{
                win[0][i]--;ctab[Pos1][i]=true;win[1][i]=0;
				for (int k=0;k<3;k++)
				{
					if (m_nGameGrid[nPattern[i][k]]==EX) {win[1][i]=5;break;}
					if (m_nGameGrid[nPattern[i][k]]==OH) {win[1][i]++;}
				}
			}
			    if (Pos2==nPattern[i][j])
			{
				win[0][i]++;ctab[Pos2][i]=false;win[1][i]=5;
			}
		}
	}
    //��������
    CpDraw(&dc);
	Pos1=Pos2=0;
    if(CheckForGameOver ())  return;
}

//��������Ҽ���Ӧ��ͬ�����
void CMainWindow::OnRButtonDown (UINT nFlags, CPoint point)
{
    if (m_nNextChar != OH)
        return;

    int nPos = GetRectID (point);
    if ((nPos == -1) || (m_nGameGrid[nPos] != 0))
        return;

    m_nGameGrid[nPos] = OH;
    m_nNextChar = EX;

    CClientDC dc (this);
    DrawO (&dc, nPos);
    CheckForGameOver ();
}

//���˫���߿����¿�ʼ
//dc.GetPixel (Point point)��ȡ��ǰ�����������ɫ�ж����ɫƥ��
void CMainWindow::OnLButtonDblClk (UINT nFlags, CPoint point)
{
    CClientDC dc (this);
    if (dc.GetPixel (point) == RGB (0, 0, 0))
        ResetGame ();
}

int CMainWindow::GetRectID (CPoint point)
{
    for (int i=0; i<9; i++) {
        if (m_rcSquares[i].PtInRect (point))         //�ж�����Ƿ�������ĳһ���򣬵�����������ţ�û�з���-1
            return i;                                //�˴�����һ��rect.PtInRect(Point point)���������ж�
    }
    return -1;
}

//�������̲�����Ȧ�Ͳ�
void CMainWindow::DrawBoard (CDC* pDC)
{
    //��������
    CPen pen (PS_SOLID, 16, RGB (0, 0, 0));
    CPen* pOldPen = pDC->SelectObject (&pen);

    pDC->MoveTo (120, 16);                                         //��������
    pDC->LineTo (120, 336);

    pDC->MoveTo (232, 16);
    pDC->LineTo (232, 336);

    pDC->MoveTo (16, 120);
    pDC->LineTo (336, 120);

    pDC->MoveTo (16, 232);
    pDC->LineTo (336, 232);

    //���ϲ��Ȧ
    for (int i=0; i<9; i++) {
        if (m_nGameGrid[i] == EX)
            DrawX (pDC, i);
        else if (m_nGameGrid[i] == OH)
            DrawO (pDC, i);
    }
    pDC->SelectObject (pOldPen);
}

//���溯��
void CMainWindow::DrawX (CDC* pDC, int nPos)
{
    CPen pen (PS_SOLID, 16, RGB (255, 0, 0));//��Ϊ16���صĺ��
    CPen* pOldPen = pDC->SelectObject (&pen);
    CRect rect = m_rcSquares[nPos];
    rect.DeflateRect (16, 16);               //�Ѿ���ÿ����������16��������Ϊ�����߿�
    pDC->MoveTo (rect.left, rect.top);
    pDC->LineTo (rect.right, rect.bottom);
    pDC->MoveTo (rect.left, rect.bottom);
    pDC->LineTo (rect.right, rect.top);

    pDC->SelectObject (pOldPen);
}

//��Ȧ����
void CMainWindow::DrawO (CDC* pDC, int nPos)
{
    CPen pen (PS_SOLID, 16, RGB (0, 0, 255));//��Ϊ16���صĺ��
    CPen* pOldPen = pDC->SelectObject (&pen);
    pDC->SelectStockObject (NULL_BRUSH);     //�ջ�ˢ��Ϊ�˷�ֹ������Բ�ڲ����ְ�ɫ��ס����

    CRect rect = m_rcSquares[nPos];
    rect.DeflateRect (16, 16);//�Ѿ���ÿ����������16��������ΪԲ�ı߿�
    pDC->Ellipse (rect);

    pDC->SelectObject (pOldPen);
}

//��������
void CMainWindow::Draw (CDC* pDC,int nPos)
{
    CPen pen (PS_SOLID, 16, RGB (245, 245, 245));
    CPen* pOldPen = pDC->SelectObject (&pen);
    CRect rect = m_rcSquares[nPos];
	rect.DeflateRect (8, 8); 
    InvalidateRect(&rect,TRUE);
    pDC->SelectObject (pOldPen);
}
//���Ի�ͼ
void CMainWindow::CpDraw(CDC* pDC)
{
    int grades[2][9];     
    int m,i,max=0;
    int u;
    for(m=0;m<9;m++)                            //9��λ��
    {
        grades[0][m]=0;                         //��ʼÿ��λ��˫���÷־�Ϊ0.
        grades[1][m]=0;

        if(m_nGameGrid[m]==0)                   //�����λ��û��ռ
        {  
            for(i=0;i<2;i++)                    //�ж�Ӯ�����
            {
                //��������ڿ�����ϵĻ�ʤ���� �����߻�ʤ���ʴ�
                if(ptab[m][i] && win[0][i]!=5)  //�������һ����ҿ���Ӯ�������������ϻ�û�е�������ռ��
                {
                        switch(win[0][i])       //�����
                        {
                        case 0:                 //���ֻ��0���������������
                            grades[0][m]+=1;
                            break;
                        case 1:                 //��1���������������
                            grades[0][m]+=2000;
                            break;
                        case 2:                 //��2���������������  ����Խ�� Ӯ�ÿ�����Խ�� ���мӵķ���Ҫ��������
                            grades[0][m]+=10000;
                            break;
                        }
                }
                //���������ڿո��ϵĻ�ʤ����
                if(ctab[m][i] && win[1][i]!=5)   
                {
                    switch(win[1][i])
                    {
                        case 0:
                            grades[1][m]+=1;
                            break;
                        case 1:
                            grades[1][m]+=2001;  //������������Ȩ���е�˫��ͬʱ������������һ������ʱ ���Ա�ʤ
                            break;
                        case 2:
                            grades[1][m]+=10001;
                            break;
                    }
                }
            }
            if(max==0)u=m;                      //�����û����߷� ����һ�μ�����߷�ʱ
            
            if(grades[0][m]>max){              //����9�����������߷� �����ǰλ�÷�����֮ǰ˫����߷ִ�
                max=grades[0][m];              //��ô��߷ֵ��ڵ�ǰ��
                u=m;                           //��ס��߷ֵ�λ��
            }
            else if(grades[0][m]==max){        //�����ҵ�ǰλ�÷�����֮ǰ��߷����
                if(grades[1][m]>grades[1][u])u=m;//��������ڸõ�������ڵ��������֮ǰλ�õķ��� ��ô��߷�λ�û�����ǰ Ҳ����˵ �Ե��Է�����Ϊ���ȼ�
            }

            if(grades[1][m]>max){              //������Է����ڸõ��������֮ǰ˫����߷�
                max=grades[1][m];              
                u=m;    
            }
            else if(grades[1][m]==max){
                if(grades[0][m]>grades[0][u])u=m;
            }
        }
    }
    //������²��ı���һ�����״̬
	bool ok=false;Pos2=u;
	for (i=0;i<9;i++)
	{
		if (m_nGameGrid[i]==OH)
		{
			Pos1=i;
		    if (can()) {ok=true;break;}
		}
	}
	if (!ok)
	{
	for (int i=0;i<9;i++){
		if (m_nGameGrid[i]==OH){
			Pos1=i;
			int direct[4];
   	        direct[0]=Pos1-3;direct[1]=Pos1+3;
            if (Pos1%3==0) direct[2]=direct[3]=Pos1+1;
	        else if (Pos1%3==1) direct[2]=Pos1-1,direct[3]=Pos1+1;
            else direct[2]=direct[3]=Pos1-1;
			if (direct[0]<0) direct[0]=direct[2];
			if (direct[1]>8) direct[1]=direct[2];
		    for (int j=0;j<4;j++)
			{
                if (m_nGameGrid[direct[j]]==0) 
				{
					ok=true;Pos2=direct[j];
				}
			}
		}
		if (ok) break;
	}
    }
	if (ok)
	{ 
    m_nGameGrid[Pos2]=OH;
	m_nGameGrid[Pos1]=0;
    m_nNextChar = EX;
    DrawO(pDC,Pos2);
	Draw(pDC,Pos1);
	Pos1=Pos2=0;
	}
	else
	{
    m_nNextChar = EX; 
	CString string = _T ("Computer can not move any chesspieces!");
	MessageBox (string, _T ("Please continue!"), MB_ICONEXCLAMATION | MB_OK);
	}
}
//��Ӧʤ�������ĺ���
bool CMainWindow::CheckForGameOver ()
{
    int nWinner;

    //ͨ������IsWinner ()������ȡ˭��ʤ������MessageBox���ʤ����Ϣ����ӦOK���ؿ�һ��
    //==Message(CString,_T(����),����)
    if (nWinner = IsWinner ()) {
        CString string = (nWinner == EX) ?                                //�ʺű��ʽ
            _T ("X wins!") : _T ("O wins!");
        MessageBox (string, _T ("Game Over"), MB_ICONEXCLAMATION | MB_OK);
        ResetGame ();
        return 1;
    }
    return 0;
}
//�ж���ӮEX��ʤ��OH��ʤ��0û��ʤ
int CMainWindow::IsWinner ()
{
    //�þ�̬����洢��ʤ���
    static int nPattern[2][3] = {
        0, 4, 8,
        2, 4, 6
    };

    for (int i=0; i<2; i++) {
        if ((m_nGameGrid[nPattern[i][0]] == EX) &&
            (m_nGameGrid[nPattern[i][1]] == EX) &&
            (m_nGameGrid[nPattern[i][2]] == EX))
            return EX;

        if ((m_nGameGrid[nPattern[i][0]] == OH) &&
            (m_nGameGrid[nPattern[i][1]] == OH) &&
            (m_nGameGrid[nPattern[i][2]] == OH))
            return OH;
    }
    return 0;
}
//��ʼ����Ϸ
void CMainWindow::InitGame()
{
    int i;
    int count=0;
	Pos1=Pos2=0;
    //�趨����������ڸ�����ʤ����е�������
    for(i=0;i<2;i++)
    {
        win[0][i]=0;
        win[1][i]=0;
    }
    //��ʼ������״̬
    ::ZeroMemory (m_nGameGrid,9*sizeof(int));
    memset(ctab,0,sizeof(ctab));
    memset(ptab,0,sizeof(ptab));
    m_nGameGrid[0]=m_nGameGrid[1]=m_nGameGrid[2]=2;
    m_nGameGrid[6]=m_nGameGrid[7]=m_nGameGrid[8]=1;
    //�趨�Խ��߷����ϵĻ�ʤ���
    
    for(i=0;i<=8;i+=4){
        ptab[i][count]=true;
        ctab[i][count]=true;
    }count++;
	for(i=2;i<=6;i+=2){
        ptab[i][count]=true;
        ctab[i][count]=true;
    }
    srand(unsigned(time(NULL)));

    m_nNextChar = EX;//�������
}
//���¿�ʼ��ʼ��
void CMainWindow::ResetGame ()
{
    InitGame();
    Invalidate ();   //ʹ�ؼ�������ͼ����Ч�������ػ�ؼ�
}
bool CMainWindow::can()
{
	int direct[4];
	direct[0]=Pos1-3;direct[1]=Pos1+3;
    if (Pos1%3==0) direct[2]=direct[3]=Pos1+1;
	else if (Pos1%3==1) direct[2]=Pos1-1,direct[3]=Pos1+1;
    else direct[2]=direct[3]=Pos1-1;
	if (direct[0]<0) direct[0]=direct[2];
	if (direct[1]>8) direct[1]=direct[2];
	for (int i=0;i<4;i++)
		if (direct[i]==Pos2) return true;
	return false;
}
bool CMainWindow::cannotmove()
{
	int direct[4];
	direct[0]=Pos1-3;direct[1]=Pos1+3;
    if (Pos1%3==0) direct[2]=direct[3]=Pos1+1;
	else if (Pos1%3==1) direct[2]=Pos1-1,direct[3]=Pos1+1;
    else direct[2]=direct[3]=Pos1-1;
	if (direct[0]<0) direct[0]=direct[2];
	if (direct[1]>8) direct[1]=direct[2];
	for (int i=0;i<4;i++)
		if (m_nGameGrid[direct[i]]==0) return false;
	return true;
}
