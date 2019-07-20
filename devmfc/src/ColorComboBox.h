#if !defined(AFX_COLORCOMBOBOX_H__01BA5612_C1DA_45A6_9CA0_F0D3EB753A07__INCLUDED_)
#define AFX_COLORCOMBOBOX_H__01BA5612_C1DA_45A6_9CA0_F0D3EB753A07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorComboBox.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CColorComboBox ウィンドウ

class CColorComboBox : public CComboBox{
// コンストラクション
public:
	CColorComboBox();

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CColorComboBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParent, UINT uID);
	virtual ~CColorComboBox();

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CColorComboBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_COLORCOMBOBOX_H__01BA5612_C1DA_45A6_9CA0_F0D3EB753A07__INCLUDED_)
