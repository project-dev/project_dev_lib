// WndTabCtrl.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "devmfc.h"
#include "WndTabCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWndTabCtrl

/**
 *�R���X�g���N�^
 */
CWndTabCtrl::CWndTabCtrl(){
	m_nOldPage = -1;
	m_nNowPage = -1;
}

/**
 *�f�X�g���N�^
 */
CWndTabCtrl::~CWndTabCtrl()
{
}


BEGIN_MESSAGE_MAP(CWndTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CWndTabCtrl)
	ON_WM_MOVE()
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, OnSelchange)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CWndTabCtrl ���b�Z�[�W �n���h��

/**
 * �y�[�W�̕\���ʒu�𒲐�
 */
void CWndTabCtrl::SetPagePosition(){
	TCITEM tcItem;
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;

	GetItem(m_nNowPage, &tcItem);
	CWnd *pWnd = (CWnd*)tcItem.lParam;

	if(pWnd == NULL){
		return;
	}

	SetRedraw(FALSE);

	CRect rect;
	GetPageRect(rect);
	pWnd->SetWindowPos(&wndTop,
					   rect.left,
					   rect.top,
					   rect.Width(),
					   rect.Height(),
					   SWP_SHOWWINDOW | SWP_DRAWFRAME | SWP_NOCOPYBITS);
	SetRedraw(TRUE);
	InvalidateRect(rect, FALSE);
	pWnd->InvalidateRect(NULL, TRUE);
}

/**
 * �w��y�[�W���A�N�e�B�u�ɂ���
 * @param nIndex �^�u�̃C���f�b�N�X
 */
void CWndTabCtrl::SetActivePage(int nIndex){
	CWnd *pWnd = NULL;
	TCITEM tcItem;
	memset(&tcItem, 0, sizeof(TCITEM));

	int nCnt = GetItemCount();
	if((nCnt <= nIndex) || (0 > nIndex)){
		return;
	}

	tcItem.mask = TCIF_PARAM;
	m_nOldPage = m_nNowPage;
	m_nNowPage = nIndex;
	//�Â��y�[�W���B��
	if((m_nNowPage != m_nOldPage) && m_nOldPage != -1){
		GetItem(m_nOldPage, &tcItem);
		pWnd = (CWnd*)tcItem.lParam;
		if(pWnd){
			pWnd->ShowWindow(SW_HIDE);
		}
	}
	if(GetItem(m_nNowPage, &tcItem)){
		pWnd = (CWnd*)tcItem.lParam;
		if(pWnd && ::IsWindow(pWnd->m_hWnd)){
			pWnd->SetActiveWindow();
			pWnd->SetFocus();
			SetPagePosition();
		}
	}
}

// 
// �֐��� : OnMove
// �T  �v : �ړ����̃n���h���֐�
// ��  �� : �Ȃ�
// �߂�l : �Ȃ�
// ��  �l : �Ȃ�
//
void CWndTabCtrl::OnMove(int x, int y) {
	CTabCtrl::OnMove(x, y);
	//SetPagePosition();
}

// 
// �֐��� : OnShowWindow
// �T  �v : �E�B���h�E�\��/��\���̃n���h���֐�
// ��  �� : �Ȃ�
// �߂�l : �Ȃ�
// ��  �l : �Ȃ�
//
void CWndTabCtrl::OnShowWindow(BOOL bShow, UINT nStatus) {
	CTabCtrl::OnShowWindow(bShow, nStatus);
	SetPagePosition();
}

// 
// �֐��� : OnSize
// �T  �v : �E�B���h�E�T�C�Y�ύX���̃n���h���֐�
// ��  �� : �Ȃ�
// �߂�l : �Ȃ�
// ��  �l : �Ȃ�
//
void CWndTabCtrl::OnSize(UINT nType, int cx, int cy) {
	CTabCtrl::OnSize(nType, cx, cy);
	SetPagePosition();
}

// 
// �֐��� : OnSelchange
// �T  �v : �I��ύX���̃n���h���֐�
// ��  �� : �Ȃ�
// �߂�l : �Ȃ�
// ��  �l : �Ȃ�
//
void CWndTabCtrl::OnSelchange(NMHDR* pNMHDR, LRESULT* pResult) {
	SetActivePage(GetCurSel());	
	GetParent()->SendMessage(WM_HWNDTABCHANGE, (WPARAM)pNMHDR, (LPARAM)pResult);
	*pResult = 0;
}

void CWndTabCtrl::OnPaint() {
	//CPaintDC dc(this); // �`��p�̃f�o�C�X �R���e�L�X�g
	CClientDC	dc( this ) ;
	Default();

	int nCnt = GetItemCount();
	CRect rect;
	TCITEM  tcItem;
	char szText[MAX_PATH];
	CFont *pFont = GetFont();
	CFont *pOldFont = dc.SelectObject(pFont);
	CBrush brushNormal;
	brushNormal.CreateSolidBrush(::GetSysColor(COLOR_BTNFACE));
	dc.SetBkMode(TRANSPARENT);
	for(int i = 0; i < nCnt; i++){
		GetItemRect(i, rect);
		memset(szText, 0, MAX_PATH);
		tcItem.mask = TCIF_TEXT;
		tcItem.pszText = szText;
		tcItem.cchTextMax = MAX_PATH;
		GetItem(i, &tcItem);
		CString strTitle = tcItem.pszText;

		//�\���̈�ɂ��킹����������擾����
		CRect textRect;
		textRect.left	= rect.left + 4;
		textRect.top	= rect.top + 2;
		textRect.right	= rect.right - 2;
		textRect.bottom	= rect.bottom - 2;

		if(GetCurSel() == i){
			::SetTextColor(dc.m_hDC, RGB(0x00, 0x00, 0x00));
			dc.FillRect(textRect, &brushNormal);
			textRect.top	= rect.top + 1;
			textRect.bottom	= rect.bottom - 3;
		}else{
			::SetTextColor(dc.m_hDC, RGB(0x66, 0x66, 0x66));
			dc.FillRect(textRect, &brushNormal);
		}

		dc.DrawText(strTitle, 
					strTitle.GetLength(), 
					textRect, 
					DT_NOCLIP | DT_VCENTER |DT_SINGLELINE | DT_MODIFYSTRING | DT_END_ELLIPSIS );
		
	}
	dc.SelectObject(pOldFont);
}

BOOL CWndTabCtrl::OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult ){
	if(pNMHDR == NULL){
		return FALSE;
	}

	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	UINT nID = pNMHDR->idFrom;

	switch(pNMHDR->code){
	case TTN_NEEDTEXTA:
		nID = pTTTA->hdr.idFrom;
		break;
	case TTN_NEEDTEXTW:
		nID = pTTTW->hdr.idFrom;
		break;
	}
	CString strTipText;
#ifndef _UNICODE
//�R���p�C������UNICODE�̏ꍇ
	switch(pNMHDR->code){
	case TTN_NEEDTEXTA:
		lstrcpyn(pTTTA->szText, m_strHintText, 80);
		break;
	default:
		_mbstowcsz(pTTTW->szText, m_strHintText, 80);
		break;
	}
#else
//�R���p�C������UNICODE�ȊO�̏ꍇ
	switch(pNMHDR->code){
	case TTN_NEEDTEXTA:
		_wcstombsz(pTTTA->szText, m_strHintText, 80);
		break;
	default:
		lstrcpyn(pTTTW->szText, m_strHintText, 80);
		break;
	}
#endif

	*pResult = 0;
	return TRUE;
}


