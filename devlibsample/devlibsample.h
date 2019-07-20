// devlibsample.h : DEVLIBSAMPLE アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_DEVLIBSAMPLE_H__D9CF2AC6_C6BA_4983_94FF_542061A20D5F__INCLUDED_)
#define AFX_DEVLIBSAMPLE_H__D9CF2AC6_C6BA_4983_94FF_542061A20D5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CLibSampApp:
// このクラスの動作の定義に関しては devlibsample.cpp ファイルを参照してください。
//

class CLibSampApp : public CWinApp
{
public:
	CLibSampApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CLibSampApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CLibSampApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DEVLIBSAMPLE_H__D9CF2AC6_C6BA_4983_94FF_542061A20D5F__INCLUDED_)
