// RichEditCtrlEx.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "devmfc.h"
#include "richeditctrlex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRichEditCtrlEx

/**
 * �R���X�g���N�^
 */
CRichEditCtrlEx::CRichEditCtrlEx(){
	m_bModify = FALSE;
	m_pOldBmp = NULL;
	m_bLineShow = FALSE;
	m_nOldIndex = -1;
	m_pBackDC = NULL;
	m_pBackBmp = NULL;
}

/**
 * �f�X�g���N�^
 */
CRichEditCtrlEx::~CRichEditCtrlEx(){
	DestroyWindow();
}


BEGIN_MESSAGE_MAP(CRichEditCtrlEx, CRichEditCtrl)
	//{{AFX_MSG_MAP(CRichEditCtrlEx)
	ON_WM_CREATE()
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_CONTROL_REFLECT(EN_VSCROLL, OnVscroll)
	ON_WM_SHOWWINDOW()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
//	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEWHEEL()
	ON_CONTROL_REFLECT(EN_SETFOCUS, OnSetfocus)
	ON_WM_ACTIVATE()
	ON_WM_ACTIVATEAPP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRichEditCtrlEx ���b�Z�[�W �n���h��
int CRichEditCtrlEx::OnCreate(LPCREATESTRUCT lpCreateStruct){
	if (CRichEditCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	memset(&m_lFont, 0, sizeof(LOGFONT));
	CFont *pFont = GetFont();
	if(pFont){
		pFont->GetLogFont(&m_lFont);
		m_lFont.lfWeight= 8;
		m_objFont.CreateFontIndirect(&m_lFont);
		SetFont(&m_objFont);
	}else{
		memset(&m_lFont, 0, sizeof(LOGFONT));
		m_lFont.lfHeight= -16;
		strcpy(m_lFont.lfFaceName, "�l�r �S�V�b�N");
		m_objFont.CreateFontIndirect(&m_lFont);
		SetFont(&m_objFont);
	}

	long evMask = GetEventMask();
	evMask |= ENM_CHANGE | ENM_MOUSEEVENTS;
	SetEventMask(evMask);
	DrawLineNo();
	m_bModify = FALSE;
	return 0;
}

void CRichEditCtrlEx::OnChange() 
{
	// TODO: ���ꂪ RICHEDIT �R���g���[���̏ꍇ�A�R���g���[���́A lParam �}�X�N
	// ���ł̘_���a�� ENM_CHANGE �t���O�t���� CRichEditCrtl().SetEventMask()
	// ���b�Z�[�W���R���g���[���֑��邽�߂� CRichEditCtrl::OnInitDialog() �֐����I�[�o�[
	// ���C�h���Ȃ����肱�̒ʒm�𑗂�܂���B
	
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	m_bModify = TRUE;
	DrawLineNo();
	
}

void CRichEditCtrlEx::OnDestroy() {
	if(m_pBackDC){
		if(m_pOldBmp){
			m_pBackDC->SelectObject(m_pOldBmp);
		}
		delete m_pBackDC;
		m_pBackDC = NULL;
	}
	if(m_pBackBmp){
		m_pBackBmp->DeleteObject();
		delete m_pBackBmp;
		m_pBackBmp = NULL;
	}
	CRichEditCtrl::OnDestroy();
	
}

void CRichEditCtrlEx::OnPaint() {
//	CPaintDC dc(this); // �`��p�̃f�o�C�X �R���e�L�X�g
	CClientDC dc(this);

	Default();

//	//������CDC���ς��Ă݂����Ȃ�(������
//	int nPlanes = dc.GetDeviceCaps(PLANES);
//	if(nPlanes == 1){
//	}
	CRect rect;
	GetClientRect(rect);
	rect.right  = rect.left + m_nLeftMargin + 2;
	dc.BitBlt(rect.left + 1, rect.top + 1, 
			  rect.Width() - 2, rect.Height() - 2, 
			  m_pBackDC, 0, 0, SRCCOPY);
}

BOOL CRichEditCtrlEx::OnEraseBkgnd( CDC* pDC ){
	return FALSE;
}


void CRichEditCtrlEx::SetMarginFromLine(){
	CString strLine = "";
	CString strEnd;
	int nLine = GetLineCount();
	strLine.Format("%d", nLine + 1);
	int nLen = strLine.GetLength();
	int nMax = nLen > 4 ? nLen : 4;
	while(strLine.GetLength() < nMax){
		strLine = "0" + strLine;
	}
	CDC *pDC = GetDC();
	CSize size = pDC->GetTextExtent(strLine);
	m_nLeftMargin = size.cx + 2;
	CRect rect;
	GetRect(rect);
	int nNowMargin = rect.left;
	if(nNowMargin != m_nLeftMargin){
		rect.left = m_nLeftMargin + 2;
		SetRect(rect);
	}
}

void CRichEditCtrlEx::CharFromPos(int &nLine, int &nPos){
//	nLine = LineIndex();
	nLine = LineFromChar(-1);
	long lPos;
	long lEndPos;
	GetSel(lPos, lEndPos);
	nPos = lPos;
}

void CRichEditCtrlEx::DrawLineNo(){
	SetMarginFromLine();
	CreateBackBuffer();
	if(!m_bLineShow){
		CRect rect;
		GetRect(rect);
		rect.left = 0;
		SetRect(rect);
		return;
	}
	
	if(!m_pBackDC || !m_pBackDC->m_hDC){
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

	int nPos;
	int nIndex;
	CharFromPos(nIndex, nPos);
	nPos = GetScrollPos(SB_VERT);
//	if(nIndex == m_nOldIndex){
//		InvalidateRect(drawAreaRect);
//		return;
//	}
//	m_nOldIndex = nIndex;
	CFont *pFont = m_pBackDC->SelectObject(&m_objFont);

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
	//drawRect.top++;
	drawRect.bottom = drawRect.top + nHeight + 4;
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
		drawRect.bottom = drawRect.top + nHeight + 4;
		nLine++;
	}
//	InvalidateRect(drawAreaRect);
//	GetClientRect(rect);
//	rect.right  = rect.left + m_nLeftMargin + 2;
//	InvalidateRect(rect);
	if(pFont){
		m_pBackDC->SelectObject(pFont);
	}
}

BOOL CRichEditCtrlEx::CreateBackBuffer(){
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
		if(m_pBackDC){
			delete m_pBackDC;
			m_pBackDC = NULL;
		}
		if(m_pBackBmp){
			m_pBackBmp->DeleteObject();
			delete m_pBackBmp;
			m_pBackBmp = NULL;
		}

		CDC* pDC = GetDC();
		m_pBackDC = new CDC();
		m_pBackDC->CreateCompatibleDC(pDC);
		m_pBackBmp = new CBitmap();
		m_pBackBmp->CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());

		m_pBackDC->SelectObject(m_pBackBmp);
		m_pBackDC->SelectObject(&m_objFont);
		m_oldRect = rect;

		COLORREF crBack = GetSysColor(COLOR_MENU);
		m_pBackDC->FillSolidRect(rect, crBack);
		POINT pts[2];
		pts[0].x = rect.right-1;
		pts[1].x = rect.right-1;
		pts[0].y = rect.top;
		pts[1].y = rect.bottom;
		m_pBackDC->Polyline(pts, 2);
	}
	return TRUE;
}

