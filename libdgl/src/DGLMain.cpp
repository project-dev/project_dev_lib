// DGLMain.cpp: CDGLMain クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "DGLMain.h"

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CDGLMain::CDGLMain(){

}

CDGLMain::~CDGLMain(){

}

CDGLResource* CDGLMain::GetResource(){
	return m_pDGLResource;
}

//制御
void CDGLMain::Main(){

}

bool CDGLMain::Create(CDGLResource *pDGLResource){
	if(!pDGLResource){
		return false;
	}
	m_pDGLResource = pDGLResource;
	return true;
}

void CDGLMain::OnPaint(){
	HWND hWnd = m_pDGLResource->m_hWnd;
	if(!hWnd){
		return;
	}
	HDC hDC = GetDC(hWnd);
	if(!hDC){
		return;
	}
	RECT rect;
	if(!GetClientRect(hWnd, &rect)){
		return;
	}
	
	HBRUSH hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
	if(!hBrush){
		return;
	}
	
	
	if(!FillRect(hDC, &rect, hBrush)){
		return;
	}

	SetTextColor(hDC, RGB(0x00, 0x00, 0x00));
	TextOut(hDC, 10, 10, 
			"Please override", 
			strlen("Please override"));
	TextOut(hDC, 10, 30, 
			"CDGLMain::OnPaint() function.", 
			strlen("CDGLMain::OnPaint() function."));
	ReleaseDC(hWnd, hDC);
}
