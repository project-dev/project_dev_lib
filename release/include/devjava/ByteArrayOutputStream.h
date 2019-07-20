// ByteArrayOutputStream.h: CByteArrayOutputStream クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(__DEVJAVA_BYTEARRAYOUTPUTSTREAM__)
#define __DEVJAVA_BYTEARRAYOUTPUTSTREAM__

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
 * java.io.ByteArrayOutputStreamの模造品(一部関数のみサポート)
 */
class DEVJAVA_EXT_CLASS ByteArrayOutputStream{
public:
	ByteArrayOutputStream();
	virtual ~ByteArrayOutputStream();

	void open();
	void write(char ch);
	void write(char ch[]);
	void close();
	char* toByteArray();
private:
	char *m_pBuff;
	int m_nPosition;
	int m_nBuffSize;
};

#endif // !defined(__DEVJAVA_BYTEARRAYOUTPUTSTREAM__)
