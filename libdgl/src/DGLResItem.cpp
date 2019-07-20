// DGLResItem.cpp: CDGLResItem クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "DGLResItem.h"

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CDGLResItem::CDGLResItem(eResType eType){
	m_nType = eType;
}

CDGLResItem::~CDGLResItem(){

}

//ファイルの読み込み
bool CDGLResItem::LoadData(char* pszFileName){
	switch(m_nType){
	case RES_BITMAP:
	case RES_WAVE:
	case RES_MIDI:
		break;
	default:
		return false;
	}
	return false;
}

//リソースの読み込み
bool CDGLResItem::LoadData(long lID){
	switch(m_nType){
	case RES_BITMAP:
	case RES_WAVE:
	case RES_MIDI:
		break;
	default:
		return false;
	}
	return false;
}
