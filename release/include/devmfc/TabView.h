#if !defined(AFX_TABVIEW_H__2A453483_0A1A_4C14_AB3E_CB507E2E900C__INCLUDED_)
#define AFX_TABVIEW_H__2A453483_0A1A_4C14_AB3E_CB507E2E900C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BaseTabView.h : �w�b�_�[ �t�@�C��
//

#include "HwndTabCtrl.h"



#ifdef DEVMFC_EXPORTS
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_IMPORT
#endif

/**
 * CHwndTabCtrl�������o�Ƃ��Ď��r���[�B
 */
class DEV_EXT_MFCCLASS CTabView : public CView{
protected:
	CTabView();           // ���I�����Ɏg�p�����v���e�N�g �R���X�g���N�^
	DECLARE_DYNCREATE(CTabView)

// �A�g���r���[�g
public:

// �I�y���[�V����
public:
	CHwndTabCtrl& GetTabCtrl();
	int CreatePage(int nIndex, LPCTSTR strTitle, HWND hWNd);
	virtual void OnSelChangeFunc(NMHDR* pNMHDR, LRESULT* pResult);
// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CTabView)
	protected:
	virtual void OnDraw(CDC* pDC);      // ���̃r���[��`�悷�邽�߂ɃI�[�o�[���C�h���܂����B
	//afx_msg void OnSelchange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSelchange(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	virtual ~CTabView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CTabView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CHwndTabCtrl m_objTabCtrl;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_BASETABVIEW_H__2A453483_0A1A_4C14_AB3E_CB507E2E900C__INCLUDED_)
