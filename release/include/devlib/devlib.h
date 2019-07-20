//-------------------------------------------------------------------------------------
// Project D.E.V Liblaly
// - なるべくMFCは使わずに作るようにしましょう(言語依存しないようにするため)
//
//
//
//-------------------------------------------------------------------------------------
/** \mainpage
 * <h1 class="index1">はじめに</h1>
 * Project D.E.V Library はWindows APIに不足している部分を補ったり、
 * MFCのクラスを拡張したクラスが含まれるライブラリです。<BR>
 * 現在、開発途中で、実装が十分でないクラスや関数が存在します。<BR>
 * devlib.h グローバル関数が宣言されています。<BR>
 */

/** 
 * @file devlib.h 
 * グローバル関数が宣言されています。<BR>
 * Windows API の移植/拡張版関数などがあります。
 */

#if !defined(__DEVLIB__)
#define __DEVLIB__

#include <windows.h>
#include <stdio.h>
#include "devtypedef.h"

#ifdef DEVLIB_EXPORTS
	#define DEV_EXT_CLASS		 __declspec(dllexport)
#else
	#define DEV_EXT_CLASS		 __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
	typedef struct tagFILEVERSION{
		char szFileVersion[32];
		char szProductVersion[32];
		char szPrivateBuild[32];
		char szSpecialBuild[32];
	}FILEVERSION, *PFILEVERSION;

	/**
	 * EnumFile 関数のコールバック関数の書式です。
	 */
	typedef bool (CALLBACK *EnumFilesProcFunc)(const char*, WIN32_FIND_DATA*, LPARAM);

	//-------------------------------------------------------------------
	//ファイル関連
	DEV_EXT_CLASS BOOL WINAPI CreateDir(LPCTSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);
	DEV_EXT_CLASS void WINAPI AddDirLastSepalator(char *pszDir);
	DEV_EXT_CLASS BOOL WINAPI RemoveDirectoryEx(LPCTSTR lpDir, BOOL bChildDelete);
	DEV_EXT_CLASS BOOL WINAPI IsFileExsist(LPCTSTR pszFileName);
	DEV_EXT_CLASS BOOL WINAPI IsDir(LPCTSTR pszFileName);
	DEV_EXT_CLASS BOOL WINAPI DeleteFileEx(LPCTSTR pszFileName);
	DEV_EXT_CLASS char* WINAPI GetNowTimeText();

	DEV_EXT_CLASS DWORD WINAPI GetInifileString(const char* lpAppName,
												const char* lpKeyName,
												const char* lpDefault,
												char*		lpRetValue,
												int			nLen,
												const char* lpFileName);
	DEV_EXT_CLASS int WINAPI GetInifileInt(	const char* lpAppName,
											const char* lpKeyName,
											int          nDefault,
											const char* lpFileName);

	DEV_EXT_CLASS BOOL WINAPI WriteInifileString(const char* lpAppName,
												 const char* lpKeyName,
												 const char* lpString,
												 const char* lpFileName );
	DEV_EXT_CLASS BOOL WINAPI WriteInifileInt(	const char* lpAppName,
												const char* lpKeyName,
												int         nValue,
												const char* lpFileName );
	DEV_EXT_CLASS BOOL WINAPI EnumFiles(EnumFilesProcFunc EnumFilesProc,
										const char* strFileName,
										LPARAM lParam);

	DEV_EXT_CLASS bool WINAPI GetFileVerInfo(HMODULE hMod, PFILEVERSION pfv);

	//クリップボード系
	DEV_EXT_CLASS BOOL WINAPI SetTextToClipBoard(HWND hWnd, LPCTSTR pszText, int nLen);

	//デバッグ
	DEV_EXT_CLASS void WINAPI ShowError(DWORD errID);
	DEV_EXT_CLASS void WINAPI ShowSysMsg(DWORD error, char *pszMsg = NULL);

	DEV_EXT_CLASS int WINAPI MsgBoxInfo(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType = MB_OK);
	DEV_EXT_CLASS int WINAPI MsgBoxWarning(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType = MB_OK);
	DEV_EXT_CLASS int WINAPI MsgBoxQuestion(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType = MB_OK);
	DEV_EXT_CLASS int WINAPI MsgBoxErr(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType = MB_OK);

	//メッセージ
	DEV_EXT_CLASS void WINAPI PumpMessage(UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0);
#if __cplusplus
}
#endif

#endif