// DGIDraw.h: CDGIDraw クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DGIDRAW_H__333C79F8_0F79_4DE8_924A_0AF7BC79835D__INCLUDED_)
#define AFX_DGIDRAW_H__333C79F8_0F79_4DE8_924A_0AF7BC79835D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DGLDrawBase.h"
#include <windows.h>



#ifdef LIBDGL_EXPORTS
	#define DGL_EXT_CLASS		 __declspec(dllexport)
#else
	#define DGL_EXT_CLASS		 __declspec(dllimport)
#endif
class DGL_EXT_CLASS CGDIDraw : public CDGLDrawBase {
public:
	CGDIDraw();
	virtual ~CGDIDraw();
	HBITMAP	m_objBackBuff;
	HDC		m_objBackDC;
	bool Create(CDGLMain *pMain);
	virtual bool Draw(int x, int y, int cx, int cy, long lParam = NULL);
	virtual bool DrawText(LPCTSTR pszText, int nLen, int x, int y);
	virtual bool StretchDraw(int x, int y, int cx, int cy, long lParam = NULL);
	virtual bool DrawDisp(int x, int y, int cx, int cy, long lParam = NULL);
};

#endif // !defined(AFX_DGIDRAW_H__333C79F8_0F79_4DE8_924A_0AF7BC79835D__INCLUDED_)
