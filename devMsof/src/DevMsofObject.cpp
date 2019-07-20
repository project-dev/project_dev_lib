// DevMsofObject.cpp: CDevMsofObject クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "devMsof.h"
#include "DevMsofObject.h"
#include <afxdisp.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


BOOL CDevMsofObject::m_bOleInitalized = FALSE;
//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

/**
 * @verify コンストラクタ
 */
CDevMsofObject::CDevMsofObject(){
	m_bShowError = FALSE;
	m_strErrMsg = "";
}

/**
 * @verify デストラクタ
 */
CDevMsofObject::~CDevMsofObject(){
	Finalize();
}

/**
 * @verify 初期化
 */
BOOL CDevMsofObject::Initalize(){
	if(!m_bOleInitalized){
		if ( !::AfxOleInit()){
			m_strErrMsg = "OLEを初期化できません。";
			ShowErrorMsg();
			return FALSE;
		}
    
		// OLE コントロールを包含することを宣言する
		::AfxEnableControlContainer();
		m_bOleInitalized = TRUE;
	}
	HRESULT hRes = ::CoInitialize(NULL);
	if((hRes == S_OK) || (hRes == S_FALSE)){
		return TRUE;
	}
	return FALSE;
}

/**
 * @verify 後処理
 */
BOOL CDevMsofObject::Finalize(){
	::CoUninitialize();
	return TRUE;
}

/**
 * @verify エラーを表示する。
 *ただし、SetShowError関数で引数にFALSEが指定されている場合は、エラーメッセージを保持するのみ
 */
void CDevMsofObject::ShowComError(_com_error e){
	BSTR bError = e.Description();
	const TCHAR *pszMsg = e.ErrorMessage();

	CString strError;
	AfxBSTR2CString(&strError, bError);
	m_strErrMsg.Format("%s\n%s", pszMsg, strError);
	
	ShowErrorMsg();
}

/**
 * @verify エラーメッセージの表示/非表示を設定する
 * @param bShow TRUEで表示。
 */
void CDevMsofObject::SetShowError(BOOL bShow){
	m_bShowError = bShow;
}

/**
 * @verify 現在のエラーメッセージ表示フラグを取得する
 */
BOOL CDevMsofObject::IsShowError(){
	return m_bShowError;
}

/**
 * 一番最後のエラーのエラーメッセージを取得する
 */
LPCTSTR CDevMsofObject::GetLastErrorMsg(){
	return m_strErrMsg;
}

/**
 * @verify エラーメッセージ表示
 */
void CDevMsofObject::ShowErrorMsg(){
	if(m_bShowError){
		::AfxMessageBox(m_strErrMsg);
	}
}

/**
 * @verify エラーメッセージ設定
 */
void CDevMsofObject::SetLastErrorMsg(LPCTSTR pszMsg){
	m_strErrMsg = pszMsg;
}
