// devlib.cpp : DLL �A�v���P�[�V�����p�̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include "devlib.h"
#include "DebugSupport.h"
#include <crtdbg.h>
#include "LogFile.h"
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 ){
#ifdef _DEBUG
	CLogFile::SetLogState(TRUE);
	CLogFile::SetDevLibLogState(TRUE);
#else
	CLogFile::SetDevLibLogState(FALSE);
#endif
	switch(ul_reason_for_call){
	case DLL_PROCESS_ATTACH:
		CLogFile::SaveDevLibLog("DLL_PROCESS_ATTACH - devlib.dll DLL Main");
		break;
	case DLL_THREAD_ATTACH:
		CLogFile::SaveDevLibLog("DLL_THREAD_ATTACH  - devlib.dll DLL Main");
		break;
	case DLL_THREAD_DETACH:
		CLogFile::SaveDevLibLog("DLL_THREAD_DETACH  - devlib.dll DLL Main");
		break;
	case DLL_PROCESS_DETACH:
		CLogFile::SaveDevLibLog("DLL_PROCESS_DETACH - devlib.dll DLL Main");
		break;
	}
//	_CrtSetBreakAlloc(54);
//	_CrtSetBreakAlloc(53);
  return TRUE;
}

/**
 * @brief ��������N���b�v�{�[�h�ɓ]������
 *
 * @param hWnd �E�B���h�E�n���h��
 * @param pszText �N���b�v�{�[�h�ɓ]�����镶����
 * @param nLen ������̒���
 * @return ���������ꍇ�� true��Ԃ�
 */
BOOL WINAPI SetTextToClipBoard(HWND hWnd, LPCTSTR pszText, int nLen){
	HGLOBAL hMem;
	LPTSTR lpMem;

	//�������I�u�W�F�N�g�m��
	hMem = GlobalAlloc(GHND, nLen);
	if(!hMem){
		::MessageBox(hWnd, "�R�s�[�Ɏ��s���܂���", "�G���[", MB_OK);
		return FALSE;
	}
	
	//�������I�u�W�F�N�g�����b�N���ăA�h���X���擾 
	lpMem = (LPTSTR)GlobalLock(hMem);
	if(!hMem){
		if(!::GlobalFree(hMem)){
			::MessageBox(hWnd, "�R�s�[�Ɏ��s���܂���", "�G���[", MB_OK);
		}else{
			::MessageBox(hWnd, "�R�s�[�Ɏ��s���܂���", "�G���[", MB_OK);
		}
		return FALSE;
	}

	//�������I�u�W�F�N�g�ɕ�������������� 
	lstrcpy(lpMem, pszText);

	//�N���b�v�{�[�h�փR�s�[
	if(!::OpenClipboard(hWnd)){
		::MessageBox(hWnd, "�N���b�v�{�[�h�̃I�[�v���Ɏ��s���܂���", "�G���[", MB_OK);
		return FALSE;
	}

	if(!::EmptyClipboard()){
		::MessageBox(hWnd, "�N���b�v�{�[�h�̃I�[�v���Ɏ��s���܂���", "�G���[", MB_OK);
		if(!::CloseClipboard()){
			::MessageBox(hWnd, "�N���b�v�{�[�h�̃N���[�Y�Ɏ��s���܂����B", "�G���[", MB_OK);
		}
		return FALSE;
	}

	// �N���b�v�{�[�h�Ƀ������I�u�W�F�N�g�̕�������R�s�[
	HANDLE hRes = ::SetClipboardData(CF_TEXT, hMem);
	if(!hRes){
		::MessageBox(hWnd, "�R�s�[�Ɏ��s���܂���", "�G���[", MB_OK);
		if(!::CloseClipboard()){
			::MessageBox(hWnd, "�N���b�v�{�[�h�̃N���[�Y�Ɏ��s���܂����B", "�G���[", MB_OK);
		}
		return FALSE;
	}

	//�N���b�v�{�[�h�����
	if(!::CloseClipboard()){
		::MessageBox(hWnd, "�N���b�v�{�[�h�̃N���[�Y�Ɏ��s���܂����B", "�G���[", MB_OK);
		return FALSE;
	}
	return TRUE;

}

