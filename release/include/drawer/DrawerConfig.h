// DrawerConfig.h: CDrawerConfig クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWERCONFIG_H__02E861CC_F9E0_4A65_AB50_7C1C3FBBEDB3__INCLUDED_)
#define AFX_DRAWERCONFIG_H__02E861CC_F9E0_4A65_AB50_7C1C3FBBEDB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DrawerCoreDef.h"

class DRAWER_EXT_CLASS CDrawerConfig{
public:
	void SetIniFileName(LPCTSTR pszFileName);
	BOOL Load(LPCTSTR pszFileName = NULL);
	BOOL Save(LPCTSTR pszFileName = NULL);
	CDrawerConfig();
	virtual ~CDrawerConfig();

	int m_nDefWidth;			// @brif デフォルトの描画エリアXサイズ
	int m_nDefHeight;			// @brif デフォルトの描画エリアYサイズ
	int m_nGridSize;			// @brif グリッドサイズ
	BOOL m_bShowGrid;			// @brif グリッド表示設定
	BOOL m_bPosGrid;			// @brif グリッドにスナップ
	CString m_strWorkDir;		// @brif 作業フォルダ
protected:
	BOOL IniAccess(BOOL bWrite, LPCTSTR pszFileName = NULL);

	CString m_strIniFileName;
private:
	BOOL ProfileAccessInt(LPCTSTR pszSection, LPCTSTR pszName, int &nData, int nDefault, BOOL bWrite, LPCTSTR pszFileName = NULL);
	BOOL ProfileAccessStr(LPCTSTR pszSection, LPCTSTR pszName, CString &strData, CString strDefault, BOOL bWrite, LPCTSTR pszFileName = NULL);
};

#endif // !defined(AFX_DRAWERCONFIG_H__02E861CC_F9E0_4A65_AB50_7C1C3FBBEDB3__INCLUDED_)
