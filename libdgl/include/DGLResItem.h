// DGLResItem.h: CDGLResItem クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DGLRESITEM_H__EB04BC8E_9428_4FFA_96F9_30DDABC43000__INCLUDED_)
#define AFX_DGLRESITEM_H__EB04BC8E_9428_4FFA_96F9_30DDABC43000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef LIBDGL_EXPORTS
	#define DGL_EXT_CLASS		 __declspec(dllexport)
#else
	#define DGL_EXT_CLASS		 __declspec(dllimport)
#endif

typedef enum eResType{
	RES_UNKNOW = -1,
	RES_BITMAP = 0,
	RES_WAVE,
	RES_MIDI

};

class DGL_EXT_CLASS CDGLResItem{
public:
	bool LoadData(long lID);
	bool LoadData(char* pszFileName);
	CDGLResItem(eResType eType);
	virtual ~CDGLResItem();

private:
	eResType m_nType;

};

#endif // !defined(AFX_DGLRESITEM_H__EB04BC8E_9428_4FFA_96F9_30DDABC43000__INCLUDED_)