/**
 * @brief ���b�Z�[�W�{�b�N�X�̕\��(�C���t�H���[�V�����p)
 *
 * @param hWnd �E�B���h�E�n���h��
 * @param pszText �\�����b�Z�[�W
 * @param lpCaption ���b�Z�[�W�{�b�N�X�̃^�C�g��
 * @param uType �{�^���̃^�C�v
 */
int WINAPI MsgBoxInfo(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType){
	
	uType &= ~MB_ICONEXCLAMATION | MB_ICONINFORMATION | MB_ICONQUESTION | MB_ICONSTOP;
	uType |= MB_ICONINFORMATION;
	
	int nLen = strlen(lpText);
	char *pszMsg = new char[nLen + 10];
	strcpy(pszMsg, "INF : ");
	strcat(pszMsg, lpText);
	CDebugSupport::OutputDebugLog(pszMsg);
	delete pszMsg;

	return ::MessageBox(hWnd, lpText, lpCaption, uType);
}

/**
 * @brief ���b�Z�[�W�{�b�N�X�̕\��(�x���p)
  *
* @param hWnd �E�B���h�E�n���h��
 * @param pszText �\�����b�Z�[�W
 * @param lpCaption ���b�Z�[�W�{�b�N�X�̃^�C�g��
 * @param uType �{�^���̃^�C�v
 */
int WINAPI MsgBoxWarning(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType){
	uType &= ~MB_ICONEXCLAMATION | MB_ICONINFORMATION | MB_ICONQUESTION | MB_ICONSTOP;
	uType |= MB_ICONEXCLAMATION;
	
	int nLen = strlen(lpText);
	char *pszMsg = new char[nLen + 10];
	strcpy(pszMsg, "WAR : ");
	strcat(pszMsg, lpText);
	CDebugSupport::OutputDebugLog(pszMsg);
	delete pszMsg;

	return ::MessageBox(hWnd, lpText, lpCaption, uType);
}

/**
 *���b�Z�[�W�{�b�N�X�̕\��(�m�F�p)
 *
 * @param hWnd �E�B���h�E�n���h��
 * @param pszText �\�����b�Z�[�W
 * @param lpCaption ���b�Z�[�W�{�b�N�X�̃^�C�g��
 * @param uType �{�^���̃^�C�v
 */
int WINAPI MsgBoxQuestion(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType){
	uType &= ~MB_ICONEXCLAMATION | MB_ICONINFORMATION | MB_ICONQUESTION | MB_ICONSTOP;
	uType |= MB_ICONQUESTION;
	return ::MessageBox(hWnd, lpText, lpCaption, uType);
}

/**
 * @brief ���b�Z�[�W�{�b�N�X�̕\��(�G���[�p)
 *
 * @param hWnd �E�B���h�E�n���h��
 * @param pszText �\�����b�Z�[�W
 * @param lpCaption ���b�Z�[�W�{�b�N�X�̃^�C�g��
 * @param uType �{�^���̃^�C�v
 */
int WINAPI MsgBoxErr(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType){
	uType &= ~MB_ICONEXCLAMATION | MB_ICONINFORMATION | MB_ICONQUESTION | MB_ICONSTOP;
	uType |= MB_ICONSTOP;

	int nLen = strlen(lpText);
	char *pszMsg = new char[nLen + 10];
	strcpy(pszMsg, "ERR : ");
	strcat(pszMsg, lpText);
	CDebugSupport::OutputDebugLog(pszMsg);
	delete pszMsg;
	
	return ::MessageBox(hWnd, lpText, lpCaption, uType);
}
