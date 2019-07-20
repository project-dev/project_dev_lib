// DevWindow.h: CDevWindow クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVWINDOW_H__50136FC6_897F_4B80_A827_E4406B74E949__INCLUDED_)
#define AFX_DEVWINDOW_H__50136FC6_897F_4B80_A827_E4406B74E949__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DGLMain.h"
#include <windows.h>

#ifdef LIBDGL_EXPORTS
	#define DGL_EXT_CLASS		 __declspec(dllexport)
#else
	#define DGL_EXT_CLASS		 __declspec(dllimport)
#endif

/*
 ウィンドウの生成などの処理をカプセル化したクラスです。
 このクラスの使い方は下記のように利用します

	#include "DevWindow.h"
	#include "DGLMain.h"
	#include "DGLResource.h"
	int APIENTRY WinMain(HINSTANCE hInstance,
						 HINSTANCE hPrevInstance,
						 LPSTR     lpCmdLine,
						 int       nCmdShow ){

		//DGLのメインオブジェクト
		CDGLMain dglMain;

		//DGLリソースオブジェクト
		CDGLResource objRes;

		if(!dglMain.Create(&objRes)){
			return -1;
		}
		
		//ウィンドウ生成
		CDevWindow devWin(0, NULL, "DGL_TEST_CLASS", "テスト", 320, 240, &dglMain);
	
	//アイコンがある場合は以下を参照
	//	objRes.m_hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_DGLSAMPLE);
	//	CDevWindow devWin(0, m_hIcon, "DGL_TEST_CLASS", "テスト", 320, 240, &dglMain);

		//メインループの実行
		return devWin.WndMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	}

 */

class DGL_EXT_CLASS CDevWindow{
public:
	CDevWindow(long style,
			  HICON hIcon, 
			  char *pszClassName,
			  char *pszTitle,
			  int winWidth,
			  int winHeight,
			  CDGLMain *pMain);
	virtual ~CDevWindow();

	//static
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static void CALLBACK TimerProc(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);

	int WndMain(HINSTANCE hInstance, HINSTANCE hPreInst,LPSTR lpszCmdLine, int nCmdShow);
	LRESULT DefWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	virtual void OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam);
	virtual void OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam);
private:
	BOOL m_bFirst;
	CDevWindow	*m_pWnd;
	void SequenceProc();
	WNDCLASS m_objWndClass;
	char szTitle[256];
	char szClassName[256];
	int m_nWidth;
	int m_nHeight;
	CDGLMain *m_pDGLMain;
};

#endif // !defined(AFX_DEVWINDOW_H__50136FC6_897F_4B80_A827_E4406B74E949__INCLUDED_)
