// devmfc.h : DEVMFC �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_DEVMFC_H__BBF9495F_66ED_4463_9A94_4992B10E1C0D__INCLUDED_)
#define AFX_DEVMFC_H__BBF9495F_66ED_4463_9A94_4992B10E1C0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CDevmfcApp
// ���̃N���X�̓���̒�`�Ɋւ��Ă� devmfc.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CDevmfcApp : public CWinApp
{
public:
	CDevmfcApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDevmfcApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDevmfcApp)
		// ���� -  ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//         ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DEVMFC_H__BBF9495F_66ED_4463_9A94_4992B10E1C0D__INCLUDED_)
