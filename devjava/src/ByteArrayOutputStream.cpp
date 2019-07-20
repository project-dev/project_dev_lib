// ByteArrayOutputStream.cpp: ByteArrayOutputStream クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////
#include <stdafx.h>
#include "ByteArrayOutputStream.h"

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

/**
 *コンストラクタ
 */
ByteArrayOutputStream::ByteArrayOutputStream(){
	m_pBuff = NULL;
}

/**
 *デストラクタ
 */
ByteArrayOutputStream::~ByteArrayOutputStream(){
	if(m_pBuff){
		delete m_pBuff;
	}
}

/**
 * java.io.ByteArrayOutputStream::openの模造品
 * このクラスを利用する場合は必ず呼び出す必要がある
 */
void ByteArrayOutputStream::open(){
	//とりあえず
	m_nBuffSize = 1024;
	m_pBuff = new char[m_nBuffSize + 1];
	memset(m_pBuff, 0, m_nBuffSize + 1);
	m_nPosition = 0;
}


/**
 * java.io.ByteArrayOutputStream::writeの模造品
 * @param ch 書き込む文字
 */
void ByteArrayOutputStream::write(char ch){
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
 * java.io.ByteArrayOutputStream::writeの模造品
 * @param ch 書き込む文字列
 */
void ByteArrayOutputStream::write(char ch[]){
	int nLen = strlen(ch);
	
	if((m_nPosition + nLen) >= m_nBuffSize){
		//バッファの再確保
		m_nBuffSize += (m_nPosition + nLen) - m_nBuffSize + 1024; 
		char *pszBuff = new char[m_nBuffSize + 1];
		memset(pszBuff, 0, m_nBuffSize + 1);
		strcpy(pszBuff, m_pBuff);
		delete m_pBuff;
		m_pBuff = pszBuff;
	}

	strcat(m_pBuff, ch);
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
 * java.io.ByteArrayOutputStream::closeの模造品
 * open関数とペアで呼ぶ必要がある 
 */
void ByteArrayOutputStream::close(){
	if(m_pBuff){
		delete m_pBuff;
	}
	m_pBuff = NULL;
	m_nBuffSize = 0;
	m_nPosition = 0;
}

/**
 * java.io.ByteArrayOutputStream::toByteArrayの模造品
 * @return 書き込まれたデータ
 */
char* ByteArrayOutputStream::toByteArray(){
	return m_pBuff;
}
