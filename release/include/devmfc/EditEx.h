#if !defined(AFX_EDITEX_H__BA012C00_5E40_492F_999A_87EEB7D778FB__INCLUDED_)
#define AFX_EDITEX_H__BA012C00_5E40_492F_999A_87EEB7D778FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SQLEdit.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CEditEx �E�B���h�E
#ifdef DEVMFC_EXPORTS
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_EXPORT
#else
	#define DEV_EXT_MFCCLASS		 AFX_CLASS_IMPORT
#endif

/**
 * �g�����ꂽCEdit�N���X�ł�<BR>
 * �s�ԍ���\�����邱�Ƃ��\�ł��B
 */
class DEV_EXT_MFCCLASS CEditEx : public CEdit{
// �R���X�g���N�V����
public:
	CEditEx();

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CEditEx)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	void InvalidateTextArea();
	void SetFont( CFont* pFont, BOOL bRedraw = TRUE );
	void SetLineShow(BOOL bShow = TRUE);
	virtual ~CEditEx();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CEditEx)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnChange();
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVscroll();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	BOOL m_bModify;

private:
	int m_nOldIndex;
	int m_nOldScPos;
	int m_nRetCnt;
	BOOL CreateBackBuffer();
	void DrawLineNo();
	void SetMarginFromLine();

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

#endif // !defined(AFX_EDITEX_H__BA012C00_5E40_492F_999A_87EEB7D778FB__INCLUDED_)
