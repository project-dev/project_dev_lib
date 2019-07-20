// FolderDialog.cpp: CFolderDialog �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FolderDialog.h"

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

/**
 * @brief �f�X�g���N�^
 */
CFolderDialog::~CFolderDialog(){
}

/**
 * @brief �R���X�g���N�^
 * @param hwndOwner       �E�B���h�E�n���h��
 * @param pszDisplayName  �\����
 * @param pszTitle        �^�C�g��
 * @param pszRootDir      ���[�g�f�B���N�g��
 */
CFolderDialog::CFolderDialog(HWND hWnd,
							 char *pszDisplayName,
							 char *pszTitle /*= "�t�H���_�̑I��"*/,
							 char *pszRootDir /* = NULL */){
	memset(&m_objBrowInfo, 0, sizeof(BROWSEINFO));

	memset(m_szDispName, 0, 1024);
	memset(m_szTitle, 0, 1024);

	strcpy(m_szDispName, pszDisplayName);
	strcpy(m_szTitle, pszTitle);

	m_objBrowInfo.hwndOwner			= hWnd;
	m_objBrowInfo.pidlRoot			= NULL;
	m_objBrowInfo.pszDisplayName	= m_szDispName;
	m_objBrowInfo.lpszTitle			= m_szTitle;
	m_objBrowInfo.ulFlags			= BIF_RETURNONLYFSDIRS;
	m_objBrowInfo.lpfn				= BrowseCallbackProc;
	m_objBrowInfo.lParam			= (LPARAM)pszRootDir;
	m_objBrowInfo.iImage			= 0;
}

/**
 * @brief �R�[���o�b�N
 */
int CALLBACK CFolderDialog::BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData){
    // ����������
    if( uMsg == BFFM_INITIALIZED){
        SendMessage(hWnd, BFFM_SETSELECTION, (WPARAM)TRUE, lpData);
    }
    return 0;
}

/**
 * @brief �t�H���_�I���_�C�A���O��\������
 * @return �t�H���_���I�����ꂽ�ꍇ��TRUE
 */
BOOL CFolderDialog::DoModal(){
	
	LPMALLOC g_pMalloc = NULL;
	LPITEMIDLIST pList;
	BOOL bRet = FALSE;
	memset(m_szPath, 0, MAX_PATH);

	//COM�̏�����
	HRESULT hRes = ::CoInitialize(NULL);
	if(FAILED(hRes)){
		return bRet;
	}

	HRESULT hr = ::SHGetMalloc(&g_pMalloc);
	if(FAILED(hr)){
		return bRet;
	}
	
	//�t�H���_�I���_�C�A���O�̕\��
	pList = ::SHBrowseForFolder(&m_objBrowInfo);

	//���ۂ̃p�X���擾
	if(pList && ::SHGetPathFromIDList(pList, m_szPath)){
		bRet = TRUE;
		g_pMalloc->Free(pList);
	}

	if(hRes == S_OK){
		//COM�̉��
		::CoUninitialize();
	}
	
	return bRet;
}

/**
 * @brief �I�����ꂽ�p�X���擾����
 * @return �I�����ꂽ�p�X
 */
char* CFolderDialog::GetFolder(){
	return m_szPath;
}
