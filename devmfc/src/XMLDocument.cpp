// XMLDocument.cpp: CXMLDocument �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "devlib.h"
#include "XMLDocument.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CXMLDocument::CXMLDocument()
{
	m_bInitalize = FALSE;
}

CXMLDocument::~CXMLDocument(){
	Release();
}

BOOL CXMLDocument::LoadXML(const char *pszFileName){
	HRESULT hRes;
    VARIANT_BOOL vBool;

	if(!m_bInitalize){
		return FALSE;
	}
    
	hRes = m_pXMLDoc->put_async(VARIANT_FALSE); // load ���\�b�h�����[�h����������܂ő҂悤�ɂ���B
    
	hRes = m_pXMLDoc->load(_variant_t(L"http://majissuka.com/NewInfo.xml"), &vBool);// �A�h���X�͉ˋ�ł��̂ł������炸;
    
	if((hRes != S_OK) || !vBool){
        // �G���[����
        return FALSE;
    }

	IXMLDOMNode *node;
	hRes = m_pXMLDoc->get_firstChild(&node);
	
	IXMLDOMNodePtr pNodePtr(node, FALSE);

	BOOL bRet = m_objRoot.SetNode(pNodePtr);
	pNodePtr = NULL;
	return bRet;
}

BOOL CXMLDocument::SaveXML(const char *pszFileName){
	if(!m_bInitalize){
		return FALSE;
	}
	return TRUE;
}

BOOL CXMLDocument::Initalize(){
	HRESULT hRes;
	TRY{
		if(!m_bInitalize){
			hRes = ::CoInitialize(NULL);
			if(hRes == S_OK){
				m_bInitalize = TRUE;
			}else if(hRes == S_FALSE){
			}else{
				return FALSE;	
			}
		}
		HRESULT hr = m_pXMLDoc.CreateInstance(__uuidof(DOMDocument));
		if(FAILED(hr)){
			// �G���[����
			Release();
			return FALSE;
		}

		m_pXMLDoc->put_preserveWhiteSpace(VARIANT_TRUE);
	}CATCH_ALL(e){
		return FALSE;
	}END_CATCH_ALL
	return TRUE;
}

BOOL CXMLDocument::Release(){
	if(m_bInitalize){
		::CoUninitialize();
	}
	m_pXMLDoc = NULL;
	return TRUE;
}
