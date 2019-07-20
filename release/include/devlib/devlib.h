//-------------------------------------------------------------------------------------
// Project D.E.V Liblaly
// - �Ȃ�ׂ�MFC�͎g�킸�ɍ��悤�ɂ��܂��傤(����ˑ����Ȃ��悤�ɂ��邽��)
//
//
//
//-------------------------------------------------------------------------------------
/** \mainpage
 * <h1 class="index1">�͂��߂�</h1>
 * Project D.E.V Library ��Windows API�ɕs�����Ă��镔����������A
 * MFC�̃N���X���g�������N���X���܂܂�郉�C�u�����ł��B<BR>
 * ���݁A�J���r���ŁA�������\���łȂ��N���X��֐������݂��܂��B<BR>
 * devlib.h �O���[�o���֐����錾����Ă��܂��B<BR>
 */

/** 
 * @file devlib.h 
 * �O���[�o���֐����錾����Ă��܂��B<BR>
 * Windows API �̈ڐA/�g���Ŋ֐��Ȃǂ�����܂��B
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
	 * EnumFile �֐��̃R�[���o�b�N�֐��̏����ł��B
	 */
	typedef bool (CALLBACK *EnumFilesProcFunc)(const char*, WIN32_FIND_DATA*, LPARAM);

	//-------------------------------------------------------------------
	//�t�@�C���֘A
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

	//�N���b�v�{�[�h�n
	DEV_EXT_CLASS BOOL WINAPI SetTextToClipBoard(HWND hWnd, LPCTSTR pszText, int nLen);

	//�f�o�b�O
	DEV_EXT_CLASS void WINAPI ShowError(DWORD errID);
	DEV_EXT_CLASS void WINAPI ShowSysMsg(DWORD error, char *pszMsg = NULL);

	DEV_EXT_CLASS int WINAPI MsgBoxInfo(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType = MB_OK);
	DEV_EXT_CLASS int WINAPI MsgBoxWarning(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType = MB_OK);
	DEV_EXT_CLASS int WINAPI MsgBoxQuestion(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType = MB_OK);
	DEV_EXT_CLASS int WINAPI MsgBoxErr(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType = MB_OK);

	//���b�Z�[�W
	DEV_EXT_CLASS void WINAPI PumpMessage(UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0);
#if __cplusplus
}
#endif

#endif