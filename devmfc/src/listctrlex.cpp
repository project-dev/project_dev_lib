// ListCtrlEx.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "devmfc.h"
#include "ListCtrlEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx

CListCtrlEx::CListCtrlEx()
{
}

CListCtrlEx::~CListCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	//{{AFX_MSG_MAP(CListCtrlEx)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx メッセージ ハンドラ

/**
 *全カラムのカラム幅を調整します。
 */
void CListCtrlEx::SetAllColumnWidth(){
	CHeaderCtrl *pHead = GetHeaderCtrl();
	if(!pHead){
		return;
	}
	int nMax = pHead->GetItemCount();
	for(int j = 0; j < nMax; j++){
		SetColumnWidth(j, LVSCW_AUTOSIZE);
		int nWidth1 = GetColumnWidth(j);
		SetColumnWidth(j, LVSCW_AUTOSIZE_USEHEADER );
		int nWidth2 = GetColumnWidth(j);
		if(nWidth1 > nWidth2){
			SetColumnWidth(j, LVSCW_AUTOSIZE);
		}
	}
}

int CListCtrlEx::OnCreate(LPCREATESTRUCT lpCreateStruct){
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

/**
 *生成
 * @param dwStyle ウィンドウスタイル
 * @param rect 位置とサイズ
 * @param pParentWnd 親ウィンドウにあたるCWndクラスのポインタ
 * @param nID ID
 */
BOOL CListCtrlEx::Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID ){
	return CListCtrl::Create(dwStyle, rect, pParentWnd, nID);
}

