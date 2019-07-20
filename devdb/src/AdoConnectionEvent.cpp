// AdoEvent.cpp: CAdoEvent クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "devdb.h"
#include "AdoEvent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////
/*
CAdoConnectionEvent::CAdoConnectionEvent()
{
	m_cRef = 0;
}

CAdoConnectionEvent::~CAdoConnectionEvent()
{

}

STDMETHODIMP CAdoConnectionEvent::QueryInterface(REFIID riid, void ** ppv){
	*ppv = NULL;
	if (riid == __uuidof(IUnknown) || riid == __uuidof(ConnectionEventsVt)){
		*ppv = this;
	}
	if (*ppv == NULL){
		return ResultFromScode(E_NOINTERFACE);
	}
	AddRef();
	return NOERROR;
}

STDMETHODIMP_(ULONG) CAdoConnectionEvent::AddRef(void){
	return ++m_cRef;
}

STDMETHODIMP_(ULONG) CAdoConnectionEvent::Release(void){
	if (0 != --m_cRef){
		return m_cRef;
	}
	delete this;
	return 0;

}

STDMETHODIMP CAdoConnectionEvent::raw_InfoMessage(struct Error *pError,
							 EventStatusEnum *adStatus,
							 struct _Connection *pConnection){
	*adStatus = adStatusUnwantedEvent;
	return S_OK;
}

STDMETHODIMP CAdoConnectionEvent::raw_BeginTransComplete(LONG TransactionLevel,
									struct Error *pError,
									EventStatusEnum *adStatus,
									struct _Connection *pConnection){
	*adStatus = adStatusUnwantedEvent;
	return S_OK;
}

STDMETHODIMP CAdoConnectionEvent::raw_CommitTransComplete(struct Error *pError,
									 EventStatusEnum *adStatus,
									 struct _Connection *pConnection){
	*adStatus = adStatusUnwantedEvent;
	return S_OK;
}

STDMETHODIMP CAdoConnectionEvent::raw_RollbackTransComplete(struct Error *pError,
									   EventStatusEnum *adStatus,
									   struct _Connection *pConnection){
	*adStatus = adStatusUnwantedEvent;
	return S_OK;
}

STDMETHODIMP CAdoConnectionEvent::raw_WillExecute(BSTR *Source,
							 CursorTypeEnum *CursorType,
							 ADOCG::LockTypeEnum *LockType,
							 long *Options,
							 EventStatusEnum *adStatus,
							 struct _Command *pCommand,
							 struct _Recordset *pRecordset,
							 struct _Connection *pConnection){
	*adStatus = adStatusUnwantedEvent;
	return S_OK;
}

STDMETHODIMP CAdoConnectionEvent::raw_ExecuteComplete(LONG RecordsAffected,
								 struct Error *pError,
								 EventStatusEnum *adStatus,
								 struct _Command *pCommand,
								 struct _Recordset *pRecordset,
								 struct _Connection *pConnection){
	*adStatus = adStatusUnwantedEvent;
	return S_OK;
}

STDMETHODIMP CAdoConnectionEvent::raw_WillConnect(BSTR *ConnectionString,
							 BSTR *UserID,
							 BSTR *Password,
							 long *Options,
							 EventStatusEnum *adStatus,
							 struct _Connection *pConnection){
	*adStatus = adStatusUnwantedEvent;
	return S_OK;
}

STDMETHODIMP CAdoConnectionEvent::raw_ConnectComplete(struct Error *pError,
								 EventStatusEnum *adStatus,
								 struct _Connection *pConnection){
	*adStatus = adStatusUnwantedEvent;
	return S_OK;
}

STDMETHODIMP CAdoConnectionEvent::raw_Disconnect(EventStatusEnum *adStatus,
							struct _Connection *pConnection){
	*adStatus = adStatusUnwantedEvent;
	return S_OK;
}
*/