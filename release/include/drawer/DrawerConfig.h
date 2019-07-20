// DrawerConfig.h: CDrawerConfig �N���X�̃C���^�[�t�F�C�X
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

	int m_nDefWidth;			// @brif �f�t�H���g�̕`��G���AX�T�C�Y
	int m_nDefHeight;			// @brif �f�t�H���g�̕`��G���AY�T�C�Y
	int m_nGridSize;			// @brif �O���b�h�T�C�Y
	BOOL m_bShowGrid;			// @brif �O���b�h�\���ݒ�
	BOOL m_bPosGrid;			// @brif �O���b�h�ɃX�i�b�v
	CString m_strWorkDir;		// @brif ��ƃt�H���_
protected:
	BOOL IniAccess(BOOL bWrite, LPCTSTR pszFileName = NULL);

	CString m_strIniFileName;
private:
	BOOL ProfileAccessInt(LPCTSTR pszSection, LPCTSTR pszName, int &nData, int nDefault, BOOL bWrite, LPCTSTR pszFileName = NULL);
	BOOL ProfileAccessStr(LPCTSTR pszSection, LPCTSTR pszName, CString &strData, CString strDefault, BOOL bWrite, LPCTSTR pszFileName = NULL);
};

#endif // !defined(AFX_DRAWERCONFIG_H__02E861CC_F9E0_4A65_AB50_7C1C3FBBEDB3__INCLUDED_)
