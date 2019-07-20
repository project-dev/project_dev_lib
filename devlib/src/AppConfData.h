// AppConfData.h: CAppConfData クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APPCONFDATA_H__C3297E7C_0F5D_4653_8C21_5E1958DC6EBA__INCLUDED_)
#define AFX_APPCONFDATA_H__C3297E7C_0F5D_4653_8C21_5E1958DC6EBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAppConfData {
public:
	BOOL Create(char* pszIniFilePath, char* pszAppName);
	CAppConfData();
	virtual ~CAppConfData();


private:
	char m_szIniFile[MAX_PATH];		//iniファイルパス
};

#endif // !defined(AFX_APPCONFDATA_H__C3297E7C_0F5D_4653_8C21_5E1958DC6EBA__INCLUDED_)
