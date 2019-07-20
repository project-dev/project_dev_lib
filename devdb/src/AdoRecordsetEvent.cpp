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
CAdoRecordSetEvent::CAdoRecordSetEvent(){
	m_cRef = 0;
}

CAdoRecordSetEvent::~CAdoRecordSetEvent(){

}

STDMETHODIMP CAdoRecordSetEvent::QueryInterface(REFIID riid, void ** ppv){
      *ppv = NULL;
      if (riid == __uuidof(IUnknown) || 
              riid == __uuidof(RecordsetEventsVt)) *ppv = this;
      if (*ppv == NULL)
         return ResultFromScode(E_NOINTERFACE);
      AddRef();
      return NOERROR;
}

STDMETHODIMP_(ULONG) CAdoRecordSetEvent::AddRef(void){
	return ++m_cRef;
}

STDMETHODIMP_(ULONG) CAdoRecordSetEvent::Release(void){
	if (0 != --m_cRef){
		return m_cRef;
	}
	delete this;
	return 0;
}

STDMETHODIMP CAdoRecordSetEvent::raw_WillChangeField(LONG cFields,
								VARIANT Fields,
								EventStatusEnum *adStatus,
								struct _Recordset *pRecordset){
	*adStatus = adStatusUnwantedEvent;
	return S_OK;
}

STDMETHODIMP CAdoRecordSetEvent::raw_FieldChangeComplete(LONG cFields,
									VARIANT Fields,
									struct Error *pError,
									EventStatusEnum *adStatus,
									struct _Recordset *pRecordset){
	*adStatus = adStatusUnwantedEvent;
	return S_OK;
}

STDMETHODIMP CAdoRecordSetEvent::raw_WillChangeRecord(EventReasonEnum adReason,
								LONG cRecords,
								EventStatusEnum *adStatus,
								struct _Recordset *pRecordset){
	*adStatus = adStatusUnwantedEvent;
	return S_OK;
}

STDMETHODIMP CAdoRecordSetEvent::raw_RecordChangeComplete(EventReasonEnum adReason,
									LONG cRecords,
									struct Error *pError,
									EventStatusEnum *adStatus,
									struct _Recordset *pRecordset){
	*adStatus = adStatusUnwantedEvent;
	return S_OK;
}

STDMETHODIMP CAdoRecordSetEvent::raw_WillChangeRecordset(EventReasonEnum adReason,
									EventStatusEnum *adStatus,
									struct _Recordset *pRecordset){
	*adStatus = adStatusUnwantedEvent;
	return S_OK;
}

STDMETHODIMP CAdoRecordSetEvent::raw_RecordsetChangeComplete(EventReasonEnum adReason,
										struct Error *pError,
										EventStatusEnum *adStatus,
										struct _Recordset *pRecordset){
	*adStatus = adStatusUnwantedEvent;
	return S_OK;
}

STDMETHODIMP CAdoRecordSetEvent::raw_WillMove(EventReasonEnum adReason,
						EventStatusEnum *adStatus,
						struct _Recordset *pRecordset){
	*adStatus = adStatusUnwantedEvent;
	return S_OK;
}

STDMETHODIMP CAdoRecordSetEvent::raw_MoveComplete(EventReasonEnum adReason,
							struct Error *pError,
							EventStatusEnum *adStatus,
							struct _Recordset *pRecordset){
	*adStatus = adStatusUnwantedEvent;
	return S_OK;
}

STDMETHODIMP CAdoRecordSetEvent::raw_EndOfRecordset(VARIANT_BOOL *fMoreData,
								EventStatusEnum *adStatus,
								struct _Recordset *pRecordset){
	*adStatus = adStatusUnwantedEvent;
	return S_OK;
}

STDMETHODIMP CAdoRecordSetEvent::raw_FetchProgress(long Progress,
							long MaxProgress,
							EventStatusEnum *adStatus,
							struct _Recordset *pRecordset){
	*adStatus = adStatusUnwantedEvent;
	return S_OK;
}

STDMETHODIMP CAdoRecordSetEvent::raw_FetchComplete(struct Error *pError,
							EventStatusEnum *adStatus,
							struct _Recordset *pRecordset){
	*adStatus = adStatusUnwantedEvent;
	return S_OK;
}
*/