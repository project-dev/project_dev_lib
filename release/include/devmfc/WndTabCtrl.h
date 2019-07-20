#if !defined(AFX_WNDTABCTRL_H__D4583C36_A019_4DE0_9C8F_CDF01B4EF8CB__INCLUDED_)
#define AFX_WNDTABCTRL_H__D4583C36_A019_4DE0_9C8F_CDF01B4EF8CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WndTabCtrl.h : �w�b�_�[ �t�@�C��
//
#include "TabCtrlEx.h"

/////////////////////////////////////////////////////////////////////////////
// CWndTabCtrl �E�B���h�E
#ifdef DEVMFC_EXPORTS
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_IMPORT
#endif

#define WM_HWNDTABCHANGE		WM_APP + 0x200

/**
 * �^�u�̃y�[�W��CWnd�ŊǗ�����N���X�B
 * �e�^�u�ɂ�1��CWnd���֘A�t���邱�Ƃ��ł���B
 * �y�[�W�؂�ւ��̍ۂɎ����Ă��Ƀy�[�W��؂�ւ���
 */
class DEV_EXT_MFCCLASS CWndTabCtrl : public CTabCtrlEx{
// �R���X�g���N�V����
public:
	CWndTabCtrl();

// �A�g���r���[�g
public:
	void SetPagePosition();
	void GetPageRect(LPRECT rect);
	
// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CWndTabCtrl)
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CWndTabCtrl();
	BOOL AddNewPage(int nItem, LPCTSTR pszText, CWnd *pWnd);
	virtual void SetActivePage(int nIndex);
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CWndTabCtrl)
	afx_msg void OnMove(int x, int y);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg BOOL OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult );

	DECLARE_MESSAGE_MAP()
private:
	CString m_strHintText;
	int m_nOldPage;
	int m_nNowPage;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_WNDTABCTRL_H__D4583C36_A019_4DE0_9C8F_CDF01B4EF8CB__INCLUDED_)
