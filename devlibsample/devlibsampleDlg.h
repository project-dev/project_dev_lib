// devlibsampleDlg.h : ヘッダー ファイル
//

#if !defined(AFX_DEVLIBSAMPLEDLG_H__A665300C_6A57_4535_BE4F_DA6CBC8B2CC8__INCLUDED_)
#define AFX_DEVLIBSAMPLEDLG_H__A665300C_6A57_4535_BE4F_DA6CBC8B2CC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSampleDlg ダイアログ

class CSampleDlg : public CDialog
{
// 構築
public:
	CSampleDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CSampleDlg)
	enum { IDD = IDD_DEVLIBSAMPLE_DIALOG };
		// メモ: この位置に ClassWizard によってデータ メンバが追加されます。
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CSampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnIniread();
	afx_msg void OnBtnIniwrite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DEVLIBSAMPLEDLG_H__A665300C_6A57_4535_BE4F_DA6CBC8B2CC8__INCLUDED_)
