// DevMsofObject.cpp: CDevMsofObject �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "devMsof.h"
#include "DevMsofObject.h"
#include <afxdisp.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


BOOL CDevMsofObject::m_bOleInitalized = FALSE;
//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

/**
 * @verify �R���X�g���N�^
 */
CDevMsofObject::CDevMsofObject(){
	m_bShowError = FALSE;
	m_strErrMsg = "";
}

/**
 * @verify �f�X�g���N�^
 */
CDevMsofObject::~CDevMsofObject(){
	Finalize();
}

/**
 * @verify ������
 */
BOOL CDevMsofObject::Initalize(){
	if(!m_bOleInitalized){
		if ( !::AfxOleInit()){
			m_strErrMsg = "OLE���������ł��܂���B";
			ShowErrorMsg();
			return FALSE;
		}
    
		// OLE �R���g���[�����܂��邱�Ƃ�錾����
		::AfxEnableControlContainer();
		m_bOleInitalized = TRUE;
	}
	HRESULT hRes = ::CoInitialize(NULL);
	if((hRes == S_OK) || (hRes == S_FALSE)){
		return TRUE;
	}
	return FALSE;
}

/**
 * @verify �㏈��
 */
BOOL CDevMsofObject::Finalize(){
	::CoUninitialize();
	return TRUE;
}

/**
 * @verify �G���[��\������B
 *�������ASetShowError�֐��ň�����FALSE���w�肳��Ă���ꍇ�́A�G���[���b�Z�[�W��ێ�����̂�
 */
void CDevMsofObject::ShowComError(_com_error e){
	BSTR bError = e.Description();
	const TCHAR *pszMsg = e.ErrorMessage();

	CString strError;
	AfxBSTR2CString(&strError, bError);
	m_strErrMsg.Format("%s\n%s", pszMsg, strError);
	
	ShowErrorMsg();
}

/**
 * @verify �G���[���b�Z�[�W�̕\��/��\����ݒ肷��
 * @param bShow TRUE�ŕ\���B
 */
void CDevMsofObject::SetShowError(BOOL bShow){
	m_bShowError = bShow;
}

/**
 * @verify ���݂̃G���[���b�Z�[�W�\���t���O���擾����
 */
BOOL CDevMsofObject::IsShowError(){
	return m_bShowError;
}

/**
 * ��ԍŌ�̃G���[�̃G���[���b�Z�[�W���擾����
 */
LPCTSTR CDevMsofObject::GetLastErrorMsg(){
	return m_strErrMsg;
}

/**
 * @verify �G���[���b�Z�[�W�\��
 */
void CDevMsofObject::ShowErrorMsg(){
	if(m_bShowError){
		::AfxMessageBox(m_strErrMsg);
	}
}

/**
 * @verify �G���[���b�Z�[�W�ݒ�
 */
void CDevMsofObject::SetLastErrorMsg(LPCTSTR pszMsg){
	m_strErrMsg = pszMsg;
}
