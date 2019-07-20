// AdoDatabase.cpp: CAdoDatabase �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AdoDatabase.h"
#include <atlbase.h>
#include "AfxPriv2.h"
#include "logfile.h"
#include "ColumnInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//SQLServer/MSDE�\���
CString szReserveSQL[]={
	 "ADD"
	,"ALL"
	,"ALTER"
	,"AND"
	,"ANY"
	,"AS"
	,"ASC"
	,"AUTHORIZATION"
	,"BACKUP"
	,"BEGIN"
	,"BETWEEN"
	,"BREAK"
	,"BROWSE"
	,"BULK"
	,"BY"
	,"CASCADE"
	,"CASE"
	,"CHECK"
	,"CHECKPOINT"
	,"CLOSE"
	,"CLUSTERED"
	,"COALESCE"
	,"COLLATE"
	,"COLUMN"
	,"COMMIT"
	,"COMPUTE"
	,"CONSTRAINT"
	,"CONTAINS"
	,"CONTAINSTABLE"
	,"CONTINUE"
	,"CONVERT"
	,"CREATE"
	,"CROSS"
	,"CURRENT"
	,"CURRENT_DATE"
	,"CURRENT_TIME"
	,"CURRENT_TIMESTAMP"
	,"CURRENT_USER"
	,"CURSOR"
	,"DATABASE"
	,"DBCC"
	,"DEALLOCATE"
	,"DECLARE"
	,"DEFAULT"
	,"DELETE"
	,"DENY"
	,"DESC"
	,"DISK"
	,"DISTINCT"
	,"DISTRIBUTED"
	,"DOUBLE"
	,"DROP"
	,"DUMMY"
	,"DUMP"
	,"ELSE"
	,"END"
	,"ERRLVL"
	,"ESCAPE"
	,"EXCEPT"
	,"EXEC"
	,"EXECUTE"
	,"EXISTS"
	,"EXIT"
	,"FETCH"
	,"FILE"
	,"FILLFACTOR"
	,"FOR"
	,"FOREIGN"
	,"FREETEXT"
	,"FREETEXTTABLE"
	,"FROM"
	,"FULL"
	,"FUNCTION"
	,"GOTO"
	,"GRANT"
	,"GROUP"
	,"HAVING"
	,"HOLDLOCK"
	,"IDENTITY"
	,"IDENTITY_INSERT"
	,"IDENTITYCOL"
	,"IF"
	,"IN"
	,"INDEX"
	,"INNER"
	,"INSERT"
	,"INTERSECT"
	,"INTO"
	,"IS"
	,"JOIN"
	,"KEY"
	,"KILL"
	,"LEFT"
	,"LIKE"
	,"LINENO"
	,"LOAD"
	,"NATIONAL"
	,"NOCHECK"
	,"NONCLUSTERED"
	,"NOT"
	,"NULL"
	,"NULLIF"
	,"OF"
	,"OFF"
	,"OFFSETS"
	,"ON"
	,"OPEN"
	,"OPENDATASOURCE"
	,"OPENQUERY"
	,"OPENROWSET"
	,"OPENXML"
	,"OPTION"
	,"OR"
	,"ORDER"
	,"OUTER"
	,"OVER"
	,"PERCENT"
	,"PLAN"
	,"PRECISION"
	,"PRIMARY"
	,"PRINT"
	,"PROC"
	,"PROCEDURE"
	,"PUBLIC"
	,"RAISERROR"
	,"READ"
	,"READTEXT"
	,"RECONFIGURE"
	,"REFERENCES"
	,"REPLICATION"
	,"RESTORE"
	,"RESTRICT"
	,"RETURN"
	,"REVOKE"
	,"RIGHT"
	,"ROLLBACK"
	,"ROWCOUNT"
	,"ROWGUIDCOL"
	,"RULE"
	,"SAVE"
	,"SCHEMA"
	,"SELECT"
	,"SESSION_USER"
	,"SET"
	,"SETUSER"
	,"SHUTDOWN"
	,"SOME"
	,"STATISTICS"
	,"SYSTEM_USER"
	,"TABLE"
	,"TEXTSIZE"
	,"THEN"
	,"TO"
	,"TOP"
	,"TRAN"
	,"TRANSACTION"
	,"TRIGGER"
	,"TRUNCATE"
	,"TSEQUAL"
	,"UNION"
	,"UNIQUE"
	,"UPDATE"
	,"UPDATETEXT"
	,"USE"
	,"USER"
	,"VALUES"
	,"VARYING"
	,"VIEW"
	,"WAITFOR"
	,"WHEN"
	,"WHERE"
	,"WHILE"
	,"WITH"
	,"WRITETEXT"
};

