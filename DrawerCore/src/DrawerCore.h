// DrawerCore.h : DRAWERCORE アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_DRAWERCORE_H__822E1639_256A_469D_A820_97E85BA36E13__INCLUDED_)
#define AFX_DRAWERCORE_H__822E1639_256A_469D_A820_97E85BA36E13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CDrawerCoreApp
// このクラスの動作の定義に関しては DrawerCore.cpp ファイルを参照してください。
//

class CDrawerCoreApp : public CWinApp
{
public:
	CDrawerCoreApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDrawerCoreApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDrawerCoreApp)
		// メモ -  ClassWizard はこの位置にメンバ関数を追加または削除します。
		//         この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DRAWERCORE_H__822E1639_256A_469D_A820_97E85BA36E13__INCLUDED_)
