// LogFile.h: CLogFile クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGFILE_H__62AACD57_5537_4994_AC5B_14C884ACBC9B__INCLUDED_)
#define AFX_LOGFILE_H__62AACD57_5537_4994_AC5B_14C884ACBC9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CException;
class CLogFile{
public:
	static void SaveFatalLog(LPCTSTR pszLog);
	static void SaveAppLog(LPCTSTR pszLog);
	static void SaveExceptionLog(CException *pExcept, LPCTSTR pszOpt = NULL);
	static void SaveExceptionLog(LPCTSTR pszLog);
	static void SaveDevLibLog(LPCTSTR pszLog);
	
	static void SetLogState(BOOL bOutput);
	static void SetFatalLogState(BOOL bOutput);
	static void SetAppLogState(BOOL bOutput);
	static void SetExceptLogState(BOOL bOutput);
	static void SetDevLibLogState(BOOL bOutput);
	CLogFile();
	virtual ~CLogFile();

protected:
	static void SaveLogFile(LPCTSTR pszPath, LPCTSTR pszLog, BOOL bNowDateTime, long lLogMaxSize = 1024 * 2);
	static BOOL m_bLog;
	static BOOL m_bFatalLog;
	static BOOL m_bAppLog;
	static BOOL m_bExceptLog;
	static BOOL m_bDevLibLog;
};

#endif // !defined(AFX_LOGFILE_H__62AACD57_5537_4994_AC5B_14C884ACBC9B__INCLUDED_)
