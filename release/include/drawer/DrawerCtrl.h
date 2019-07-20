// Drawer1.h: CDrawer �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWERCTRL_H__799EF0A9_ACB0_47C8_860C_9376282E0B96__INCLUDED_)
#define AFX_DRAWERCTRL_H__799EF0A9_ACB0_47C8_860C_9376282E0B96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define USE_SCROLLBAR_OBJ

#include <AfxTempl.h>
#include "DRawerEdit.h"
#include "DrawInfo.h"
#include "DrawerCoreDef.h"
#include "DrawerConfig.h"

class DRAWER_EXT_CLASS CDrawerCtrl : public CWnd{
public:
	BOOL IsShowGrid();
	void ShowGrid(BOOL bShow);
	void SelectAll(BOOL bSel);
	void Paste();
	BOOL UnDo();
	BOOL CutItem(CDrawInfo *pItem = NULL);
	BOOL CopyItem(CDrawInfo *pInfo = NULL);
	void ClearCopyBuff();
	int IsSelected();
	void CalcScrollRange();
	BOOL SetSize(int nWidth, int nHeight);
	BOOL LoadItemData(LPCTSTR pszFilename);
	BOOL SaveItemData(LPCTSTR pszFileName, LPCTSTR pszVersion);
	CDrawerCtrl();
	DECLARE_DYNCREATE(CDrawerCtrl)

//	PDRAWINFO GetTextEditInfo();
	CDrawInfo* GetTextEditInfo();

	virtual ~CDrawerCtrl();
#if defined(USE_SCROLLBAR_OBJ)
	virtual CScrollBar* GetScrollBarCtrl( int nBar ) const;
#endif

	BOOL DeleteItem(CDrawInfo* pItem = NULL, BOOL bSelOnly = TRUE );
	BOOL EditText(CDrawInfo* pInfo);
	void MakeGridBmp();
	BOOL GetUsePosGrid();
	void SetUsePosGrid(BOOL bUse);
	int GetGridSize();
	BOOL SetGridSize(int nSize);
	void SetText(CDrawInfo* pInfo, LPCTSTR pszText);
	eDrawType GetDrawType();
	void SetEditMode(eEditMode eMode);
	eEditMode GetEditMode();
	const CDrawInfo* GetDrawInfo(int x, int y, BOOL bHeightLight = FALSE);
	void SetBkColor(COLORREF crBack);
	BOOL Create(CWnd *pParent, int nWidth, int nHeight, COLORREF crBack = RGB(0xFF, 0xFF, 0xFF));
	void SetDrawType(eDrawType eDraw);
	BOOL DrawImage(CDC *pDc, int dx, int dy, int sx, int sy, int nWidth, int nHeight);
	const CDrawInfo* DrawStart(COLORREF crDraw, int x, int y);
	void DrawMove(CDrawInfo* pInfo, int x, int y);
	void DrawEnd(CDrawInfo* pInfo, int x, int y);

	BOOL SaveBitmap(LPCTSTR pszSaveFile);
	BOOL SaveJpeg(LPCTSTR pszSaveFile);
	BOOL SavePng(LPCTSTR pszSaveFile);
	BOOL SaveGif(LPCTSTR pszSaveFile);
	BOOL SaveImage(LPCTSTR pszSaveFile, LPCTSTR pszType); 
// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(CDrawerCtrl)
	public:
	//}}AFX_VIRTUAL

//�萔
	static const char* imgBMP;						// @brif SaveImage()�֐��Ŏg�p�Bimage/bmp
	static const char* imgGIF;						// @brif SaveImage()�֐��Ŏg�p�Bimage/gif
	static const char* imgJPG;						// @brif SaveImage()�֐��Ŏg�p�Bimage/jpeg
	static const char* imgPNG;						// @brif SaveImage()�֐��Ŏg�p�Bimage/png

protected:
	BOOL CreateImage(int cx, int cy, BOOL bNew = TRUE);

	CDrawerConfig					m_objCfg;
	CString							m_strName;		// @brif ���O
	static int						m_nClCnt;		// @brif �N����
	static BOOL						m_bComInit;		// @brif COM���������s��ꂽ���ǂ���

	CDC								*m_pBackDC;		// @brif �o�b�N�o�b�t�@
	CBitmap							*m_pBackBmp;	// @brif �o�b�N�o�b�t�@

	CDC								*m_pGridDC;		// @brif �O���b�h�p�o�b�t�@
	CBitmap							*m_pGridBmp;	// @brif �O���b�h�p�o�b�t�@

	int								m_nWidth;		// @brif ��
	int								m_nHeight;		// @brif ����
	COLORREF						m_crBack;		// @brif �w�i�F

	CWnd*							m_pParentWnd;	// @brif �e�E�B���h�E
	CDRawerEdit						m_objEdit;		// @brif �G�f�B�b�g�R���g���[��
	int								m_nOldCurX;		// @brif �O��̃J�[�\���ʒu
	int								m_nOldCurY;		// @brif �O��̃J�[�\���ʒu

	GdiplusStartupInput				m_gdiSI;		// @brif GDI+
	ULONG_PTR						m_gdiToken;		// @brif GDI+�p

	BOOL							m_bSelect;		// @brif �I�𒆂��ǂ���
	CRect							m_objSelRect;	// @brif �I����`

	eEditMode						m_eMode;		// @brif �ҏW���[�h
	eDrawType						m_eDrawType;	// @brif �`����

	CArray<CDrawInfo*, CDrawInfo*>	m_arrDrawinfo;	// @brif �A�C�e�����X�g
	CArray<CDrawInfo*, CDrawInfo*>	m_arrCopyinfo;	// @brif �A�C�e�����X�g
	CDrawInfo*						m_pActive;		// @brif ���݂̃A�C�e��
	CDrawInfo*						m_pHeightRight;	// @brif �n�C���C�g
	CDrawInfo*						m_pTxtInfo;		// @brif 

	CArray<CDrawInfo*, CDrawInfo*>	m_arrUndo;		// @brif UnDo�o�b�t�@

	CRect							m_selRect;		// @brif �͈͑I��pRECT
#if defined(USE_SCROLLBAR_OBJ)
	CScrollBar						m_objVScrBar;	// @brif �����X�N���[���o�[
	CScrollBar						m_objHScrBar;	// @brif �����X�N���[���o�[
#endif
	int m_nPasteShiftV;
	int m_nPasteShiftH;
	//{{AFX_MSG(CDrawerCtrl)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnDrCopy();
	afx_msg void OnDrDelete();
	afx_msg void OnInpText();
	afx_msg void OnProperty();
	afx_msg void OnUpdateDrCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrDelete(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInpText(CCmdUI* pCmdUI);
	afx_msg void OnUpdateProperty(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void SetJudgeRect(CDrawInfo* pInfo);

};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DRAWERCTRL_H__799EF0A9_ACB0_47C8_860C_9376282E0B96__INCLUDED_)
