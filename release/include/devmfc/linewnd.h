#if !defined(AFX_LINEWND_H__1B86DF79_3FE1_4779_8E6E_C703F9D5BB8B__INCLUDED_)
#define AFX_LINEWND_H__1B86DF79_3FE1_4779_8E6E_C703F9D5BB8B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LineWnd.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CLineWnd �E�B���h�E
#ifdef DEVMFC_EXPORTS
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_IMPORT
#endif

class DEV_EXT_MFCCLASS CLineWnd : public CWnd
{
// �R���X�g���N�V����
public:
	CLineWnd();

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CLineWnd)
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	void CreateBuffer();
	CDC m_objBackDC;
	CBitmap m_objBackBmp;
	void SetMarginFromLine(CEdit *pEdit);
	void DrawLineNo(CEdit *pEdit);
	virtual ~CLineWnd();

	int m_nLeftMargin;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CLineWnd)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_nOldIndex;
	CRect m_oldRect;
	CBitmap* m_pOldBmp;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_LINEWND_H__1B86DF79_3FE1_4779_8E6E_C703F9D5BB8B__INCLUDED_)
