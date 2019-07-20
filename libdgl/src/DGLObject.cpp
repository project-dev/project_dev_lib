// DGLObject.cpp: CDGLObject クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "DGLObject.h"

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CDGLObject::CDGLObject(){
	m_pDGLMain = NULL;
}

CDGLObject::~CDGLObject(){
	if(Destroy()){
		//デバッグルーチン動作
	}
}

bool CDGLObject::Create(CDGLMain *pDGLMain){
	if(!pDGLMain){
		return false;
	}
	m_pDGLMain = pDGLMain;
	return true;
}

bool CDGLObject::Destroy(){
	return true;
}

CDGLMain* CDGLObject::GetDGLMain(){
	return m_pDGLMain;
}
