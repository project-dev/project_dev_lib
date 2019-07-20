#if !defined(AFX_PROGRESSSTATUSBAR_H__92ABD1E4_E425_4F61_8573_5CDE7A223AF1__INCLUDED_)
#define AFX_PROGRESSSTATUSBAR_H__92ABD1E4_E425_4F61_8573_5CDE7A223AF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgressStatusBar.h : �w�b�_�[ �t�@�C��
//


/////////////////////////////////////////////////////////////////////////////
// CProgressStatusBar �E�B���h�E
#ifdef DEVMFC_EXPORTS
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_IMPORT
#endif

/**
 * �X�e�[�^�X�o�[�̔C�ӂ̈ʒu�Ƀv���O���X�o�[��\���ł���X�e�[�^�X�o�[
 */
class DEV_EXT_MFCCLASS CProgressStatusBar : public CStatusBar{

	// �R���X�g���N�V����
public:
	CProgressStatusBar();

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CProgressStatusBar)
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	int StepIt( );
	int SetStep( int nStep );
	int OffsetPos( int nPos );
	int SetPos( int nPos );
	int GetPos( );
	void GetRange( int& nLower, int& nUpper );
	void SetRange( short nLower, short nUpper );
	void SetRange32( int nLower, int nUpper );
	UINT ShowProgressBar(int nIndex);
	CProgressCtrl* GetProgressBar();
	virtual ~CProgressStatusBar();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CProgressStatusBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	CProgressCtrl m_objProgress;
	int m_nIndex;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_PROGRESSSTATUSBAR_H__92ABD1E4_E425_4F61_8573_5CDE7A223AF1__INCLUDED_)
