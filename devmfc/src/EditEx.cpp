// SQLEdit.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "EditEx.h"
#include "DebugSupport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditEx

/**
 *コンストラクタ
 */
CEditEx::CEditEx(){
	m_bModify = FALSE;
	m_pOldBmp = NULL;
	m_bLineShow = FALSE;
	m_nOldIndex = -1;
	m_pBackDC = NULL;
	m_pBackBmp = NULL;
	m_nOldScPos = 0;
	m_nLeftMargin = 0;
	m_nRetCnt = 0;
}

/**
 *デストラクタ
 */
CEditEx::~CEditEx(){
	DestroyWindow();
	if(m_pBackDC){
		delete m_pBackDC;
	}
	if(m_pBackBmp){
		delete m_pBackBmp;
	}
}


BEGIN_MESSAGE_MAP(CEditEx, CEdit)
	//{{AFX_MSG_MAP(CEditEx)
	ON_WM_CREATE()
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_CONTROL_REFLECT(EN_VSCROLL, OnVscroll)
	ON_WM_SHOWWINDOW()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditEx メッセージ ハンドラ

int CEditEx::OnCreate(LPCREATESTRUCT lpCreateStruct){
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	memset(&m_lFont, 0, sizeof(LOGFONT));
	CFont *pFont = GetFont();
	if(pFont){
		pFont->GetLogFont(&m_lFont);
		m_lFont.lfWeight= 8;
		m_objFont.CreateFontIndirect(&m_lFont);
		SetFont(&m_objFont);
	}else{
		m_lFont.lfHeight = 8;
		strcpy(m_lFont.lfFaceName, "ＭＳ ゴシック");
		m_objFont.CreateFontIndirect(&m_lFont);
		SetFont(&m_objFont);
	}

	DrawLineNo();

	return 0;
}

void CEditEx::OnChange(){
	m_bModify = TRUE;

	DrawLineNo();

}

void CEditEx::OnDestroy() {
	TRACE("CEditEx::OnDestroy\n");
	if(m_pBackBmp){
		if(m_pBackDC && m_pOldBmp){
			m_pBackDC->SelectObject(m_pOldBmp);
		}
		m_pOldBmp = NULL;
		m_pBackBmp->DeleteObject();
		delete m_pBackBmp;
		m_pBackBmp = NULL;
	}
	if(m_pBackDC){
		ReleaseDC(m_pBackDC);
		delete m_pBackDC;
		m_pBackDC = NULL;
	}
	CEdit::OnDestroy();
	
}

void CEditEx::OnPaint() {
//	CPaintDC dc(this); // 描画用のデバイス コンテキスト
	CClientDC dc(this);

	Default();

	//ここでCDC作り変えてみたいなぁ(白黒の
	int nPlanes = dc.GetDeviceCaps(PLANES);
	if(nPlanes == 1){
	}

	CRect rect;
	GetClientRect(rect);
	rect.right  = rect.left + m_nLeftMargin + 2;
	dc.BitBlt(rect.left + 1, rect.top + 1, 
			  rect.Width() - 2, rect.Height() - 2, 
			  m_pBackDC, 0, 0, SRCCOPY);
	ReleaseDC(&dc);
}

void CEditEx::SetMarginFromLine(){
	CString strLine = "";
	CString strEnd;
	int nLine = GetLineCount();
	int nLen = strLine.GetLength();
	int nMax = nLen > 4 ? nLen : 4;
	while(strLine.GetLength() < nMax){
		strLine += "0";
	}
	CDC *pDC = GetDC();
	CSize size = pDC->GetTextExtent(strLine);
	m_nLeftMargin = size.cx + 2;
	DWORD dwMargin = GetMargins();
	int nNowMargin = LOWORD(dwMargin);
	TRACE("%d %d\n", nNowMargin, m_nLeftMargin);
	if(nNowMargin != m_nLeftMargin){
		SetMargins(m_nLeftMargin, 2);
		CreateBackBuffer();
	}
	ReleaseDC(pDC);
}

