// FileDialogEx.h: CFileDialogEx クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(__DEVLIB_FILEDIALOGEX__)
#define __DEVLIB_FILEDIALOGEX__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <windows.h>
#include <Commdlg.h>
#ifdef DEVLIB_EXPORTS
	#define DEV_EXT_CLASS		 __declspec(dllexport)
#else
	#define DEV_EXT_CLASS		 __declspec(dllimport)
#endif

/**
 * @brief ファイルダイアログクラス
 * @author Project D.E.V
 */
class DEV_EXT_CLASS CFileDialogEx{
public:
	char* GetFileName();
	
	CFileDialogEx(HWND hwndOwner,
				  HINSTANCE hInstance,
				  LPTSTR  lpstrFile, 
				  LPTSTR  lpstrFileTitle, 
				  LPCTSTR lpstrFilter, 
				  DWORD   nFilterIndex, 
				  LPCTSTR lpstrInitialDir, 
				  LPCTSTR lpstrTitle, 
				  LPCTSTR lpstrDefExt);

	int DoModal();
	virtual ~CFileDialogEx();


protected:
	OPENFILENAME m_ofn;

private:
	char *m_lpstrFile;
	char *m_lpstrFileTitle;
	char *m_lpstrFilter;
	char *m_lpstrInitialDir;
	char *m_lpstrTitle;
	char *m_lpstrDefExt;
};

#endif // !defined(__DEVLIB_FILEDIALOGEX__)
