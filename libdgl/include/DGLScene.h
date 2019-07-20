// DGLScene.h: CDGLScene クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DGLSCENE_H__E60A3C51_309C_444D_8C61_EE2FB18B5A6C__INCLUDED_)
#define AFX_DGLSCENE_H__E60A3C51_309C_444D_8C61_EE2FB18B5A6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DGLObject.h"
#include "DGLCharData.h"
#include <map>

#ifdef LIBDGL_EXPORTS
	#define DGL_EXT_CLASS		 __declspec(dllexport)
#else
	#define DGL_EXT_CLASS		 __declspec(dllimport)
#endif

class DGL_EXT_CLASS CDGLScene : public CDGLObject{
public:

	CDGLScene();
	virtual ~CDGLScene();

	bool AddCharData(CDGLCharData *pData);
	void SceneMain();

	CDGLResource *m_pSceneRes;		//シーンに閉じたリソースを扱う場合はこの変数を利用してください。

private:

};

#endif // !defined(AFX_DGLSCENE_H__E60A3C51_309C_444D_8C61_EE2FB18B5A6C__INCLUDED_)
