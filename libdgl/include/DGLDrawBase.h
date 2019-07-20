// DGLDrawBase.h: CDGLDrawBase クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DGLDRAWBASE_H__B85FDAE2_C01C_4BDF_A8AA_E1B404EFCEAF__INCLUDED_)
#define AFX_DGLDRAWBASE_H__B85FDAE2_C01C_4BDF_A8AA_E1B404EFCEAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DGLObject.h"

#ifdef LIBDGL_EXPORTS
	#define DGL_EXT_CLASS		 __declspec(dllexport)
#else
	#define DGL_EXT_CLASS		 __declspec(dllimport)
#endif
//#include <gdiplus.h>
class DGL_EXT_CLASS CDGLDrawBase : public CDGLObject{
public:
	CDGLDrawBase();
	virtual ~CDGLDrawBase();

	//抽象メソッド
	virtual bool Draw(int x, int y, int cx, int cy, long lParam = NULL) = 0;
	virtual bool DrawText(LPCTSTR pszText, int nLen, int x, int y) = 0;
	virtual bool StretchDraw(int x, int y, int cx, int cy, long lParam = NULL) = 0;
	virtual bool DrawDisp(int x, int y, int cx, int cy, long lParam = NULL) = 0;
};

#endif // !defined(AFX_DGLDRAWBASE_H__B85FDAE2_C01C_4BDF_A8AA_E1B404EFCEAF__INCLUDED_)
