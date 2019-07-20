#if !defined(AFX_TREECTRLEX_H__2C429E07_2F97_4EEE_970B_655693D5C662__INCLUDED_)
#define AFX_TREECTRLEX_H__2C429E07_2F97_4EEE_970B_655693D5C662__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TreeCtrlEx.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlEx ウィンドウ
#ifdef DEVMFC_EXPORTS
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_IMPORT
#endif
class DEV_EXT_MFCCLASS CTreeCtrlEx : public CTreeCtrl{
// コンストラクション
public:
	CTreeCtrlEx();
	void CancelSearch();

// アトリビュート
public:

// オペレーション
public:
	virtual void ChangeIncrementBuffer(CString strBuff);
// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CTreeCtrlEx)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	void SetIncrementalSearch(BOOL bUse);
	virtual ~CTreeCtrlEx();

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CTreeCtrlEx)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	HTREEITEM FindTreeText(LPCTSTR pszText, HTREEITEM hItem);
	CString m_strKeyBuff;
	BOOL m_bIncSearch;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_TREECTRLEX_H__2C429E07_2F97_4EEE_970B_655693D5C662__INCLUDED_)