//ODBC�\���
CString szReserveODBC[]={
	 "ABSOLUTE"
	,"ACTION"
	,"ADA"
	,"ADD"
	,"ALL"
	,"ALLOCATE"
	,"ALTER"
	,"AND"
	,"ANY"
	,"ARE"
	,"AS"
	,"ASC"
	,"ASSERTION"
	,"AT"
	,"AUTHORIZATION"
	,"AVG"
	,"BEGIN"
	,"BETWEEN"
	,"BIT"
	,"BIT_LENGTH"
	,"BOTH"
	,"BY"
	,"CASCADE"
	,"CASCADED"
	,"CASE"
	,"CAST"
	,"CATALOG"
	,"CHAR"
	,"CHAR_LENGTH"
	,"CHARACTER"
	,"CHARACTER_LENGTH"
	,"CHECK"
	,"CLOSE"
	,"COALESCE"
	,"COLLATE"
	,"COLLATION"
	,"COLUMN"
	,"COMMIT"
	,"CONNECT"
	,"CONNECTION"
	,"CONSTRAINT"
	,"CONSTRAINTS"
	,"CONTINUE"
	,"CONVERT"
	,"CORRESPONDING"
	,"COUNT"
	,"CREATE"
	,"CROSS"
	,"CURRENT"
	,"CURRENT_DATE"
	,"CURRENT_TIME"
	,"CURRENT_TIMESTAMP"
	,"CURRENT_USER"
	,"CURSOR"
	,"DATE"
	,"DAY"
	,"DEALLOCATE"
	,"DEC"
	,"DECIMAL"
	,"DECLARE"
	,"DEFAULT"
	,"DEFERRABLE"
	,"DEFERRED"
	,"DELETE"
	,"DESC"
	,"DESCRIBE"
	,"DESCRIPTOR"
	,"DIAGNOSTICS"
	,"DISCONNECT"
	,"DISTINCT"
	,"DOMAIN"
	,"DOUBLE"
	,"DROP"
	,"ELSE"
	,"END"
	,"END-EXEC"
	,"ESCAPE"
	,"EXCEPT"
	,"EXCEPTION"
	,"EXEC"
	,"EXECUTE"
	,"EXISTS"
	,"EXTERNAL"
	,"EXTRACT"
	,"FETCH"
	,"FIRST"
	,"FLOAT"
	,"FOR"
	,"FOREIGN"
	,"FORTRAN"
	,"FOUND"
	,"FROM"
	,"FULL"
	,"GET"
	,"GLOBAL"
	,"GO"
	,"GOTO"
	,"GRANT"
	,"GROUP"
	,"HAVING"
	,"HOUR"
	,"IDENTITY"
	,"IMMEDIATE"
	,"IN"
	,"INCLUDE"
	,"INDEX"
	,"INDICATOR"
	,"INITIALLY"
	,"INNER"
	,"INPUT"
	,"INSENSITIVE"
	,"INSERT"
	,"INT"
	,"INTEGER"
	,"INTERSECT"
	,"INTERVAL"
	,"INTO"
	,"IS"
	,"ISOLATION"
	,"JOIN"
	,"KEY"
	,"LANGUAGE"
	,"LAST"
	,"LEADING"
	,"LEFT"
	,"LEVEL"
	,"LIKE"
	,"LOCAL"
	,"LOWER"
	,"MATCH"
	,"MAX"
	,"MIN"
	,"MINUTE"
	,"MODULE"
	,"MONTH"
	,"NAMES"
	,"NATIONAL"
	,"NATURAL"
	,"NCHAR"
	,"NEXT"
	,"NO"
	,"NONE"
	,"NOT"
	,"NULL"
	,"NULLIF"
	,"NUMERIC"
	,"OCTET_LENGTH"
	,"OF"
	,"ON"
	,"ONLY"
	,"OPEN"
	,"OPTION"
	,"OR"
	,"ORDER"
	,"OUTER"
	,"OUTPUT"
	,"OVERLAPS"
	,"PAD"
	,"PARTIAL"
	,"PASCAL"
	,"POSITION"
	,"PRECISION"
	,"PREPARE"
	,"PRESERVE"
	,"PRIMARY"
	,"PRIOR"
	,"PRIVILEGES"
	,"PROCEDURE"
	,"PUBLIC"
	,"READ"
	,"REAL"
	,"REFERENCES"
	,"RELATIVE"
	,"RESTRICT"
	,"REVOKE"
	,"RIGHT"
	,"ROLLBACK"
	,"ROWS"
	,"SCHEMA"
	,"SCROLL"
	,"SECOND"
	,"SECTION"
	,"SELECT"
	,"SESSION"
	,"SESSION_USER"
	,"SET"
	,"SIZE"
	,"SMALLINT"
	,"SOME"
	,"SPACE"
	,"SQL"
	,"SQLCA"
	,"SQLCODE"
	,"SQLERROR"
	,"SQLSTATE"
	,"SQLWARNING"
	,"SUBSTRING"
	,"SUM"
	,"SYSTEM_USER"
	,"TABLE"
	,"TEMPORARY"
	,"THEN"
	,"TIME"
	,"TIMESTAMP"
	,"TIMEZONE_HOUR"
	,"TIMEZONE_MINUTE"
	,"TO"
	,"TRAILING"
	,"TRANSACTION"
	,"TRANSLATE"
	,"TRANSLATION"
	,"TRIM"
	,"UNION"
	,"UNIQUE"
	,"UNKNOWN"
	,"UPDATE"
	,"UPPER"
	,"USAGE"
	,"USER"
	,"USING"
	,"VALUE"
	,"VALUES"
	,"VARCHAR"
	,"VARYING"
	,"VIEW"
	,"WHEN"
	,"WHENEVER"
	,"WHERE"
	,"WITH"
	,"WORK"
	,"WRITE"
	,"YEAR"
	,"ZONE"
	,"FALSE"
	,"TRUE"
};

typedef struct tagCMDDAT{
	int		nType;
	LPCTSTR	pszKey;
}CMDDAT;

CMDDAT arrCmdDat[] = {
	{1, "SELECT"},
	{0, "INSERT"},
	{0, "DELETE"},
	{0, "UPDATE"},
	{0, "DROP"},
	{0, "REMOVE"},
	{0, "CREATE"},
	{0, "TRANCATE"},
	{0, "RESTORE"},
	{0, "ALTER"},
};

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

/**
 *�R���X�g���N�^
 */
CAdoDatabase::CAdoDatabase(){
	m_hComInit = ::CoInitialize(NULL);
	m_bErrOut = FALSE;
	m_bConnect = FALSE;

	m_pConnect = NULL;
	m_pCommand = NULL;
	m_eDBType = UNKNOW;
	m_eODBCType = ODBC_UNKNOW;

	int nSize = sizeof(szReserveSQL) / sizeof(CString);
	for(int i = 0; i < nSize; i++){
		m_mapSQLReserve.SetAt(szReserveSQL[i], szReserveSQL[i]);
	}
	
	nSize = sizeof(szReserveODBC) / sizeof(CString);
	for(i = 0; i < nSize; i++){
		m_mapODBCReserve.SetAt(szReserveODBC[i], szReserveODBC[i]);
	}

}

/**
 *�f�X�g���N�^
 */
CAdoDatabase::~CAdoDatabase(){
	if(m_hComInit == S_OK){
		::CoUninitialize();
	}
	if(m_bConnect){
		m_pConnect->Close();
	}
	if(m_pConnect){
		m_pConnect = NULL;
	}

	if(m_pCommand){
		m_pCommand = NULL;
	}

	
	POSITION pos = m_arrTableInfo.GetStartPosition();
	CString strKey;
	PTABLEINFO pInfo = NULL;
	void* pVal;
	while(pos){
		m_arrTableInfo.GetNextAssoc(pos, strKey, pVal);
		pInfo = (PTABLEINFO)pVal;
		delete pInfo;
	}
	m_arrTableInfo.RemoveAll();
}

/**
 * ����
 * @return �����ɐ��������ꍇ��TRUE��Ԃ��܂��B
 */
