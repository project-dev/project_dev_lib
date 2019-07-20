// DrawInfo.h: CDrawInfo クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWINFO_H__27DA2766_EFB2_4097_9C87_E372BC9FEAB2__INCLUDED_)
#define AFX_DRAWINFO_H__27DA2766_EFB2_4097_9C87_E372BC9FEAB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "DrawerCoreDef.h"

class DRAWER_EXT_CLASS CDrawInfo  
{
public:
	CDrawInfo(LPCTSTR pszName = NULL);
	virtual ~CDrawInfo();

	BOOL Copy(CDrawInfo* pFrom);
	void GetXMLData(CString &strXML);
	void SetString(LPCTSTR pszStr);
	void SetString(CString strText);
	void GetString(CString &strText);
	void SetPaint(BOOL bPaint);
	BOOL IsPaint();
	void SetDrawing(BOOL bDrawing);
	BOOL IsDrawing();
	BOOL IsSelect();
	void Select(BOOL bSel);
	CRect* GetRect(int nIndex);

	eDrawType	eType;					// @bnrif 描画種別
	CRect		judgeRect;				// @bnrif 選択用
	COLORREF	crBack;					// @bnrif 背景色
	COLORREF	crEdge;					// @bnrif 境界線
	COLORREF	cfFront;				// @bnrif 前景色
	int			nRectCnt;				// @bnrif 
	int			nLinkCnt;				// @bnrif 
	HTEXT_ALIGN	hAlign;					// @bnrif 
	VTEXT_ALIGN	vAlign;					// @bnrif 

protected:
	CArray< CRect*, CRect*> m_arrRect;	// @bnrif 
	CArray< LPVOID, LPVOID> m_arrLinks; // @bnrif リンク情報
	LOGFONT		m_lFont;				// @bnrif フォント
	BOOL		m_bSel;					// @bnrif 選択されているか？
	BOOL		m_bDrawing;				// @bnrif 描画中かどうか？
	BOOL		m_bPaint;				// @bnrif 塗りつぶしフラグ
	CString		m_strText;
	CString		m_strName;
};

#endif // !defined(AFX_DRAWINFO_H__27DA2766_EFB2_4097_9C87_E372BC9FEAB2__INCLUDED_)
