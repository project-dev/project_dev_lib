#if !defined(AFX_DRAWERPROPDLG_H__4F4F4020_2528_4098_BA4C_26552454317C__INCLUDED_)
#define AFX_DRAWERPROPDLG_H__4F4F4020_2528_4098_BA4C_26552454317C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DrawerPropDlg.h : �w�b�_�[ �t�@�C��
//
#include "TabCtrlEx.h"

/////////////////////////////////////////////////////////////////////////////
// CDrawerPropDlg �_�C�A���O
class CDrawerCtrl;

class CDrawerPropDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CDrawerPropDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
	CDrawerCtrl *m_pCtrl;
// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDrawerPropDlg)
	enum { IDD = IDD_PROP_DLG };
	CTabCtrlEx	m_objTab;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDrawerPropDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL


// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDrawerPropDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DRAWERPROPDLG_H__4F4F4020_2528_4098_BA4C_26552454317C__INCLUDED_)
