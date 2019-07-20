#if !defined(AFX_TABCTRLEX_H__C4415EAF_E588_4C13_A435_F552E1937C9D__INCLUDED_)
#define AFX_TABCTRLEX_H__C4415EAF_E588_4C13_A435_F552E1937C9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabCtrlEx.h : �w�b�_�[ �t�@�C��
//
#include <afxole.h>

#ifdef DEVMFC_EXPORTS
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_IMPORT
#endif

//#define USE_DROPTARGET

class CTabCtrlEx;

class DEV_EXT_MFCCLASS CTabDropTarget : public COleDropTarget{
public:
	BOOL StartDrop(CTabCtrlEx* pWnd);
	CTabDropTarget();
	BOOL Register( CTabCtrlEx* pWnd );
	virtual ~CTabDropTarget();
	virtual DROPEFFECT OnDragEnter( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point );
	virtual void OnDragLeave( CWnd* pWnd );
	virtual DROPEFFECT OnDragOver( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point );

	DWORD m_dwHoverInterval;
private:
	POINT m_oldPos;
};


class DEV_EXT_MFCCLASS CTabCtrlEx : public CTabCtrl{
// �R���X�g���N�V����
public:
	CTabCtrlEx();
	void GetTabRect(int nIndex, CRect &retRect);
	BOOL SetIsHoverTab(BOOL isHover, DWORD dwHoverInterval = -1);
	void GetPageRect(LPRECT rect);
	static BOOL CALLBACK FindProc(HWND hwnd, LPARAM lParam);
	virtual void SetActivePage(int nIndex);
#ifdef USE_DROPTARGET
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
#endif
// �A�g���r���[�g
public:

private:
	BOOL m_bIsHoverTab;
	CString m_strHintText;
	CBrush m_objGrayBrush;
#ifdef USE_DROPTARGET
	CTabDropTarget m_objDropTarget;
#endif

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CTabCtrlEx)
	virtual int OnToolHitTest( CPoint point, TOOLINFO* pTI ) const;
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CTabCtrlEx();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CTabCtrlEx)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg BOOL OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult );
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_TABCTRLEX_H__C4415EAF_E588_4C13_A435_F552E1937C9D__INCLUDED_)
