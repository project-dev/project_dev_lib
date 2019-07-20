// BaseTabView.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "TabView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabView

IMPLEMENT_DYNCREATE(CTabView, CView)

// 
// 関数名 : CTabView
// 概  要 : コンストラクタ
// 引  数 : なし
// 戻り値 : なし
// 備  考 : なし
//
CTabView::CTabView(){
}

// 
// 関数名 : ~CTabView
// 概  要 : デストラクタ
// 引  数 : なし
// 戻り値 : なし
// 備  考 : なし
//
CTabView::~CTabView(){
}


BEGIN_MESSAGE_MAP(CTabView, CView)
	//{{AFX_MSG_MAP(CTabView)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_MESSAGE(WM_HWNDTABCHANGE, OnSelchange)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabView 描画

// 
// 関数名 : OnDraw
// 概  要 : 描画
// 引  数 : なし
// 戻り値 : なし
// 備  考 : なし
//
void CTabView::OnDraw(CDC* pDC){
	CDocument* pDoc = GetDocument();
}

/////////////////////////////////////////////////////////////////////////////
// CTabView 診断

#ifdef _DEBUG
void CTabView::AssertValid() const{
	CView::AssertValid();
}

void CTabView::Dump(CDumpContext& dc) const{
	CView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTabView メッセージ ハンドラ

// 
// 関数名 : OnCreate
// 概  要 : 生成時に呼び出される
// 引  数 : なし
// 戻り値 : なし
// 備  考 : なし
//
int CTabView::OnCreate(LPCREATESTRUCT lpCreateStruct){
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect;
	GetClientRect(rect);
	m_objTabCtrl.Create(WS_CHILD | WS_VISIBLE | TCS_TOOLTIPS | TCS_TABS | WS_TABSTOP, rect, this, 0);
	m_objTabCtrl.EnableToolTips();

	return 0;
}

/**
 * 新規ページの作成
 * @param nIndex    インデックス
 * @param strTitle  タブの名前
 * @param hWnd      タブに関連付けるウィンドウハンドル
 * @return 挿入位置
 */
int CTabView::CreatePage(int nIndex, LPCTSTR strTitle, HWND hWnd){
	if(!hWnd){
		return -1;
	}
	TCITEM tcItem;
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask			= TCIF_TEXT | TCIF_PARAM;
	tcItem.pszText		= (LPTSTR)strTitle;
	tcItem.cchTextMax	= strlen(strTitle);
	tcItem.lParam		= (LPARAM)hWnd;
	
	int nRet = m_objTabCtrl.InsertItem(nIndex, &tcItem);
	::SetParent(hWnd, m_objTabCtrl.m_hWnd);
	return nRet;
}

// 
// 関数名 : OnPaint
// 概  要 : 描画
// 引  数 : なし
// 戻り値 : なし
// 備  考 : なし
//
void CTabView::OnPaint(){
	CPaintDC dc(this); // 描画用のデバイス コンテキスト
	CRect rect;
	GetClientRect(rect);
	m_objTabCtrl.SetWindowPos(&wndTop, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
	m_objTabCtrl.SetPagePosition();
}

/**
 * CCustTabCtrlコントロールを取得
 * @return  CCustTabCtrlオブジェクト
 */
CHwndTabCtrl& CTabView::GetTabCtrl(){
	return m_objTabCtrl;
}

// 
// 関数名 : OnSelchange
// 概  要 : 選択変更時のハンドラ関数
// 引  数 : なし
// 戻り値 : なし
// 備  考 : なし
//
LRESULT CTabView::OnSelchange(WPARAM wParam, LPARAM lParam) {
	m_objTabCtrl.SetActivePage(m_objTabCtrl.GetCurSel());	
	NMHDR* pNMHDR = (NMHDR*)wParam; 
	LRESULT* pResult = (LRESULT*)lParam;
	*pResult = 0;
	OnSelChangeFunc(pNMHDR, pResult);
	return *pResult;
}

/**
 *ページ切り替え時に呼び出される関数
 * @param pNMHDR WM_HWNDTABCHANGE のwParam
 * @param pResult WM_HWNDTABCHANGE のlParam
 */
void CTabView::OnSelChangeFunc(NMHDR* pNMHDR, LRESULT* pResult){
}
