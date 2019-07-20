// StringBuffer.cpp: StringBuffer �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////
#include <stdafx.h>
#include "StringBuffer.h"

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

/**
 *�R���X�g���N�^
 */
StringBuffer::StringBuffer(){
	m_nBuffSize = 1024;
	m_pBuff = new char[m_nBuffSize + 1];
	memset(m_pBuff, 0, m_nBuffSize + 1);
	m_nPosition = 0;
}

/**
 *�f�X�g���N�^
 */
StringBuffer::~StringBuffer(){
	if(m_pBuff){
		delete m_pBuff;
	}
	m_pBuff = 0;
}

/**
 * java.lang.StringBuffer.append�̖͑��i
 * @param ch �ǋL���镶��
 */
void StringBuffer::append(char ch){
	m_pBuff[m_nPosition] = ch;
	m_nPosition++;
	if(m_nPosition >= m_nBuffSize){
		//�o�b�t�@�̍Ċm��
		m_nBuffSize += 1024;
		char *pszBuff = new char[m_nBuffSize + 1];
		memset(pszBuff, 0, m_nBuffSize + 1);
		strcpy(pszBuff, m_pBuff);
		delete m_pBuff;
		m_pBuff = pszBuff;
	}
}


/**
 * java.lang.StringBuffer.append�̖͑��i
 * @param pszText �ǋL���镶����
 */
void StringBuffer::append(char *pszText){
	int nLen = strlen(pszText);
	
	if((m_nPosition + nLen) >= m_nBuffSize){
		//�o�b�t�@�̍Ċm��
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
		//�o�b�t�@�̍Ċm��
		m_nBuffSize += m_nPosition - m_nBuffSize + 1024;
		char *pszBuff = new char[m_nBuffSize + 1];
		memset(pszBuff, 0, m_nBuffSize + 1);
		strcpy(pszBuff, m_pBuff);
		delete m_pBuff;
		m_pBuff = pszBuff;
	}
}

/**
 * java.lang.StringBuffer.getBytes�̖͑��i
 * �֐�����Java�ƈႤ�̂Œ���
 * @return ������
 */
char* StringBuffer::toByte(){
	return m_pBuff;
}

/**
 * java.lang.StringBuffer.length�̖͑��i
 * @return ������̒���
 */
int StringBuffer::length(){
	return strlen(m_pBuff);
}

/**
 * java.lang.StringBuffer.Empty�̖͑��i
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