BOOL CAdoDatabase::Create(){
	m_eDBType = UNKNOW;
	return TRUE;

}

/**
 *�f�[�^�x�[�X�ɐڑ��������ׂ܂��B
 * @return �ڑ����̏ꍇ��TRUE��Ԃ��܂��B
 */
BOOL CAdoDatabase::IsConnect(){
	m_strLastError = "";
	return m_bConnect;
}

/**
 *�f�[�^�x�[�X�ɐڑ����܂��B
 * @param pszCommand �ڑ�������
 * @param eDB �ڑ�����f�[�^�x�[�X�̎��
 * @return �ڑ��ɐ��������ꍇ��TRUE��Ԃ��܂��B
 */
BOOL CAdoDatabase::Connect(LPCTSTR pszCommand, eDBType eDB){
	m_strLastError = "";
	HRESULT hRes;
	m_bConnect = FALSE;

	try{
		try{
			// ADO�I�u�W�F�N�g�̐���
			hRes = m_pConnect.CreateInstance(__uuidof(Connection));
			if(hRes != S_OK){
				m_pConnect = NULL;
				return FALSE;
			}
		}catch(_com_error &e){
			DispError(e.Description());
			m_pConnect = NULL;
			return FALSE;
		}
		
		try{
			hRes = m_pCommand.CreateInstance(__uuidof(Command));
			if(hRes != S_OK){
				if(m_pConnect){
					m_pConnect.Release();
					m_pConnect = NULL;
				}
				return FALSE;
			}
		}catch(_com_error &e){
			DispError(e.Description());
			if(m_pConnect){
				m_pConnect.Release();
				m_pConnect = NULL;
			}
			m_pCommand = NULL;
			return FALSE;
		}

		if(!pszCommand){
			if(m_pConnect){
				m_pConnect.Release();
				m_pConnect = NULL;
			}
			if(m_pCommand){
				m_pCommand.Release();
			}
			return FALSE;
		}

		m_pConnect->CommandTimeout = 30;
		m_pConnect->CursorLocation = adUseClient;
		//m_pConnect. TrustedConnection
		try{
			hRes = m_pConnect->Open(pszCommand, "", "", adConnectUnspecified);
			if(hRes != S_OK){
				if(m_pConnect){
					m_pConnect->Close();
					m_pConnect.Release();
					m_pConnect = NULL;
				}
				if(m_pCommand){
					m_pCommand.Release();
				}
				return FALSE;
			}
		}catch(_com_error &e){
			DispError(e.Description());
			if(m_pConnect){
				m_pConnect.Release();
				m_pConnect = NULL;
			}
			m_pCommand = NULL;
			return FALSE;
		}

		try{
			_bstr_t bstrProvider = m_pConnect->GetProvider();
			_bstr_t bstrVer = m_pConnect->GetVersion();

			CString strProvider;
			CString strVer;
			AfxBSTR2CString(&strProvider, bstrProvider);
			AfxBSTR2CString(&strVer, bstrVer);
			CLogFile::SetLogState(TRUE);
			CLogFile::SetAppLogState(TRUE);
			CString strLog;
			strLog.Format("PROVIDER : %s", strProvider);
			CLogFile::SaveAppLog(strLog);

			strLog.Format("VERSION  : %s", strVer);
			CLogFile::SaveAppLog(strLog);

			m_bConnect = TRUE;
			m_eDBType = eDB;
	/*
			DWORD dwTick = GetTickCount();
			DWORD dwEndTick;
			while(true){
				dwEndTick = GetTickCount();
				if(abs(dwEndTick - dwTick) > 1000){
					break;
				}
			}
	*/
		}catch(_com_error &e){
			DispError(e.Description());
			if(m_pConnect){
				m_pConnect->Close();
				m_pConnect.Release();
				m_pConnect = NULL;
			}
			if(m_pCommand){
				m_pCommand.Release();
				m_pCommand = NULL;
			}
			return FALSE;
		}
		return TRUE;
	}catch(_com_error &e){
		DispError(e.Description());
		if(m_pConnect){
			m_pConnect.Release();
			m_pConnect = NULL;
		}
		if(m_pCommand){
			m_pCommand.Release();
			m_pCommand = NULL;
		}
		return FALSE;
	}
}
#if defined(NEW_DBTYPE)
BOOL CAdoDatabase::ConnectODBC(eDBType eDB, LPCTSTR pszServer /*= "(local)"*/, LPCTSTR pszUser /*= "sa"*/, LPCTSTR pszPass /*= ""*/, LPCTSTR pszDBName /*= "master"*/){
	m_strLastError = "";
	CString strConnect;
	//ODBC;DSN=afx;UID=sa;PWD=Fred;
	strConnect.Format("ODBC;Data Source=%s;DSN=%s;UID=%s;PWD=%s;", pszServer, pszDBName, pszUser, pszPass);
	return Connect(strConnect, eDB);
}
BOOL CAdoDatabase::ConnectSqlServer(eDBType eDB, LPCTSTR pszServer /*= "(local)"*/, LPCTSTR pszUser /*= "sa"*/, LPCTSTR pszPass /*= ""*/, LPCTSTR pszDBName /*= "master"*/){
	m_strLastError = "";
	CString strConnect = "";
	CString strServer;
	if(!pszServer){
		strServer = "(local)";
	}else{
		strServer = pszServer;
	}
	switch(eDB){
	case SQLSERVER_OLEDB:
		strConnect.Format("Provider=SQLOLEDB;Data Source=%s;User Id=%s;Password=%s;Initial Catalog=%s;", strServer, pszUser, pszPass, pszDBName);
		break;
	case SQLSERVER_ODBC:
		strConnect.Format("Driver={SQL Server};Server=%s;Database=%s;Uid=%s;Pwd=%s;", strServer, pszDBName, pszUser, pszPass);
		break;
	case SQLSERVER_AUTO:
		if(!strlen(pszUser) && !strlen(pszPass)){
			//NT�F��
			//"driver={sql server};SERVER=(local);Database=LOCALDB;UID=;PWD=;"
			//strSqlServer.Format("Provider=SQLOLEDB; Server=%s; Integrated Security=SSPI;Persist Security Info=False; Initial Catalog=%s;", strServer, pszDBName);
			strConnect.Format("driver={sql server};SERVER=%s;Database=%s;UID=%s;PWD=%s;", strServer, pszDBName, pszUser, pszPass);
		}else{
			//SQLServer�F��
			//strSqlServer.Format("Provider=SQLOLEDB; Persist Security Info=False; Server=%s; User Id=%s; Password=%s; Initial Catalog=%s;", strServer, pszUser, pszPass, pszDBName);
			//strSqlServer.Format("Provider=SQLOLEDB; Server=%s; Persist Security Info=True; User Id=%s; Password=%s; Initial Catalog=%s;", strServer, pszUser, pszPass, pszDBName);
			strConnect.Format("Provider=SQLOLEDB; Server=%s; User Id=%s; Password=%s; Initial Catalog=%s;", strServer, pszUser, pszPass, pszDBName);
		}
		break;
	}
	return Connect(strConnect, eDB);
}
BOOL CAdoDatabase::ConnectOracle(eDBType eDB, LPCTSTR pszServer /*= "(local)"*/, LPCTSTR pszUser /*= "scott"*/, LPCTSTR pszPass /*= "tiger"*/){
	m_strLastError = "";
	CString strConnect = "";
	switch(eDB){
	case ORACLE_OLEDB:
		strConnect.Format("Provider=OraOLEDB.Oracle;Data Source=%s;User Id=%s;Password=%s", pszServer, pszUser, pszPass);
		break;
/*
	case ORACLE_ODBC:
//		strConnect.Format("Driver={Oracle in OraHome92};DBQ=%s;UID=%s;PWD=%s", pszServer, pszUser, pszPass);
		strConnect.Format("Driver={Oracle in OraHome81};DBQ=%s;UID=%s;PWD=%s", pszServer, pszUser, pszPass);
		break;
*/
	case ORACLE_MS_OLEDB:
		strConnect.Format("Provider=MSDAORA;Data Source=%s;User Id=%s;Password=%s", pszServer, pszUser, pszPass);
		break;
	case ORACLE_MS_ODBC:
		strConnect.Format("Driver={Microsoft ODBC for Oracle};Server=%s;UID=%s;PWD=%s", pszServer, pszUser, pszPass);
		break;
	}
	return Connect(strConnect, eDB);
}
BOOL CAdoDatabase::ConnectAccess(eDBType eDB, LPCTSTR pszMDB, LPCTSTR pszUser, LPCTSTR pszPass){
	CString strConnect = "";
	switch(eDB){
	case ACCESS_OLEDB:
		strConnect.Format("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;User Id=%s;Password=%s", pszMDB, pszUser, pszPass);
		break;
	case ACCESS_ODBC:
		strConnect.Format("Driver={Microsoft Access Driver (*.mdb)};DBQ=%s;Uid=%s;Pwd=%s", pszMDB, pszUser, pszPass);
		break;
	}
	return Connect(strConnect, eDB);
}
BOOL CAdoDatabase::ConnectDB2(eDBType eDB, LPCTSTR pszDSN, LPCTSTR pszUser, LPCTSTR pszPass){
	CString strConnect = "";
	strConnect.Format("Provider=IBMDADB2;DSN=%s;User ID=%s;Password=%s", pszDSN, pszUser, pszPass);
	return Connect(strConnect, eDB);
}

