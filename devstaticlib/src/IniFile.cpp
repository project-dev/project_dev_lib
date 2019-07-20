// IniFile.cpp: CIniFile クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IniFile.h"
#include "LogFile.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CIniFile::CIniFile(){
}

CIniFile::~CIniFile(){

}

BOOL CIniFile::IniFileAccess(LPCTSTR pszIniPath, BOOL bSave){
	CLogFile::SaveAppLog(bSave ? "Iniファイル保存" : "Iniファイル読み込み");

	INIDATA *arrData;
	int nSize;	
	if(!OnIniFileAccess(arrData, nSize)){
		return FALSE;
	}
	if(!arrData){
		return FALSE;
	}

	CString strSec;
	CString strKey;
	CString strVal;
	for(int i = 0; i < nSize; i++){
		strSec = arrData[i].szSecssion;
		strKey = arrData[i].szKey;
		switch(arrData[i].eType){
		case IT_INT:
			{
				int *pData = (int*)arrData[i].pData;
				if(bSave){
					strVal.Format("%d", *pData);
					::WritePrivateProfileString(strSec, strKey, strVal, pszIniPath);
				}else{
					*pData = ::GetPrivateProfileInt(strSec, strKey, (int)arrData[i].pDefault, pszIniPath);
				}
			}
			break;
		case IT_BOOL:
			{
				BOOL *pData = (BOOL*)arrData[i].pData;
				if(bSave){
					strVal.Format("%s", *pData ? "1" : "0");
					::WritePrivateProfileString(strSec, strKey, strVal, pszIniPath);
				}else{
					*pData = ::GetPrivateProfileInt(strSec, strKey, (BOOL)arrData[i].pDefault, pszIniPath);
				}
			}
			break;
		case IT_STRING:
			{
				char *pData = (char*)arrData[i].pData;
				if(bSave){
					::WritePrivateProfileString(strSec, strKey, pData, pszIniPath);
				}else{
					::GetPrivateProfileString(strSec, strKey, (char*)arrData[i].pDefault, pData, arrData[i].nLen, pszIniPath);
				}
			}
			break;
		case IT_DOUBLE:
			{
				double *pData = (double*)arrData[i].pData;
				if(bSave){
					strVal.Format("%f", *pData);
					::WritePrivateProfileString(strSec, strKey, strVal, pszIniPath);
				}else{
					char *szData = new char[257];
					char *szDef = new char[257];
					memset(szData, 0, 257);
					memset(szDef, 0, 257);
					sprintf(szDef, "%f", (double*)arrData[i].pDefault);
					::GetPrivateProfileString(strSec, strKey, szDef, szData, 256, pszIniPath);
					*pData = atof(szData);
					delete szData;
					delete szDef;
				}
			}
			break;
		}
	}
	return TRUE;
}

