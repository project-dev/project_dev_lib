#if !defined(AFX_LISTCTRLEX_H__2162378B_9793_4194_A299_183F4C6F9E39__INCLUDED_)
#define AFX_LISTCTRLEX_H__2162378B_9793_4194_A299_183F4C6F9E39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListCtrlEx.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx �E�B���h�E
#ifdef DEVMFC_EXPORTS
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_IMPORT
#endif

/**
 *�g�����ꂽCListCtrl�N���X<BR>
 */
class DEV_EXT_MFCCLASS CListCtrlEx : public CListCtrl{
// �R���X�g���N�V����
public:
	CListCtrlEx();

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CListCtrlEx)
	public:
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	void SetAllColumnWidth();
	BOOL Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID );


	virtual ~CListCtrlEx();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CListCtrlEx)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_LISTCTRLEX_H__2162378B_9793_4194_A299_183F4C6F9E39__INCLUDED_)
