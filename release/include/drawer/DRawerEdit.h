#if !defined(AFX_DRAWEREDIT_H__583EE923_3F06_461A_ACEE_D66BFBD2D144__INCLUDED_)
#define AFX_DRAWEREDIT_H__583EE923_3F06_461A_ACEE_D66BFBD2D144__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DRawerEdit.h : ヘッダー ファイル
//
#include "DrawerCoreDef.h"


/////////////////////////////////////////////////////////////////////////////
// CDRawerEdit ウィンドウ
class DRAWER_EXT_CLASS CDRawerEdit : public CEdit{
// コンストラクション
public:
	CDRawerEdit();

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDRawerEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CDRawerEdit();

	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID );


	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CDRawerEdit)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG


	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DRAWEREDIT_H__583EE923_3F06_461A_ACEE_D66BFBD2D144__INCLUDED_)
