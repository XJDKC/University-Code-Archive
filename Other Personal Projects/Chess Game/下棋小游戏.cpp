#include <afxwin.h>                                                         //包含CRect 类
#include <stdafx.h>  
#include "下棋小游戏.h"
#include <fstream>
#include <iostream>
#include<iomanip>
using namespace std;
CMyApp myApp;                                                               //调用一个CMyApp的类 含有InitInstance 虚函数用来初始化窗口

BOOL CMyApp::InitInstance ()                                                //初始化窗口 宏定义
{                                                                           
    m_pMainWnd = new CMainWindow;                                           //创建一个CMainWindow的类并用前面指针操作
    m_pMainWnd->ShowWindow (m_nCmdShow);                                    //显示窗口
    m_pMainWnd->UpdateWindow ();                                            //创新窗口
    return TRUE;                                                            //创建成功
}

BEGIN_MESSAGE_MAP (CMainWindow, CWnd)                                       //宏开始的消息映射
    ON_WM_PAINT ()                                                          //绘图信号
    ON_WM_LBUTTONDOWN ()                                                    //鼠标左键按下
    ON_WM_LBUTTONDBLCLK ()                                                  //鼠标左键双击
    ON_WM_RBUTTONDOWN ()                                                    //鼠标右键按下
END_MESSAGE_MAP ()                                                          //停止

const CRect CMainWindow::m_rcSquares[9] = {                                 //划分9个矩形区域 用来判定鼠标是否点进某一区域
    CRect ( 16,  16, 112, 112),                                             //左上角坐标 和右下角坐标确定矩形下面依次类推
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
    InitGame();                                                                 //初始化游戏
    CString strWndClass = AfxRegisterWndClass (                                 //注册一个 WNDCLASS 窗口类.
        CS_DBLCLKS,                                                             // Class style（有双击时间发生的窗口类型）
        AfxGetApp ()->LoadStandardCursor (IDC_ARROW),                           // Class cursor（加载一个系统光标）
        (HBRUSH) (COLOR_3DFACE + 1),                                            // Background brush（每次：：BeginPaint时用它清空客户区）；COLOR_3DFACE+1是指定窗口具有与按钮对话框一致的背景色和其他一些3D属性；默认为灰亮色
        AfxGetApp ()->LoadStandardIcon (IDI_WINLOGO)                            // Class icon（加载系统图标）
    );
    //调用CWnd::CreateEx()创建主窗口
    CreateEx (0, strWndClass, _T ("井字棋"),                                    //第一个参数表示0个或是多个WS_EX标志组合；2：AfxRegisterWndClass（）返回的WNDCLASS名称；3、标题；//4、窗口样式
        WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,               //WS_THICKFRAME窗口可调大小属性（这里不用）
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,             //初始位置和大小，这里用CW_USEDEFAULT让Windows拾取窗口和大小
        NULL, NULL);                                                            //处理窗口位置和尺寸
    CRect rect (0, 0, 352, 352);                                                //理想客户区窗口矩形形状 让棋盘与窗口件留16的间隙
    CalcWindowRect (&rect);                                                     //根据分辨率、菜单...计算窗口矩形大小（必须在窗口创建后调用）
    SetWindowPos (NULL, 0, 0, rect.Width (), rect.Height (),
    SWP_NOZORDER | SWP_NOMOVE | SWP_NOREDRAW);
}

void CMainWindow::PostNcDestroy ()                                              //在程序结束之前销毁创建的CMainWindow对象
{
    delete this;
}

void CMainWindow::OnPaint ()                                                    //OnPaint()响应每次重绘棋盘
{
    CPaintDC dc (this);
    DrawBoard (&dc);    
}