#else
BOOL CAdoDatabase::ConnectAccess(LPCTSTR pszMDB, LPCTSTR pszUser, LPCTSTR pszPass, LPCTSTR pszProvider /* = "Microsoft.Jet.OLEDB.4.0"*/){
	CString strConnect;
	strConnect.Format("Driver={Microsoft Access Driver (*.mdb)};DBQ=%s;Uid=%s;Pwd=%s", pszMDB, pszUser, pszPass);
	//strConnect.Format("Provider=%s;Data Source =%s;User Id=%s;Password=%s", pszProvider, pszMDB, pszUser, pszPass);
	return Connect(strConnect, ACCESS);
}


/**
 *Oracle�ɐڑ����܂��B(������)
 */
BOOL CAdoDatabase::ConnectOracle(LPCTSTR pszServer /* = "(local)" */, LPCTSTR pszUser /* = "scott" */, LPCTSTR pszPass /* = "tiger" */){
	m_strLastError = "";
	try{
		CString strODBC;
		//ODBC;DSN=�f�[�^�\�[�X��;UID=���[�U��;PWD=�p�X���[�h;DBQ=�T�[�r�X��;
		//ODBC;DSN=afx;UID=sa;PWD=Fred;
		//strODBC.Format("ODBC;DSN=%s;UID=%s;PWD=%s;DBQ=%s", pszDBName, pszUser, pszPass, pszService);
		//strODBC.Format("driver={Oracle in OraHome92};UID=%s;PWD=%s;DBQ=%s", pszUser, pszPass, pszService);
		//strODBC.Format("driver=MSDAORA.1;UID=%s;PWD=%s;DBQ=%s", pszUser, pszPass, pszService);
		//"Provider=MSDAORA;Data Source=serverName;User ID=userName; Password=userPassword;"
		
		strODBC.Format("Provider=MSDAORA;Data Source=%s;User ID=%s;Password=%s;", pszServer, pszUser, pszPass);
		//strODBC.Format("Driver={Microsoft ODBC for Oracle};Server=%s;UID=%s;PWD=%s", pszServer, pszUser, pszPass);

		return Connect(strODBC, ORACLE);
	}catch(_com_error &e){
		DispError(e.Description());
		return FALSE;
	}
}

/**
 *ODBC�Ńf�[�^�x�[�X�ɐڑ����܂��B
 * @param pszServer �T�[�o��
 * @param pszUser ���[�U�[��
 * @param pszPass �p�X���[�h
 * @param pszDBName �f�[�^�\�[�X��
 * @return �ڑ��ɐ��������ꍇ��TRUE��Ԃ��܂��B
 */
BOOL CAdoDatabase::ConnectODBC(LPCTSTR pszServer /* = "(local)" */, LPCTSTR pszUser /* = "sa" */, LPCTSTR pszPass /* = "" */, LPCTSTR pszDBName /* = "master"*/){
	m_strLastError = "";
	try{
		CString strODBC;
		//ODBC;DSN=afx;UID=sa;PWD=Fred;
		strODBC.Format("ODBC;Data Source=%s;DSN=%s;UID=%s;PWD=%s;", pszServer, pszDBName, pszUser, pszPass);
		return Connect(strODBC, ODBC);
	}catch(_com_error &e){
		DispError(e.Description());
		return FALSE;
	}
}

