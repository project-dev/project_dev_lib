// Drawer1.h: CDrawer クラスのインターフェイス
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
// オーバーライド
	//{{AFX_VIRTUAL(CDrawerCtrl)
	public:
	//}}AFX_VIRTUAL

//定数
	static const char* imgBMP;						// @brif SaveImage()関数で使用。image/bmp
	static const char* imgGIF;						// @brif SaveImage()関数で使用。image/gif
	static const char* imgJPG;						// @brif SaveImage()関数で使用。image/jpeg
	static const char* imgPNG;						// @brif SaveImage()関数で使用。image/png

protected:
	BOOL CreateImage(int cx, int cy, BOOL bNew = TRUE);

	CDrawerConfig					m_objCfg;
	CString							m_strName;		// @brif 名前
	static int						m_nClCnt;		// @brif 起動数
	static BOOL						m_bComInit;		// @brif COM初期化が行われたかどうか

	CDC								*m_pBackDC;		// @brif バックバッファ
	CBitmap							*m_pBackBmp;	// @brif バックバッファ

	CDC								*m_pGridDC;		// @brif グリッド用バッファ
	CBitmap							*m_pGridBmp;	// @brif グリッド用バッファ

	int								m_nWidth;		// @brif 幅
	int								m_nHeight;		// @brif 高さ
	COLORREF						m_crBack;		// @brif 背景色

	CWnd*							m_pParentWnd;	// @brif 親ウィンドウ
	CDRawerEdit						m_objEdit;		// @brif エディットコントロール
	int								m_nOldCurX;		// @brif 前回のカーソル位置
	int								m_nOldCurY;		// @brif 前回のカーソル位置

	GdiplusStartupInput				m_gdiSI;		// @brif GDI+
	ULONG_PTR						m_gdiToken;		// @brif GDI+用

	BOOL							m_bSelect;		// @brif 選択中かどうか
	CRect							m_objSelRect;	// @brif 選択矩形

	eEditMode						m_eMode;		// @brif 編集モード
	eDrawType						m_eDrawType;	// @brif 描画種別

	CArray<CDrawInfo*, CDrawInfo*>	m_arrDrawinfo;	// @brif アイテムリスト
	CArray<CDrawInfo*, CDrawInfo*>	m_arrCopyinfo;	// @brif アイテムリスト
	CDrawInfo*						m_pActive;		// @brif 現在のアイテム
	CDrawInfo*						m_pHeightRight;	// @brif ハイライト
	CDrawInfo*						m_pTxtInfo;		// @brif 

	CArray<CDrawInfo*, CDrawInfo*>	m_arrUndo;		// @brif UnDoバッファ

	CRect							m_selRect;		// @brif 範囲選択用RECT
#if defined(USE_SCROLLBAR_OBJ)
	CScrollBar						m_objVScrBar;	// @brif 垂直スクロールバー
	CScrollBar						m_objHScrBar;	// @brif 水平スクロールバー
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
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DRAWERCTRL_H__799EF0A9_ACB0_47C8_860C_9376282E0B96__INCLUDED_)
