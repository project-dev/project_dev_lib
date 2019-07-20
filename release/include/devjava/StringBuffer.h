// StringBuffer.h: CStringBuffer クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(__DEVJAVA_STRINGBUFFER__)
#define __DEVJAVA_STRINGBUFFER__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "devjava.h"

#ifdef DEVJAVA_EXPORTS
	#define DEVJAVA_EXT_CLASS		 __declspec(dllexport)
#else
	#define DEVJAVA_EXT_CLASS		 __declspec(dllimport)
#endif

/**
 * java.lang.StringBufferの模造品(一部関数のみサポート)
 */
class DEVJAVA_EXT_CLASS StringBuffer{
public:
	void Empty();
	int length();
	char* toByte();
	void append(char* pszText);
	void append(char ch);
	StringBuffer();
	virtual ~StringBuffer();
private:
	char *m_pBuff;
	int m_nPosition;
	int m_nBuffSize;
};

#endif // !defined(__DEVJAVA_STRINGBUFFER__)
