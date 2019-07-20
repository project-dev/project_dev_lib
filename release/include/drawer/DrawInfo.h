// DrawInfo.h: CDrawInfo �N���X�̃C���^�[�t�F�C�X
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

	eDrawType	eType;					// @bnrif �`����
	CRect		judgeRect;				// @bnrif �I��p
	COLORREF	crBack;					// @bnrif �w�i�F
	COLORREF	crEdge;					// @bnrif ���E��
	COLORREF	cfFront;				// @bnrif �O�i�F
	int			nRectCnt;				// @bnrif 
	int			nLinkCnt;				// @bnrif 
	HTEXT_ALIGN	hAlign;					// @bnrif 
	VTEXT_ALIGN	vAlign;					// @bnrif 

protected:
	CArray< CRect*, CRect*> m_arrRect;	// @bnrif 
	CArray< LPVOID, LPVOID> m_arrLinks; // @bnrif �����N���
	LOGFONT		m_lFont;				// @bnrif �t�H���g
	BOOL		m_bSel;					// @bnrif �I������Ă��邩�H
	BOOL		m_bDrawing;				// @bnrif �`�撆���ǂ����H
	BOOL		m_bPaint;				// @bnrif �h��Ԃ��t���O
	CString		m_strText;
	CString		m_strName;
};

#endif // !defined(AFX_DRAWINFO_H__27DA2766_EFB2_4097_9C87_E372BC9FEAB2__INCLUDED_)