void CEditEx::DrawLineNo(){
	if(!m_bLineShow){
		SetMargins(2, 2);
		return;
	}else{
		SetMarginFromLine();
		//CreateBackBuffer();
	}
	
	if(!m_pBackDC){
		return;
	}

	CString strLine;
	CRect drawRect;
	CRect drawAreaRect;
	CRect rect;
	
	GetClientRect(rect);
	drawRect		= rect;
	drawRect.right	= drawRect.left + m_nLeftMargin ;
	drawAreaRect	= drawRect;

	CPoint pos = GetCaretPos();
	int nPos = CharFromPos(pos);
	int nIndex = HIWORD(nPos);
	int sbPos = GetScrollPos(SB_VERT);
	//行数をカウントする
	CString strText;
	GetWindowText(strText);
	int retPos = 0;
	int nRetCnt = GetLineCount();
	if((nIndex == m_nOldIndex) && (m_nOldScPos == sbPos) && (nRetCnt == m_nRetCnt)){
		InvalidateRect(drawAreaRect);
		return;
	}
	m_nOldScPos = sbPos;
	m_nOldIndex = nIndex;
	m_nRetCnt = nRetCnt;
	CFont *pFont;
	LOGFONT lFont;
	GetFont()->GetLogFont(&lFont);
	CFont* pOldFont = NULL;

	pFont = new CFont();
	if(pFont->CreateFontIndirect(&lFont)){
		pOldFont = m_pBackDC->SelectObject(pFont);
		if(!pOldFont){
			DWORD dwErr = ::GetLastError();
			char szMsg[1024];
			memset(szMsg, 0, 1024);
			::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwErr, 0, szMsg, 1024, NULL); 
			TRACE(szMsg);
		}
	}

	int nLine		= GetFirstVisibleLine();
	int nEnd		= GetLineCount();
	CSize size		= m_pBackDC->GetTextExtent("0", 1);
	int nHeight		= size.cy;
	CString strEnd;
	strEnd.Format("%d", nEnd);
	strLine.Format("%d", nLine + 1);
	int nMax = strEnd.GetLength() > 4 ? strEnd.GetLength() : 4;

	COLORREF crBack = GetSysColor(COLOR_MENU);
	m_pBackDC->FillSolidRect(drawAreaRect, crBack);
	POINT pts[2];
	pts[0].x = drawAreaRect.right-1;
	pts[1].x = drawAreaRect.right-1;
	pts[0].y = drawAreaRect.top;
	pts[1].y = drawAreaRect.bottom;
	m_pBackDC->Polyline(pts, 2);

	m_pBackDC->SetBkMode(TRANSPARENT);

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

			m_pBackDC->FillSolidRect(drawRect, GetSysColor(COLOR_HIGHLIGHT));
			m_pBackDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
		}else{
			m_pBackDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
		}
		
		strLine.Format("%d", nLine + 1);
		while(strLine.GetLength() < nMax){
			strLine = "0" + strLine;
		}

		m_pBackDC->DrawText(strLine, drawRect, DT_RIGHT | DT_NOCLIP | DT_VCENTER);

		drawRect.top = drawRect.bottom;
		drawRect.bottom = drawRect.top + nHeight;
		nLine++;
	}

	InvalidateRect(drawAreaRect);
	if(pOldFont){
		m_pBackDC->SelectObject(pOldFont);
	}
	pFont->DeleteObject();
	delete pFont;
}

BOOL CEditEx::CreateBackBuffer(){
		TRACE("CreateBackBuffer\n");
	if(!m_bLineShow){
		return TRUE;
	}

	if(!::IsWindow(m_hWnd)){
		return FALSE;
	}
	CRect rect;
	GetClientRect(rect);
	rect.right = rect.left + m_nLeftMargin;

	int nOldHeight = m_oldRect.Height();
	int nNowHeight = rect.Height();
	int nOldWidth  = m_oldRect.Width();
	int nNowWidth  = rect.Width();
	if((nOldHeight != nNowHeight) || (nOldWidth != nNowWidth)){
		if(m_pBackBmp){
			if(m_pOldBmp){
				m_pBackDC->SelectObject(m_pOldBmp);
			}
			m_pBackBmp->DeleteObject();
			delete m_pBackBmp;
			m_pBackBmp = NULL;
			m_nOldIndex = -1;
		}
		if(m_pBackDC){
			ReleaseDC(m_pBackDC);
			delete m_pBackDC;
			m_pBackDC = NULL;
		}

		CDC *pDC = GetDC();
		if(!m_pBackDC){
			m_pBackDC = new CDC();
			m_pBackDC->CreateCompatibleDC(pDC);
		}
		if(!m_pBackBmp){
			m_pBackBmp = new CBitmap();
			m_pBackBmp->CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
		}

		m_pOldBmp = (CBitmap*)m_pBackDC->SelectObject(m_pBackBmp);
		m_oldRect = rect;

		COLORREF crBack = GetSysColor(COLOR_MENU);
		m_pBackDC->FillSolidRect(rect, crBack);
		POINT pts[2];
		pts[0].x = rect.right-1;
		pts[1].x = rect.right-1;
		pts[0].y = rect.top;
		pts[1].y = rect.bottom;
		m_pBackDC->Polyline(pts, 2);
		ReleaseDC(pDC);
	}
	return TRUE;
}

