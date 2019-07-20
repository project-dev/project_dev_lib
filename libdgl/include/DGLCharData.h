// DGLCharData.h: CDGLCharData クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DGLCHARDATA_H__ACD47649_6E52_4616_9770_414009319BF8__INCLUDED_)
#define AFX_DGLCHARDATA_H__ACD47649_6E52_4616_9770_414009319BF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DGLObject.h"

#ifdef LIBDGL_EXPORTS
	#define DGL_EXT_CLASS		 __declspec(dllexport)
#else
	#define DGL_EXT_CLASS		 __declspec(dllimport)
#endif

class DGL_EXT_CLASS CDGLCharData : public CDGLObject{
public:
	CDGLCharData();
	virtual ~CDGLCharData();
	virtual void Main() = 0;
private:
	
};

#endif // !defined(AFX_DGLCHARDATA_H__ACD47649_6E52_4616_9770_414009319BF8__INCLUDED_)
