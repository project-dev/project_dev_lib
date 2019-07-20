// DGLResource.h: CDGLResource クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DGLRESOURCE_H__2D7D2588_1482_4571_9A4C_17572CD7D0FA__INCLUDED_)
#define AFX_DGLRESOURCE_H__2D7D2588_1482_4571_9A4C_17572CD7D0FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DGLResItem.h"
#include <windows.h>

#ifdef LIBDGL_EXPORTS
	#define DGL_EXT_CLASS		 __declspec(dllexport)
#else
	#define DGL_EXT_CLASS		 __declspec(dllimport)
#endif

class DGL_EXT_CLASS CDGLResource{
public:
	CDGLResource();
	virtual ~CDGLResource();
	bool AddResource(CDGLResItem *pItem);

	//基本パラメータ
	int m_nTop;
	int m_nLeft;
	int m_nHeight;
	int m_nWidth;

	long m_nInterval;
	long m_TimeId;

	HICON m_hIcon;
	HINSTANCE m_hInst;
	HWND m_hWnd;

	//サウンド用

	//グラフィック用
private:

};

#endif // !defined(AFX_DGLRESOURCE_H__2D7D2588_1482_4571_9A4C_17572CD7D0FA__INCLUDED_)
