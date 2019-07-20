// GDIMain.h: CGDIMain クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GDIMAIN_H__0E21604F_AD36_4E88_94D3_4B09E41304C1__INCLUDED_)
#define AFX_GDIMAIN_H__0E21604F_AD36_4E88_94D3_4B09E41304C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DGLMain.h"
#include "GDIDraw.h"

#ifdef LIBDGL_EXPORTS
	#define DGL_EXT_CLASS		 __declspec(dllexport)
#else
	#define DGL_EXT_CLASS		 __declspec(dllimport)
#endif

class DGL_EXT_CLASS CGDIMain : public CDGLMain{
public:
	CGDIMain();
	virtual ~CGDIMain();
	virtual void OnPaint();
	bool Initalize();

private:
	CGDIDraw m_objBackBuff;

};

#endif // !defined(AFX_GDIMAIN_H__0E21604F_AD36_4E88_94D3_4B09E41304C1__INCLUDED_)