void CWndTabCtrl::OnMouseMove(UINT nFlags, CPoint point) {
	m_strHintText = "";

	TCHITTESTINFO tcHitTest;
	tcHitTest.pt = point;
	tcHitTest.flags = TCHT_ONITEM;
	int nIndex = HitTest(&tcHitTest);

	TCITEM  tcItem;
	char szText[MAX_PATH];
	memset(szText, 0, MAX_PATH);
	tcItem.mask = TCIF_TEXT;
	tcItem.pszText = szText;
	tcItem.cchTextMax = MAX_PATH;
	GetItem(nIndex, &tcItem);
	m_strHintText = tcItem.pszText;
	
	CTabCtrl::OnMouseMove(nFlags, point);
}

/**
 *�y�[�W�̃T�C�Y���擾���܂��B
 * @param rect �y�[�W�̃T�C�Y���󂯎��RECT�\���̂̃|�C���^
 */
void CWndTabCtrl::GetPageRect(LPRECT rect){
		GetClientRect(rect);
		AdjustRect(FALSE, rect);
		rect->left		+= 2;
		rect->top		+= 2;
		rect->right		-= 2;
		rect->bottom	-= 2;
}


/**
 * �y�[�W��ǉ����܂��B
 * @param nItem �ǉ��ʒu
 * @param pszText �^�u��
 * @param pWnd �^�u�Ɋ֘A�t����CWnd�̃|�C���^
 * @return �ǉ��ɐ��������ꍇ��TRUE��Ԃ�
 */
BOOL CWndTabCtrl::AddNewPage(int nItem, LPCTSTR pszText, CWnd *pWnd){
	if(!pWnd){
		return FALSE;
	}

	CWnd *pParent = pWnd->GetParent();
	if(pParent->m_hWnd != m_hWnd){
		DWORD dwStyle = ::GetWindowLong(pWnd->m_hWnd, GWL_STYLE);
		::SetWindowLong(pWnd->m_hWnd, GWL_STYLE, 0);
		pWnd->SetParent(this);
		::SetWindowLong(pWnd->m_hWnd, GWL_STYLE, dwStyle);

	}
	return InsertItem(TCIF_TEXT | TCIF_PARAM, nItem, pszText, 0, (LPARAM)pWnd);
}
