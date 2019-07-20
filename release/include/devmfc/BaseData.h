// BaseData.h: CBaseData クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASEDATA_H__6859A4D0_4C0A_4226_911F_6D90F2407C8B__INCLUDED_)
#define AFX_BASEDATA_H__6859A4D0_4C0A_4226_911F_6D90F2407C8B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifdef DEVMFC_EXPORTS
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_IMPORT
#endif

class DEV_EXT_MFCCLASS CBaseData {
public:
	CBaseData();
	virtual ~CBaseData();

	static void SetPath();
	static LPCTSTR GetInifilePath();
	static LPCTSTR GetBasePath();

private:	
	static CString m_strBasePath;
	static CString m_strIniFilePath;

};

#endif // !defined(AFX_BASEDATA_H__6859A4D0_4C0A_4226_911F_6D90F2407C8B__INCLUDED_)
