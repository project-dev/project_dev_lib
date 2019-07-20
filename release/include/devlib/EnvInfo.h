#if !defined(__DEVLIB_ENVINFO__)
#define __DEVLIB_ENVINFO__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "devstructs.h"
#include "devlib.h"

#ifdef DEVLIB_EXPORTS
	#define DEV_EXT_CLASS		 __declspec(dllexport)
#else
	#define DEV_EXT_CLASS		 __declspec(dllimport)
#endif

/**
 *@brief ������̏��������N���X
 *@author Project D.E.V
 */
class DEV_EXT_CLASS CEnvInfo{
public:
	CEnvInfo();
	virtual ~CEnvInfo();
	static int GetOSInfo(char *pszOSName, DWORD &dwBuild, char *pszCSD);
	static void GetProcesserInfo(char *pszVender, char *pszType, char *pszLevel, char *pszRevison);
	static void GetDeviceInfo(HWND hWnd, PDEVICEINFO pDevInfo);

	/**
	 * Windows�̃o�[�W������\���񋓌^
	 */
	typedef enum eWIN_VER{
		UNKNOW    = -1,	///UNKNOW
		WINNT3    = 0,	///Windows NT 3.x
		WIN95,			///Windows 95
		WIN98,			///Windows 98
		WINME,			///Windows Me
		WINNT4,			///Windows NT 4
		WIN2K,			///Windows 2000
		WINXP			///Windows XP�ȍ~
	};

};

#endif // !defined(__DEVLIB_ENVINFO__)
