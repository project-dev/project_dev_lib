#if !defined(_DEVIMGFUNC_)
#define _DEVIMGFUNC_

#include <windows.h>

#ifdef DEVGRAPG_EXPORTS
	#define DEV_EXT_CLASS		 __declspec(dllexport)
#else
	#define DEV_EXT_CLASS		 __declspec(dllimport)
#endif
#ifdef __cplusplus
extern "C" {
#endif

	DEV_EXT_CLASS BOOL WINAPI Strong(HDC hOutDC, HDC hTargDC, int nWidth, int nHeight, int nLevel);
	DEV_EXT_CLASS BOOL WINAPI DummyColor(HDC hOutDC, HDC hTargDC, int nWidth, int nHeight, int nType);
	DEV_EXT_CLASS int WINAPI GetLuminance(COLORREF crTarget);
	DEV_EXT_CLASS BOOL WINAPI Grayscale(HDC hOutDC, HDC hTargDC, int nWidth, int nHeight);
	DEV_EXT_CLASS BOOL WINAPI Binalize(HDC hOutDC, HDC hTargDC, int nWidth, int nHeight, int nLevel);
	DEV_EXT_CLASS BOOL WINAPI Diff(HDC hOutDC, HDC hDC1, HDC hDC2, int nWidth, int nHeight);
	DEV_EXT_CLASS BOOL WINAPI ConvColorBitImg(HDC hFromDC, HBITMAP hFromBmp, HDC hToDC, HBITMAP hToBmp, int nToCrBit);
	DEV_EXT_CLASS BOOL WINAPI TextOutWhiteEdge(HDC hDC, int nX, int nY, LPCTSTR pszText);
#endif

#if __cplusplus
}
#endif
