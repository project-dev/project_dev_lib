// FileDialogEx.cpp: CFileDialogEx クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileDialogEx.h"

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

/**
 * @brief コンストラクタ
 * @param 
 * @param hwndOwner       ウィンドウハンドル
 * @param hInstance       インスタンスハンドル
 * @param lpstrFile       ファイル名
 * @param lpstrFileTitle  タイトル
 * @param lpstrFilter     フィルタ
 * @param nFilterIndex    フィルタインデックス
 * @param lpstrInitialDir 初期フォルダ
 * @param lpstrTitle      タイトル
 * @param lpstrDefExt     拡張子
 */
CFileDialogEx::CFileDialogEx( HWND hwndOwner,
							  HINSTANCE hInstance,
							  LPTSTR  lpstrFile, 
							  LPTSTR  lpstrFileTitle, 
							  LPCTSTR lpstrFilter, 
							  DWORD   nFilterIndex, 
							  LPCTSTR lpstrInitialDir, 
							  LPCTSTR lpstrTitle, 
							  LPCTSTR lpstrDefExt){
	memset(&m_ofn, 0, sizeof(OPENFILENAME));

	m_lpstrFile			= NULL;
	m_lpstrFileTitle	= NULL;
	m_lpstrFilter		= NULL;
	m_lpstrInitialDir	= NULL;
	m_lpstrTitle		= NULL;
	m_lpstrDefExt		= NULL;

	m_lpstrFile = new char[MAX_PATH];
	memset(m_lpstrFile, 0, MAX_PATH);
	if(lpstrFile && strlen(lpstrFile)){
		strcpy(m_lpstrFile, lpstrFile);
	}

	if(lpstrFileTitle && strlen(lpstrFileTitle)){
		m_lpstrFileTitle = new char[strlen(lpstrFileTitle) + 1];
		memset(m_lpstrFileTitle, 0, strlen(lpstrFileTitle) + 1);
		strcpy(m_lpstrFileTitle, lpstrFileTitle);
	}

	if(lpstrFilter && strlen(lpstrFilter)){
		m_lpstrFilter = new char[strlen(lpstrFilter) + 1];
		memset(m_lpstrFilter, 0, strlen(lpstrFilter) + 1);
		strcpy(m_lpstrFilter, lpstrFilter);
	}

	if(lpstrInitialDir && strlen(lpstrInitialDir)){
		m_lpstrInitialDir = new char[strlen(lpstrInitialDir) + 1];
		memset(m_lpstrInitialDir, 0, strlen(lpstrInitialDir) + 1);
		strcpy(m_lpstrInitialDir, lpstrInitialDir);
	}

	if(lpstrTitle && strlen(lpstrTitle)){
		m_lpstrTitle = new char[strlen(lpstrTitle) + 1];
		memset(m_lpstrTitle, 0, strlen(lpstrTitle) + 1);
		strcpy(m_lpstrTitle, lpstrTitle);
	}

	if(lpstrDefExt && strlen(lpstrDefExt)){
		m_lpstrDefExt = new char[strlen(lpstrDefExt) + 1];
		memset(m_lpstrDefExt, 0, strlen(lpstrDefExt) + 1);
		strcpy(m_lpstrDefExt, lpstrDefExt);
	}

	m_ofn.Flags				= OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_ENABLESIZING | OFN_HIDEREADONLY;
	m_ofn.lStructSize		= sizeof(OPENFILENAME);
	m_ofn.hwndOwner			= hwndOwner;
	m_ofn.hInstance			= hInstance;
	m_ofn.lpstrFile			= m_lpstrFile;
	m_ofn.nMaxFile			= MAX_PATH;
	m_ofn.lpstrFileTitle	= m_lpstrFileTitle;
	m_ofn.nMaxFileTitle		= m_lpstrFileTitle ? strlen(m_lpstrFileTitle) : 0;
	m_ofn.lpstrFilter		= lpstrFilter;
	m_ofn.nFilterIndex		= nFilterIndex;
	m_ofn.lpstrInitialDir	= lpstrInitialDir;
	m_ofn.lpstrTitle		= lpstrTitle;
	m_ofn.lpstrDefExt		= lpstrDefExt;
}

/**
 * @brief デストラクタ
 */
CFileDialogEx::~CFileDialogEx(){
	
	if(m_lpstrFile){
		delete m_lpstrFile;
		m_lpstrFile = NULL;
	}

	if(m_lpstrFileTitle){
		delete m_lpstrFileTitle;
		m_lpstrFileTitle = NULL;
	}

	if(m_lpstrFilter){
		delete m_lpstrFilter;
		m_lpstrFilter = NULL;
	}

	if(m_lpstrInitialDir){
		delete m_lpstrInitialDir;
		m_lpstrInitialDir = NULL;
	}

	if(m_lpstrTitle){
		delete m_lpstrTitle;
		m_lpstrTitle = NULL;
	}

	if(m_lpstrDefExt){
		delete m_lpstrDefExt;
		m_lpstrDefExt = NULL;
	}
}

/**
 * @brief ファイル選択ダイアログを表示する
 * @return 開くを押された場合はIDOK、キャンセルはIDCANCEL
 */
int CFileDialogEx::DoModal(){
	if(!GetOpenFileName(&m_ofn)){
		return IDCANCEL;
	}
	return IDOK;
}

/**
 * @brief 選択されたファイルを取得する
 * @return ファイル名
 */
char* CFileDialogEx::GetFileName(){
	return m_ofn.lpstrFile;
}
