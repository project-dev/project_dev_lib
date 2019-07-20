// DevWord.cpp: CDevWord クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "devMsof.h"
#include "DevWord.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

/**
 * @verify コンストラクタ
 */
CDevWord::CDevWord(){
	m_pWord = NULL;
}

/**
 * @verify デストラクタ
 */
CDevWord::~CDevWord(){

}

/**
 * @verify 初期化
 * @return 初期化に成功するとTRUEを返却。
 */
BOOL CDevWord::Initalize(){
	try{
		if(!CDevMsofObject::Initalize()){
			return FALSE;
		}
		HRESULT hRes = m_pWord.CreateInstance( "Word.Application.9");
		if(hRes != S_OK){
			return FALSE;
		}
	}catch(_com_error e){
		ShowComError(e);
		return FALSE;
	}
	
	return TRUE;
}

/**
 * @verify 後処理
 * @return 後処理に成功するとTRUEを返却。
 */
BOOL CDevWord::Finalize(){
	try{
		if(m_pWord){
			m_pWord.Release();
			m_pWord = NULL;
		}
	}catch(_com_error e){
		ShowComError(e);
		return FALSE;
	}
	return TRUE;
}

/**
 * @verify 表示
 * @param bIsShow TRUEをしていすると表示
 * @return 表示に成功するとTRUEを返します。
 */
BOOL CDevWord::Show(BOOL bIsShow){
	try{
		if(m_pWord){
			return TRUE;
		}else{
			return FALSE;
		}
	}catch(_com_error e){
		ShowComError(e);
		return FALSE;
	}
}

/**
 * @verify 終了
 * @param 
 * @return 
 */
BOOL CDevWord::Quit(LPCTSTR pszFileName, BOOL bIsSaveQuit){
	try{
	}catch(_com_error e){
		ShowComError(e);
		return FALSE;
	}
	return TRUE;
}

BOOL CDevWord::Load(LPCTSTR pszFileName){
	try{
	}catch(_com_error e){
		ShowComError(e);
		return FALSE;
	}
	return TRUE;
}

BOOL CDevWord::Save(LPCTSTR pszFileName, BOOL isOverWrite){
	try{
	}catch(_com_error e){
		ShowComError(e);
		return FALSE;
	}
	return TRUE;
}