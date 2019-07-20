// ColumnInfo.h: CColumnInfo クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLUMNINFO_H__4872C481_D4E4_43B8_B16E_0D757F4C856F__INCLUDED_)
#define AFX_COLUMNINFO_H__4872C481_D4E4_43B8_B16E_0D757F4C856F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <AfxTempl.h>

#ifdef DEVDB_EXPORTS
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_IMPORT
#endif

typedef struct tagCOLUMNINFO{
	char szColumnName[256];
	int nType;
	char szTypeName[14];
	BOOL bKey;
	BOOL bNull;
	int nLen;
}COLUMNINFO, *PCOLUMNINFO;

class DEV_EXT_MFCCLASS CColumnInfo {
public:
	CColumnInfo();
	virtual ~CColumnInfo();
	void AddInfo(PCOLUMNINFO pInfo);
	PCOLUMNINFO GetInfo(int nIndex);
	int GetSize();
private:
	CArray<PCOLUMNINFO, PCOLUMNINFO> m_arrInfo;
};

#endif // !defined(AFX_COLUMNINFO_H__4872C481_D4E4_43B8_B16E_0D757F4C856F__INCLUDED_)