void CRichEditCtrlEx::OnSize(UINT nType, int cx, int cy){
	//SetRedraw(FALSE);
	CRichEditCtrl::OnSize(nType, cx, cy);
	//UpdateWindow();
	DrawLineNo();
	//SetRedraw(TRUE);
	//InvalidateRect(NULL);
}

void CRichEditCtrlEx::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar){
	//SetRedraw(FALSE);
	CRichEditCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
	//UpdateWindow();
	DrawLineNo();
	//SetRedraw(TRUE);
	//InvalidateRect(NULL);
}

void CRichEditCtrlEx::OnVscroll(){
//	DrawLineNo();
}

void CRichEditCtrlEx::OnShowWindow(BOOL bShow, UINT nStatus){
	//SetRedraw(FALSE);
	CRichEditCtrl::OnShowWindow(bShow, nStatus);

	DrawLineNo();	
//	SetRedraw(TRUE);
//	InvalidateRect(NULL);
//	SetActiveWindow();
//	SetFocus();
}

void CRichEditCtrlEx::OnMouseMove(UINT nFlags, CPoint point){
//	SetRedraw(FALSE);
	CRichEditCtrl::OnMouseMove(nFlags, point);
	//UpdateWindow();
	switch(nFlags){
	case MK_LBUTTON :
		DrawLineNo();	
		break;
	}
//	SetRedraw(TRUE);
//	InvalidateRect(NULL);

}

BOOL CRichEditCtrlEx::OnMouseWheel( UINT nFlags, short zDelta, CPoint pt ){
//	SetRedraw(FALSE);
	BOOL bRet = CRichEditCtrl::OnMouseWheel(nFlags, zDelta, pt);
	//UpdateWindow();
	DrawLineNo();
//	SetRedraw(TRUE);
//	InvalidateRect(NULL);
	return bRet;
}

/**
 * �s�ԍ���\�����邩���Ȃ����̐ݒ���s�Ȃ��܂��B
 * @param bShow �s�ԍ���\������ꍇ��TRUE��ݒ肵�܂��B
 */
void CRichEditCtrlEx::SetLineShow(BOOL bShow){
	m_bLineShow = bShow;

}

