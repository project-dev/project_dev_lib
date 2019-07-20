// DevImgTool.h: CDevImgTool クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVIMGTOOL_H__ACA45D04_CF96_4857_B189_84AC2D019686__INCLUDED_)
#define AFX_DEVIMGTOOL_H__ACA45D04_CF96_4857_B189_84AC2D019686__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifdef DEVGRAPG_EXPORTS
	#define DEV_EXT_CLASS		 __declspec(dllexport)
#else
	#define DEV_EXT_CLASS		 __declspec(dllimport)
#endif
class DEV_EXT_CLASS CDevImgTool{
public:
	CDevImgTool();
	virtual ~CDevImgTool();


};

#endif // !defined(AFX_DEVIMGTOOL_H__ACA45D04_CF96_4857_B189_84AC2D019686__INCLUDED_)
