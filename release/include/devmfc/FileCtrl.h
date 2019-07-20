// FileCtrl.h: CFileCtrl クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILECTRL_H__8773FF28_09EE_4ED7_ADBB_5D5A2C2A6A78__INCLUDED_)
#define AFX_FILECTRL_H__8773FF28_09EE_4ED7_ADBB_5D5A2C2A6A78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifdef DEVMFC_EXPORTS
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_IMPORT
#endif

class DEV_EXT_MFCCLASS CFileCtrl {
public:
	static BOOL IsExistDir(LPCTSTR pszDir);
	CFileCtrl();
	virtual ~CFileCtrl();

	static BOOL CreateDirectory(LPCTSTR pszDir);
};

#endif // !defined(AFX_FILECTRL_H__8773FF28_09EE_4ED7_ADBB_5D5A2C2A6A78__INCLUDED_)
