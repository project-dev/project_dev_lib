// devlibsample.h : DEVLIBSAMPLE �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_DEVLIBSAMPLE_H__D9CF2AC6_C6BA_4983_94FF_542061A20D5F__INCLUDED_)
#define AFX_DEVLIBSAMPLE_H__D9CF2AC6_C6BA_4983_94FF_542061A20D5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CLibSampApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� devlibsample.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CLibSampApp : public CWinApp
{
public:
	CLibSampApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CLibSampApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CLibSampApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DEVLIBSAMPLE_H__D9CF2AC6_C6BA_4983_94FF_542061A20D5F__INCLUDED_)
