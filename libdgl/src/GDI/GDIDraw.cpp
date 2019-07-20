// DGIDraw.cpp: CDGIDraw クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "GDIDraw.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CGDIDraw::CGDIDraw()
{

}

CGDIDraw::~CGDIDraw()
{

}
bool CGDIDraw::Create(CDGLMain *pMain){
	CDGLDrawBase::Create(pMain);
	CDGLResource *pResource = pMain->GetResource();
	HWND hWnd = pResource->m_hWnd;
	HDC hDC = GetDC(hWnd);
	m_objBackDC = CreateCompatibleDC(hDC);
	m_objBackBuff = CreateCompatibleBitmap(m_objBackDC, pResource->m_nWidth, pResource->m_nHeight);

	HBRUSH hBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);
	RECT rect;
	memset(&rect, 0, sizeof(RECT));
	GetClientRect(hWnd, &rect);
	FillRect(m_objBackDC, &rect, hBrush);
	ReleaseDC(hWnd, hDC);
	
	char szMsg[1024];
	memset(szMsg, 0, 1024);
	sprintf(szMsg, "\nleft = %d top = %d right = %d bottom = %d\n", rect.left, rect.top, rect.right, rect.bottom);
	OutputDebugString(szMsg);

	return true;
}

bool CGDIDraw::Draw(int x, int y, int cx, int cy, long lParam){
	return true;
}

bool CGDIDraw::DrawText(LPCTSTR pszText, int nLen, int x, int y){
	return true;
}

bool CGDIDraw::StretchDraw(int x, int y, int cx, int cy, long lParam){
	return true;
}

bool CGDIDraw::DrawDisp(int x, int y, int cx, int cy, long lParam){
	CDGLMain *pMain = GetDGLMain();
	if(!pMain){
		OutputDebugString("pMain is null\n");
		return false;
	}
	CDGLResource *pResource = pMain->GetResource();

	HWND hWnd = pResource->m_hWnd;
	HDC hDC = GetDC(hWnd);
	RECT rect;
	GetClientRect(hWnd, &rect);
	BitBlt(hDC, 0, 0, rect.right - rect.left, rect.bottom - rect.top,
		   m_objBackDC, 0, 0, SRCCOPY);
	OutputDebugString("DrawDisp\n");
	return true;
}
