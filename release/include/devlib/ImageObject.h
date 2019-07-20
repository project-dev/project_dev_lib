// ImageObject.h: CImageObject クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(__DEVLIB_IMAGEOBJECT__)
#define __DEVLIB_IMAGEOBJECT__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#ifdef DEVLIB_EXPORTS
	#define DEV_EXT_CLASS		 __declspec(dllexport)
#else
	#define DEV_EXT_CLASS		 __declspec(dllimport)
#endif

/**
 * @brief GetDeviceCapsの値をみて適切な描画方法で描画する(未完成)
 * @deprecated このクラスは未完成なので利用しないで下さい
 */
class DEV_EXT_CLASS CImageObject {
public:
	BOOL DrawStretchImage(HDC hDC, int x, int y, int width, int height);
	BOOL DrawImage(HDC hDC, int x, int y);
	int GetType();
	HBITMAP GetBitmapHandle();
	BOOL SaveImage(char *pszFileName);
	BOOL LoadImage(char *pszFileName);
	CImageObject();
	virtual ~CImageObject();
	typedef enum eType{
		IO_UNKNOW	= -1,
		IO_BMP		= 0,
		IO_JPG,
		IO_PNG,
		IO_GIF
	};
private:
	void SearchImageType();
	HBITMAP m_hBmp;
	HDC		m_hDC;
	eType	m_eImgType;
	char	m_szFileName[MAX_PATH];
	BITMAPINFO	*m_pBmpInfo;
};

#endif // !defined(__DEVLIB_IMAGEOBJECT__)
