// DGLResItem.cpp: CDGLResItem �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "DGLResItem.h"

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CDGLResItem::CDGLResItem(eResType eType){
	m_nType = eType;
}

CDGLResItem::~CDGLResItem(){

}

//�t�@�C���̓ǂݍ���
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

//���\�[�X�̓ǂݍ���
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
