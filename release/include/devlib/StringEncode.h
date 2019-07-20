#if !defined(__DEVLIB_STRINGENCODE__)
#define __DEVLIB_STRINGENCODE__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "devtypedef.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#ifdef DEVLIB_EXPORTS
	#define DEV_EXT_CLASS		 __declspec(dllexport)
#else
	#define DEV_EXT_CLASS		 __declspec(dllimport)
#endif

/**
 * @brief ������̃G���R�[�h�������N���X
 * @author Project D.E.V
 */
class DEV_EXT_CLASS CStringEncode {
public:
	CStringEncode();
	virtual ~CStringEncode();
	
	int CheckCode(char *pszBuff);

	char* toURL();
	char* decodeURL(char* chars);
	char* toBASE64();
	char* decodeBASE64(const char* base64s);
	char getBasebyte(int pos);

public:

	//EUC��JIS�ɕϊ����܂�
	static char* euc2jis(char* eucchars);

	//EUC��Shift-JIS�ɕϊ����܂�
	static char* euc2sjis(char* eucchars);

	//JIS��EUC�ɕϊ����܂�
	static char* jis2euc(char *jischars);

	//JIS��Shift-JIS�ɕϊ����܂�
	static char* jis2sjis(char *jischars);

	//Shift-JIS��JIS�ɕϊ����܂�
	static char* sjis2jis(char *sjischars);

	//Shift-JIS��EUC�ɕϊ����܂�
	static char* sjis2euc(char *sjischars);

	//UTF-8��Shift-JIS�ɕϊ����܂�
	static char* utf82sjis(char *utfchars);

public:	
	char* sjis2utf8(char *sjischars);
	char* toUTF8();
	char* toEUC();
	char* toSJIS();
	char* toJIS();
	static void ReleaseBuff(char *pszBuff);
	typedef enum eCode{
		NaN		= -1,
		JIS		= 0,
		SJIS	= 1,
		EUC		= 2,
		UTF8	= 3,
		UNICODE	= 4,
	};

private:
	char	*m_pszBuff;				//������̃o�b�t�@
	int		m_nType;
};

#endif // !defined(__DEVLIB_STRINGENCODE__)
