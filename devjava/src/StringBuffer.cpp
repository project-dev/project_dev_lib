// StringBuffer.cpp: StringBuffer クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////
#include <stdafx.h>
#include "StringBuffer.h"

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

/**
 *コンストラクタ
 */
StringBuffer::StringBuffer(){
	m_nBuffSize = 1024;
	m_pBuff = new char[m_nBuffSize + 1];
	memset(m_pBuff, 0, m_nBuffSize + 1);
	m_nPosition = 0;
}

/**
 *デストラクタ
 */
StringBuffer::~StringBuffer(){
	if(m_pBuff){
		delete m_pBuff;
	}
	m_pBuff = 0;
}

/**
 * java.lang.StringBuffer.appendの模造品
 * @param ch 追記する文字
 */
void StringBuffer::append(char ch){
	m_pBuff[m_nPosition] = ch;
	m_nPosition++;
	if(m_nPosition >= m_nBuffSize){
		//バッファの再確保
		m_nBuffSize += 1024;
		char *pszBuff = new char[m_nBuffSize + 1];
		memset(pszBuff, 0, m_nBuffSize + 1);
		strcpy(pszBuff, m_pBuff);
		delete m_pBuff;
		m_pBuff = pszBuff;
	}
}


/**
 * java.lang.StringBuffer.appendの模造品
 * @param pszText 追記する文字列
 */
void StringBuffer::append(char *pszText){
	int nLen = strlen(pszText);
	
	if((m_nPosition + nLen) >= m_nBuffSize){
		//バッファの再確保
		m_nBuffSize += (m_nPosition + nLen) - m_nBuffSize + 1024;
		char *pszBuff = new char[m_nBuffSize + 1];
		memset(pszBuff, 0, m_nBuffSize + 1);
		strcpy(pszBuff, m_pBuff);
		delete m_pBuff;
		m_pBuff = pszBuff;
	}

	strcat(m_pBuff, pszText);
	m_nPosition += nLen;
	if(m_nPosition >= m_nBuffSize){
		//バッファの再確保
		m_nBuffSize += m_nPosition - m_nBuffSize + 1024;
		char *pszBuff = new char[m_nBuffSize + 1];
		memset(pszBuff, 0, m_nBuffSize + 1);
		strcpy(pszBuff, m_pBuff);
		delete m_pBuff;
		m_pBuff = pszBuff;
	}
}

/**
 * java.lang.StringBuffer.getBytesの模造品
 * 関数名がJavaと違うので注意
 * @return 文字列
 */
char* StringBuffer::toByte(){
	return m_pBuff;
}

/**
 * java.lang.StringBuffer.lengthの模造品
 * @return 文字列の長さ
 */
int StringBuffer::length(){
	return strlen(m_pBuff);
}

/**
 * java.lang.StringBuffer.Emptyの模造品
 */
void StringBuffer::Empty(){
	if(m_pBuff){
		delete m_pBuff;
	}
	m_nBuffSize = 1024;
	m_pBuff = new char[m_nBuffSize + 1];
	memset(m_pBuff, 0, m_nBuffSize + 1);
	m_nPosition = 0;
}
