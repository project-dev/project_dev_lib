// Cryptography.cpp: CCryptography �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Cryptography.h"
/*
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
*/
//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CCryptography::CCryptography(){
	m_pszBuff = NULL;
}

CCryptography::~CCryptography(){
	if(m_pszBuff){
		delete m_pszBuff;
		m_pszBuff = NULL;
	}
}

/**
 * @brief �w�肳�ꂽ�f�[�^���Í������܂��B
 *
 * @param bData �Í����Ώۂ̃f�[�^
 * @param nSize �Í����Ώۂ̔z��̃T�C�Y�B
 * @param pPass �Í����ׂ̈̃p�X���[�h
 * @param pRetByte �Í�����̃f�[�^�B�T�C�Y�͈���nSize�B(����ύX�����\�L��)
 */
void CCryptography::EncodeData(byte *bData, int nSize, char *pPass, byte*& pRetByte){
	if(m_pszBuff){
		delete m_pszBuff;
		m_pszBuff = NULL;
	}
	
	if(!bData || !nSize){
		pRetByte = NULL;
		return;
	}

	if(!pPass || !strlen(pPass)){
		pRetByte = NULL;
		return;
	}


	//�p�X���[�h����L�[�R�[�h�𐶐�����
	byte keyCode = 0;
	if(GetKeyCode(pPass, keyCode) == -1){
		pRetByte = NULL;
		return;
	}

	m_pszBuff = new byte[nSize + 1];
	memset(m_pszBuff, 0, nSize + 1);
	for(int i = 0; i < nSize; i++){
		byte bEncData = (byte)(bData[i] ^ keyCode);
//		bEncData++;
		m_pszBuff[i] = bEncData;
	}
	pRetByte = m_pszBuff;
	return;
}

/**
 * @brief �w�肳�ꂽ�f�[�^�𕡍������܂��B
 *
 * @param bData �������Ώۂ̃f�[�^
 * @param nSize �������Ώۂ̔z��̃T�C�Y�B
 * @param pPass �������ׂ̈̃p�X���[�h
 * @param pRetByte �������Ώۂ̃f�[�^�B�T�C�Y�͈���nSize�B(����ύX�����\�L��)
 */
void CCryptography::DecodeData(byte *bData, int nSize, char *pPass, byte*& pRetByte){
	if(m_pszBuff){
		delete m_pszBuff;
		m_pszBuff = NULL;
	}
	
	if(!bData || !nSize){
		pRetByte = NULL;
		return;
	}

	if(!pPass || !strlen(pPass)){
		pRetByte = NULL;
		return;
	}

	//�p�X���[�h����L�[�R�[�h�𐶐�����
	byte keyCode = 0;
	if(GetKeyCode(pPass, keyCode) == -1){
		pRetByte = NULL;
		return;
	}

	m_pszBuff = new byte[nSize + 1];
	memset(m_pszBuff, 0, nSize + 1);
	for(int i = 0; i < nSize; i++){
//		bData[i]--;
		byte bEncData = (byte)(bData[i] ^ keyCode);
		m_pszBuff[i] = bEncData;
	}
	pRetByte = m_pszBuff;
	return;
}

/**
 * @brief �p�X���[�h����L�[�R�[�h���擾���܂��B
 */
int CCryptography::GetKeyCode(char *pPass, byte &bCode) const{
	if(!pPass || !strlen(pPass)){
		return -1;
	}
	int nCode = 0;
	int nSize = strlen(pPass);
	for(int i = 0; i < nSize; i++){
		byte ch = (byte)pPass[i];

		//�o�C�g�𔽓]
		byte code1 = (byte)((ch << 4) & 0xF0);
		byte code2 = (byte)((ch >> 4) & 0x0F);
		byte revCode = (byte)(code1 | code2);
		nCode += revCode;
	}

	while(nCode > 0x7F){
		nCode = nCode / 128;
	}
	bCode = (byte)nCode;
	return 0;
}


void CCryptography::GetDecodeString(char* pszPass, char*& strDecPass, const char *pszCrypPass){
	//�f�R�[�h���ꂽ�p�X���[�h
	strDecPass = NULL;
	if(!pszPass && !strlen(pszPass)){
		return;
	}

	char *pszData = new char[strlen(pszPass) + 1];
	memset(pszData, 0, strlen(pszPass) + 1);
	char *pszStartData = pszData;
	strcpy(pszData, pszPass);

	int nSize = strlen(pszPass) / 2;
	
	byte *pByte = new byte[nSize + 1];
	memset(pByte,  0, nSize + 1);

	int nCnt = 0;
	char chData[2];
	while(strlen(pszData)){
		chData[0] = pszData[0];
		chData[1] = pszData[1];
		byte bData;
		pByte[nCnt] = 0;
		for(int i = 0; i < 2; i++){
			bData = chData[i];
			if(bData >= 'a'){
				bData = (byte)(bData - (byte)'a' + 10);
			}else if(bData >= 'A'){
				bData = (byte)(bData - (byte)'A' + 10);
			}else{
				bData = (byte)(bData - (byte)'0');
			}

			if((bData > 16) || (bData < 0)){
				delete pByte;
				delete pszStartData;
				return;
			}
			if(i == 0){
				bData = (byte)(bData << 4);
			}
			pByte[nCnt] += bData;
			
		}		
		//�A�h���X���C���N�������g
		pszData += 2;
		nCnt++;
	}
	delete pszStartData;

	byte *pRetByte = NULL;
	DecodeData(pByte, nSize, (char*)pszCrypPass, pRetByte);
	if(pRetByte){
		strDecPass = (char*)pRetByte;
	}
	delete pByte;
}

//�p�X���[�h��ݒ肷��
void CCryptography::GetEncodeString(char* pszPass, char*& strDecPass, const char *pszCrypPass){
	int nSize = strlen(pszPass);
	byte *pByte = new byte[nSize];
	byte *pRetByte = NULL;
	memcpy(pByte, pszPass, nSize);
	EncodeData(pByte, nSize, (char*)pszCrypPass, pRetByte);

	char szData[3];
	char *pszRetPass = new char[nSize * 2 + 1];
	memset(szData, 0, 3);
	memset(pszRetPass, 0, nSize * 2 + 1);

	strDecPass = pszRetPass;
	if(pRetByte){
		for(int i = 0; i < nSize; i++){
			sprintf(szData, "%02x", pRetByte[i]);
			strcpy(pszRetPass, szData);
			pszRetPass += 2;
		}
	}
	delete pByte;
	if(m_pszBuff){
		delete m_pszBuff;
		m_pszBuff = NULL;
	}
	m_pszBuff = (byte*)strDecPass;
}
