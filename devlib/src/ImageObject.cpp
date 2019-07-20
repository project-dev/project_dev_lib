// ImageObject.cpp: CImageObject �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ImageObject.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

// 
// �֐��� : CImageObject
// �T  �v : �R���X�g���N�^
// ��  �� : �Ȃ�
// �߂�l : �Ȃ�
// ��  �l : �Ȃ�
//
CImageObject::CImageObject(){
	m_hBmp = NULL;
	m_eImgType = IO_UNKNOW;
	memset(m_szFileName, 0, MAX_PATH);
}

// 
// �֐��� : ~CImageObject
// �T  �v : �f�X�g���N�^
// ��  �� : �Ȃ�
// �߂�l : �Ȃ�
// ��  �l : �Ȃ�
//
CImageObject::~CImageObject(){
	if(m_hBmp){
		::DeleteObject(m_hBmp);
	}
}

// 
// �֐��� : LoadImage
// �T  �v : �C���[�W�����[�h����
// ��  �� : pszFileName ���[�h����t�@�C����
// �߂�l : ����ɓǂݍ��߂��ꍇ��TRUE
// ��  �l : �Ȃ�
//
BOOL CImageObject::LoadImage(char *pszFileName){
	strcpy(m_szFileName, pszFileName);

	FILE *file = fopen(m_szFileName, "a+");
	if(file == NULL){
		return FALSE;
	}
	return TRUE;
}

// 
// �֐��� : SaveImage
// �T  �v : �C���[�W��ۑ�����
// ��  �� : pszFileName �ۑ�����t�@�C����
// �߂�l : ����ɕۑ������ꍇ��TRUE
// ��  �l : �Ȃ�
//
BOOL CImageObject::SaveImage(char *pszFileName){
	strcpy(m_szFileName, pszFileName);

	return TRUE;
}

// 
// �֐��� : GetBitmapHandle
// �T  �v : �r�b�g�}�b�v�n���h���̎擾
// ��  �� : �Ȃ�
// �߂�l : �r�b�g�}�b�v�n���h��
// ��  �l : �Ȃ�
//
HBITMAP CImageObject::GetBitmapHandle(){
	return m_hBmp;
}

// 
// �֐��� : GetType
// �T  �v : �C���[�W�̃^�C�v
// ��  �� : �Ȃ�
// �߂�l : �^�C�v
// ��  �l : �Ȃ�
//
int CImageObject::GetType(){
	return m_eImgType;
}

// 
// �֐��� : SearchImageType
// �T  �v : �C���[�W�̃^�C�v�𔻒肷��
// ��  �� : �Ȃ�
// �߂�l : �Ȃ�
// ��  �l : �Ȃ�
//
void CImageObject::SearchImageType(){
	m_eImgType = IO_UNKNOW;

	//��͂��܂�
}

// 
// �֐��� : DrawImage
// �T  �v : �C���[�W��`��
// ��  �� : hDC �f�o�C�X�R���e�L�X�g�̃n���h��
//          x   �o�͍��W
//          y   �o�͍��W
// �߂�l : ����ɏ��������ꍇTRUE
// ��  �l : �Ȃ�
//
BOOL CImageObject::DrawImage(HDC hDC, int x, int y){
	DWORD dwRet = ::GetDeviceCaps(hDC, RASTERCAPS);
	if(dwRet & RC_BITBLT){
		//BitBlt�ŕ`��
	}else if(dwRet & RC_DIBTODEV){
		//SetDIBitsToDevice�ŕ`��
	}else if(dwRet & RC_DI_BITMAP){
		//SetDIBits�ŕ`��
	}else if(dwRet & RC_STRETCHBLT){
		//StretchBlt�ŕ`��
	}else if(dwRet & RC_STRETCHDIB){
		//StretchDIBits�ŕ`��
	}
	return TRUE;
}

// 
// �֐��� : DrawStretchImage
// �T  �v : �C���[�W���w��T�C�Y�ŕ`��
// ��  �� : hDC �f�o�C�X�R���e�L�X�g�̃n���h��
//          x      �o�͍��W
//          y      �o�͍��W
//          width  �C���[�W�̕�
//          height �C���[�W�̍���
// �߂�l : ����ɏ��������ꍇTRUE
// ��  �l : �Ȃ�
//
BOOL CImageObject::DrawStretchImage(HDC hDC, int x, int y, int width, int height){
	DWORD dwRet = ::GetDeviceCaps(hDC, RASTERCAPS);
	if(dwRet & RC_STRETCHBLT){
		//StretchBlt�ŕ`��
	}else if(dwRet & RC_STRETCHDIB){
		//StretchDIBits�ŕ`��
	}else if(dwRet & RC_BITBLT){
		//BitBlt�ŕ`��
	}else if(dwRet & RC_DIBTODEV){
		//SetDIBitsToDevice�ŕ`��
	}else if(dwRet & RC_DI_BITMAP){
		//SetDIBits�ŕ`��
	}
	return TRUE;
}
