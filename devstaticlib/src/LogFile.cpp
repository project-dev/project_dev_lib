// LogFile.cpp: CLogFile クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "LogFile.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////
BOOL CLogFile::m_bLog = FALSE;
BOOL CLogFile::m_bFatalLog = FALSE;
BOOL CLogFile::m_bAppLog = FALSE;
BOOL CLogFile::m_bExceptLog = FALSE;
BOOL CLogFile::m_bDevLibLog = FALSE;

CLogFile::CLogFile(){

}

CLogFile::~CLogFile(){

}

void CLogFile::SetLogState(BOOL bOutput){
	m_bLog = bOutput;
}

void CLogFile::SetFatalLogState(BOOL bOutput){
	m_bFatalLog = bOutput;
}

void CLogFile::SetAppLogState(BOOL bOutput){
	m_bAppLog = bOutput;
}

void CLogFile::SetExceptLogState(BOOL bOutput){
	m_bExceptLog = bOutput;
}
void CLogFile::SetDevLibLogState(BOOL bOutput){
	m_bDevLibLog = bOutput;
}

void CLogFile::SaveLogFile(LPCTSTR pszPath, LPCTSTR pszLog, BOOL bNowDateTime, long lLogMaxSize /*= 1024 * 2*/){
	if(!m_bLog){
		return;
	}

	if(!pszPath || !pszLog){
		return;
	}
	try{
		CStdioFile file;
		if(!file.Open(pszPath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite)){
			return;
		}
		file.SeekToEnd();
		COleDateTime objCurrent = COleDateTime::GetCurrentTime();
		CString strLog;
		strLog.Format("%s : %s\n", objCurrent.Format("%Y/%m/%d %H:%M:%S"), pszLog);
		file.WriteString(strLog);
		file.Close();
	}catch(CFileException &fe){
		char szErr[1025];
		memset(szErr, 0, 1025);
		fe.GetErrorMessage(szErr, 1024);
	}catch(CMemoryException &me){
		char szErr[1025];
		memset(szErr, 0, 1025);
		me.GetErrorMessage(szErr, 1024);
	}
}

void CLogFile::SaveFatalLog(LPCTSTR pszLog){
	if(!m_bFatalLog){
		return;
	}

	char szFile[MAX_PATH + 1];
	char szDrv[MAX_PATH + 1];
	char szDir[MAX_PATH + 1];
	memset(szDrv, 0, MAX_PATH + 1);
	memset(szDir, 0, MAX_PATH + 1);
	memset(szFile, 0, MAX_PATH + 1);
	::GetModuleFileName(NULL, szFile, MAX_PATH);

	_splitpath(szFile, szDrv, szDir, NULL, NULL);
	CString strPath;
	strPath.Format("%s%s\\Log\\FatalLog.txt", szDrv, szDir);
	SaveLogFile(strPath, pszLog, TRUE);

}

void CLogFile::SaveAppLog(LPCTSTR pszLog){
	if(!m_bAppLog){
		return;
	}

	char szFile[MAX_PATH + 1];
	char szDrv[MAX_PATH + 1];
	char szDir[MAX_PATH + 1];
	memset(szDrv, 0, MAX_PATH + 1);
	memset(szDir, 0, MAX_PATH + 1);
	memset(szFile, 0, MAX_PATH + 1);
	::GetModuleFileName(NULL, szFile, MAX_PATH);

	_splitpath(szFile, szDrv, szDir, NULL, NULL);
	CString strPath;
	strPath.Format("%s%s\\Log\\AppLog.txt", szDrv, szDir);
	SaveLogFile(strPath, pszLog, TRUE, 1024 * 5);

}

void CLogFile::SaveExceptionLog(CException *pExcept, LPCTSTR pszOpt /* = NULL*/){
	char szErr[1025];
	memset(szErr, 0, 1025);
	pExcept->GetErrorMessage(szErr, 1024);
	CString strErr;
	if(pszOpt){
		strErr.Format("%s : %s", szErr, pszOpt);
	}else{
		strErr.Format("%s", szErr);
	}
	SaveExceptionLog(strErr);
}

void CLogFile::SaveExceptionLog(LPCTSTR pszLog){
	if(!m_bExceptLog){
		return;
	}
	char szFile[MAX_PATH + 1];
	char szDrv[MAX_PATH + 1];
	char szDir[MAX_PATH + 1];
	memset(szDrv, 0, MAX_PATH + 1);
	memset(szDir, 0, MAX_PATH + 1);
	memset(szFile, 0, MAX_PATH + 1);
	::GetModuleFileName(NULL, szFile, MAX_PATH);

	_splitpath(szFile, szDrv, szDir, NULL, NULL);
	CString strPath;
	strPath.Format("%s%s\\Log\\ExceptionLog.txt", szDrv, szDir);
	SaveLogFile(strPath, pszLog, TRUE, 1024 * 5);
}
void CLogFile::SaveDevLibLog(LPCTSTR pszLog){
	if(!m_bDevLibLog){
		return;
	}
	char szFile[MAX_PATH + 1];
	char szDrv[MAX_PATH + 1];
	char szDir[MAX_PATH + 1];
	memset(szDrv, 0, MAX_PATH + 1);
	memset(szDir, 0, MAX_PATH + 1);
	memset(szFile, 0, MAX_PATH + 1);
	::GetModuleFileName(NULL, szFile, MAX_PATH);

	_splitpath(szFile, szDrv, szDir, NULL, NULL);
	CString strPath;
	strPath.Format("%s%s\\Log\\DevLibLog.txt", szDrv, szDir);
	CString strTrace;
	strTrace.Format("%s\n", pszLog);
	::OutputDebugString(strTrace);
	SaveLogFile(strPath, pszLog, TRUE, 1024 * 5);
}
