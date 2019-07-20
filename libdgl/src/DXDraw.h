// DXDraw.h: CDXDraw クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DXDRAW_H__9C3EEC45_D1DD_473A_98C3_F772027AC412__INCLUDED_)
#define AFX_DXDRAW_H__9C3EEC45_D1DD_473A_98C3_F772027AC412__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\INCLUDE\DGLDrawBase.h"

#if defined(D3D_SDK_VERSION)
	#include <d3d8.h>
#endif

class CDXDraw : public CDGLDrawBase  
{
public:
	CDXDraw();
	virtual ~CDXDraw();

	virtual bool Draw(int x, int y, int cx, int cy, long lParam = NULL);
	virtual bool DrawText(LPCTSTR pszText, int nLen, int x, int y);
	virtual bool StretchDraw(int x, int y, int cx, int cy, long lParam = NULL);
	virtual bool DrawDisp(int x, int y, int cx, int cy, long lParam = NULL);
private:
#if defined(D3D_SDK_VERSION)
	IDirect3D8* m_pDXObject;
#endif
};

#endif // !defined(AFX_DXDRAW_H__9C3EEC45_D1DD_473A_98C3_F772027AC412__INCLUDED_)