void CMainWindow::OnLButtonDown (UINT nFlags, CPoint point)                     //单击鼠标左键响应
{
    CClientDC dc (this);                                                    
    if (m_nNextChar != EX){                                                     //如果不该左键响应（即不该左键下，返回）
        return ;
    }
	if (Pos1==0)
    {
		Pos1 = GetRectID (point);   
        if ((Pos1 == -1) || (m_nGameGrid[Pos1] != 1))                           //-1表示未点上
        {
			Pos1=0;
		}
		if (cannotmove()){ Pos1=0;}
		return ;
    }
    else 
	{
		Pos2 = GetRectID (point); 
        if ((Pos2 == -1) || (m_nGameGrid[Pos2] != 0)||!can())                   //-1表示未点上
        {
			Pos2=0;return ;
		}
	}
    m_nGameGrid[Pos1] = 0;                                                      //标记已下并改变下一个点击状态
	m_nGameGrid[Pos2] = EX;
    m_nNextChar = OH;
    Draw (&dc, Pos1);                                                           //画上图并判断游戏是否结束
    DrawX (&dc, Pos2);
    if(CheckForGameOver ())return;                                              //后续改变胜利表和各人、机各胜利组合的棋子数
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
    //电脑下棋
    CpDraw(&dc);
	Pos1=Pos2=0;
    if(CheckForGameOver ())  return;
}

//单击鼠标右键响应（同左键）
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

//左键双击边框重新开始
//dc.GetPixel (Point point)获取当前光标下像素颜色判断与黑色匹配
void CMainWindow::OnLButtonDblClk (UINT nFlags, CPoint point)
{
    CClientDC dc (this);
    if (dc.GetPixel (point) == RGB (0, 0, 0))
        ResetGame ();
}

int CMainWindow::GetRectID (CPoint point)
{
    for (int i=0; i<9; i++) {
        if (m_rcSquares[i].PtInRect (point))         //判定鼠标是否点进矩形某一区域，点进返回区域编号，没有返回-1
            return i;                                //此处用了一个rect.PtInRect(Point point)函数帮助判定
    }
    return -1;
}

//画上棋盘并画上圈和叉
void CMainWindow::DrawBoard (CDC* pDC)
{
    //画上棋盘
    CPen pen (PS_SOLID, 16, RGB (0, 0, 0));
    CPen* pOldPen = pDC->SelectObject (&pen);

    pDC->MoveTo (120, 16);                                         //画四条线
    pDC->LineTo (120, 336);

    pDC->MoveTo (232, 16);
    pDC->LineTo (232, 336);

    pDC->MoveTo (16, 120);
    pDC->LineTo (336, 120);

    pDC->MoveTo (16, 232);
    pDC->LineTo (336, 232);

    //画上叉和圈
    for (int i=0; i<9; i++) {
        if (m_nGameGrid[i] == EX)
            DrawX (pDC, i);
        else if (m_nGameGrid[i] == OH)
            DrawO (pDC, i);
    }
    pDC->SelectObject (pOldPen);
}

//画叉函数
void CMainWindow::DrawX (CDC* pDC, int nPos)
{
    CPen pen (PS_SOLID, 16, RGB (255, 0, 0));//宽为16像素的红笔
    CPen* pOldPen = pDC->SelectObject (&pen);
    CRect rect = m_rcSquares[nPos];
    rect.DeflateRect (16, 16);               //把矩形每个方向都缩进16个像素作为线条边框
    pDC->MoveTo (rect.left, rect.top);
    pDC->LineTo (rect.right, rect.bottom);
    pDC->MoveTo (rect.left, rect.bottom);
    pDC->LineTo (rect.right, rect.top);

    pDC->SelectObject (pOldPen);
}

//画圈函数
void CMainWindow::DrawO (CDC* pDC, int nPos)
{
    CPen pen (PS_SOLID, 16, RGB (0, 0, 255));//宽为16像素的红笔
    CPen* pOldPen = pDC->SelectObject (&pen);
    pDC->SelectStockObject (NULL_BRUSH);     //空画刷是为了防止画出的圆内部出现白色遮住背景

    CRect rect = m_rcSquares[nPos];
    rect.DeflateRect (16, 16);//把矩形每个方向都缩进16个像素作为圆的边框
    pDC->Ellipse (rect);

    pDC->SelectObject (pOldPen);
}

