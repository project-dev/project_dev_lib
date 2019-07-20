// CustTabCtrl.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "HwndTabCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHwndTabCtrl

/**
 *�R���X�g���N�^
 */
CHwndTabCtrl::CHwndTabCtrl(){
	m_nOldPage = -1;
	m_nNowPage = -1;

}

/**
 *�f�X�g���N�^
 */
CHwndTabCtrl::~CHwndTabCtrl(){
}


BEGIN_MESSAGE_MAP(CHwndTabCtrl, CTabCtrlEx)
	//{{AFX_MSG_MAP(CHwndTabCtrl)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, OnSelchange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHwndTabCtrl ���b�Z�[�W �n���h��

/**
 * �y�[�W�̕\���ʒu�𒲐�
 */
void CHwndTabCtrl::SetPagePosition(){
	TCITEM tcItem;
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;

	GetItem(m_nNowPage, &tcItem);
	HWND hWnd = (HWND)tcItem.lParam;

	if(hWnd == NULL){
		return;
	}
	SetRedraw(FALSE);

	CRect rect;
	GetPageRect(rect);
	::SetWindowPos(hWnd,
				   HWND_TOP,
				   rect.left,
				   rect.top,
				   rect.Width(),
				   rect.Height(),
				   SWP_SHOWWINDOW | SWP_DRAWFRAME | SWP_NOCOPYBITS);
	SetRedraw(TRUE);
	InvalidateRect(rect, FALSE);
	::InvalidateRect(hWnd, NULL, TRUE);
}

/**
 * �w��y�[�W���A�N�e�B�u�ɂ���
 * @param nIndex �^�u�̃C���f�b�N�X
 */
void CHwndTabCtrl::SetActivePage(int nIndex){
	HWND hWnd;
	TCITEM tcItem;
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;

	int nCnt = GetItemCount();
	if((nCnt <= nIndex) || (0 > nIndex)){
		return;
	}

	m_nOldPage = m_nNowPage;
	m_nNowPage = nIndex;

	//�Â��y�[�W���B��
	if((m_nNowPage != m_nOldPage) && m_nOldPage != -1){
		GetItem(m_nOldPage, &tcItem);
		hWnd = (HWND)tcItem.lParam;
		if(hWnd){
			::ShowWindow(hWnd, SW_HIDE);
			::SetFocus(hWnd);
		}
	}
	GetItem(m_nNowPage, &tcItem);
	hWnd = (HWND)tcItem.lParam;
	::SetActiveWindow(hWnd);
	::SetFocus(hWnd);
	SetPagePosition();

}

// 
// �֐��� : OnShowWindow
// �T  �v : �E�B���h�E�\��/��\���̃n���h���֐�
// ��  �� : �Ȃ�
// �߂�l : �Ȃ�
// ��  �l : �Ȃ�
//
void CHwndTabCtrl::OnShowWindow(BOOL bShow, UINT nStatus) {
	CTabCtrlEx::OnShowWindow(bShow, nStatus);
	SetPagePosition();
}

// 
// �֐��� : OnSize
// �T  �v : �E�B���h�E�T�C�Y�ύX���̃n���h���֐�
// ��  �� : �Ȃ�
// �߂�l : �Ȃ�
// ��  �l : �Ȃ�
//
void CHwndTabCtrl::OnSize(UINT nType, int cx, int cy) {
	CTabCtrlEx::OnSize(nType, cx, cy);
	SetPagePosition();
}

// 
// �֐��� : OnSelchange
// �T  �v : �I��ύX���̃n���h���֐�
// ��  �� : �Ȃ�
// �߂�l : �Ȃ�
// ��  �l : �Ȃ�
//
void CHwndTabCtrl::OnSelchange(NMHDR* pNMHDR, LRESULT* pResult) {
	SetActivePage(GetCurSel());	

	GetParent()->SendMessage(WM_HWNDTABCHANGE, (WPARAM)pNMHDR, (LPARAM)pResult);
	*pResult = 0;
}


/**
 * �y�[�W��ǉ����܂��B
 * @param nItem �ǉ��ʒu
 * @param pszText �^�u��
 * @param hWnd �^�u�Ɋ֘A�t����HWND
 * @return �ǉ��ɐ��������ꍇ��TRUE��Ԃ�
 */
BOOL CHwndTabCtrl::AddNewPage(int nItem, LPCTSTR pszText, HWND hWnd){
	if(!hWnd){
		return FALSE;
	}

	if(::GetParent(hWnd) != m_hWnd){
		DWORD dwStyle = ::GetWindowLong(hWnd, GWL_STYLE);
		::SetWindowLong(hWnd, GWL_STYLE, 0);
		::SetParent(hWnd, m_hWnd);
		::SetWindowLong(hWnd, GWL_STYLE, dwStyle);

	}
	BOOL bRet =  InsertItem(TCIF_TEXT | TCIF_PARAM, nItem, pszText, 0, (LPARAM)hWnd);
	return bRet;
}
