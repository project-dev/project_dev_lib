// DevWindow.cpp: CDevWindow クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "DevWindow.h"

CDevWindow *pWnd;

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CDevWindow::CDevWindow(long style,
			  HICON hIcon, 
			  char *pszClassName,
			  char *pszTitle,
			  int winWidth,
			  int winHeight,
			  CDGLMain *pMain){
	m_pDGLMain = pMain;
	if(!m_pDGLMain){
		return;
	}
	CDGLResource *pResource = m_pDGLMain->GetResource();

	strcpy(szClassName, pszClassName);
	strcpy(szTitle, pszTitle);
	pResource->m_nWidth = winWidth;
	pResource->m_nHeight = winHeight;

	m_objWndClass.style			= CS_HREDRAW | CS_VREDRAW | style;
	m_objWndClass.lpfnWndProc	= CDevWindow::WndProc;
	m_objWndClass.cbClsExtra	= 0;
	m_objWndClass.cbWndExtra	= 0;
	m_objWndClass.hIcon			= hIcon;
	m_objWndClass.hCursor		= LoadCursor(NULL,IDC_ARROW);
	m_objWndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	m_objWndClass.lpszMenuName	= NULL;
	m_objWndClass.lpszClassName	= szClassName;

	m_bFirst = TRUE;
}

CDevWindow::~CDevWindow(){

}

LRESULT CDevWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
	if(pWnd != NULL){
		return pWnd->DefWndProc(hWnd, msg, wParam, lParam);
	}else{
		switch (msg) {
			case WM_CREATE:
				break;

			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			default:
				return(DefWindowProc(hWnd, msg, wParam, lParam));
		}
	}
	return 0;
}

int CDevWindow::WndMain(HINSTANCE hInstance, HINSTANCE hPreInst,LPSTR lpszCmdLine, int nCmdShow){
	
	if(!m_pDGLMain){
		return -1;
	}
	CDGLResource *pResource = m_pDGLMain->GetResource();


	HWND hWnd;
	MSG msg;
	if (!hPreInst){
		m_objWndClass.hInstance = hInstance;
		if (!RegisterClass(&m_objWndClass)){
			return FALSE;
		}
	}
	pWnd = this;

	//-------------------------------------------------------------------------
	//ウィンドウ生成
	//	HWND CreateWindow(
	//		LPCTSTR lpClassName,	// 登録されているクラス名
	//		LPCTSTR lpWindowName,	// ウィンドウ名
	//		DWORD dwStyle,			// ウィンドウスタイル
	//		int x,					// ウィンドウの横方向の位置
	//		int y,					// ウィンドウの縦方向の位置
	//		int nWidth,				// ウィンドウの幅
	//		int nHeight,			// ウィンドウの高さ
	//		HWND hWndParent,		// 親ウィンドウまたはオーナーウィンドウのハンドル
	//		HMENU hMenu,			// メニューハンドルまたは子ウィンドウ ID
	//		HINSTANCE hInstance,	// アプリケーションインスタンスのハンドル
	//		LPVOID lpParam			// ウィンドウ作成データ
	//		);
	//-------------------------------------------------------------------------
	hWnd = CreateWindow(szClassName, szTitle,
						WS_CAPTION | WS_OVERLAPPED | WS_SYSMENU | WS_BORDER,
						CW_USEDEFAULT, CW_USEDEFAULT,
						pResource->m_nWidth, pResource->m_nHeight,
						NULL,
						NULL,
						hInstance,
						NULL
						);

	pResource->m_hWnd = hWnd;
	pResource->m_hInst = hInstance;

	MoveWindow(hWnd, 
			   pResource->m_nLeft, pResource->m_nTop, 
			   pResource->m_nWidth, pResource->m_nHeight, TRUE);
	UpdateWindow(hWnd);
	ShowWindow(hWnd, nCmdShow);

	RECT scRect;
    GetClientRect( hWnd, &scRect );
    ClientToScreen( hWnd, (POINT*)&scRect.left );
    ClientToScreen( hWnd, (POINT*)&scRect.right );
    pResource->m_nWidth  = scRect.right - scRect.left;
    pResource->m_nHeight = scRect.bottom - scRect.top;

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (msg.wParam);
}