void CEditEx::OnSize(UINT nType, int cx, int cy){
	CEdit::OnSize(nType, cx, cy);
	if(::IsWindowVisible(m_hWnd)){
		CreateBackBuffer();
		DrawLineNo();
	}
	InvalidateRect(NULL);
}

void CEditEx::OnVscroll(){
	DrawLineNo();
}

void CEditEx::OnShowWindow(BOOL bShow, UINT nStatus){
	CEdit::OnShowWindow(bShow, nStatus);

	DrawLineNo();	
	SetActiveWindow();
	SetFocus();
}

void CEditEx::OnMouseMove(UINT nFlags, CPoint point) {
	switch(nFlags){
	case MK_LBUTTON :
		DrawLineNo();	
		break;
	}
	CEdit::OnMouseMove(nFlags, point);
}

/**
 * 行番号を表示するかしないかの設定を行ないます。
 * @param bShow 行番号を表示する場合はTRUEを設定します。
 */
void CEditEx::SetLineShow(BOOL bShow){
	m_bLineShow = bShow;

}

//DEL void CEditEx::SetSel( DWORD dwSelection, BOOL bNoScroll){
//DEL 	CEdit::SetSel(dwSelection, bNoScroll);
//DEL 	DrawLineNo();	
//DEL }
//DEL void CEditEx::SetSel( int nStartChar, int nEndChar, BOOL bNoScroll){
//DEL 	CEdit::SetSel(nStartChar, nEndChar, bNoScroll);
//DEL 	DrawLineNo();	
//DEL }


void CEditEx::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
	DrawLineNo();
}

void CEditEx::OnLButtonDown(UINT nFlags, CPoint point){
	CEdit::OnLButtonDown(nFlags, point);
	DrawLineNo();
}

void CEditEx::OnLButtonUp(UINT nFlags, CPoint point){
	CEdit::OnLButtonUp(nFlags, point);
	DrawLineNo();
}

/**
 * フォントを設定します
 * @param pFont フォント情報をもつ CFontのポインタ
 * @param bRedraw 再描画を行なう場合はTRUEを設定します。
 */

void CEditEx::SetFont(CFont *pFont, BOOL bRedraw){
	if(::IsWindow(m_hWnd)){
		memset(&m_lFont, 0, sizeof(LOGFONT));
		if(pFont->GetLogFont(&m_lFont)){
			m_objFont.DeleteObject();
			m_objFont.CreateFontIndirect(&m_lFont);
			CEdit::SetFont(&m_objFont, bRedraw);
			CreateBackBuffer();
			DrawLineNo();
		}
	}
}

BOOL CEditEx::PreCreateWindow(CREATESTRUCT& cs){
	cs.style |= WS_CLIPCHILDREN;
	return CEdit::PreCreateWindow(cs);
}

LRESULT CEditEx::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam){
	if(message == EM_SETSEL){
		DrawLineNo();
	}
	return CEdit::DefWindowProc(message, wParam, lParam);
}

LRESULT CEditEx::WindowProc(UINT message, WPARAM wParam, LPARAM lParam){
	if(message == EM_SETSEL){
		DrawLineNo();
	}
	return CEdit::WindowProc(message, wParam, lParam);
}

BOOL CEditEx::PreTranslateMessage(MSG* pMsg){
	
	return CEdit::PreTranslateMessage(pMsg);
}

BOOL CEditEx::OnEraseBkgnd(CDC* pDC){
	//return FALSE;	
	return CEdit::OnEraseBkgnd(pDC);
}

void CEditEx::InvalidateTextArea(){
	CRect rect;
	GetClientRect(rect);
	rect.left = m_nLeftMargin;
	InvalidateRect(rect);
}
