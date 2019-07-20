// XMLItem.h: CXMLItem クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLITEM_H__F6B6DCF4_A808_40F9_82D5_03BFAD7523AE__INCLUDED_)
#define AFX_XMLITEM_H__F6B6DCF4_A808_40F9_82D5_03BFAD7523AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <atlbase.h>
#include <afxtempl.h>
#import "msxml.dll" named_guids raw_interfaces_only
using namespace MSXML;
#ifdef DEVMFC_EXPORTS
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_IMPORT
#endif
/**
 * XMLのノードを表すクラス
 */
class DEV_EXT_MFCCLASS CXMLItem {
public:
	LPCTSTR GetAttrValue(LPCTSTR pszName);
	LPCTSTR GetTagName();
	void Release();
	BOOL SetNode(IXMLDOMNodePtr pEle);
	CXMLItem();
	virtual ~CXMLItem();
private:
	CList <CXMLItem*, CXMLItem*>m_arrChilds;
	CString m_strTagName;
	CMapStringToString m_mapAttr;
};

#endif // !defined(AFX_XMLITEM_H__F6B6DCF4_A808_40F9_82D5_03BFAD7523AE__INCLUDED_)
