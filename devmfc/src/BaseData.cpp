// BaseData.cpp: CBaseData �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BaseData.h"

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////
CString CBaseData::m_strBasePath = "";
CString CBaseData::m_strIniFilePath = "";

CBaseData::CBaseData(){

}

CBaseData::~CBaseData(){

}

/**
 * @brif ��{�I�ȃp�X���𐶐�����
 */
void CBaseData::SetPath(){
	char szPath[MAX_PATH + 1];
	memset(szPath, 0, MAX_PATH + 1);
	::GetModuleFileName(NULL, szPath, MAX_PATH);
	char szDrv[MAX_PATH];
	char szDir[MAX_PATH];
	char szFile[MAX_PATH];
	_splitpath(szPath, szDrv, szDir, szFile, NULL);
	m_strBasePath.Format("%s%s", szDrv, szDir);
	m_strIniFilePath.Format("%s%s%s.ini", szDrv, szDir, szFile);
	if(m_strBasePath.Right(1).Compare("\\")){
		m_strBasePath += "\\";
	}
}

/**
 * @brif �A�v���P�[�V�����̂���p�X���擾����
 */
LPCTSTR CBaseData::GetBasePath(){
	return m_strBasePath;
};

/**
 * @brif Ini�t�@�C�������擾����
 */
LPCTSTR CBaseData::GetInifilePath(){
	return m_strIniFilePath;
}