/**
 * SQLServer/MSDE�ɐڑ����܂��B
 * @param pszServer �T�[�o��
 * @param pszUser ���[�U�[��
 * @param pszPass �p�X���[�h
 * @param pszDBName �f�[�^�x�[�X��
 * @return �ڑ��ɐ��������ꍇ��TRUE��Ԃ��܂��B
 */
BOOL CAdoDatabase::ConnectSqlServer(LPCTSTR pszServer /* = "(local)" */, LPCTSTR pszUser /* = "sa" */, LPCTSTR pszPass /* = "" */, LPCTSTR pszDBName /* = "master"*/){
	m_strLastError = "";
	try{
		CString strSqlServer;
		CString strServer;
		if(!pszServer){
			strServer = "(local)";
		}else{
			strServer = pszServer;
		}
		BOOL bTrustedConnection = FALSE;
		if(!strlen(pszUser) && !strlen(pszPass)){
			//NT�F��
			//"driver={sql server};SERVER=(local);Database=LOCALDB;UID=;PWD=;"
			//strSqlServer.Format("Provider=SQLOLEDB; Server=%s; Integrated Security=SSPI;Persist Security Info=False; Initial Catalog=%s;", strServer, pszDBName);
			strSqlServer.Format("driver={sql server};SERVER=%s;Database=%s;UID=%s;PWD=%s;", strServer, pszDBName, pszUser, pszPass);
		}else{
			//SQLServer�F��
			//strSqlServer.Format("Provider=SQLOLEDB; Persist Security Info=False; Server=%s; User Id=%s; Password=%s; Initial Catalog=%s;", strServer, pszUser, pszPass, pszDBName);
			//strSqlServer.Format("Provider=SQLOLEDB; Server=%s; Persist Security Info=True; User Id=%s; Password=%s; Initial Catalog=%s;", strServer, pszUser, pszPass, pszDBName);
			strSqlServer.Format("Provider=SQLOLEDB; Server=%s; User Id=%s; Password=%s; Initial Catalog=%s;", strServer, pszUser, pszPass, pszDBName);
		}
		return Connect(strSqlServer, SQLSERVER);
	}catch(_com_error &e){
		DispError(e.Description());
		return FALSE;
	}
}
#endif
/**
 * �ڑ�����܂��B
 * @return ����ɕ����ꍇ��TRUE��Ԃ��܂��B
 */
BOOL CAdoDatabase::Close(){
	POSITION pos = m_arrTableInfo.GetStartPosition();
	CString strKey;
	PTABLEINFO pInfo = NULL;
	void* pVal;
	while(pos){
		m_arrTableInfo.GetNextAssoc(pos, strKey, pVal);
		pInfo = (PTABLEINFO)pVal;
		delete pInfo;
	}
	m_arrTableInfo.RemoveAll();

	HRESULT hRes;
	try{
		hRes = m_pConnect->Close();
		if(hRes != S_OK){
			return FALSE;
		}
		m_pConnect = 0;

		m_pCommand = 0;

		m_bConnect = FALSE;
		return TRUE;
	}catch(_com_error &e){
		DispError(e.Description());
		return FALSE;
	}
}
/*
BOOL CAdoDatabase::CreateMDB(LPCTSTR pszPath){
	BOOL bRet = TRUE;
	_CatalogPtr pCtalog = NULL;
	HRESULT hr;
	CString strProvider;
	CString strDBPath = pszPath;
	strProvider.Format("Provider=Microsoft.Jet.OLEDB.4.0;Data Source = %s", strDBPath);

	try{

		hr = pCtalog.CreateInstance( __uuidof( Catalog));
		if( FAILED(hr) == TRUE){
			pCtalog = NULL;
			_com_issue_error( hr);
		}

		//mdb�̍쐬
		pCtalog->Create( (LPCTSTR)strProvider);
	}catch( _com_error &e){
		bRet = FALSE;
	}
	if( pCtalog != NULL){
		pCtalog.Release();
	}
	return bRet;
}
*/
/**
 * SQL�����s���܂��B
 * @param pszSql SQL��
 * @return ���R�[�h�Z�b�g
 */
_RecordsetPtr CAdoDatabase::ExecSQL(LPCTSTR pszSql){
	m_strLastError = "";
	try{

		//SQL���
		CString strSQL = pszSql;
		strSQL.TrimLeft();
		int nLen = strSQL.GetLength();
		int nCmdType = CheckCommandType(strSQL);
		switch(nCmdType){
		case 0:
			m_pCommand->CommandType = adCmdText;
			break;
		case 1:
			m_pCommand->CommandType = adCmdText;
			break;
		case -1:
			m_pCommand->CommandType = adCmdUnknown;
			break;
		}


		m_pCommand->ActiveConnection = m_pConnect;
		m_pCommand->CommandText = pszSql;
//		m_pCommand->Parameters = NULL;
		m_pCommand->CommandTimeout = 30;
		_RecordsetPtr rs = NULL;

		switch(nCmdType){
		case 0:
			m_pCommand->Execute(NULL, NULL, 0);
			break;
		case 1:
			rs = m_pCommand->Execute(NULL, NULL, 0);
			break;
		default:
			rs = m_pCommand->Execute(NULL, NULL, 0);
			break;
		}

		return rs;
	}catch(_com_error &e){
		TRACE("%s\n", e.ErrorMessage());
		DispError(e.Description());
		return NULL;
	}
}

/**
 * �Q�Ɨp�̃��R�[�h�Z�b�g�̎擾�B
 * @param pszSql SQL��
 * @return ���R�[�h�Z�b�g
 */
_RecordsetPtr CAdoDatabase::OpenRecordSet(LPCTSTR pszSql){
	m_strLastError = "";
	try{
		_RecordsetPtr rs;
		rs.CreateInstance(__uuidof(Recordset));
		m_pCommand->ActiveConnection = m_pConnect;
		m_pCommand->CommandText = pszSql;
		m_pCommand->CommandType = adCmdUnknown;
//		m_pCommand->Parameters = NULL;
		m_pCommand->CommandTimeout = 30;

		rs->PutRefSource(m_pCommand);

		_variant_t vNull;  // VARIANT�^��NULL�Ƃ��Ďg��
		vNull.vt = VT_ERROR;
		vNull.scode = DISP_E_PARAMNOTFOUND;
		rs->Open(vNull, vNull, adOpenDynamic, adLockReadOnly, adCmdUnknown);
		return rs;
	}catch(_com_error &e){
		DispError(e.Description());
		return NULL;
	}
}

