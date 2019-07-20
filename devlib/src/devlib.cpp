// devlib.cpp : DLL アプリケーション用のエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "devlib.h"
#include "DebugSupport.h"
#include <crtdbg.h>
#include "LogFile.h"
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 ){
#ifdef _DEBUG
	CLogFile::SetLogState(TRUE);
	CLogFile::SetDevLibLogState(TRUE);
#else
	CLogFile::SetDevLibLogState(FALSE);
#endif
	switch(ul_reason_for_call){
	case DLL_PROCESS_ATTACH:
		CLogFile::SaveDevLibLog("DLL_PROCESS_ATTACH - devlib.dll DLL Main");
		break;
	case DLL_THREAD_ATTACH:
		CLogFile::SaveDevLibLog("DLL_THREAD_ATTACH  - devlib.dll DLL Main");
		break;
	case DLL_THREAD_DETACH:
		CLogFile::SaveDevLibLog("DLL_THREAD_DETACH  - devlib.dll DLL Main");
		break;
	case DLL_PROCESS_DETACH:
		CLogFile::SaveDevLibLog("DLL_PROCESS_DETACH - devlib.dll DLL Main");
		break;
	}
//	_CrtSetBreakAlloc(54);
//	_CrtSetBreakAlloc(53);
  return TRUE;
}

/**
 * @brief 文字列をクリップボードに転送する
 *
 * @param hWnd ウィンドウハンドル
 * @param pszText クリップボードに転送する文字列
 * @param nLen 文字列の長さ
 * @return 成功した場合は trueを返す
 */
BOOL WINAPI SetTextToClipBoard(HWND hWnd, LPCTSTR pszText, int nLen){
	HGLOBAL hMem;
	LPTSTR lpMem;

	//メモリオブジェクト確保
	hMem = GlobalAlloc(GHND, nLen);
	if(!hMem){
		::MessageBox(hWnd, "コピーに失敗しました", "エラー", MB_OK);
		return FALSE;
	}
	
	//メモリオブジェクトをロックしてアドレスを取得 
	lpMem = (LPTSTR)GlobalLock(hMem);
	if(!hMem){
		if(!::GlobalFree(hMem)){
			::MessageBox(hWnd, "コピーに失敗しました", "エラー", MB_OK);
		}else{
			::MessageBox(hWnd, "コピーに失敗しました", "エラー", MB_OK);
		}
		return FALSE;
	}

	//メモリオブジェクトに文字列を書き込む 
	lstrcpy(lpMem, pszText);

	//クリップボードへコピー
	if(!::OpenClipboard(hWnd)){
		::MessageBox(hWnd, "クリップボードのオープンに失敗しました", "エラー", MB_OK);
		return FALSE;
	}

	if(!::EmptyClipboard()){
		::MessageBox(hWnd, "クリップボードのオープンに失敗しました", "エラー", MB_OK);
		if(!::CloseClipboard()){
			::MessageBox(hWnd, "クリップボードのクローズに失敗しました。", "エラー", MB_OK);
		}
		return FALSE;
	}

	// クリップボードにメモリオブジェクトの文字列をコピー
	HANDLE hRes = ::SetClipboardData(CF_TEXT, hMem);
	if(!hRes){
		::MessageBox(hWnd, "コピーに失敗しました", "エラー", MB_OK);
		if(!::CloseClipboard()){
			::MessageBox(hWnd, "クリップボードのクローズに失敗しました。", "エラー", MB_OK);
		}
		return FALSE;
	}

	//クリップボードを閉じる
	if(!::CloseClipboard()){
		::MessageBox(hWnd, "クリップボードのクローズに失敗しました。", "エラー", MB_OK);
		return FALSE;
	}
	return TRUE;

}

/**
 * @brief メッセージボックスの表示(インフォメーション用)
 *
 * @param hWnd ウィンドウハンドル
 * @param pszText 表示メッセージ
 * @param lpCaption メッセージボックスのタイトル
 * @param uType ボタンのタイプ
 */
int WINAPI MsgBoxInfo(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType){
	
	uType &= ~MB_ICONEXCLAMATION | MB_ICONINFORMATION | MB_ICONQUESTION | MB_ICONSTOP;
	uType |= MB_ICONINFORMATION;
	
	int nLen = strlen(lpText);
	char *pszMsg = new char[nLen + 10];
	strcpy(pszMsg, "INF : ");
	strcat(pszMsg, lpText);
	CDebugSupport::OutputDebugLog(pszMsg);
	delete pszMsg;

	return ::MessageBox(hWnd, lpText, lpCaption, uType);
}

/**
 * @brief メッセージボックスの表示(警告用)
  *
* @param hWnd ウィンドウハンドル
 * @param pszText 表示メッセージ
 * @param lpCaption メッセージボックスのタイトル
 * @param uType ボタンのタイプ
 */
int WINAPI MsgBoxWarning(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType){
	uType &= ~MB_ICONEXCLAMATION | MB_ICONINFORMATION | MB_ICONQUESTION | MB_ICONSTOP;
	uType |= MB_ICONEXCLAMATION;
	
	int nLen = strlen(lpText);
	char *pszMsg = new char[nLen + 10];
	strcpy(pszMsg, "WAR : ");
	strcat(pszMsg, lpText);
	CDebugSupport::OutputDebugLog(pszMsg);
	delete pszMsg;

	return ::MessageBox(hWnd, lpText, lpCaption, uType);
}

/**
 *メッセージボックスの表示(確認用)
 *
 * @param hWnd ウィンドウハンドル
 * @param pszText 表示メッセージ
 * @param lpCaption メッセージボックスのタイトル
 * @param uType ボタンのタイプ
 */
int WINAPI MsgBoxQuestion(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType){
	uType &= ~MB_ICONEXCLAMATION | MB_ICONINFORMATION | MB_ICONQUESTION | MB_ICONSTOP;
	uType |= MB_ICONQUESTION;
	return ::MessageBox(hWnd, lpText, lpCaption, uType);
}

/**
 * @brief メッセージボックスの表示(エラー用)
 *
 * @param hWnd ウィンドウハンドル
 * @param pszText 表示メッセージ
 * @param lpCaption メッセージボックスのタイトル
 * @param uType ボタンのタイプ
 */
int WINAPI MsgBoxErr(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType){
	uType &= ~MB_ICONEXCLAMATION | MB_ICONINFORMATION | MB_ICONQUESTION | MB_ICONSTOP;
	uType |= MB_ICONSTOP;

	int nLen = strlen(lpText);
	char *pszMsg = new char[nLen + 10];
	strcpy(pszMsg, "ERR : ");
	strcat(pszMsg, lpText);
	CDebugSupport::OutputDebugLog(pszMsg);
	delete pszMsg;
	
	return ::MessageBox(hWnd, lpText, lpCaption, uType);
}
