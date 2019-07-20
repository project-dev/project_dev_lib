#if !defined(AFX_HWNDTABCTRL_H__79D6A8D2_9F45_42C2_83CA_65D6007BA8A0__INCLUDED_)
#define AFX_HWNDTABCTRL_H__79D6A8D2_9F45_42C2_83CA_65D6007BA8A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustTabCtrl.h : �w�b�_�[ �t�@�C��
//

#include "TabCtrlEx.h"

#ifdef DEVMFC_EXPORTS
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_IMPORT
#endif

#define WM_HWNDTABCHANGE		WM_APP + 0x200

/**
 * �^�u�̃y�[�W��HWNDde�ŊǗ�����N���X�B
 * �e�^�u�ɂ�1��HWND���֘A�t���邱�Ƃ��ł���B
 * �y�[�W�؂�ւ��̍ۂɎ����Ă��Ƀy�[�W��؂�ւ���
 */
class DEV_EXT_MFCCLASS CHwndTabCtrl : public CTabCtrlEx{
// �R���X�g���N�V����
public:
	CHwndTabCtrl();

// �A�g���r���[�g
public:

// �I�y���[�V����
public:
	void SetPagePosition();
// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CHwndTabCtrl)
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	BOOL AddNewPage(int nItem, LPCTSTR pszText, HWND hWnd);
	virtual void SetActivePage(int nIndex);
	virtual ~CHwndTabCtrl();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CHwndTabCtrl)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	int m_nOldPage;
	int m_nNowPage;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_CUSTTABCTRL_H__79D6A8D2_9F45_42C2_83CA_65D6007BA8A0__INCLUDED_)
