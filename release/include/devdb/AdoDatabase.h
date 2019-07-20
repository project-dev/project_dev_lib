// AdoDatabase.h: CAdoDatabase クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADODATABASE_H__E11EE96E_3FE7_4708_8406_7269AB37B0DE__INCLUDED_)
#define AFX_ADODATABASE_H__E11EE96E_3FE7_4708_8406_7269AB37B0DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*
#define INITGUID		// これはADOを定義するための定数(GUID)の初期化
#pragma warning(disable : 4146)		//ADOの警告抑止

#import "C:\Program Files\Common Files\System\ADO\msado15.dll" rename_namespace("ADOCG") rename("EOF", "EndOfFile")
using namespace ADOCG;	// 名前空間
#include "icrsint.h"	// ADOを使って取得したフィールドのデータを変換するマクロなどが定義されたヘッダー
*/
//#include <atlbase.h>
//#include <comdef.h>
#include <afxtempl.h>
#include "AdoEvent.h"
#ifdef DEVDB_EXPORTS
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_IMPORT
#endif

/**
 * データベースの種別を表す列挙型
 */
#if defined(NEW_DBTYPE)
typedef enum eDBType{
	///不明
	UNKNOW				= -1,

	///ODBC データソース
	ODBC_DATASRC		= 0,

	///SQLServer/MSDE OLE DBプロバイダ
	SQLSERVER_AUTO		= 1,
	SQLSERVER_OLEDB		= 2,
	SQLSERVER_ODBC		= 3,

	///ACCESS
	ACCESS_OLEDB		= 4,
	ACCESS_ODBC			= 5,

	///Oracle
	ORACLE_OLEDB		= 6,
//	ORACLE_ODBC			= 7,
	ORACLE_MS_OLEDB		= 7,
	ORACLE_MS_ODBC		= 8,

	//DB2
	DB2_OLEDB			= 9,
/*
	//PostgreSQL
	POSTGRESQL_OLEDB	= 9,
	POSTGRESQL_ODBC		= 10,

	//Excel
	EXCEL_OLEDB			= 11,
	EXCEL_ODBC			= 12,

	//CSV
	CSV_OLEDB			= 13,
	CSV_ODBC			= 14,

	//HTML
	HTML_OLEDB			= 4,
	HTML_ODBC			= 4,
*/
};
#else
typedef enum eDBType{
	///不明
	UNKNOW	  = -1,
	///SQLServer/MSDE
	SQLSERVER = 0,

	///ODBC
	ODBC	  = 1,

	///ACCESS
	ACCESS	  = 2,

	///Oracle
	ORACLE	  = 3
};
#endif

typedef enum eODBCType{
	ODBC_UNKNOW		= -1,
	ODBC_SQLSERVER	= 0,
	ODBC_ACCESS,
	ODBC_DB2,
	ODBC_ORACLE,
	ODBC_POSTGRESQL,
	ODBC_SYBASE,
};

/**
 * テーブルの種別を表す列挙型
 */
typedef enum eTableType{
	///不明
	T_UNKNOW		= 0,
	///テーブル
	T_TABLE			= 1,
	///システムテーブル
	T_SYSTEMTABLE,
	///ビュー
	T_VIEW
};

/**
 * テーブルの情報を格納する構造体
 */
typedef struct tagTABLEINFO{
	///クオリファイア
	char szQualifier[256];

	///テーブルのオーナー
	char szOwner[256];

	///カタログ
	char szCatalog[256];

	///スキーマ
	char szSchema[256];

	///テーブル名
	char szTableName[256];

	///テーブルの種別
	eTableType nType;
}TABLEINFO, *PTABLEINFO;

/**
 *ADOを利用したデータベースアクセスクラス
 */
class CColumnInfo;
class DEV_EXT_MFCCLASS CAdoDatabase : CObject{
public:
	BOOL IsReserve(LPCTSTR pszText);
	int CheckCommandType(LPCTSTR pszCmd);
	_RecordsetPtr GetProcedures();
	eDBType GetDBType();
	eODBCType GetODBCType();
	void SetODBCType(eODBCType odbc);
	LPCTSTR GetError();
	BOOL SetErrorOut(BOOL bOut = TRUE);
	BOOL Connect(LPCTSTR pszCommand, eDBType eDB);
#if defined(NEW_DBTYPE)
	BOOL ConnectODBC(eDBType eDB, LPCTSTR pszServer = "(local)", LPCTSTR pszUser = "sa", LPCTSTR pszPass = "", LPCTSTR pszDBName = "master");
	BOOL ConnectSqlServer(eDBType eDB, LPCTSTR pszServer = "(local)", LPCTSTR pszUser = "sa", LPCTSTR pszPass = "", LPCTSTR pszDBName = "master");
	BOOL ConnectOracle(eDBType eDB, LPCTSTR pszServer = "(local)", LPCTSTR pszUser = "scott", LPCTSTR pszPass = "tiger");
	BOOL ConnectAccess(eDBType eDB, LPCTSTR pszMDB, LPCTSTR pszUser, LPCTSTR pszPass);
	BOOL ConnectDB2(eDBType eDB, LPCTSTR pszDSN, LPCTSTR pszUser, LPCTSTR pszPass);
#else
	BOOL ConnectSqlServer(LPCTSTR pszServer = "(local)", LPCTSTR pszUser = "sa", LPCTSTR pszPass = "", LPCTSTR pszDBName = "master");
	BOOL ConnectODBC(LPCTSTR pszServer = "(local)", LPCTSTR pszUser = "sa", LPCTSTR pszPass = "", LPCTSTR pszDBName = "master");
	BOOL ConnectOracle(LPCTSTR pszServer = "(local)", LPCTSTR pszUser = "scott", LPCTSTR pszPass = "tiger");
	BOOL ConnectAccess(LPCTSTR pszMDB, LPCTSTR pszUser, LPCTSTR pszPass, LPCTSTR pszProvider = "Microsoft.Jet.OLEDB.4.0");
#endif
	_RecordsetPtr GetDatabases();
	_RecordsetPtr GetColumns(LPCTSTR pszTable);
	_RecordsetPtr GetTables(LPCTSTR pszDBName = NULL);
	CColumnInfo* GetColumnInfo(LPCTSTR psztableName);
	PTABLEINFO GetTableInfo(LPCTSTR pszTableName);
	_variant_t GetFieldValue(_RecordsetPtr rs, LPCTSTR pszName);
	_RecordsetPtr OpenEditRecordSet(LPCTSTR pszSql);
	_RecordsetPtr OpenRecordSet(LPCTSTR pszSql);
	_RecordsetPtr ExecSQL(LPCTSTR pszSql);
	BOOL Close();
	BOOL IsConnect();
	BOOL Create();
	CAdoDatabase();
	virtual ~CAdoDatabase();

//	BOOL CreateMDB(LPCTSTR pszPath);

private:
	CString m_strLastError;
	BOOL m_bErrOut;
	BOOL m_bConnect;
	_ConnectionPtr m_pConnect;   // Connectionオブジェクト
	_CommandPtr m_pCommand;      // Commandオブジェクト

	HRESULT m_hComInit;

	void DispError(LPCTSTR pszErr);
	CMapStringToPtr m_arrTableInfo;
	eDBType m_eDBType;
	eODBCType m_eODBCType;

	CMapStringToString m_mapSQLReserve;
	CMapStringToString m_mapODBCReserve;


};

#endif // !defined(AFX_ADODATABASE_H__E11EE96E_3FE7_4708_8406_7269AB37B0DE__INCLUDED_)
