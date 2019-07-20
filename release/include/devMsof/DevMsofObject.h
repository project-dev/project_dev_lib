// DevMsofObject.h: CDevMsofObject クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVMSOFOBJECT_H__22686B4D_2752_4C1C_B0DC_B93237A6BB90__INCLUDED_)
#define AFX_DEVMSOFOBJECT_H__22686B4D_2752_4C1C_B0DC_B93237A6BB90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MsImport.h"
#include <AfxPriv2.h>

#ifdef DEV_EXP
	#define DEV_EXPORT __declspec( dllexport )
#else
	#define DEV_EXPORT __declspec( dllimport )
#endif

/**
 * @verify 基底クラス
 */
class DEV_EXPORT CDevMsofObject{
public:
	void SetShowError(BOOL bShow);
	BOOL IsShowError();
	LPCTSTR GetLastErrorMsg();
	CDevMsofObject();
	virtual ~CDevMsofObject();
	virtual BOOL Show(BOOL bIsSHow) = 0;
	virtual BOOL Quit(LPCTSTR pszFileName, BOOL bIsSaveQuit) = 0;
	BOOL Initalize();
	BOOL Finalize();

private:
	///OLEの初期化が完了しているかどうか
	static m_bOleInitalized;

	///エラーメッセージ
	CString m_strErrMsg;

	///エラーメッセージを表示するかどうか
	BOOL m_bShowError;
protected:
	void ShowErrorMsg();
	void ShowComError(_com_error e);
	void SetLastErrorMsg(LPCTSTR pszMsg);

};

#endif // !defined(AFX_DEVMSOFOBJECT_H__22686B4D_2752_4C1C_B0DC_B93237A6BB90__INCLUDED_)
