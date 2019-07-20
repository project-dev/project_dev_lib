#if !defined(AFX_TABVIEW_H__2A453483_0A1A_4C14_AB3E_CB507E2E900C__INCLUDED_)
#define AFX_TABVIEW_H__2A453483_0A1A_4C14_AB3E_CB507E2E900C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BaseTabView.h : ヘッダー ファイル
//

#include "HwndTabCtrl.h"



#ifdef DEVMFC_EXPORTS
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_IMPORT
#endif

/**
 * CHwndTabCtrlをメンバとして持つビュー。
 */
class DEV_EXT_MFCCLASS CTabView : public CView{
protected:
	CTabView();           // 動的生成に使用されるプロテクト コンストラクタ
	DECLARE_DYNCREATE(CTabView)

// アトリビュート
public:

// オペレーション
public:
	CHwndTabCtrl& GetTabCtrl();
	int CreatePage(int nIndex, LPCTSTR strTitle, HWND hWNd);
	virtual void OnSelChangeFunc(NMHDR* pNMHDR, LRESULT* pResult);
// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CTabView)
	protected:
	virtual void OnDraw(CDC* pDC);      // このビューを描画するためにオーバーライドしました。
	//afx_msg void OnSelchange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSelchange(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	virtual ~CTabView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CTabView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CHwndTabCtrl m_objTabCtrl;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_BASETABVIEW_H__2A453483_0A1A_4C14_AB3E_CB507E2E900C__INCLUDED_)
