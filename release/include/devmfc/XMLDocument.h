// XMLDocument.h: CXMLDocument クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLDOCUMENT_H__F7237849_35A0_4C08_A727_3D37122CFB61__INCLUDED_)
#define AFX_XMLDOCUMENT_H__F7237849_35A0_4C08_A727_3D37122CFB61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <atlbase.h>
#include "XMLItem.h"

#ifdef DEVMFC_EXPORTS
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_IMPORT
#endif
/**
 * XMLを扱う簡易的なクラス。
 */
class DEV_EXT_MFCCLASS CXMLDocument{
public:
	BOOL Release();
	BOOL Initalize();
	BOOL LoadXML(const char *pszFileName);
	BOOL SaveXML(const char *pszFileName);
	CXMLDocument();
	virtual ~CXMLDocument();
private:
	BOOL m_bInitalize;
	IXMLDOMDocumentPtr m_pXMLDoc;

	CXMLItem m_objRoot;
};

#endif // !defined(AFX_XMLDOCUMENT_H__F7237849_35A0_4C08_A727_3D37122CFB61__INCLUDED_)
