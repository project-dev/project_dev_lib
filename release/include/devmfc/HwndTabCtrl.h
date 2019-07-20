#if !defined(AFX_HWNDTABCTRL_H__79D6A8D2_9F45_42C2_83CA_65D6007BA8A0__INCLUDED_)
#define AFX_HWNDTABCTRL_H__79D6A8D2_9F45_42C2_83CA_65D6007BA8A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustTabCtrl.h : ヘッダー ファイル
//

#include "TabCtrlEx.h"

#ifdef DEVMFC_EXPORTS
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_IMPORT
#endif

#define WM_HWNDTABCHANGE		WM_APP + 0x200

/**
 * タブのページをHWNDdeで管理するクラス。
 * 各タブには1つのHWNDを関連付けることができる。
 * ページ切り替えの際に自動てきにページを切り替える
 */
class DEV_EXT_MFCCLASS CHwndTabCtrl : public CTabCtrlEx{
// コンストラクション
public:
	CHwndTabCtrl();

// アトリビュート
public:

// オペレーション
public:
	void SetPagePosition();
// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CHwndTabCtrl)
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	BOOL AddNewPage(int nItem, LPCTSTR pszText, HWND hWnd);
	virtual void SetActivePage(int nIndex);
	virtual ~CHwndTabCtrl();

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CHwndTabCtrl)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	int m_nOldPage;
	int m_nNowPage;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CUSTTABCTRL_H__79D6A8D2_9F45_42C2_83CA_65D6007BA8A0__INCLUDED_)
