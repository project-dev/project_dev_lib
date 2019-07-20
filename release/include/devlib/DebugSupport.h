#if !defined(__DEVLIB_DEBUGSUPPORT__)
#define __DEVLIB_DEBUGSUPPORT__
#include <windows.h>

#ifdef DEVLIB_EXPORTS
	#define DEV_EXT_CLASS		 __declspec(dllexport)
#else
	#define DEV_EXT_CLASS		 __declspec(dllimport)
#endif

/**
 * @brief デバッグサポートクラス
 *
 * デバッグをサポートする為のクラスです。<BR>
 * 
 * @author Project D.E.V
 */

class DEV_EXT_CLASS CDebugSupport {
public:
	static void Except(LPEXCEPTION_POINTERS pExp);
	CDebugSupport();
	virtual ~CDebugSupport();
	static char* WINAPI GetLastErrorText(DWORD dwID);
	static void WINAPI OutputSystemInfo();
	static void WINAPI GetModuleVersionInfo(HMODULE hMod, char *pszOutBuff);
	static void WINAPI OutputModuleVer(HMODULE hMod);
	static void WINAPI OutputDebugLog(char *pszMsg);
	static void WINAPI OutputGetLastErrorMsg(DWORD dwID);
	static bool WINAPI GetDebugMode();
	static bool WINAPI StartDebugMode(char *pszLogFIlePath);
	static void WINAPI EndDebugMode();
};

#endif // !defined(__DEVLIB_DEBUGSUPPORT__)
