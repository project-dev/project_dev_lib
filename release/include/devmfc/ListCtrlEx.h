#if !defined(AFX_LISTCTRLEX_H__2162378B_9793_4194_A299_183F4C6F9E39__INCLUDED_)
#define AFX_LISTCTRLEX_H__2162378B_9793_4194_A299_183F4C6F9E39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListCtrlEx.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx ウィンドウ
#ifdef DEVMFC_EXPORTS
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_IMPORT
#endif

/**
 *拡張されたCListCtrlクラス<BR>
 */
class DEV_EXT_MFCCLASS CListCtrlEx : public CListCtrl{
// コンストラクション
public:
	CListCtrlEx();

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CListCtrlEx)
	public:
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	void SetAllColumnWidth();
	BOOL Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID );


	virtual ~CListCtrlEx();

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CListCtrlEx)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_LISTCTRLEX_H__2162378B_9793_4194_A299_183F4C6F9E39__INCLUDED_)
