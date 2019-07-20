// LineWnd.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "devmfc.h"
#include "LineWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLineWnd

CLineWnd::CLineWnd()
{
	m_pOldBmp = NULL;
	m_nOldIndex = -1;
}

CLineWnd::~CLineWnd()
{
}


BEGIN_MESSAGE_MAP(CLineWnd, CWnd)
	//{{AFX_MSG_MAP(CLineWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLineWnd メッセージ ハンドラ

void CLineWnd::DrawLineNo(CEdit *pEdit){
	if(!::IsWindow(m_hWnd)){
		return;
	}
	CPoint pos = pEdit->GetCaretPos();
	int nPos = pEdit->CharFromPos(pos);
	int nIndex = HIWORD(nPos);
	if(m_nOldIndex == nIndex){
		return;
	}
	m_nOldIndex = nIndex;

	SetRedraw(FALSE);

	CDC *pDC = GetDC();
	CString strLine;
	CRect drawRect;
	CRect drawAreaRect;
	CRect rect;

	CFont *pNowFont	= GetFont();
	CFont objFont;
	LOGFONT lFont;
	memset(&lFont, 0, sizeof(LOGFONT));
	CFont *pFont = NULL;
	if(pNowFont){
		pNowFont->GetLogFont(&lFont);
//		lFont.lfWeight= 8;
		objFont.CreateFontIndirect(&lFont);
		pFont = pDC->SelectObject(&objFont);
	}
	
/*
	SetFont(&m_objFont);
	pDC->SelectObject(&m_objFont);
*/
	int nLine		= pEdit->GetFirstVisibleLine();
	int nEnd		= pEdit->GetLineCount();
	CSize size		= pDC->GetTextExtent("0", 1);
	int nHeight		= size.cy;
	
	pEdit->GetClientRect(rect);
	drawRect		= rect;
	drawRect.right	= drawRect.left + m_nLeftMargin ;
	drawAreaRect	= drawRect;

	COLORREF crBack = GetSysColor(COLOR_MENU);
	pDC->FillSolidRect(drawAreaRect, crBack);

	pDC->SetBkMode(TRANSPARENT);

	drawRect.right--;
	drawRect.top++;
	drawRect.bottom = drawRect.top + nHeight;
	while((nLine < nEnd) && (nHeight < rect.Height())){
		if(nIndex == nLine){
			CPoint linePos[2];
			linePos[0].x = drawRect.left;
			linePos[1].x = drawRect.right;
			linePos[0].y = drawRect.bottom - 1;
			linePos[1].y = drawRect.bottom - 1;

			pDC->Polyline(linePos, 2);
			pDC->SetTextColor(GetSysColor(COLOR_MENUTEXT));
		}else{
			pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
		}

		strLine.Format("%d", nLine);
		pDC->DrawText(strLine, drawRect, DT_RIGHT | DT_NOCLIP);
		drawRect.top = drawRect.bottom;
		drawRect.bottom = drawRect.top + nHeight;
		nLine++;
	}

	UpdateWindow();
	SetRedraw(TRUE);
	InvalidateRect(NULL);
	pEdit->InvalidateRect(drawAreaRect);
}

void CLineWnd::SetMarginFromLine(CEdit *pEdit){
	if(!::IsWindow(m_hWnd)){
		return;
	}
	CString strLine;
	int nLine = pEdit->GetLineCount();
	strLine.Format("%d", nLine + 1);
	while(strLine.GetLength() < 4){
		strLine = "0" + strLine;
	}
	CDC *pDC = GetDC();
	CSize size = pDC->GetTextExtent(strLine);
	m_nLeftMargin = size.cx + 2;
	DWORD dwMargin = pEdit->GetMargins();
//	int nNowMargin = LOWORD(dwMargin);
	if(LOWORD(dwMargin) != m_nLeftMargin){
		pEdit->SetMargins(m_nLeftMargin, 2);
	}
}

void CLineWnd::OnPaint(){
	CPaintDC dc(this); // 描画用のデバイス コンテキスト
	dc.BitBlt(0, 0, 
			  m_oldRect.Width(), m_oldRect.Height(), 
			  &m_objBackDC, 0, 0, SRCCOPY);

}

void CLineWnd::CreateBuffer(){
	CEdit *pEdit = (CEdit*)GetParent();
	CRect rect;
	pEdit->GetClientRect(rect);
	rect.right	= rect.left + m_nLeftMargin ;

	int nOldHeight = m_oldRect.Height();
	int nNowHeight = rect.Height();
	if(nOldHeight != nNowHeight){
		if(m_pOldBmp){
			ReleaseDC(&m_objBackDC);
			m_objBackBmp.DeleteObject();
			//m_pOldBmp = NULL;
		}

		if(!m_pOldBmp){
			HDC hDC = ::GetDC(NULL);
			CDC objDC;
			objDC.Attach(hDC);
			m_objBackDC.CreateCompatibleDC(&objDC);
			objDC.Detach();
			//CDC *pDC = GetDC();
			//m_objBackDC.CreateCompatibleDC(pDC);
		}

		if(m_objBackDC.m_hDC){
			m_objBackBmp.CreateCompatibleBitmap(&m_objBackDC, rect.Width(), rect.Height());
			m_pOldBmp = (CBitmap*)m_objBackDC.SelectObject(m_objBackBmp);

			COLORREF crBack = GetSysColor(COLOR_MENU);
			m_objBackDC.FillSolidRect(rect, crBack);
			POINT pts[2];
			pts[0].x = rect.right-1;
			pts[1].x = rect.right-1;
			pts[0].y = rect.top;
			pts[1].y = rect.bottom;
			m_objBackDC.Polyline(pts, 2);
		}
	}
	m_oldRect = rect;
	InvalidateRect(NULL);
}

BOOL CLineWnd::OnEraseBkgnd(CDC* pDC) {
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	return FALSE;
//	return CWnd::OnEraseBkgnd(pDC);
}
