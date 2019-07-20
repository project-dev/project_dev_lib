// devjava.cpp : DLL アプリケーション用のエントリ ポイントを定義します。
//

#include "stdafx.h"
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
		CLogFile::SaveDevLibLog("DLL_PROCESS_ATTACH - devjava.dll DLL Main");
		break;
	case DLL_THREAD_ATTACH:
		CLogFile::SaveDevLibLog("DLL_THREAD_ATTACH  - devjava.dll DLL Main");
		break;
	case DLL_THREAD_DETACH:
		CLogFile::SaveDevLibLog("DLL_THREAD_DETACH  - devjava.dll DLL Main");
		break;
	case DLL_PROCESS_DETACH:
		CLogFile::SaveDevLibLog("DLL_PROCESS_DETACH - devjava.dll DLL Main");
		break;
	}
//	_CrtSetBreakAlloc(54);
//	_CrtSetBreakAlloc(53);
   return TRUE;
}

