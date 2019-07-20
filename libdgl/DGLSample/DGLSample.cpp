// DGLSample.cpp : �A�v���P�[�V�����p�̃G���g�� �|�C���g�̒�`
//

#include "stdafx.h"
#include "DevWindow.h"
#include "GDIMain.h"
#include "DGLResource.h"
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow ){

	//DGL�̃��C���I�u�W�F�N�g
	CGDIMain dglMain;
	CDGLResource objRes;
	objRes.m_nInterval = 1000;

	if(!dglMain.Create(&objRes)){
		return -1;
	}
	
//  �K�v�ɉ����ăA�C�R�������[�h
//	objRes.m_hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_DGLSAMPLE);

	//�E�B���h�E����
	CDevWindow devWin(0, NULL, "DGL_TEST_CLASS", "�e�X�g", 320, 240, (CDGLMain*)&dglMain);

	//���C�����[�v�̎��s
	return devWin.WndMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}



