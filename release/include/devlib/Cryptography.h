// Cryptography.h: CCryptography クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRYPTOGRAPHY_H__CB117437_88B4_44F0_9FFD_6F959ECEAC4B__INCLUDED_)
#define AFX_CRYPTOGRAPHY_H__CB117437_88B4_44F0_9FFD_6F959ECEAC4B__INCLUDED_

#ifdef DEVLIB_EXPORTS
	#define DEV_EXT_CLASS		 __declspec(dllexport)
#else
	#define DEV_EXT_CLASS		 __declspec(dllimport)
#endif

#include "devlib.h"
//#include "..\..\RELEASE\INCLUDE\DEVLIB\devtypedef.h"	// ClassView によって追加されました。

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class DEV_EXT_CLASS CCryptography {
public:
	void DecodeData(byte *bData, int nSize, char *pPass, byte*& pRetByte);
	void EncodeData(byte *bData, int nSize, char *pPass, byte*& pRetByte);
	void GetDecodeString(char* pszData, char*& strDecPass, const char *pszPass);
	void GetEncodeString(char* pszData, char*& strEncPass, const char *pszPass);
	CCryptography();
	virtual ~CCryptography();


private:
	int GetKeyCode(char *pPass, byte &bCode) const;
	byte *m_pszBuff;
};

#endif // !defined(AFX_CRYPTOGRAPHY_H__CB117437_88B4_44F0_9FFD_6F959ECEAC4B__INCLUDED_)
