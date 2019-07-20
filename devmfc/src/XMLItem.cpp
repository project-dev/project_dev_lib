// XMLItem.cpp: CXMLItem クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "devmfc.h"
#include "XMLItem.h"
#include <AfxPriv2.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CXMLItem::CXMLItem()
{

}

CXMLItem::~CXMLItem()
{

}

BOOL CXMLItem::SetNode(IXMLDOMNodePtr pEle){
	TRY{
		LONG lLen;
		BSTR bStr;
		IXMLDOMNode *pNode;

		HRESULT hRes = pEle->get_nodeName(&bStr);
		if(FAILED(hRes)){
			return FALSE;
		}
		AfxBSTR2CString(&m_strTagName, bStr);

		IXMLDOMNamedNodeMap *attrMap;
		hRes = pEle->get_attributes(&attrMap);
		
		IXMLDOMNamedNodeMapPtr attrMapPtr(attrMap, FALSE);
		hRes = attrMapPtr->get_length(&lLen);

		CString strAttrName;
		CString strVal;
		VARIANT val;
		for(LONG nLoop = 0; nLoop < lLen; nLoop++){
			attrMapPtr->get_item(nLoop, &pNode);
			IXMLDOMNodePtr pNodePtr(pNode, FALSE);

			hRes = pNode->get_nodeName(&bStr);
			AfxBSTR2CString(&strAttrName, bStr);

			pNode->get_nodeValue(&val);
			_variant_t val_t(val, FALSE);
			val_t.ChangeType(VT_BSTR);
			AfxBSTR2CString(&strVal, val_t.bstrVal);

			m_mapAttr.SetAt(strAttrName, strVal);

			pNodePtr = NULL;
		}


		VARIANT_BOOL vBool;
		pEle->hasChildNodes(&vBool);

		if(vBool){
			IXMLDOMNodeList *nodeList;
			hRes = pEle->get_childNodes(&nodeList);
			if(FAILED(hRes)){
				return FALSE;
			}

			IXMLDOMNodeListPtr nodeListPtr(nodeList, FALSE);
			nodeListPtr->get_length(&lLen);

			CXMLItem *pItem;
			for(LONG i = 0; i < lLen; i++){
				nodeListPtr->get_item( i, &pNode);
				IXMLDOMNodePtr pNodePtr(pNode, FALSE);

				DOMNodeType eType;
				hRes = pNodePtr->get_nodeType(&eType);
				if(eType == NODE_TEXT){
					continue;
				}
				pItem = new CXMLItem();
				pItem->SetNode(pNodePtr);
				m_arrChilds.AddTail(pItem);
				pNodePtr = NULL;
			}
			nodeListPtr = NULL;
		}

	}CATCH_ALL(e){
		return FALSE;
	}END_CATCH_ALL

	return TRUE;
}


void CXMLItem::Release(){
	POSITION pos = m_arrChilds.GetHeadPosition();
	CXMLItem *pItem;
	while(pos != NULL){
		pItem = m_arrChilds.GetNext(pos);
		pItem->Release();
		delete pItem;
	}
	m_arrChilds.RemoveAll();
}

LPCTSTR CXMLItem::GetTagName(){
	return m_strTagName;
}

LPCTSTR CXMLItem::GetAttrValue(LPCTSTR pszName){
	CString strVal;
	if( !m_mapAttr.Lookup (pszName, strVal) ){
		return NULL;
	}

	return strVal;
}
