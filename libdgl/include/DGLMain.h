// DGLMain.h: CDGLMain クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DGLMAIN_H__879D84D9_1D09_479E_869A_BFFCF3E415E4__INCLUDED_)
#define AFX_DGLMAIN_H__879D84D9_1D09_479E_869A_BFFCF3E415E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DGLResource.h"

#ifdef LIBDGL_EXPORTS
	#define DGL_EXT_CLASS		 __declspec(dllexport)
#else
	#define DGL_EXT_CLASS		 __declspec(dllimport)
#endif


class DGL_EXT_CLASS CDGLMain{
public:
	virtual void OnPaint();
	bool Create(CDGLResource *pDGLResource);
	void Main();
	CDGLResource* GetResource();
	CDGLMain();
	virtual ~CDGLMain();
	virtual bool Initalize() = 0;

private:	
	CDGLResource* m_pDGLResource;
};

#endif // !defined(AFX_DGLMAIN_H__879D84D9_1D09_479E_869A_BFFCF3E415E4__INCLUDED_)
