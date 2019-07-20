#if !defined(AFX_PROGRESSSTATUSBAR_H__92ABD1E4_E425_4F61_8573_5CDE7A223AF1__INCLUDED_)
#define AFX_PROGRESSSTATUSBAR_H__92ABD1E4_E425_4F61_8573_5CDE7A223AF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgressStatusBar.h : ヘッダー ファイル
//


/////////////////////////////////////////////////////////////////////////////
// CProgressStatusBar ウィンドウ
#ifdef DEVMFC_EXPORTS
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_IMPORT
#endif

/**
 * ステータスバーの任意の位置にプログレスバーを表示できるステータスバー
 */
class DEV_EXT_MFCCLASS CProgressStatusBar : public CStatusBar{

	// コンストラクション
public:
	CProgressStatusBar();

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CProgressStatusBar)
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	int StepIt( );
	int SetStep( int nStep );
	int OffsetPos( int nPos );
	int SetPos( int nPos );
	int GetPos( );
	void GetRange( int& nLower, int& nUpper );
	void SetRange( short nLower, short nUpper );
	void SetRange32( int nLower, int nUpper );
	UINT ShowProgressBar(int nIndex);
	CProgressCtrl* GetProgressBar();
	virtual ~CProgressStatusBar();

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CProgressStatusBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	CProgressCtrl m_objProgress;
	int m_nIndex;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_PROGRESSSTATUSBAR_H__92ABD1E4_E425_4F61_8573_5CDE7A223AF1__INCLUDED_)
