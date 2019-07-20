// ByteArrayOutputStream.cpp: ByteArrayOutputStream �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////
#include <stdafx.h>
#include "ByteArrayOutputStream.h"

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

/**
 *�R���X�g���N�^
 */
ByteArrayOutputStream::ByteArrayOutputStream(){
	m_pBuff = NULL;
}

/**
 *�f�X�g���N�^
 */
ByteArrayOutputStream::~ByteArrayOutputStream(){
	if(m_pBuff){
		delete m_pBuff;
	}
}

/**
 * java.io.ByteArrayOutputStream::open�̖͑��i
 * ���̃N���X�𗘗p����ꍇ�͕K���Ăяo���K�v������
 */
void ByteArrayOutputStream::open(){
	//�Ƃ肠����
	m_nBuffSize = 1024;
	m_pBuff = new char[m_nBuffSize + 1];
	memset(m_pBuff, 0, m_nBuffSize + 1);
	m_nPosition = 0;
}


/**
 * java.io.ByteArrayOutputStream::write�̖͑��i
 * @param ch �������ޕ���
 */
void ByteArrayOutputStream::write(char ch){
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
 * java.io.ByteArrayOutputStream::write�̖͑��i
 * @param ch �������ޕ�����
 */
void ByteArrayOutputStream::write(char ch[]){
	int nLen = strlen(ch);
	
	if((m_nPosition + nLen) >= m_nBuffSize){
		//�o�b�t�@�̍Ċm��
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
 * java.io.ByteArrayOutputStream::close�̖͑��i
 * open�֐��ƃy�A�ŌĂԕK�v������ 
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
 * java.io.ByteArrayOutputStream::toByteArray�̖͑��i
 * @return �������܂ꂽ�f�[�^
 */
char* ByteArrayOutputStream::toByteArray(){
	return m_pBuff;
}