/**
 * �ҏW�\�ȃ��R�[�h�Z�b�g�̎擾
 * @param pszSql SQL��
 * @return ���R�[�h�Z�b�g
 */
_RecordsetPtr CAdoDatabase::OpenEditRecordSet(LPCTSTR pszSql){
	m_strLastError = "";
	try{
		_RecordsetPtr rs;
		rs.CreateInstance(__uuidof(Recordset));
		m_pCommand->ActiveConnection = m_pConnect;
		m_pCommand->CommandText = pszSql;
		m_pCommand->CommandType = adCmdUnknown;
//		m_pCommand->Parameters = NULL;
		m_pCommand->CommandTimeout = 30;
		rs->PutRefSource(m_pCommand);

		_variant_t vNull;  // VARIANT�^��NULL�Ƃ��Ďg��
		vNull.vt = VT_ERROR;
		vNull.scode = DISP_E_PARAMNOTFOUND;
		rs->Open(vNull, vNull, adOpenDynamic, adLockOptimistic, adCmdUnknown);
		return rs;
	}catch(_com_error &e){
		DispError(e.Description());
		return NULL;
	}
}

/**
 *���R�[�h�Z�b�g����l���擾���܂��B
 * @param rs ���R�[�h�Z�b�g
 * @param pszName �t�B�[���h��
 * @return �l
 */
_variant_t CAdoDatabase::GetFieldValue(_RecordsetPtr rs, LPCTSTR pszName){
	_variant_t val;
	m_strLastError = "";
	try{
		LONG lCount = rs->GetRecordCount();
		if(lCount == 0){
			val.vt = VT_NULL;
			return val;
		}
		
		val = rs->GetCollect(_variant_t(pszName));
	}catch(_com_error &e){
		DispError(e.Description());
		val.vt = VT_NULL;
	}
	return val;
}

/**
 *�e�[�u���ꗗ�̎擾
 * @param pszDBName �f�[�^�x�[�X��
 * @return ���R�[�h�Z�b�g
 */
_RecordsetPtr CAdoDatabase::GetTables(LPCTSTR pszDBName){
	m_strLastError = "";
	POSITION pos = m_arrTableInfo.GetStartPosition();
	CString strKey;
	void* pVal;
	PTABLEINFO pInfo = NULL;
	while(pos){
		m_arrTableInfo.GetNextAssoc(pos, strKey, pVal);
		pInfo = (PTABLEINFO)pVal;
		delete pInfo;
	}
	m_arrTableInfo.RemoveAll();


	_RecordsetPtr rs = m_pConnect->OpenSchema(adSchemaTables);
	if(rs == NULL){
		return rs;
	}

	_variant_t val;
	CString strVal;

	while(rs->EndOfFile == VARIANT_FALSE){
		//TABLE_CATALOG
		//TABLE_SCHEMA
		//TABLE_NAME
		//TABLE_TYPE
		//TABLE_GUID
		//DESCRIPTION
		//TABLE_PROPID
		//DATE_CREATED
		//DATE_MODIFIED
		
		pInfo = new TABLEINFO;
		memset(pInfo, 0, sizeof(TABLEINFO));

		val = GetFieldValue(rs, "TABLE_CATALOG");
		if(val.vt != VT_NULL){
			strVal = val.bstrVal;
//			strKey = strVal;
			strcpy(pInfo->szCatalog, strVal);
		}

		val = GetFieldValue(rs, "TABLE_SCHEMA");
		if(val.vt != VT_NULL){
			strVal = val.bstrVal;
//			strKey = strVal;
			strcpy(pInfo->szSchema, strVal);
		}

		val = GetFieldValue(rs, "TABLE_NAME");
		strVal = val.bstrVal;
		strKey = strVal;
		strcpy(pInfo->szTableName, strVal);

		val = GetFieldValue(rs, "TABLE_TYPE");
		strVal = val.bstrVal;

		if(!strVal.Compare("TABLE") || !strVal.Compare("T") || !strVal.Compare("U") || !strVal.Compare("")){
			pInfo->nType = T_TABLE;

		}else if(!strVal.Compare("SYSTEM TABLE")){
			pInfo->nType = T_SYSTEMTABLE;
		
		}else if(!strVal.Compare("VIEW") || !strVal.Compare("V")){
			pInfo->nType = T_VIEW;
		
		}else{
			pInfo->nType = T_UNKNOW;
		}
		m_arrTableInfo.SetAt(strKey, pInfo);
		rs->MoveNext();
	}

	rs->Close();
//	rs->Release();
	rs = NULL;

	rs = m_pConnect->OpenSchema(adSchemaTables);
	
	return rs;
}

