// devgraph.h : DEVGRAPH �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_DEVGRAPH_H__E4CA409E_D2CD_4D0A_9DB4_7D4A9DFD9F37__INCLUDED_)
#define AFX_DEVGRAPH_H__E4CA409E_D2CD_4D0A_9DB4_7D4A9DFD9F37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CDevgraphApp
// ���̃N���X�̓���̒�`�Ɋւ��Ă� devgraph.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CDevgraphApp : public CWinApp
{
public:
	CDevgraphApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDevgraphApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDevgraphApp)
		// ���� -  ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//         ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DEVGRAPH_H__E4CA409E_D2CD_4D0A_9DB4_7D4A9DFD9F37__INCLUDED_)
