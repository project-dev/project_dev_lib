// FolderDialog.h: CFolderDialog �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(__DEVLIB_FOLDERDIALOG__)
#define __DEVLIB_FOLDERDIALOG__

#include <windows.h>
#include <Shlobj.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifdef DEVLIB_EXPORTS
	#define DEV_EXT_CLASS		 __declspec(dllexport)
#else
	#define DEV_EXT_CLASS		 __declspec(dllimport)
#endif

/**
 *�t�H���_�I���_�C�A���O�N���X<BR>
 *@author Project D.E.V
 */
class DEV_EXT_CLASS CFolderDialog{
public:
	char* GetFolder();
	CFolderDialog(HWND hWnd, 
				  char *pszDisplayName, 
				  char *pszTitle = "�t�H���_�̑I��", 
				  char *pszRootDit = NULL);
	BOOL DoModal();
	virtual ~CFolderDialog();
	static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);

private:
	BROWSEINFO m_objBrowInfo;
	char m_szDispName[1024];
	char m_szTitle[1024];
	char m_szPath[MAX_PATH];
};

#endif // !defined(__DEVLIB_FOLDERDIALOG__)
