// DrawerConfig.cpp: CDrawerConfig クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "drawercore.h"
#include "DrawerConfig.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CDrawerConfig::CDrawerConfig(){

}

CDrawerConfig::~CDrawerConfig()
{

}

BOOL CDrawerConfig::Save(LPCTSTR pszFileName){
	return IniAccess(TRUE, pszFileName);
}

BOOL CDrawerConfig::Load(LPCTSTR pszFileName){
	return IniAccess(FALSE, pszFileName);
}

BOOL CDrawerConfig::IniAccess(BOOL bWrite, LPCTSTR pszFileName /*= NULL */){
	CString strIniFile = pszFileName;
	if(!pszFileName){
		strIniFile = m_strIniFileName;
	}
	char szDrv[MAX_PATH];
	char szDir[MAX_PATH];
	_splitpath(strIniFile, szDrv, szDir, NULL, NULL);
	CString strChkPath;
	strChkPath.Format("%s%s", szDrv, szDir);
	if(strChkPath.Right(1) == "\\"){
		strChkPath = strChkPath.Left(strChkPath.GetLength() - 1);
	}
	WIN32_FIND_DATA wfd;
	HANDLE hRet = ::FindFirstFile(strChkPath, &wfd);
	if((hRet == INVALID_HANDLE_VALUE) && bWrite){
		return FALSE;
	}

	ProfileAccessInt("AppData",	"DefWidth",		m_nDefWidth,	640,	bWrite, strIniFile);
	ProfileAccessInt("AppData",	"DefHeight",	m_nDefHeight,	480,	bWrite, strIniFile);
	ProfileAccessInt("AppData",	"GridSize",		m_nGridSize,	8,		bWrite, strIniFile);
	ProfileAccessInt("AppData",	"PosGrid",		m_bPosGrid,		0,		bWrite, strIniFile);
	ProfileAccessInt("AppData",	"ShowGrid",		m_bShowGrid,	1,		bWrite, strIniFile);
	ProfileAccessStr("AppData",	"WorkDir",		m_strWorkDir,	"",		bWrite, strIniFile);

	return TRUE;
}

BOOL CDrawerConfig::ProfileAccessInt(LPCTSTR pszSection, LPCTSTR pszName, int &nData, int nDefault, BOOL bWrite, LPCTSTR pszFileName /*= NULL*/){
	CString strIniFile = pszFileName;
	if(!pszFileName){
		strIniFile = m_strIniFileName;
	}
	BOOL bRet = FALSE;
	if(bWrite){
		CString strData;
		strData.Format("%d", nData);
		::WritePrivateProfileString(pszSection, pszName, strData, strIniFile);
	}else{
		nData = ::GetPrivateProfileInt(pszSection, pszName, nDefault, strIniFile);
	}
	return bRet;
}

BOOL CDrawerConfig::ProfileAccessStr(LPCTSTR pszSection, LPCTSTR pszName, CString &strData, CString strDefault, BOOL bWrite, LPCTSTR pszFileName /*= NULL*/){
	CString strIniFile = pszFileName;
	if(!pszFileName){
		strIniFile = m_strIniFileName;
	}
	BOOL bRet = FALSE;
	if(bWrite){
		::WritePrivateProfileString(pszSection, pszName, strData, strIniFile);
	}else{
		char szData[1025];
		memset(szData, 0, 1025);
		::GetPrivateProfileString(pszSection, pszName, strDefault, szData, 1024, strIniFile);
		strData = szData;
	}
	return bRet;
}

void CDrawerConfig::SetIniFileName(LPCTSTR pszFileName)
{
	m_strIniFileName = pszFileName;
}
