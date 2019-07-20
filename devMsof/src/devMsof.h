// devMsof.h : DEVMSOF アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_DEVMSOF_H__81A6CAED_DA1D_4167_B3D6_3C87612C413C__INCLUDED_)
#define AFX_DEVMSOF_H__81A6CAED_DA1D_4167_B3D6_3C87612C413C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CDevMsofApp
// このクラスの動作の定義に関しては devMsof.cpp ファイルを参照してください。
//

class CDevMsofApp : public CWinApp
{
public:
	CDevMsofApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDevMsofApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDevMsofApp)
		// メモ -  ClassWizard はこの位置にメンバ関数を追加または削除します。
		//         この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DEVMSOF_H__81A6CAED_DA1D_4167_B3D6_3C87612C413C__INCLUDED_)
