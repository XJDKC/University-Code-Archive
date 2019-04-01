#define EX 1            //该点表示左鼠标
#define OH 2            //该点表示右鼠标
#include "resource.h"
class CMyApp : public CWinApp
{
public:
    virtual BOOL InitInstance ();
};

class CMainWindow : public CWnd       //不是继承CFrameWnd 因此需要在CMainWindow()自己定义窗口类了
{
protected:
    static const CRect m_rcSquares[9];    // Grid coordinates
    int m_nGameGrid[9];            // 9个格子的状态是否被下0没下；1左下了；2右下了
    int m_nNextChar;            // 下一个鼠标状态左or右 (EX or OH)
    bool ptab[9][8];            //玩家的获胜的状态表
    bool ctab[9][8];            //电脑的获胜的状态表
    int win[2][8];              //每种状态表里的棋子数
    int Pos1;
	int Pos2;                          
    int GetRectID (CPoint point);
    void DrawBoard (CDC* pDC);
    void DrawX (CDC* pDC, int nPos);
    void DrawO (CDC* pDC, int nPos);
	void Draw  (CDC* pDC, int nPos);
    void CpDraw(CDC* pDC);
    void InitGame();
    void out();
    void ResetGame ();
    bool CheckForGameOver ();
	bool cannotmove();
	bool can();
    int IsWinner ();

public:
    CMainWindow ();

protected:
    virtual void PostNcDestroy ();//在程序终止之前销毁CMainWindow对象

    afx_msg void OnPaint ();
    afx_msg void OnLButtonDown (UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk (UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown (UINT nFlags, CPoint point);

    DECLARE_MESSAGE_MAP ()
};

