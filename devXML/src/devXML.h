// devXML.h : DEVXML アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_DEVXML_H__73C61B02_B9A7_4931_B41B_B8FDA6294D52__INCLUDED_)
#define AFX_DEVXML_H__73C61B02_B9A7_4931_B41B_B8FDA6294D52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CDevXMLApp
// このクラスの動作の定義に関しては devXML.cpp ファイルを参照してください。
//

class CDevXMLApp : public CWinApp
{
public:
	CDevXMLApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDevXMLApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDevXMLApp)
		// メモ -  ClassWizard はこの位置にメンバ関数を追加または削除します。
		//         この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DEVXML_H__73C61B02_B9A7_4931_B41B_B8FDA6294D52__INCLUDED_)
