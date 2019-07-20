// TabCtrlEx.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "TabCtrlEx.h"
#include "DevString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabCtrlEx

CTabCtrlEx::CTabCtrlEx(){
	m_bIsHoverTab = TRUE;
}

CTabCtrlEx::~CTabCtrlEx(){
}


BEGIN_MESSAGE_MAP(CTabCtrlEx, CTabCtrl)
	//{{AFX_MSG_MAP(CTabCtrlEx)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabCtrlEx メッセージ ハンドラ

void CTabCtrlEx::OnPaint() {
	//CPaintDC dc(this); // 描画用のデバイス コンテキスト
	DWORD dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);
	BOOL bBtn = (dwStyle & TCS_BOTTOM) == TCS_BOTTOM;
	CClientDC	dc( this ) ;

	//心なしか描画がちらつかない気がする・・・
	::SetTextColor(dc.m_hDC, ::GetSysColor(COLOR_BTNFACE));

	Default();

	int nCnt = GetItemCount();
	CRect rect;
	TCITEM  tcItem;
	tcItem.mask = TCIF_TEXT;
	tcItem.cchTextMax = MAX_PATH;

	char szText[MAX_PATH];
	CFont *pFont = GetFont();
	CFont *pOldFont = dc.SelectObject(pFont);
	CBrush brushNormal;
	brushNormal.CreateSolidBrush(::GetSysColor(COLOR_BTNFACE));
	dc.SetBkMode(TRANSPARENT);
	for(int i = 0; i < nCnt; i++){
		GetTabRect(i, rect);
		memset(szText, 0, MAX_PATH);

		tcItem.pszText = szText;
		GetItem(i, &tcItem);
		CString strTitle = tcItem.pszText;

		CRect textRect = rect;

		if((dwStyle & TCS_BUTTONS) == TCS_BUTTONS){
			CRect paintRect;
			GetItemRect(i, paintRect);
			//dc.FrameRect(paintRect, &brushNormal);
			paintRect.left += 2;
			paintRect.right -= 2;
			paintRect.top += 2;
			paintRect.bottom -= 2;
			dc.FillRect(paintRect, &brushNormal);
		}else{
			if(bBtn){
				if(GetCurSel() == i){
					textRect.top	= rect.top + 1;
					textRect.bottom	= rect.bottom + 1;
				}
			}else{
				//表示領域にあわせた文字列を取得する
				if(GetCurSel() == i){
					textRect.top	= rect.top - 1;
					textRect.bottom	= rect.bottom - 3;
				}
			}
			dc.FillRect(textRect, &brushNormal);
		}

		if(GetCurSel() == i){
			::SetTextColor(dc.m_hDC, RGB(0x00, 0x00, 0x00));

			if((dwStyle & TCS_BUTTONS) == TCS_BUTTONS){
				textRect.top	= rect.top + 1;
				textRect.left	= rect.left + 1;
//				textRect.right	= rect.right - 2;
				textRect.bottom	= rect.bottom - 1;
			}
		}else{
			::SetTextColor(dc.m_hDC, RGB(0x66, 0x66, 0x66));
		}

		
		//文字列を加工する
		if((dwStyle & TCS_FIXEDWIDTH) == TCS_FIXEDWIDTH){
			CSize sz = dc.GetTextExtent(strTitle);
			BOOL bShorted = FALSE;
			while((sz.cx > textRect.Width()) && !strTitle.IsEmpty() ){
				bShorted = TRUE;
				CDevString strTitleCut = strTitle;
				int nLen = strTitleCut.GetTextLength() - 1;
				strTitleCut = strTitleCut.RightText(nLen);
				strTitle = strTitleCut.GetBuffer();
				CString strText = "…" + strTitle;
				sz = dc.GetTextExtent(strText);
			}
			if(bShorted){
				strTitle = "…" + strTitle;
			}
		}
		
		::DrawTextEx(dc.m_hDC,
					 strTitle.GetBuffer(strTitle.GetLength()), 
					 strTitle.GetLength(), 
					 textRect, 
					 DT_NOCLIP | DT_VCENTER | DT_SINGLELINE /*| DT_CENTER*/,
					 NULL);
	
	}
	dc.SelectObject(pOldFont);

	//"msctrl_updown32"
	::EnumChildWindows(m_hWnd, FindProc, NULL);
}

void CTabCtrlEx::GetTabRect(int nIndex, CRect &retRect){
	CRect rect;
	GetItemRect(nIndex, rect);
	DWORD dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);
	retRect.top		= rect.top	+ 1;
	retRect.left	= rect.left + 4;
	retRect.right	= rect.right- 2;
	retRect.left--;
	retRect.right -= 1;
	if((dwStyle & TCS_BUTTONS) == TCS_BUTTONS){
		retRect.top += 1;
		retRect.bottom	= rect.bottom - 2;
	}else{
		if((dwStyle & TCS_BOTTOM) == TCS_BOTTOM){
			retRect.top += 1;
			retRect.bottom	= rect.bottom - 2;
		}else{
			retRect.top += 1;
			retRect.bottom	= rect.bottom;
		}
	}
}

