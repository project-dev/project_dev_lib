// TreeCtrlEx.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "devmfc.h"
#include "TreeCtrlEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlEx

CTreeCtrlEx::CTreeCtrlEx(){
	m_bIncSearch = FALSE;
}

CTreeCtrlEx::~CTreeCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CTreeCtrlEx, CTreeCtrl)
	//{{AFX_MSG_MAP(CTreeCtrlEx)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlEx メッセージ ハンドラ

void CTreeCtrlEx::SetIncrementalSearch(BOOL bUse){
	m_bIncSearch = bUse;
}

void CTreeCtrlEx::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){

	if(!m_bIncSearch){
		//インクリメンタルサーチ無効時
		CTreeCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
		return;
	}

	SHORT sShift = ::GetKeyState(VK_SHIFT);
	BOOL bShift = sShift & 0x80;

	SHORT sCaps = ::GetKeyState(VK_CAPITAL);
	BOOL bCaps = sCaps & 0x01;

	DWORD dwCode	= nChar;
	BOOL bSearch = TRUE;
	
	if((dwCode >= 0x30) && (dwCode <= 0x39)){
		//数値
		m_strKeyBuff += (char)dwCode;
		ChangeIncrementBuffer(m_strKeyBuff);

	}else if((dwCode >= 0x41) && (dwCode <= 0x5A)){
		//英字
		if(bShift){
			if(bCaps){
				m_strKeyBuff += (char)(dwCode + 0x20);
			}else{
				m_strKeyBuff += (char)dwCode;
			}
		}else{
			if(bCaps){
				m_strKeyBuff += (char)dwCode;
			}else{
				m_strKeyBuff += (char)(dwCode + 0x20);
			}
		}
		ChangeIncrementBuffer(m_strKeyBuff);
	
	}else if((dwCode >= 0x60) && (dwCode <= 0x69)){
		//数値(テンキー)
		m_strKeyBuff += (char)(dwCode - 0x30);
		ChangeIncrementBuffer(m_strKeyBuff);
	
	}else if((dwCode == 0xE2) && bShift){
		//_ 押下
		m_strKeyBuff += "_";
		ChangeIncrementBuffer(m_strKeyBuff);
	
	}else if((dwCode == VK_DECIMAL) || (dwCode == 0xBE)){
		//_ 押下
		m_strKeyBuff += ".";
		ChangeIncrementBuffer(m_strKeyBuff);
		
	}else if(dwCode == VK_SPACE){
		//_ 押下
		m_strKeyBuff += " ";
		ChangeIncrementBuffer(m_strKeyBuff);
	
	}else if((dwCode == VK_SHIFT)
	      || (dwCode == VK_CAPITAL)
		  || (dwCode == 0xF0)
	){
		//無視
		bSearch = FALSE;
	}else{
		m_strKeyBuff.Empty();
		bSearch = FALSE;
		ChangeIncrementBuffer(m_strKeyBuff);
	}	

	if(!bSearch){
		//検索しない
		CTreeCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
		return;
	}

	//ツリーを検索
	HTREEITEM hItem = GetSelectedItem();
	FindTreeText(m_strKeyBuff, hItem);
}

void CTreeCtrlEx::CancelSearch(){
	m_strKeyBuff.Empty();
	ChangeIncrementBuffer(m_strKeyBuff);
}

HTREEITEM CTreeCtrlEx::FindTreeText(LPCTSTR pszText, HTREEITEM hItem){
	CString strItemText;
	CString strFindText = pszText;
	CString strTarget;
	while(hItem != NULL){
		strItemText = GetItemText(hItem);
		if(strItemText.GetLength() >= strFindText.GetLength()){
			strTarget = strItemText.Left(strFindText.GetLength());
			if(!strTarget.Compare(strFindText)){
				SelectItem(hItem);
				return hItem;
			}
		}

		if(ItemHasChildren(hItem)){
			HTREEITEM hChild = GetChildItem(hItem);
			HTREEITEM retItem = FindTreeText(pszText, hChild);
			if(retItem){
				Expand(hItem, TVE_EXPAND);
				return retItem;
			}
		}
		hItem = GetNextItem(hItem, TVGN_NEXT);
	}
	return NULL;

}

BOOL CTreeCtrlEx::PreTranslateMessage(MSG* pMsg){
	switch(pMsg->message){
	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MOUSEWHEEL:
		CancelSearch();
		break;
	case WM_NOTIFY:
		{
			NMHDR *pNmhdr = (NMHDR*)pMsg->lParam;
			switch(pNmhdr->code){
			case TVN_DELETEITEM:
			case TVN_ENDLABELEDIT:
			case TVN_ITEMEXPANDED:
			case TVN_SELCHANGED:
			case NM_KILLFOCUS:
				CancelSearch();
				break;
			}
		}
		break;
	}	
	return CTreeCtrl::PreTranslateMessage(pMsg);
}

void CTreeCtrlEx::ChangeIncrementBuffer(CString strBuff){
}

