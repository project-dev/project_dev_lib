// devXML.h : DEVXML �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_DEVXML_H__73C61B02_B9A7_4931_B41B_B8FDA6294D52__INCLUDED_)
#define AFX_DEVXML_H__73C61B02_B9A7_4931_B41B_B8FDA6294D52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CDevXMLApp
// ���̃N���X�̓���̒�`�Ɋւ��Ă� devXML.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CDevXMLApp : public CWinApp
{
public:
	CDevXMLApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDevXMLApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDevXMLApp)
		// ���� -  ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//         ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DEVXML_H__73C61B02_B9A7_4931_B41B_B8FDA6294D52__INCLUDED_)
