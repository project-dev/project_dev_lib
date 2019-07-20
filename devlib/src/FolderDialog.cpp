// FolderDialog.cpp: CFolderDialog クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FolderDialog.h"

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

/**
 * @brief デストラクタ
 */
CFolderDialog::~CFolderDialog(){
}

/**
 * @brief コンストラクタ
 * @param hwndOwner       ウィンドウハンドル
 * @param pszDisplayName  表示名
 * @param pszTitle        タイトル
 * @param pszRootDir      ルートディレクトリ
 */
CFolderDialog::CFolderDialog(HWND hWnd,
							 char *pszDisplayName,
							 char *pszTitle /*= "フォルダの選択"*/,
							 char *pszRootDir /* = NULL */){
	memset(&m_objBrowInfo, 0, sizeof(BROWSEINFO));

	memset(m_szDispName, 0, 1024);
	memset(m_szTitle, 0, 1024);

	strcpy(m_szDispName, pszDisplayName);
	strcpy(m_szTitle, pszTitle);

	m_objBrowInfo.hwndOwner			= hWnd;
	m_objBrowInfo.pidlRoot			= NULL;
	m_objBrowInfo.pszDisplayName	= m_szDispName;
	m_objBrowInfo.lpszTitle			= m_szTitle;
	m_objBrowInfo.ulFlags			= BIF_RETURNONLYFSDIRS;
	m_objBrowInfo.lpfn				= BrowseCallbackProc;
	m_objBrowInfo.lParam			= (LPARAM)pszRootDir;
	m_objBrowInfo.iImage			= 0;
}

/**
 * @brief コールバック
 */
int CALLBACK CFolderDialog::BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData){
    // 初期化処理
    if( uMsg == BFFM_INITIALIZED){
        SendMessage(hWnd, BFFM_SETSELECTION, (WPARAM)TRUE, lpData);
    }
    return 0;
}

/**
 * @brief フォルダ選択ダイアログを表示する
 * @return フォルダが選択された場合はTRUE
 */
BOOL CFolderDialog::DoModal(){
	
	LPMALLOC g_pMalloc = NULL;
	LPITEMIDLIST pList;
	BOOL bRet = FALSE;
	memset(m_szPath, 0, MAX_PATH);

	//COMの初期化
	HRESULT hRes = ::CoInitialize(NULL);
	if(FAILED(hRes)){
		return bRet;
	}

	HRESULT hr = ::SHGetMalloc(&g_pMalloc);
	if(FAILED(hr)){
		return bRet;
	}
	
	//フォルダ選択ダイアログの表示
	pList = ::SHBrowseForFolder(&m_objBrowInfo);

	//実際のパスを取得
	if(pList && ::SHGetPathFromIDList(pList, m_szPath)){
		bRet = TRUE;
		g_pMalloc->Free(pList);
	}

	if(hRes == S_OK){
		//COMの解放
		::CoUninitialize();
	}
	
	return bRet;
}

/**
 * @brief 選択されたパスを取得する
 * @return 選択されたパス
 */
char* CFolderDialog::GetFolder(){
	return m_szPath;
}
