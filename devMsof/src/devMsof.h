// devMsof.h : DEVMSOF �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_DEVMSOF_H__81A6CAED_DA1D_4167_B3D6_3C87612C413C__INCLUDED_)
#define AFX_DEVMSOF_H__81A6CAED_DA1D_4167_B3D6_3C87612C413C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CDevMsofApp
// ���̃N���X�̓���̒�`�Ɋւ��Ă� devMsof.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CDevMsofApp : public CWinApp
{
public:
	CDevMsofApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDevMsofApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDevMsofApp)
		// ���� -  ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//         ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DEVMSOF_H__81A6CAED_DA1D_4167_B3D6_3C87612C413C__INCLUDED_)