BOOL CTabCtrlEx::FindProc(HWND hwnd, LPARAM lParam){
	if(!::IsWindowVisible(hwnd)){
		return TRUE;
	}
	char szClass[MAX_PATH];
	memset(szClass, 0, MAX_PATH);
	GetClassName(hwnd, szClass, MAX_PATH);
	CString strClass = szClass;
	if(!strClass.CompareNoCase("msctrl_updown32")){
		::SetWindowPos(hwnd, 
					   HWND_TOP, 
					   0, 0, 0, 0, 
					   SWP_NOSIZE | SWP_NOREPOSITION | SWP_SHOWWINDOW);
		return FALSE;
	}
	return TRUE;
}
int CTabCtrlEx::OnToolHitTest( CPoint point, TOOLINFO* pTI ) const{
	POINT pt = point;
	ScreenToClient(&pt);
	TCHITTESTINFO tcHitTest;
	memset(&tcHitTest, 0, sizeof(TCHITTESTINFO));
	tcHitTest.flags = TCHT_ONITEM;
	tcHitTest.pt = pt;
	int nIndex = HitTest(&tcHitTest);
	
	if(nIndex == -1){
		return -1;
	}
	return CTabCtrl::OnToolHitTest(point, pTI);
}
BOOL CTabCtrlEx::OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult ){
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
//コンパイル環境がUNICODEの場合
	switch(pNMHDR->code){
	case TTN_NEEDTEXTA:
		lstrcpyn(pTTTA->szText, m_strHintText, 80);
		break;
	default:
		_mbstowcsz(pTTTW->szText, m_strHintText, 80);
		break;
	}
#else
//コンパイル環境がUNICODE以外の場合
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

/**
 *ページのサイズを取得します。
 * @param rect ページのサイズを受け取るRECT構造体のポインタ
 */
void CTabCtrlEx::GetPageRect(LPRECT rect){
	GetClientRect(rect);

	DWORD dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);
	CRect itemRect;

	if((dwStyle & TCS_BUTTONS) == TCS_BUTTONS){
		GetItemRect(0, itemRect);
		if((dwStyle & TCS_BOTTOM) == TCS_BOTTOM){
			rect->bottom -= itemRect.Height();
		}else{
			rect->top += itemRect.Height();
		}
	}else{
		AdjustRect(FALSE, rect);
		rect->left		+= 2;
		rect->top		+= 2;
		rect->right		-= 2;
		rect->bottom	-= 2;
	}
}

BOOL CTabCtrlEx::SetIsHoverTab(BOOL isHover, DWORD dwHoverInterval){
#ifdef USE_DROPTARGET
	m_bIsHoverTab = isHover;
	if(dwHoverInterval <= -1){
		if(!SystemParametersInfo(SPI_GETMOUSEHOVERTIME,
								 0, &m_objDropTarget.m_dwHoverInterval, 0)){
			m_objDropTarget.m_dwHoverInterval = 100;
		}
	}else{
		m_objDropTarget.m_dwHoverInterval = dwHoverInterval;
	}

	if(isHover){
		//ドロップターゲットに登録
		if(!m_objDropTarget.Register(this)){
			return FALSE;
		}
	}else{
		//ドロップターゲットから解除
		m_objDropTarget.Revoke();
	}
#endif
	return TRUE;
}

void CTabCtrlEx::SetActivePage(int nIndex){}

int CTabCtrlEx::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTabCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: この位置に固有の作成用コードを追加してください
	m_objGrayBrush.CreateSolidBrush(::GetSysColor(COLOR_BTNFACE));

	OleInitialize(NULL);
	return 0;
}


#ifdef USE_DROPTARGET
DROPEFFECT CTabCtrlEx::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point){
	return DROPEFFECT_COPY;
}

DROPEFFECT CTabCtrlEx::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point){
	return DROPEFFECT_COPY;
}
#endif

LRESULT CTabCtrlEx::OnMouseHover(WPARAM wParam, LPARAM lParam){
	TRACE("OnMouseHover\n");
	TCHITTESTINFO tcHitTest;
	tcHitTest.pt.x = LOWORD(lParam); 
	tcHitTest.pt.y = HIWORD(lParam); 
	tcHitTest.flags = TCHT_ONITEM;
	int nIndex = HitTest(&tcHitTest);
	if((nIndex != -1) && (nIndex != GetCurSel())){
		SetCurSel(nIndex);
		SetActivePage(nIndex);
	}
	return 0;
}


void CTabCtrlEx::OnMouseMove(UINT nFlags, CPoint point) {
	m_strHintText = "";

	TCHITTESTINFO tcHitTest;
	tcHitTest.pt = point;
	tcHitTest.flags = TCHT_ONITEM;
	int nIndex = HitTest(&tcHitTest);

	if(nIndex != -1){
		TCITEM  tcItem;
		char szText[MAX_PATH];
		memset(szText, 0, MAX_PATH);
		tcItem.mask = TCIF_TEXT;
		tcItem.pszText = szText;
		tcItem.cchTextMax = MAX_PATH;
		GetItem(nIndex, &tcItem);
		m_strHintText = tcItem.pszText;

	}
	CTabCtrl::OnMouseMove(nFlags, point);
}

void CTabCtrlEx::OnDestroy(){
	//ドロップターゲットから解除
#ifdef USE_DROPTARGET
	if(m_bIsHoverTab){
		m_objDropTarget.Revoke();
	}
#endif
	CTabCtrl::OnDestroy();
}