LRESULT CDevWindow::DefWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
	CDGLResource *pResource = m_pDGLMain->GetResource();
	switch (msg) {

	//WM_CREATE
	case WM_CREATE:
		//生成用ハンドラ関数呼び出し
		OnCreate(hWnd, wParam, lParam);

		break;

	//WM_DESTROY
	case WM_DESTROY:
		//タイマー解除
		if(pResource->m_TimeId != NULL){
			timeKillEvent(pResource->m_TimeId);
			timeEndPeriod(1);
		}else{
			KillTimer(hWnd, 0);
		}

		//破棄用ハンドラ関数呼び出し
		OnDestroy(hWnd, wParam, lParam);
		PostQuitMessage(0);
		break;

	//WM_MOUSEMOVE
	case WM_MOUSEMOVE:
		//マウスの現在地を取得する
		//y = HIWORD(lParam);
		//x = LOWORD(lParam);
		break;

	//WM_TIMER
	case WM_TIMER:
		if(pResource->m_TimeId == NULL){
			//DGLのメインルーチンを呼び出す。
			//ここで呼び出されると、各シーン、ページのMain()関数も呼び出される。
			//SequenceProc();
		}
		break;

	//WMN_ACTIVATE
	case WM_ACTIVATE:
		break;

	case WM_SHOWWINDOW:
		{
			OutputDebugString("WM_SHOWWINDOW\n");
			bool bShow = (bool)wParam;
			if(m_bFirst && bShow){
				m_bFirst = FALSE;
				if(!m_pDGLMain->Initalize()){
					MessageBox(pResource->m_hWnd, "CDGLMain Initalize Error.", "Error", MB_OK);
					return 0;
				}

				//タイマー割り込み発生までウィンドウが白くなってしまうので先に一度呼び出しておく。
				SequenceProc();

				//タイマー設定
				timeBeginPeriod(1);	//分解能の最小値
				pResource->m_TimeId = timeSetEvent(pResource->m_nInterval,		// タイマー間隔[ms]
												   1,							// 時間分解能
												   CDevWindow::TimerProc,		//コールバック関数
												   0,							//ユーザー定義の値
												   TIME_PERIODIC				//単発(TIME_ONESHOT) or 繰り返し(TIME_PERIODIC)
												   );
				if(pResource->m_TimeId == NULL){
					//通常のタイマを利用する
					SetTimer(hWnd, 0, pResource->m_nInterval, NULL);
				}else{
					OutputDebugString("Multimedia Timer Start.\n");
				}
			}
		}		
		break;
	case WM_PAINT:
		OutputDebugString("WM_PAINT\n");
		m_pDGLMain->OnPaint();
		break;

	case WM_ERASEBKGND:
		//背景の消去を行なわない
//		return(DefWindowProc(hWnd, msg, wParam, lParam));
		break;
	//その他
	default:
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return 0;

}

//---------------------------------------------------------------------------
//  概要・説明
//    マルチメディアタイマー用コールバック関数
//
//  パラメタ説明
//    無し
//
//  戻り値
//    無し
//
//---------------------------------------------------------------------------
void CALLBACK CDevWindow::TimerProc(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2){
	pWnd->SequenceProc();
}

//---------------------------------------------------------------------------
//  概要・説明
//    制御関数
//
//  パラメタ説明
//    無し
//
//  戻り値
//    無し
//
//---------------------------------------------------------------------------
void CDevWindow::SequenceProc(){
	CDGLResource *pResource = m_pDGLMain->GetResource();
	if(m_pDGLMain != NULL){
		m_pDGLMain->Main();
		m_pDGLMain->OnPaint();
	}
}

void CDevWindow::OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam){
	OutputDebugString("OnCreate()\n");
}

void CDevWindow::OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam){
	OutputDebugString("OnDestroy()\n");
}
