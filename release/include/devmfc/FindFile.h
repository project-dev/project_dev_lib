// FindFile.h: CFindFile クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FINDFILE_H__C07D0231_4C67_4E27_B0DD_A7ACE8A18042__INCLUDED_)
#define AFX_FINDFILE_H__C07D0231_4C67_4E27_B0DD_A7ACE8A18042__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifdef DEVMFC_EXPORTS
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_IMPORT
#endif

typedef BOOL (WINAPI *PFindCallBack)(LPCTSTR pszDir, WIN32_FIND_DATA &wfd);
typedef BOOL (WINAPI *PPreFindNextCallBack)();
 
class DEV_EXT_MFCCLASS CFindFile{
public:
	BOOL GetFileName(int nIndex, CString &strFileName);
	int GetCount();
	BOOL IsDirectory(WIN32_FIND_DATA *wfd);
	void SetCallBack(PFindCallBack pCallBack, PPreFindNextCallBack pPreFindNextBack);
	int FindFile(LPCTSTR pszDir, LPCTSTR pszFind, BOOL bFileOnly = FALSE, BOOL bSubDir = FALSE);
	CFindFile();
	virtual ~CFindFile();
	static BOOL IsExistFile(LPCTSTR pszFile);
private:
	int PrivateFindFile(LPCTSTR pszDir, LPCTSTR pszSubDir, LPCTSTR pszFind, BOOL bFileOnly = FALSE, BOOL bSubDir = FALSE);
	CStringArray m_arrFindFile;
	PFindCallBack FindCallBack;
	PPreFindNextCallBack PreFindNextCallBack;
};

#endif // !defined(AFX_FINDFILE_H__C07D0231_4C67_4E27_B0DD_A7ACE8A18042__INCLUDED_)
