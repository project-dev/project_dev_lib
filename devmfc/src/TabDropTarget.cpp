// TabDropTarget.cpp: CTabDropTarget クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TabCtrlEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CTabDropTarget::CTabDropTarget(){
	if(!SystemParametersInfo(SPI_GETMOUSEHOVERTIME,
							 0, &m_dwHoverInterval, 0)){
		m_dwHoverInterval = 100;
	}
}

CTabDropTarget::~CTabDropTarget(){

}

BOOL CTabDropTarget::Register( CTabCtrlEx* pWnd ){
	return COleDropTarget::Register(pWnd);
}

DROPEFFECT CTabDropTarget::OnDragEnter( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point ){
#ifdef USE_DROPTARGET
	CTabCtrlEx *pTabCtrl = (CTabCtrlEx*)pWnd;
	if(StartDrop(pTabCtrl)){
		return pTabCtrl->OnDragEnter(pDataObject, dwKeyState, point);
	}else{
		return DROPEFFECT_NONE;
	}
#else
		return DROPEFFECT_NONE;
#endif
}

void CTabDropTarget::OnDragLeave( CWnd* pWnd ){
}

DROPEFFECT CTabDropTarget::OnDragOver( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point ){
#ifdef USE_DROPTARGET
	POINT pos;
	GetCursorPos(&pos);
	CTabCtrlEx *pTabCtrl = (CTabCtrlEx*)pWnd;
	if((m_oldPos.x != pos.x)
	|| (m_oldPos.y != pos.y)){
		m_oldPos = pos;
		if(StartDrop(pTabCtrl)){
			return pTabCtrl->OnDragOver(pDataObject, dwKeyState, point);
		}else{
			return DROPEFFECT_NONE;
		}
	}
#endif
	return DROPEFFECT_COPY;
}

BOOL CTabDropTarget::StartDrop(CTabCtrlEx* pWnd){
	TRACKMOUSEEVENT tmEvent;
	TRACE("StartDrop %d \n", m_dwHoverInterval);
	memset(&tmEvent, 0, sizeof(TRACKMOUSEEVENT));
	tmEvent.cbSize		= sizeof(TRACKMOUSEEVENT);
	tmEvent.dwFlags		= TME_HOVER;
	tmEvent.dwHoverTime	= m_dwHoverInterval;
	tmEvent.hwndTrack	= pWnd->m_hWnd;
	if(!::_TrackMouseEvent(&tmEvent)){
		TRACE("失敗\n");
		return FALSE;
	}
	return TRUE;
}
