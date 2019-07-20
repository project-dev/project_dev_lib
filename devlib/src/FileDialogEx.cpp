// FileDialogEx.cpp: CFileDialogEx �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileDialogEx.h"

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

/**
 * @brief �R���X�g���N�^
 * @param 
 * @param hwndOwner       �E�B���h�E�n���h��
 * @param hInstance       �C���X�^���X�n���h��
 * @param lpstrFile       �t�@�C����
 * @param lpstrFileTitle  �^�C�g��
 * @param lpstrFilter     �t�B���^
 * @param nFilterIndex    �t�B���^�C���f�b�N�X
 * @param lpstrInitialDir �����t�H���_
 * @param lpstrTitle      �^�C�g��
 * @param lpstrDefExt     �g���q
 */
CFileDialogEx::CFileDialogEx( HWND hwndOwner,
							  HINSTANCE hInstance,
							  LPTSTR  lpstrFile, 
							  LPTSTR  lpstrFileTitle, 
							  LPCTSTR lpstrFilter, 
							  DWORD   nFilterIndex, 
							  LPCTSTR lpstrInitialDir, 
							  LPCTSTR lpstrTitle, 
							  LPCTSTR lpstrDefExt){
	memset(&m_ofn, 0, sizeof(OPENFILENAME));

	m_lpstrFile			= NULL;
	m_lpstrFileTitle	= NULL;
	m_lpstrFilter		= NULL;
	m_lpstrInitialDir	= NULL;
	m_lpstrTitle		= NULL;
	m_lpstrDefExt		= NULL;

	m_lpstrFile = new char[MAX_PATH];
	memset(m_lpstrFile, 0, MAX_PATH);
	if(lpstrFile && strlen(lpstrFile)){
		strcpy(m_lpstrFile, lpstrFile);
	}

	if(lpstrFileTitle && strlen(lpstrFileTitle)){
		m_lpstrFileTitle = new char[strlen(lpstrFileTitle) + 1];
		memset(m_lpstrFileTitle, 0, strlen(lpstrFileTitle) + 1);
		strcpy(m_lpstrFileTitle, lpstrFileTitle);
	}

	if(lpstrFilter && strlen(lpstrFilter)){
		m_lpstrFilter = new char[strlen(lpstrFilter) + 1];
		memset(m_lpstrFilter, 0, strlen(lpstrFilter) + 1);
		strcpy(m_lpstrFilter, lpstrFilter);
	}

	if(lpstrInitialDir && strlen(lpstrInitialDir)){
		m_lpstrInitialDir = new char[strlen(lpstrInitialDir) + 1];
		memset(m_lpstrInitialDir, 0, strlen(lpstrInitialDir) + 1);
		strcpy(m_lpstrInitialDir, lpstrInitialDir);
	}

	if(lpstrTitle && strlen(lpstrTitle)){
		m_lpstrTitle = new char[strlen(lpstrTitle) + 1];
		memset(m_lpstrTitle, 0, strlen(lpstrTitle) + 1);
		strcpy(m_lpstrTitle, lpstrTitle);
	}

	if(lpstrDefExt && strlen(lpstrDefExt)){
		m_lpstrDefExt = new char[strlen(lpstrDefExt) + 1];
		memset(m_lpstrDefExt, 0, strlen(lpstrDefExt) + 1);
		strcpy(m_lpstrDefExt, lpstrDefExt);
	}

	m_ofn.Flags				= OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_ENABLESIZING | OFN_HIDEREADONLY;
	m_ofn.lStructSize		= sizeof(OPENFILENAME);
	m_ofn.hwndOwner			= hwndOwner;
	m_ofn.hInstance			= hInstance;
	m_ofn.lpstrFile			= m_lpstrFile;
	m_ofn.nMaxFile			= MAX_PATH;
	m_ofn.lpstrFileTitle	= m_lpstrFileTitle;
	m_ofn.nMaxFileTitle		= m_lpstrFileTitle ? strlen(m_lpstrFileTitle) : 0;
	m_ofn.lpstrFilter		= lpstrFilter;
	m_ofn.nFilterIndex		= nFilterIndex;
	m_ofn.lpstrInitialDir	= lpstrInitialDir;
	m_ofn.lpstrTitle		= lpstrTitle;
	m_ofn.lpstrDefExt		= lpstrDefExt;
}

/**
 * @brief �f�X�g���N�^
 */
CFileDialogEx::~CFileDialogEx(){
	
	if(m_lpstrFile){
		delete m_lpstrFile;
		m_lpstrFile = NULL;
	}

	if(m_lpstrFileTitle){
		delete m_lpstrFileTitle;
		m_lpstrFileTitle = NULL;
	}

	if(m_lpstrFilter){
		delete m_lpstrFilter;
		m_lpstrFilter = NULL;
	}

	if(m_lpstrInitialDir){
		delete m_lpstrInitialDir;
		m_lpstrInitialDir = NULL;
	}

	if(m_lpstrTitle){
		delete m_lpstrTitle;
		m_lpstrTitle = NULL;
	}

	if(m_lpstrDefExt){
		delete m_lpstrDefExt;
		m_lpstrDefExt = NULL;
	}
}

/**
 * @brief �t�@�C���I���_�C�A���O��\������
 * @return �J���������ꂽ�ꍇ��IDOK�A�L�����Z����IDCANCEL
 */
int CFileDialogEx::DoModal(){
	if(!GetOpenFileName(&m_ofn)){
		return IDCANCEL;
	}
	return IDOK;
}

/**
 * @brief �I�����ꂽ�t�@�C�����擾����
 * @return �t�@�C����
 */
char* CFileDialogEx::GetFileName(){
	return m_ofn.lpstrFile;
}