//擦除函数
void CMainWindow::Draw (CDC* pDC,int nPos)
{
    CPen pen (PS_SOLID, 16, RGB (245, 245, 245));
    CPen* pOldPen = pDC->SelectObject (&pen);
    CRect rect = m_rcSquares[nPos];
	rect.DeflateRect (8, 8); 
    InvalidateRect(&rect,TRUE);
    pDC->SelectObject (pOldPen);
}
//电脑画图
void CMainWindow::CpDraw(CDC* pDC)
{
    int grades[2][9];     
    int m,i,max=0;
    int u;
    for(m=0;m<9;m++)                            //9个位置
    {
        grades[0][m]=0;                         //开始每个位置双方得分均为0.
        grades[1][m]=0;

        if(m_nGameGrid[m]==0)                   //如果该位置没人占
        {  
            for(i=0;i<2;i++)                    //判断赢的组合
            {
                //计算玩家在空棋格上的获胜分数 分数高获胜几率大
                if(ptab[m][i] && win[0][i]!=5)  //如果下这一点玩家可以赢而且在这条线上还没有电脑棋子占领
                {
                        switch(win[0][i])       //分情况
                        {
                        case 0:                 //如果只有0个玩家棋子在上面
                            grades[0][m]+=1;
                            break;
                        case 1:                 //有1个玩家棋子在上面
                            grades[0][m]+=2000;
                            break;
                        case 2:                 //有2个玩家棋子在上面  棋子越多 赢得可能性越大 所有加的分数要分数量级
                            grades[0][m]+=10000;
                            break;
                        }
                }
                //计算计算机在空格上的获胜分数
                if(ctab[m][i] && win[1][i]!=5)   
                {
                    switch(win[1][i])
                    {
                        case 0:
                            grades[1][m]+=1;
                            break;
                        case 1:
                            grades[1][m]+=2001;  //电脑走有优先权所有当双方同时有两颗棋子在一条线上时 电脑必胜
                            break;
                        case 2:
                            grades[1][m]+=10001;
                            break;
                    }
                }
            }
            if(max==0)u=m;                      //如果还没有最高分 即第一次计算最高分时
            
            if(grades[0][m]>max){              //计算9个格子玩家最高分 如果当前位置分数比之前双方最高分大
                max=grades[0][m];              //那么最高分等于当前分
                u=m;                           //记住最高分的位置
            }
            else if(grades[0][m]==max){        //如果玩家当前位置分数和之前最高分相等
                if(grades[1][m]>grades[1][u])u=m;//如果电脑在该点分数大于电脑在玩家之前位置的分数 那么最高分位置换到当前 也就是说 以电脑分数高为优先级
            }

            if(grades[1][m]>max){              //如果电脑分数在该点分数大于之前双方最高分
                max=grades[1][m];              
                u=m;    
            }
            else if(grades[1][m]==max){
                if(grades[0][m]>grades[0][u])u=m;
            }
        }
    }
    //标记已下并改变下一个点击状态
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
//响应胜利结束的函数
bool CMainWindow::CheckForGameOver ()
{
    int nWinner;

    //通过调用IsWinner ()函数获取谁获胜；并用MessageBox输出胜利消息；响应OK后重开一局
    //==Message(CString,_T(标题),类型)
    if (nWinner = IsWinner ()) {
        CString string = (nWinner == EX) ?                                //问号表达式
            _T ("X wins!") : _T ("O wins!");
        MessageBox (string, _T ("Game Over"), MB_ICONEXCLAMATION | MB_OK);
        ResetGame ();
        return 1;
    }
    return 0;
}
//判断输赢EX左胜；OH右胜；0没有胜
int CMainWindow::IsWinner ()
{
    //用静态数组存储获胜组合
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
//初始化游戏
void CMainWindow::InitGame()
{
    int i;
    int count=0;
	Pos1=Pos2=0;
    //设定玩家与计算机在各个获胜组合中的棋子数
    for(i=0;i<2;i++)
    {
        win[0][i]=0;
        win[1][i]=0;
    }
    //初始化棋盘状态
    ::ZeroMemory (m_nGameGrid,9*sizeof(int));
    memset(ctab,0,sizeof(ctab));
    memset(ptab,0,sizeof(ptab));
    m_nGameGrid[0]=m_nGameGrid[1]=m_nGameGrid[2]=2;
    m_nGameGrid[6]=m_nGameGrid[7]=m_nGameGrid[8]=1;
    //设定对角线方向上的获胜组合
    
    for(i=0;i<=8;i+=4){
        ptab[i][count]=true;
        ctab[i][count]=true;
    }count++;
	for(i=2;i<=6;i+=2){
        ptab[i][count]=true;
        ctab[i][count]=true;
    }
    srand(unsigned(time(NULL)));

    m_nNextChar = EX;//玩家先走
}
//重新开始初始化
void CMainWindow::ResetGame ()
{
    InitGame();
    Invalidate ();   //使控件的整个图面无效并导致重绘控件
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
