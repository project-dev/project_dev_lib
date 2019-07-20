// DRawerEdit.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DRawerEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDRawerEdit

CDRawerEdit::CDRawerEdit()
{
}

CDRawerEdit::~CDRawerEdit()
{
}


BEGIN_MESSAGE_MAP(CDRawerEdit, CEdit)
	//{{AFX_MSG_MAP(CDRawerEdit)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDRawerEdit メッセージ ハンドラ
BOOL CDRawerEdit::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID ){
	return CEdit::Create(dwStyle, rect, pParentWnd, nID);
}

void CDRawerEdit::OnSetFocus(CWnd* pOldWnd){
	CEdit::OnSetFocus(pOldWnd);
}

void CDRawerEdit::OnKillFocus(CWnd* pNewWnd) {
/*
	if(IsWindowVisible()){
		ShowWindow(SW_HIDE);
		COPYDATASTRUCT cds;
		memset(&cds, 0, sizeof(COPYDATASTRUCT));
		cds.dwData = CDS_EDITEND;
		cds.lpData = NULL;
		cds.cbSize = 0;
		GetParent()->SendMessage(WM_COPYDATA, (WPARAM)m_hWnd, (LPARAM)&cds);
	}
*/
	CEdit::OnKillFocus(pNewWnd);
}

void CDRawerEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	SHORT sCtrl = GetKeyState(VK_CONTROL);
	if(nChar == VK_ESCAPE){
		ShowWindow(SW_HIDE);
		COPYDATASTRUCT cds;
		memset(&cds, 0, sizeof(COPYDATASTRUCT));
		cds.dwData = CDS_EDITEND;
		cds.lpData = 0;
		cds.cbData = 0;
		GetParent()->SendMessage(WM_COPYDATA, (WPARAM)m_hWnd, (LPARAM)&cds);
	}
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CDRawerEdit::PreTranslateMessage(MSG* pMsg){
	if(pMsg->message == WM_KEYDOWN){
		SHORT sCtrl = GetKeyState(VK_CONTROL);
		if((pMsg->wParam == VK_RETURN) && (sCtrl & 0x80)){
			//編集確定
			COPYDATASTRUCT cds;
			memset(&cds, 0, sizeof(COPYDATASTRUCT));
			cds.dwData = CDS_EDITEND;
			cds.lpData = (LPVOID)1;
			cds.cbData = 0;
			GetParent()->SendMessage(WM_COPYDATA, (WPARAM)m_hWnd, (LPARAM)&cds);
			ShowWindow(SW_HIDE);
			return TRUE;
		}
	}	
	return CEdit::PreTranslateMessage(pMsg);
}
