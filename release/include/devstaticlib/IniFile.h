// IniFile.h: CIniFile クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIFILE_H__F200CC2B_42BF_499B_A6BD_E4B7515D1D7A__INCLUDED_)
#define AFX_INIFILE_H__F200CC2B_42BF_499B_A6BD_E4B7515D1D7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/**
 * データ型種別列挙型
 */
typedef enum eINITYPE{
	IT_INT,
	IT_BOOL,
	IT_STRING,
	IT_DOUBLE,
};

/**
 * @brif Iniファイル定義情報構造体
 */
typedef struct tagINIDATA{
	eINITYPE eType;			//データ型種別	
	char* szSecssion;		//セッション名
	char* szKey;			//キー名
	LPVOID pData;			//データが格納されている/格納する変数のポインタ
	LPVOID pDefault;		//デフォルトの値
	int nLen;				//長さ
}INIDATA;


class CIniFile {
public:
	CIniFile();
	virtual ~CIniFile();
	BOOL IniFileAccess(LPCTSTR pszIniPath, BOOL bSave);
protected:
	virtual BOOL OnIniFileAccess(INIDATA* &pIniData, int &nCnt) = 0;
};

#endif // !defined(AFX_INIFILE_H__F200CC2B_42BF_499B_A6BD_E4B7515D1D7A__INCLUDED_)