CColumnInfo* CAdoDatabase::GetColumnInfo(LPCTSTR pszTableName){
	CColumnInfo* pInfo = NULL;
	COLUMNINFO objInfo;
	_variant_t val;
	CString strVal;
	CString strColName;
	CString strType;
	PCOLUMNINFO pColInfo;

	if(m_pConnect == NULL){
		return NULL;
	}

	_RecordsetPtr rs = NULL;
	if(m_eDBType == ODBC_SQLSERVER){
		//SQLServer/MSDE
		CString sql;
		/*
		TABLE_QUALIFIER
		TABLE_OWNER
		TABLE_NAME
		COLUMN_NAME
		DATA_TYPE
		TYPE_NAME
		PRECISION
		LENGTH
		SCALE
		RADIX
		NULLABLE
		REMARKS
		COLUMN_DEF
		SQL_DATA_TYPE
		SQL_DATETIME_SUB
		CHAR_OCTET_LENGTH
		ORDINAL_POSITION
		IS_NULLABLE
		SS_DATA_TYP
		*/
		sql.Format("sp_columns @table_name=\'%s\'", pszTableName);
		rs = OpenRecordSet(sql);
		if(rs == NULL){
			return NULL;
		}
		while(rs->EndOfFile == VARIANT_FALSE){
			if(!pInfo){
				pInfo = new CColumnInfo();
			}
			
			memset(&objInfo, 0, sizeof(COLUMNINFO));

			//�J�������擾
			val = GetFieldValue(rs, "COLUMN_NAME");
			strColName = val.bstrVal;
			strncpy(objInfo.szColumnName, strColName, 256);

			//�^�C�v�̎擾
			val = GetFieldValue(rs, "SQL_DATA_TYPE");
			objInfo.nType = val.iVal;

			memset(objInfo.szTypeName, 0, 14);
			val = GetFieldValue(rs, "TYPE_NAME");
			strType = val.bstrVal;
			strncpy(objInfo.szTypeName, (LPCTSTR)strType, 13);

			//NULL�擾
			val = GetFieldValue(rs, "IS_NULLABLE");
			objInfo.bNull = val.boolVal == VARIANT_TRUE;

			//����
			val = GetFieldValue(rs, "CHAR_OCTET_LENGTH");
			if(val.vt != VT_NULL){
				objInfo.nLen = val.iVal;
			}else{
				//����
				val = GetFieldValue(rs, "PRECISION");
				if(val.vt != VT_NULL){
					objInfo.nLen = val.iVal;
				}
			}

			pInfo->AddInfo(&objInfo);
			rs->MoveNext();
		}
		rs->Close();
		/*
		TABLE_QUALIFIER
		TABLE_OWNER
		TABLE_NAME
		COLUMN_NAME
		KEY_SEQ
		PK_NAME
		*/
		sql.Format("sp_pkeys @table_name=\'%s\'", pszTableName);
		rs = OpenRecordSet(sql);
		if(rs != NULL){
			CString strTblNameIdx;
			CString strColNameIdx;
			while(rs->EndOfFile == VARIANT_FALSE){
				//�J�������擾
				val = GetFieldValue(rs, "COLUMN_NAME");

				if(val.vt == VT_NULL){
					rs->MoveNext();
					continue;
				}
				strColNameIdx = val.bstrVal;

				int nSize = pInfo->GetSize();
				for(int i = 0; i < nSize; i++){
					pColInfo = pInfo->GetInfo(i);
					if(!strColNameIdx.Compare(pColInfo->szColumnName)){
						break;
					}
					pColInfo = NULL;
				}
				if(!pColInfo){
					rs->MoveNext();
					continue;
				}

				//�v���C�}���[�L�[
				val = GetFieldValue(rs, "PK_NAME");
				if(val.vt != VT_NULL){
					pColInfo->bKey = val.boolVal;
				}
				rs->MoveNext();
			}
		}
		rs->Close();
	}else{
		/*
		TABLE_CATALOG
		TABLE_SCHEMA
		TABLE_NAME
		COLUMN_NAME
		COLUMN_GUID
		COLUMN_PROPID
		ORDINAL_POSITION
		COLUMN_HASDEFAULT
		COLUMN_DEFAULT
		COLUMN_FLAGS
		IS_NULLABLE
		DATA_TYPE
		TYPE_GUID
		CHARACTER_MAXIMUM_LENGTH
		CHARACTER_OCTET_LENGTH
		NUMERIC_PRECISION
		NUMERIC_SCALE
		DATETIME_PRECISION
		CHARACTER_SET_CATALOG
		CHARACTER_SET_SCHEMA
		CHARACTER_SET_NAME
		COLLATION_CATALOG
		COLLATION_SCHEMA
		COLLATION_NAME
		DOMAIN_CATALOG
		DOMAIN_SCHEMA
		DOMAIN_NAME
		DESCRIPTION
		*/

		rs = m_pConnect->OpenSchema(adSchemaColumns);
		if(rs == NULL){
			return NULL;
		}

		//�m�F�p
		while(rs->EndOfFile == VARIANT_FALSE){
			val = GetFieldValue(rs, "TABLE_NAME");
			strVal = val.bstrVal;
			if(strVal.Compare(pszTableName)){
				rs->MoveNext();
				continue;
			}

			if(!pInfo){
				pInfo = new CColumnInfo();
			}
			
			memset(&objInfo, 0, sizeof(COLUMNINFO));

			//�J�������擾
			val = GetFieldValue(rs, "COLUMN_NAME");
			strColName = val.bstrVal;
			strncpy(objInfo.szColumnName, strColName, 256);

			//�^�C�v�̎擾
			val = GetFieldValue(rs, "DATA_TYPE");
			objInfo.nType = val.iVal;

			//NULL�擾
			val = GetFieldValue(rs, "IS_NULLABLE");
			objInfo.bNull = val.boolVal == VARIANT_TRUE;

			val = GetFieldValue(rs, "CHARACTER_MAXIMUM_LENGTH");
			if(val.vt != VT_NULL){
				objInfo.nLen = (int)val.dblVal;
			}

			pInfo->AddInfo(&objInfo);
			rs->MoveNext();
		}
		rs->Close();

		//�L�[����
		/**
		TABLE_CATALOG
		TABLE_SCHEMA
		TABLE_NAME
		INDEX_CATALOG
		INDEX_SCHEMA
		INDEX_NAME
		PRIMARY_KEY
		UNIQUE
		CLUSTERED
		TYPE
		FILL_FACTOR
		INITIAL_SIZE
		NULLS
		SORT_BOOKMARKS
		AUTO_UPDATE
		NULL_COLLATION
		ORDINAL_POSITION
		COLUMN_NAME
		COLUMN_GUID
		COLUMN_PROPID
		COLLATION
		CARDINALITY
		PAGES
		FILTER_CONDITION
		INTEGRATED
		*/
		rs = m_pConnect->OpenSchema(adSchemaIndexes);
		if(rs != NULL){
			CString strTblNameIdx;
			CString strColNameIdx;
			PCOLUMNINFO pColInfo;
			while(rs->EndOfFile == VARIANT_FALSE){
				val = GetFieldValue(rs, "TABLE_NAME");
				strTblNameIdx = val.bstrVal;
				if(strTblNameIdx.Compare(pszTableName)){
					rs->MoveNext();
					continue;
				}

				//�J�������擾
				val = GetFieldValue(rs, "COLUMN_NAME");

				if(val.vt == VT_NULL){
					rs->MoveNext();
					continue;
				}
				strColNameIdx = val.bstrVal;

				int nSize = pInfo->GetSize();
				for(int i = 0; i < nSize; i++){
					pColInfo = pInfo->GetInfo(i);
					if(!strColNameIdx.Compare(pColInfo->szColumnName)){
						break;
					}
					pColInfo = NULL;
				}
				if(!pColInfo){
					rs->MoveNext();
					continue;
				}

				//�v���C�}���[�L�[
				val = GetFieldValue(rs, "PRIMARY_KEY");
				if(val.vt != VT_NULL){
					pColInfo->bKey = val.boolVal;
				}
				rs->MoveNext();
			}
		}
		rs->Close();
	}
	return pInfo;
}

