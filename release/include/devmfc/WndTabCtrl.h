#if !defined(AFX_WNDTABCTRL_H__D4583C36_A019_4DE0_9C8F_CDF01B4EF8CB__INCLUDED_)
#define AFX_WNDTABCTRL_H__D4583C36_A019_4DE0_9C8F_CDF01B4EF8CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WndTabCtrl.h : ヘッダー ファイル
//
#include "TabCtrlEx.h"

/////////////////////////////////////////////////////////////////////////////
// CWndTabCtrl ウィンドウ
#ifdef DEVMFC_EXPORTS
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_IMPORT
#endif

#define WM_HWNDTABCHANGE		WM_APP + 0x200

/**
 * タブのページをCWndで管理するクラス。
 * 各タブには1つのCWndを関連付けることができる。
 * ページ切り替えの際に自動てきにページを切り替える
 */
class DEV_EXT_MFCCLASS CWndTabCtrl : public CTabCtrlEx{
// コンストラクション
public:
	CWndTabCtrl();

// アトリビュート
public:
	void SetPagePosition();
	void GetPageRect(LPRECT rect);
	
// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CWndTabCtrl)
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CWndTabCtrl();
	BOOL AddNewPage(int nItem, LPCTSTR pszText, CWnd *pWnd);
	virtual void SetActivePage(int nIndex);
	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CWndTabCtrl)
	afx_msg void OnMove(int x, int y);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg BOOL OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult );

	DECLARE_MESSAGE_MAP()
private:
	CString m_strHintText;
	int m_nOldPage;
	int m_nNowPage;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_WNDTABCTRL_H__D4583C36_A019_4DE0_9C8F_CDF01B4EF8CB__INCLUDED_)
