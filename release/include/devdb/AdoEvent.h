// AdoEvent.h: CAdoEvent クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADOEVENT_H__9EA74E21_E3AF_4131_8FF4_6939C64A3154__INCLUDED_)
#define AFX_ADOEVENT_H__9EA74E21_E3AF_4131_8FF4_6939C64A3154__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

	//参考 http://www.alpha-net.ne.jp/users2/uk413/vc/VCT_ADO.html
	#define INITGUID		// これはADOを定義するための定数(GUID)の初期化
	#pragma warning(disable : 4146)		//ADOの警告抑止

	#import "C:\Program Files\Common Files\System\ADO\msado15.dll" rename_namespace("ADOCG") rename("EOF", "EndOfFile")
	using namespace ADOCG;	// 名前空間

#ifdef DEVDB_EXPORTS
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_IMPORT
#endif

class DEV_EXT_MFCCLASS CAdoRecordSetEvent{
/*
class DEV_EXT_MFCCLASS CAdoRecordSetEvent : public RecordsetEventsVt{

public:
	CAdoRecordSetEvent();
	virtual ~CAdoRecordSetEvent();
	STDMETHODIMP QueryInterface(REFIID riid, void ** ppv);
	STDMETHODIMP_(ULONG) AddRef(void);
	STDMETHODIMP_(ULONG) Release(void);

	STDMETHODIMP raw_WillChangeField(LONG cFields,
									VARIANT Fields,
									EventStatusEnum *adStatus,
									struct _Recordset *pRecordset);

	STDMETHODIMP raw_FieldChangeComplete(LONG cFields,
										VARIANT Fields,
										struct Error *pError,
										EventStatusEnum *adStatus,
										struct _Recordset *pRecordset);

	STDMETHODIMP raw_WillChangeRecord(EventReasonEnum adReason,
									LONG cRecords,
									EventStatusEnum *adStatus,
									struct _Recordset *pRecordset);

	STDMETHODIMP raw_RecordChangeComplete(EventReasonEnum adReason,
										LONG cRecords,
										struct Error *pError,
										EventStatusEnum *adStatus,
										struct _Recordset *pRecordset);

	STDMETHODIMP raw_WillChangeRecordset(EventReasonEnum adReason,
										EventStatusEnum *adStatus,
										struct _Recordset *pRecordset);

	STDMETHODIMP raw_RecordsetChangeComplete(EventReasonEnum adReason,
											struct Error *pError,
											EventStatusEnum *adStatus,
											struct _Recordset *pRecordset);

	STDMETHODIMP raw_WillMove(EventReasonEnum adReason,
							EventStatusEnum *adStatus,
							struct _Recordset *pRecordset);

	STDMETHODIMP raw_MoveComplete(EventReasonEnum adReason,
								struct Error *pError,
								EventStatusEnum *adStatus,
								struct _Recordset *pRecordset);

	STDMETHODIMP raw_EndOfRecordset(VARIANT_BOOL *fMoreData,
									EventStatusEnum *adStatus,
									struct _Recordset *pRecordset);

	STDMETHODIMP raw_FetchProgress(long Progress,
								long MaxProgress,
								EventStatusEnum *adStatus,
								struct _Recordset *pRecordset);

	STDMETHODIMP raw_FetchComplete(struct Error *pError,
								EventStatusEnum *adStatus,
								struct _Recordset *pRecordset);

private:
	ULONG	m_cRef;
*/
};

class DEV_EXT_MFCCLASS CAdoConnectionEvent{
/*
class DEV_EXT_MFCCLASS CAdoConnectionEvent : public ConnectionEventsVt{
public:
	CAdoConnectionEvent();
	virtual ~CAdoConnectionEvent();

	STDMETHODIMP QueryInterface(REFIID riid, void ** ppv);
	STDMETHODIMP_(ULONG) AddRef(void);
	STDMETHODIMP_(ULONG) Release(void);

	STDMETHODIMP raw_InfoMessage(struct Error *pError,
								 EventStatusEnum *adStatus,
								 struct _Connection *pConnection);

	STDMETHODIMP raw_BeginTransComplete(LONG TransactionLevel,
										struct Error *pError,
										EventStatusEnum *adStatus,
										struct _Connection *pConnection);

	STDMETHODIMP raw_CommitTransComplete(struct Error *pError,
										 EventStatusEnum *adStatus,
										 struct _Connection *pConnection);

	STDMETHODIMP raw_RollbackTransComplete(struct Error *pError,
										   EventStatusEnum *adStatus,
										   struct _Connection *pConnection);

	STDMETHODIMP raw_WillExecute(BSTR *Source,
								 CursorTypeEnum *CursorType,
								 ADOCG::LockTypeEnum *LockType,
								 long *Options,
								 EventStatusEnum *adStatus,
								 struct _Command *pCommand,
								 struct _Recordset *pRecordset,
								 struct _Connection *pConnection);

	STDMETHODIMP raw_ExecuteComplete(LONG RecordsAffected,
									 struct Error *pError,
									 EventStatusEnum *adStatus,
									 struct _Command *pCommand,
									 struct _Recordset *pRecordset,
									 struct _Connection *pConnection);

	STDMETHODIMP raw_WillConnect(BSTR *ConnectionString,
								 BSTR *UserID,
								 BSTR *Password,
								 long *Options,
								 EventStatusEnum *adStatus,
								 struct _Connection *pConnection);

	STDMETHODIMP raw_ConnectComplete(struct Error *pError,
									 EventStatusEnum *adStatus,
									 struct _Connection *pConnection);

	STDMETHODIMP raw_Disconnect(EventStatusEnum *adStatus,
								struct _Connection *pConnection);

private:
	ULONG	m_cRef;

*/
};
#endif // !defined(AFX_ADOEVENT_H__9EA74E21_E3AF_4131_8FF4_6939C64A3154__INCLUDED_)
