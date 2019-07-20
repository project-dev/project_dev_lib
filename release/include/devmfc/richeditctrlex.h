#if !defined(AFX_RICHEDITCTRLEX_H__B974C3F6_3BA3_4BE0_A74B_77E259C5C06A__INCLUDED_)
#define AFX_RICHEDITCTRLEX_H__B974C3F6_3BA3_4BE0_A74B_77E259C5C06A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// richeditctrlex.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CRichEditCtrlEx �E�B���h�E
#ifdef DEVMFC_EXPORTS
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_IMPORT
#endif

/**
 * �g�����ꂽCRichEditCtrl�N���X�ł�<BR>
 * �s�ԍ���\�����邱�Ƃ��\�ł��B
 */
class DEV_EXT_MFCCLASS CRichEditCtrlEx : public CRichEditCtrl{
// �R���X�g���N�V����
public:
	CRichEditCtrlEx();
// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CRichEditCtrlEx)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	void SetFont( CFont* pFont, BOOL bRedraw = TRUE );
	void SetLineShow(BOOL bShow = TRUE);
	void CharFromPos(int &nLine, int &nPos);
	virtual ~CRichEditCtrlEx();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CRichEditCtrlEx)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnChange();
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVscroll();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel( UINT nFlags, short zDelta, CPoint pt );
	afx_msg BOOL OnEraseBkgnd( CDC* pDC );
	afx_msg void OnSetfocus();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
//	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
	afx_msg void OnActivateApp(BOOL bActive, DWORD hTask);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	BOOL m_bModify;

private:
	void DrawLineNo();
	BOOL CreateBackBuffer();
	void SetMarginFromLine();

	int m_nOldIndex;

	BOOL m_bLineShow;
	CRect m_oldRect;

	CDC* m_pBackDC;
	CBitmap* m_pBackBmp;
	CBitmap* m_pOldBmp;

	int m_nLeftMargin;
	LOGFONT m_lFont;
	CFont  m_objFont;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_RICHEDITCTRLEX_H__B974C3F6_3BA3_4BE0_A74B_77E259C5C06A__INCLUDED_)
