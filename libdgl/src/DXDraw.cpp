// DXDraw.cpp: CDXDraw クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "DXDraw.h"

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CDXDraw::CDXDraw(){
#if defined(D3D_SDK_VERSION)
	m_pDXObject = Direct3DCreate8(D3D_SDK_VERSION);
#endif
}

CDXDraw::~CDXDraw()
{

}

bool CDXDraw::Draw(int x, int y, int cx, int cy, long lParam/* = NULL*/){
	return true;
}
bool CDXDraw::DrawText(LPCTSTR pszText, int nLen, int x, int y){
	return true;
}
bool CDXDraw::StretchDraw(int x, int y, int cx, int cy, long lParam/* = NULL*/){
	return true;
}
bool CDXDraw::DrawDisp(int x, int y, int cx, int cy, long lParam/* = NULL*/){
	return true;
}