void CRichEditCtrlEx::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){
	//SetRedraw(FALSE);
	CRichEditCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
	//UpdateWindow();
	DrawLineNo();	
	//SetRedraw(TRUE);
	//InvalidateRect(NULL);
}
#if 0
void CRichEditCtrlEx::OnLButtonDown(UINT nFlags, CPoint point){
	//SetRedraw(FALSE);
	CRichEditCtrl::OnLButtonDown(nFlags, point);
	//UpdateWindow();
	DrawLineNo();	
	//SetRedraw(TRUE);
	//InvalidateRect(NULL);
	TRACE("LBUTTON2\n");
}
#endif
void CRichEditCtrlEx::OnLButtonUp(UINT nFlags, CPoint point){
	//SetRedraw(FALSE);
	CRichEditCtrl::OnLButtonUp(nFlags, point);
	//UpdateWindow();
	DrawLineNo();	
	//SetRedraw(TRUE);
	//InvalidateRect(NULL);
}

/**
 * �t�H���g��ݒ肵�܂�
 * @param pFont �t�H���g�������� CFont�̃|�C���^
 * @param bRedraw �ĕ`����s�Ȃ��ꍇ��TRUE��ݒ肵�܂��B
 */

void CRichEditCtrlEx::SetFont(CFont *pFont, BOOL bRedraw){
	//SetRedraw(FALSE);
	CRichEditCtrl::SetFont(pFont, bRedraw);
	CHARFORMAT cf;
	memset(&cf, 0, sizeof(CHARFORMAT));
	memset(&m_lFont, 0, sizeof(LOGFONT));
	if(pFont->GetLogFont(&m_lFont)){
		int iDev = GetDC()->GetDeviceCaps(LOGPIXELSY);
		cf.dwMask = CFM_FACE | CFM_SIZE | CFM_CHARSET;
		cf.cbSize = sizeof(CHARFORMAT);
		cf.yHeight = MulDiv(m_lFont.lfHeight, 72, iDev) * -20;
		cf.bCharSet = m_lFont.lfCharSet;
		cf.bPitchAndFamily = m_lFont.lfPitchAndFamily;
		strcpy(cf.szFaceName, m_lFont.lfFaceName);

		if(SetDefaultCharFormat(cf)){
		
			//���݂̃e�L�X�g�̃t�H�[�}�b�g���ύX
			long nStart;
			long nEnd;
			GetSel(nStart, nEnd);
			SetSel(0, -1);
			SetSelectionCharFormat(cf);
/*
			PARAFORMAT2 prm;
			prm.cbSize = sizeof(PARAFORMAT2);
			prm.dwMask = PFM_LINESPACING;
			prm.bLineSpacingRule = 0;
			prm.dyLineSpacing = 0;
			SendMessage(EM_SETPARAFORMAT, 0, (LPARAM)&prm);

			//SetParaFormat(prm);
*/			
			SetSel(nStart, nEnd);
			
			m_objFont.DeleteObject();
			m_objFont.CreateFontIndirect(&m_lFont);
		}
	}
	CreateBackBuffer();
	//UpdateWindow();
	DrawLineNo();
	//SetRedraw(TRUE);
	//InvalidateRect(NULL);
}

BOOL CRichEditCtrlEx::PreCreateWindow(CREATESTRUCT& cs){
//	cs.style |= WS_CLIPCHILDREN;
	return CRichEditCtrl::PreCreateWindow(cs);
}

LRESULT CRichEditCtrlEx::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam){
	if(message == EM_SETSEL){
		DrawLineNo();
	}
	return CRichEditCtrl::DefWindowProc(message, wParam, lParam);
}

LRESULT CRichEditCtrlEx::WindowProc(UINT message, WPARAM wParam, LPARAM lParam){
	if(message == EM_SETSEL){
		DrawLineNo();
	}
	return CRichEditCtrl::WindowProc(message, wParam, lParam);
}

BOOL CRichEditCtrlEx::PreTranslateMessage(MSG* pMsg){
/*
	if(pMsg->message == WM_LBUTTONDOWN){
		TRACE("LBUTTON1\n");
		CPoint pos;
		pos.x = LOWORD(pMsg->lParam);
		pos.y = HIWORD(pMsg->lParam);
		SetFocus();
		
//		OnLButtonDown(pMsg->wParam, pMsg->lParam);
//		return TRUE;
	}
*/
	BOOL bRet = CRichEditCtrl::PreTranslateMessage(pMsg);
	return bRet;
}

void CRichEditCtrlEx::OnSetfocus(){
}

void CRichEditCtrlEx::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) {
	CRichEditCtrl::OnActivate(nState, pWndOther, bMinimized);
}

void CRichEditCtrlEx::OnActivateApp(BOOL bActive, DWORD hTask) {
	CRichEditCtrl::OnActivateApp(bActive, hTask);
}
