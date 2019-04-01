#define EX 1            //�õ��ʾ�����
#define OH 2            //�õ��ʾ�����
#include "resource.h"
class CMyApp : public CWinApp
{
public:
    virtual BOOL InitInstance ();
};

class CMainWindow : public CWnd       //���Ǽ̳�CFrameWnd �����Ҫ��CMainWindow()�Լ����崰������
{
protected:
    static const CRect m_rcSquares[9];    // Grid coordinates
    int m_nGameGrid[9];            // 9�����ӵ�״̬�Ƿ���0û�£�1�����ˣ�2������
    int m_nNextChar;            // ��һ�����״̬��or�� (EX or OH)
    bool ptab[9][8];            //��ҵĻ�ʤ��״̬��
    bool ctab[9][8];            //���ԵĻ�ʤ��״̬��
    int win[2][8];              //ÿ��״̬�����������
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
    virtual void PostNcDestroy ();//�ڳ�����ֹ֮ǰ����CMainWindow����

    afx_msg void OnPaint ();
    afx_msg void OnLButtonDown (UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk (UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown (UINT nFlags, CPoint point);

    DECLARE_MESSAGE_MAP ()
};

