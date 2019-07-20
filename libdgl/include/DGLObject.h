// DGLObject.h: CDGLObject クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DGLOBJECT_H__F6DBE83E_B610_44FF_9D62_0938C47C1B26__INCLUDED_)
#define AFX_DGLOBJECT_H__F6DBE83E_B610_44FF_9D62_0938C47C1B26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DGLMain.h"

#ifdef LIBDGL_EXPORTS
	#define DGL_EXT_CLASS		 __declspec(dllexport)
#else
	#define DGL_EXT_CLASS		 __declspec(dllimport)
#endif

class DGL_EXT_CLASS CDGLObject{
public:
	bool Create(CDGLMain *pDGLMain);
	virtual bool Destroy();
	CDGLObject();
	virtual ~CDGLObject();

	CDGLMain* GetDGLMain();
private:
	CDGLMain *m_pDGLMain;
};

#endif // !defined(AFX_DGLOBJECT_H__F6DBE83E_B610_44FF_9D62_0938C47C1B26__INCLUDED_)
