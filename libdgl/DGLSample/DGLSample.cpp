// DGLSample.cpp : アプリケーション用のエントリ ポイントの定義
//

#include "stdafx.h"
#include "DevWindow.h"
#include "GDIMain.h"
#include "DGLResource.h"
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow ){

	//DGLのメインオブジェクト
	CGDIMain dglMain;
	CDGLResource objRes;
	objRes.m_nInterval = 1000;

	if(!dglMain.Create(&objRes)){
		return -1;
	}
	
//  必要に応じてアイコンをロード
//	objRes.m_hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_DGLSAMPLE);

	//ウィンドウ生成
	CDevWindow devWin(0, NULL, "DGL_TEST_CLASS", "テスト", 320, 240, (CDGLMain*)&dglMain);

	//メインループの実行
	return devWin.WndMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}



