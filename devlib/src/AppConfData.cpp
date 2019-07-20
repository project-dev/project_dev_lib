// AppConfData.cpp: CAppConfData �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "devlib.h"
#include "AppConfData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CAppConfData::CAppConfData(){
	memset(m_szIniFile, 0, MAX_PATH);

}

CAppConfData::~CAppConfData(){

}

BOOL CAppConfData::Create(char *pszIniFilePath){
	if(pszIniFilePath){
		int nLen = strlen(pszIniFilePath);
		if(nLen < MAX_PATH){
			strcpy(m_szIniFile, pszIniFilePath);
		}
	}
}
