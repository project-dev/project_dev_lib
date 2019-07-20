// DGLObject.cpp: CDGLObject �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "DGLObject.h"

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CDGLObject::CDGLObject(){
	m_pDGLMain = NULL;
}

CDGLObject::~CDGLObject(){
	if(Destroy()){
		//�f�o�b�O���[�`������
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
