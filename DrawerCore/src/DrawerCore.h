// DrawerCore.h : DRAWERCORE �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_DRAWERCORE_H__822E1639_256A_469D_A820_97E85BA36E13__INCLUDED_)
#define AFX_DRAWERCORE_H__822E1639_256A_469D_A820_97E85BA36E13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CDrawerCoreApp
// ���̃N���X�̓���̒�`�Ɋւ��Ă� DrawerCore.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CDrawerCoreApp : public CWinApp
{
public:
	CDrawerCoreApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDrawerCoreApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDrawerCoreApp)
		// ���� -  ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//         ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DRAWERCORE_H__822E1639_256A_469D_A820_97E85BA36E13__INCLUDED_)
