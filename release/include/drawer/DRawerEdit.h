#if !defined(AFX_DRAWEREDIT_H__583EE923_3F06_461A_ACEE_D66BFBD2D144__INCLUDED_)
#define AFX_DRAWEREDIT_H__583EE923_3F06_461A_ACEE_D66BFBD2D144__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DRawerEdit.h : �w�b�_�[ �t�@�C��
//
#include "DrawerCoreDef.h"


/////////////////////////////////////////////////////////////////////////////
// CDRawerEdit �E�B���h�E
class DRAWER_EXT_CLASS CDRawerEdit : public CEdit{
// �R���X�g���N�V����
public:
	CDRawerEdit();

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDRawerEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CDRawerEdit();

	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID );


	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CDRawerEdit)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG


	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DRAWEREDIT_H__583EE923_3F06_461A_ACEE_D66BFBD2D144__INCLUDED_)
