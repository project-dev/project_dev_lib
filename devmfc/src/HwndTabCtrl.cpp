// CustTabCtrl.cpp : インプリメンテーション ファイル
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
 *コンストラクタ
 */
CHwndTabCtrl::CHwndTabCtrl(){
	m_nOldPage = -1;
	m_nNowPage = -1;

}

/**
 *デストラクタ
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
// CHwndTabCtrl メッセージ ハンドラ

/**
 * ページの表示位置を調整
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
 * 指定ページをアクティブにする
 * @param nIndex タブのインデックス
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

	//古いページを隠す
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
// 関数名 : OnShowWindow
// 概  要 : ウィンドウ表示/非表示のハンドラ関数
// 引  数 : なし
// 戻り値 : なし
// 備  考 : なし
//
void CHwndTabCtrl::OnShowWindow(BOOL bShow, UINT nStatus) {
	CTabCtrlEx::OnShowWindow(bShow, nStatus);
	SetPagePosition();
}

// 
// 関数名 : OnSize
// 概  要 : ウィンドウサイズ変更時のハンドラ関数
// 引  数 : なし
// 戻り値 : なし
// 備  考 : なし
//
void CHwndTabCtrl::OnSize(UINT nType, int cx, int cy) {
	CTabCtrlEx::OnSize(nType, cx, cy);
	SetPagePosition();
}

// 
// 関数名 : OnSelchange
// 概  要 : 選択変更時のハンドラ関数
// 引  数 : なし
// 戻り値 : なし
// 備  考 : なし
//
void CHwndTabCtrl::OnSelchange(NMHDR* pNMHDR, LRESULT* pResult) {
	SetActivePage(GetCurSel());	

	GetParent()->SendMessage(WM_HWNDTABCHANGE, (WPARAM)pNMHDR, (LPARAM)pResult);
	*pResult = 0;
}


/**
 * ページを追加します。
 * @param nItem 追加位置
 * @param pszText タブ名
 * @param hWnd タブに関連付けるHWND
 * @return 追加に成功した場合はTRUEを返す
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
