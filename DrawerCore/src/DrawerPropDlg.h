#if !defined(AFX_DRAWERPROPDLG_H__4F4F4020_2528_4098_BA4C_26552454317C__INCLUDED_)
#define AFX_DRAWERPROPDLG_H__4F4F4020_2528_4098_BA4C_26552454317C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DrawerPropDlg.h : ヘッダー ファイル
//
#include "TabCtrlEx.h"

/////////////////////////////////////////////////////////////////////////////
// CDrawerPropDlg ダイアログ
class CDrawerCtrl;

class CDrawerPropDlg : public CDialog
{
// コンストラクション
public:
	CDrawerPropDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ
	CDrawerCtrl *m_pCtrl;
// ダイアログ データ
	//{{AFX_DATA(CDrawerPropDlg)
	enum { IDD = IDD_PROP_DLG };
	CTabCtrlEx	m_objTab;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDrawerPropDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL


// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDrawerPropDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DRAWERPROPDLG_H__4F4F4020_2528_4098_BA4C_26552454317C__INCLUDED_)
