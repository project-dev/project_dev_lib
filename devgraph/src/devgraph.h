// devgraph.h : DEVGRAPH アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_DEVGRAPH_H__E4CA409E_D2CD_4D0A_9DB4_7D4A9DFD9F37__INCLUDED_)
#define AFX_DEVGRAPH_H__E4CA409E_D2CD_4D0A_9DB4_7D4A9DFD9F37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CDevgraphApp
// このクラスの動作の定義に関しては devgraph.cpp ファイルを参照してください。
//

class CDevgraphApp : public CWinApp
{
public:
	CDevgraphApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDevgraphApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDevgraphApp)
		// メモ -  ClassWizard はこの位置にメンバ関数を追加または削除します。
		//         この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DEVGRAPH_H__E4CA409E_D2CD_4D0A_9DB4_7D4A9DFD9F37__INCLUDED_)
