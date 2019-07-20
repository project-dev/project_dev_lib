// DevWord.cpp: CDevWord �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "devMsof.h"
#include "DevWord.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

/**
 * @verify �R���X�g���N�^
 */
CDevWord::CDevWord(){
	m_pWord = NULL;
}

/**
 * @verify �f�X�g���N�^
 */
CDevWord::~CDevWord(){

}

/**
 * @verify ������
 * @return �������ɐ��������TRUE��ԋp�B
 */
BOOL CDevWord::Initalize(){
	try{
		if(!CDevMsofObject::Initalize()){
			return FALSE;
		}
		HRESULT hRes = m_pWord.CreateInstance( "Word.Application.9");
		if(hRes != S_OK){
			return FALSE;
		}
	}catch(_com_error e){
		ShowComError(e);
		return FALSE;
	}
	
	return TRUE;
}

/**
 * @verify �㏈��
 * @return �㏈���ɐ��������TRUE��ԋp�B
 */
BOOL CDevWord::Finalize(){
	try{
		if(m_pWord){
			m_pWord.Release();
			m_pWord = NULL;
		}
	}catch(_com_error e){
		ShowComError(e);
		return FALSE;
	}
	return TRUE;
}

/**
 * @verify �\��
 * @param bIsShow TRUE�����Ă�����ƕ\��
 * @return �\���ɐ��������TRUE��Ԃ��܂��B
 */
BOOL CDevWord::Show(BOOL bIsShow){
	try{
		if(m_pWord){
			return TRUE;
		}else{
			return FALSE;
		}
	}catch(_com_error e){
		ShowComError(e);
		return FALSE;
	}
}

/**
 * @verify �I��
 * @param 
 * @return 
 */
BOOL CDevWord::Quit(LPCTSTR pszFileName, BOOL bIsSaveQuit){
	try{
	}catch(_com_error e){
		ShowComError(e);
		return FALSE;
	}
	return TRUE;
}

BOOL CDevWord::Load(LPCTSTR pszFileName){
	try{
	}catch(_com_error e){
		ShowComError(e);
		return FALSE;
	}
	return TRUE;
}

BOOL CDevWord::Save(LPCTSTR pszFileName, BOOL isOverWrite){
	try{
	}catch(_com_error e){
		ShowComError(e);
		return FALSE;
	}
	return TRUE;
}