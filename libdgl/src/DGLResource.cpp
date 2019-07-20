// DGLResource.cpp: CDGLResource クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "DGLResource.h"

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CDGLResource::CDGLResource(){
	m_nTop		= 0;
	m_nLeft		= 0;
	m_nHeight	= 320;
	m_nWidth	= 240;
	m_hInst		= NULL;
	m_hWnd		= NULL;
	m_nInterval	= 0;
	m_TimeId	= 0;
	m_hIcon		= NULL;
}

CDGLResource::~CDGLResource(){

}

bool CDGLResource::AddResource(CDGLResItem *pItem){
	return true;
}
