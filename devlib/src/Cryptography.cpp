// Cryptography.cpp: CCryptography クラスのインプリメンテーション
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
// 構築/消滅
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
 * @brief 指定されたデータを暗号化します。
 *
 * @param bData 暗号化対象のデータ
 * @param nSize 暗号化対象の配列のサイズ。
 * @param pPass 暗号化の為のパスワード
 * @param pRetByte 暗号化後のデータ。サイズは引数nSize。(今後変更される可能有り)
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


	//パスワードからキーコードを生成する
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
 * @brief 指定されたデータを複合化します。
 *
 * @param bData 複合化対象のデータ
 * @param nSize 複合化対象の配列のサイズ。
 * @param pPass 複合化の為のパスワード
 * @param pRetByte 複合化対象のデータ。サイズは引数nSize。(今後変更される可能有り)
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

	//パスワードからキーコードを生成する
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
 * @brief パスワードからキーコードを取得します。
 */
int CCryptography::GetKeyCode(char *pPass, byte &bCode) const{
	if(!pPass || !strlen(pPass)){
		return -1;
	}
	int nCode = 0;
	int nSize = strlen(pPass);
	for(int i = 0; i < nSize; i++){
		byte ch = (byte)pPass[i];

		//バイトを反転
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
	//デコードされたパスワード
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
		//アドレスをインクリメント
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

//パスワードを設定する
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