/**
 *�e�[�u���̏����擾���܂��B
 * @param pszTableName �e�[�u����
 * @return �e�[�u���̏����i�[����PTABLEINFO�B���̎擾�Ɏ��s�����ꍇ��NULL��Ԃ��B
 */
PTABLEINFO CAdoDatabase::GetTableInfo(LPCTSTR pszTableName){
	m_strLastError = "";
	PTABLEINFO pInfo = NULL;
	if(!m_arrTableInfo.GetCount()){
		return NULL;
	}
	void* pVal;
	if(m_arrTableInfo.Lookup(pszTableName, pVal)){
		pInfo = (PTABLEINFO)pVal;
		return pInfo;
	}else{
		return NULL;
	}
}

/**
 * �J�����ꗗ�̎擾(SQLServer/MSDE��p)
 * @param pszTable �e�[�u����
 * @return ���R�[�h�Z�b�g
 */
_RecordsetPtr CAdoDatabase::GetColumns(LPCTSTR pszTable){
	m_strLastError = "";
	CString strSql;
	strSql.Format("sp_columns @table_name = '%s' ", pszTable);
	return OpenRecordSet(strSql);
}

/**
 * DB�ꗗ�̎擾(SQLServer/MSDE��p)
 * @return ���R�[�h�Z�b�g
 */
_RecordsetPtr CAdoDatabase::GetDatabases(){
	m_strLastError = "";
	if(m_pCommand == NULL){
		DispError("internal error CAdoDatabase::GetDatabases().\nm_pCommand is fault.");
		return NULL;
	}

	m_pCommand->ActiveConnection = m_pConnect;
	m_pCommand->CommandText = "sp_databases";
	m_pCommand->CommandType = adCmdUnknown;
//	m_pCommand->Parameters = NULL;
	m_pCommand->CommandTimeout = 30;
	try{
		return m_pCommand->Execute(NULL, NULL, 0);
	}catch(_com_error &e){
		DispError(e.Description());
		return NULL;
	}
//	ExecSQL("use master");
//	return OpenRecordSet("sp_databases");
}

/**
 * �G���[���o�͂��邩�ǂ����̐ݒ�<BR>
 * DispError�֐��ŃG���[���b�Z�[�W��ݒ肵���ꍇ�ɕ\�`���ǂ����̐ݒ���s�Ȃ��܂��B
 * @param bOut �G���[���o�͂���ꍇ��TRUE��ݒ肵�܂��B
 * @return �ύX�O�̏��
 */
BOOL CAdoDatabase::SetErrorOut(BOOL bOut){
	BOOL bOld = m_bErrOut;
	m_bErrOut = bOut;
	return bOld;
}

/**
 * �G���[��\�����܂��B
 * @param pszErr �G���[���b�Z�[�W
 */
void CAdoDatabase::DispError(LPCTSTR pszErr){
	if(m_bErrOut){
		AfxMessageBox(pszErr);
	}
	m_strLastError = pszErr;
}

/**
 * �Ō�ɔ��������G���[�̃��b�Z�[�W���擾���܂��B<BR>
 * DispError�֐��Őݒ肳�ꂽ���b�Z�[�W���Ԃ���܂��B
 * @return �G���[���b�Z�[�W
 */
LPCTSTR CAdoDatabase::GetError(){
	return m_strLastError;
}

/**
 *�ڑ����̃f�[�^�x�[�X�̎�ʂ�Ԃ��܂��B
 * @return �f�[�^�x�[�X�̎��
 */
eDBType CAdoDatabase::GetDBType(){
	m_strLastError = "";
	return m_eDBType;
}

/**
 * �X�g�A�h�v���V�[�W���̈ꗗ���擾���܂��B(SQLServer/MSDE��p)
 * @return ���R�[�h�Z�b�g
 */
_RecordsetPtr CAdoDatabase::GetProcedures(){
	CString strSQL;
	if(!IsConnect()){
		return NULL;
	}
	strSQL = "select name from sysobjects where xtype='P'";
	_RecordsetPtr rs = OpenRecordSet(strSQL);
	return rs;
}

/**
 * �R�}���h���X�g�Ɣ�r���s�Ȃ��܂��B
 * @param pszCmd SQL�R�}���h
 * @return ��v����R�}���h������A�Q�ƃR�}���h(SELECT)�ł����1�A�Q�ƂłȂ���� 0�A��v����R�}���h�������ꍇ��0��Ԃ��܂��B
 */
int CAdoDatabase::CheckCommandType(LPCTSTR pszCmd){
	
	int nCnt = sizeof(arrCmdDat) / sizeof(CMDDAT);
	
	CString strSQL = pszCmd;
	strSQL.TrimLeft();
	int nLen = strSQL.GetLength();

	int nCmdLen;

	for(int i = 0; i < nCnt; i++){
	
		nCmdLen = strlen(arrCmdDat[i].pszKey);
		if(nLen > nCmdLen){
			if(!strSQL.Left(nCmdLen).CompareNoCase(arrCmdDat[i].pszKey)){
				//�擾
				return arrCmdDat[i].nType;
			}
		}
	}
	return -1;

}

BOOL CAdoDatabase::IsReserve(LPCTSTR pszText){
	CString strVal;
	CString strKey = pszText;
	strKey.MakeUpper();
#if defined(NEW_DBTYPE)
	if((m_eDBType == SQLSERVER_ODBC)
	|| (m_eDBType == SQLSERVER_OLEDB)){
		return m_mapSQLReserve.Lookup(strKey, strVal);
	}else if(m_eDBType == ODBC_DATASRC){
		return m_mapODBCReserve.Lookup(strKey, strVal);
	}else{
		return FALSE;
	}
#else
	if(m_eDBType == SQLSERVER){
		return m_mapSQLReserve.Lookup(strKey, strVal);
	}else if(m_eDBType == ODBC){
		return m_mapODBCReserve.Lookup(strKey, strVal);
	}else{
		return FALSE;
	}
#endif
}
void CAdoDatabase::SetODBCType(eODBCType odbc){
	m_eODBCType = odbc;
}
eODBCType CAdoDatabase::GetODBCType(){
	return m_eODBCType;
}
