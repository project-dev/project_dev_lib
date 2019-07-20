// RichEditViewEx.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "devmfc.h"
#include "RichEditViewEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRichEditViewEx

IMPLEMENT_DYNCREATE(CRichEditViewEx, CRichEditView)

CRichEditViewEx::CRichEditViewEx()
{
}

CRichEditViewEx::~CRichEditViewEx()
{
}


BEGIN_MESSAGE_MAP(CRichEditViewEx, CRichEditView)
	//{{AFX_MSG_MAP(CRichEditViewEx)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRichEditViewEx 描画

void CRichEditViewEx::OnDraw(CDC* pDC){
	CDocument* pDoc = GetDocument();
	// TODO: この位置に描画用のコードを追加してください
}

/////////////////////////////////////////////////////////////////////////////
// CRichEditViewEx 診断

#ifdef _DEBUG
void CRichEditViewEx::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CRichEditViewEx::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRichEditViewEx メッセージ ハンドラ
