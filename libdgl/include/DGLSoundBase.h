// DGLSoundBase.h: CDGLSoundBase クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DGLSOUNDBASE_H__37638BC7_F75F_43AD_A937_0926E9795A4B__INCLUDED_)
#define AFX_DGLSOUNDBASE_H__37638BC7_F75F_43AD_A937_0926E9795A4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DGLObject.h"

#ifdef LIBDGL_EXPORTS
	#define DGL_EXT_CLASS		 __declspec(dllexport)
#else
	#define DGL_EXT_CLASS		 __declspec(dllimport)
#endif

class DGL_EXT_CLASS CDGLSoundBase : public CDGLObject{
public:
	CDGLSoundBase();
	virtual ~CDGLSoundBase();

	//抽象関数
	virtual bool Play(int nID) = 0;
	virtual bool Stop() = 0;


};

#endif // !defined(AFX_DGLSOUNDBASE_H__37638BC7_F75F_43AD_A937_0926E9795A4B__INCLUDED_)
