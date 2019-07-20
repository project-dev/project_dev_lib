#if !defined(AFX_RICHEDITVIEWEX_H__5296D702_C919_4486_A9CB_A9A83D1D1F29__INCLUDED_)
#define AFX_RICHEDITVIEWEX_H__5296D702_C919_4486_A9CB_A9A83D1D1F29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RichEditViewEx.h : ヘッダー ファイル
//
#include <afxrich.h>

/////////////////////////////////////////////////////////////////////////////
// CRichEditViewEx ビュー
#ifdef DEVMFC_EXPORTS
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_IMPORT
#endif

class DEV_EXT_MFCCLASS CRichEditViewEx : public CRichEditView 
{
protected:
	CRichEditViewEx();           // 動的生成に使用されるプロテクト コンストラクタ
	DECLARE_DYNCREATE(CRichEditViewEx)

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CRichEditViewEx)
	protected:
	virtual void OnDraw(CDC* pDC);      // このビューを描画するためにオーバーライドしました。
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	virtual ~CRichEditViewEx();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CRichEditViewEx)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_RICHEDITVIEWEX_H__5296D702_C919_4486_A9CB_A9A83D1D1F29__INCLUDED_)
