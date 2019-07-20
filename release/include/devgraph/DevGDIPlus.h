// DevGDIPlus.h: CDevGDIPlus クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVGDIPLUS_H__298B50CE_4F95_4D60_B7B8_49FC5999550F__INCLUDED_)
#define AFX_DEVGDIPLUS_H__298B50CE_4F95_4D60_B7B8_49FC5999550F__INCLUDED_

// GDI+を利用するために必要な宣言
#define ULONG_PTR DWORD 

#include "./gdiplus/gdiplus.h"
using namespace Gdiplus;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifdef DEVGRAPG_EXPORTS
	#define DEV_EXT_CLASS		 __declspec(dllexport)
#else
	#define DEV_EXT_CLASS		 __declspec(dllimport)
#endif
class DEV_EXT_CLASS CDevGDIPlus {
public:
	BOOL IsHaveImage();
	BOOL Close();
	CDevGDIPlus();
	virtual ~CDevGDIPlus();
	BOOL Create();

	BOOL SaveBitmap(HDC hDC, HBITMAP hBmp, LPCTSTR pszSaveFile);
	BOOL SaveJpeg(HDC hDC, HBITMAP hBmp, LPCTSTR pszSaveFile);
	BOOL SavePng(HDC hDC, HBITMAP hBmp, LPCTSTR pszSaveFile);
	BOOL SaveGif(HDC hDC, HBITMAP hBmp, LPCTSTR pszSaveFile);
	BOOL SaveTiff(HDC hDC, HBITMAP hBmp, LPCTSTR pszSaveFile);
	BOOL SaveImage(HDC hDC, HBITMAP hBmp, LPCTSTR pszSaveFile, LPCTSTR pszType); 
	BOOL LoadImage(LPCTSTR pszFile);
	CSize GetImageSize(LPCTSTR pszFilePath);
	CSize GetImageSize();
	BOOL DrawImage(HDC hDc);
	BOOL DrawImage(HDC hDc, int x, int y);
	BOOL DrawImage(HDC hDc, int x, int y, int cx, int cy);

//Static 変数	
	static const char* imgBMP;
	static const char* imgGIF;
	static const char* imgJPG;
	static const char* imgPNG;
	static const char* imgICON;
	static const char* imgTIFF;
	static const char* imgEMF;

private:
	int GetGDIErrorMsg(Status st, char* pszMsg, int nLen);
	BOOL UnInitalize();
	BOOL Initalize();
	GdiplusStartupInput				m_gdiSI;		// @brif GDI+
	ULONG_PTR						m_gdiToken;		// @brif GDI+用
	Image*							m_pImg;
	BOOL							m_bImgLoad;
};

#endif // !defined(AFX_DEVGDIPLUS_H__298B50CE_4F95_4D60_B7B8_49FC5999550F__INCLUDED_)
