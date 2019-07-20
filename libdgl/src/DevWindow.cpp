// DevWindow.cpp: CDevWindow �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "DevWindow.h"

CDevWindow *pWnd;

//////////////////////////////////////////////////////////////////////
// �\�z/����
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
	//�E�B���h�E����
	//	HWND CreateWindow(
	//		LPCTSTR lpClassName,	// �o�^����Ă���N���X��
	//		LPCTSTR lpWindowName,	// �E�B���h�E��
	//		DWORD dwStyle,			// �E�B���h�E�X�^�C��
	//		int x,					// �E�B���h�E�̉������̈ʒu
	//		int y,					// �E�B���h�E�̏c�����̈ʒu
	//		int nWidth,				// �E�B���h�E�̕�
	//		int nHeight,			// �E�B���h�E�̍���
	//		HWND hWndParent,		// �e�E�B���h�E�܂��̓I�[�i�[�E�B���h�E�̃n���h��
	//		HMENU hMenu,			// ���j���[�n���h���܂��͎q�E�B���h�E ID
	//		HINSTANCE hInstance,	// �A�v���P�[�V�����C���X�^���X�̃n���h��
	//		LPVOID lpParam			// �E�B���h�E�쐬�f�[�^
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
		//�����p�n���h���֐��Ăяo��
		OnCreate(hWnd, wParam, lParam);

		break;

	//WM_DESTROY
	case WM_DESTROY:
		//�^�C�}�[����
		if(pResource->m_TimeId != NULL){
			timeKillEvent(pResource->m_TimeId);
			timeEndPeriod(1);
		}else{
			KillTimer(hWnd, 0);
		}

		//�j���p�n���h���֐��Ăяo��
		OnDestroy(hWnd, wParam, lParam);
		PostQuitMessage(0);
		break;

	//WM_MOUSEMOVE
	case WM_MOUSEMOVE:
		//�}�E�X�̌��ݒn���擾����
		//y = HIWORD(lParam);
		//x = LOWORD(lParam);
		break;

	//WM_TIMER
	case WM_TIMER:
		if(pResource->m_TimeId == NULL){
			//DGL�̃��C�����[�`�����Ăяo���B
			//�����ŌĂяo�����ƁA�e�V�[���A�y�[�W��Main()�֐����Ăяo�����B
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

				//�^�C�}�[���荞�ݔ����܂ŃE�B���h�E�������Ȃ��Ă��܂��̂Ő�Ɉ�x�Ăяo���Ă����B
				SequenceProc();

				//�^�C�}�[�ݒ�
				timeBeginPeriod(1);	//����\�̍ŏ��l
				pResource->m_TimeId = timeSetEvent(pResource->m_nInterval,		// �^�C�}�[�Ԋu[ms]
												   1,							// ���ԕ���\
												   CDevWindow::TimerProc,		//�R�[���o�b�N�֐�
												   0,							//���[�U�[��`�̒l
												   TIME_PERIODIC				//�P��(TIME_ONESHOT) or �J��Ԃ�(TIME_PERIODIC)
												   );
				if(pResource->m_TimeId == NULL){
					//�ʏ�̃^�C�}�𗘗p����
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
		//�w�i�̏������s�Ȃ�Ȃ�
//		return(DefWindowProc(hWnd, msg, wParam, lParam));
		break;
	//���̑�
	default:
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return 0;

}

//---------------------------------------------------------------------------
//  �T�v�E����
//    �}���`���f�B�A�^�C�}�[�p�R�[���o�b�N�֐�
//
//  �p�����^����
//    ����
//
//  �߂�l
//    ����
//
//---------------------------------------------------------------------------
void CALLBACK CDevWindow::TimerProc(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2){
	pWnd->SequenceProc();
}

//---------------------------------------------------------------------------
//  �T�v�E����
//    ����֐�
//
//  �p�����^����
//    ����
//
//  �߂�l
//    ����
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
