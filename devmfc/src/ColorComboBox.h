#if !defined(AFX_COLORCOMBOBOX_H__01BA5612_C1DA_45A6_9CA0_F0D3EB753A07__INCLUDED_)
#define AFX_COLORCOMBOBOX_H__01BA5612_C1DA_45A6_9CA0_F0D3EB753A07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorComboBox.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CColorComboBox �E�B���h�E

class CColorComboBox : public CComboBox{
// �R���X�g���N�V����
public:
	CColorComboBox();

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CColorComboBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParent, UINT uID);
	virtual ~CColorComboBox();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CColorComboBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_COLORCOMBOBOX_H__01BA5612_C1DA_45A6_9CA0_F0D3EB753A07__INCLUDED_)
