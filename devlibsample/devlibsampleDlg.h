// devlibsampleDlg.h : �w�b�_�[ �t�@�C��
//

#if !defined(AFX_DEVLIBSAMPLEDLG_H__A665300C_6A57_4535_BE4F_DA6CBC8B2CC8__INCLUDED_)
#define AFX_DEVLIBSAMPLEDLG_H__A665300C_6A57_4535_BE4F_DA6CBC8B2CC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSampleDlg �_�C�A���O

class CSampleDlg : public CDialog
{
// �\�z
public:
	CSampleDlg(CWnd* pParent = NULL);	// �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CSampleDlg)
	enum { IDD = IDD_DEVLIBSAMPLE_DIALOG };
		// ����: ���̈ʒu�� ClassWizard �ɂ���ăf�[�^ �����o���ǉ�����܂��B
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	HICON m_hIcon;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CSampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnIniread();
	afx_msg void OnBtnIniwrite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DEVLIBSAMPLEDLG_H__A665300C_6A57_4535_BE4F_DA6CBC8B2CC8__INCLUDED_)
