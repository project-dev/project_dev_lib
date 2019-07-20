#if !defined(AFX_TREECTRLEX_H__2C429E07_2F97_4EEE_970B_655693D5C662__INCLUDED_)
#define AFX_TREECTRLEX_H__2C429E07_2F97_4EEE_970B_655693D5C662__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TreeCtrlEx.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlEx �E�B���h�E
#ifdef DEVMFC_EXPORTS
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_IMPORT
#endif
class DEV_EXT_MFCCLASS CTreeCtrlEx : public CTreeCtrl{
// �R���X�g���N�V����
public:
	CTreeCtrlEx();
	void CancelSearch();

// �A�g���r���[�g
public:

// �I�y���[�V����
public:
	virtual void ChangeIncrementBuffer(CString strBuff);
// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CTreeCtrlEx)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	void SetIncrementalSearch(BOOL bUse);
	virtual ~CTreeCtrlEx();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CTreeCtrlEx)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	HTREEITEM FindTreeText(LPCTSTR pszText, HTREEITEM hItem);
	CString m_strKeyBuff;
	BOOL m_bIncSearch;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_TREECTRLEX_H__2C429E07_2F97_4EEE_970B_655693D5C662__INCLUDED_)
