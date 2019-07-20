// DevXMLObject.h: CDevXMLObject クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVXMLOBJECT_H__0A30F5DF_4EE2_4A55_8713_910384635C61__INCLUDED_)
#define AFX_DEVXMLOBJECT_H__0A30F5DF_4EE2_4A55_8713_910384635C61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifdef DEVXML_EXPORTS
	#define DEV_EXT_XMLCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_XMLCLASS		 AFX_CLASS_IMPORT
#endif
#include <AfxTempl.h>
class DEV_EXT_XMLCLASS CDevXMLObject  {
public:
	CDevXMLObject();
	virtual ~CDevXMLObject();
	virtual BOOL GetXML(CString &strXML) = 0;

private:
	CString m_strName;
	CMapStringToString m_mapAttr;

};

#endif // !defined(AFX_DEVXMLOBJECT_H__0A30F5DF_4EE2_4A55_8713_910384635C61__INCLUDED_)
