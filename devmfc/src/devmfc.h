// devmfc.h : DEVMFC アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_DEVMFC_H__BBF9495F_66ED_4463_9A94_4992B10E1C0D__INCLUDED_)
#define AFX_DEVMFC_H__BBF9495F_66ED_4463_9A94_4992B10E1C0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CDevmfcApp
// このクラスの動作の定義に関しては devmfc.cpp ファイルを参照してください。
//

class CDevmfcApp : public CWinApp
{
public:
	CDevmfcApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDevmfcApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDevmfcApp)
		// メモ -  ClassWizard はこの位置にメンバ関数を追加または削除します。
		//         この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DEVMFC_H__BBF9495F_66ED_4463_9A94_4992B10E1C0D__INCLUDED_)
