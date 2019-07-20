// DevString.cpp: CDevString �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DevString.h"
#include <mbstring.h>

#include <string>
using namespace std;

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/**
 * @brief CDevString�̔�r�I�y���[�^�[
 */
bool __stdcall operator==(CDevString &str1, CDevString &str2){
	if(str1.Compare(str2)){
		return false;
	}else{
		return true;
	}
}

/**
 * @brief CDevString�̔�r�I�y���[�^�[
 */
bool __stdcall operator==(CDevString &str1, const char* pszText){
	CDevString str2;
	str2 = pszText;
	if(str1.Compare(str2)){
		return false;
	}else{
		return true;
	}
}

/**
 * @brief CDevString�̔�r�I�y���[�^�[
 */
bool __stdcall operator==(const char* pszText, CDevString &str2){
	CDevString str1;
	str1 = pszText;
	if(str1.Compare(str2)){
		return false;
	}else{
		return true;
	}
}

/**
 * @brief CDevString�̔�r�I�y���[�^�[
 */
bool __stdcall operator!=(CDevString &str1, CDevString &str2){
	if(str1.Compare(str2)){
		return true;
	}else{
		return false;
	}
}

/**
 * @brief CDevString�̔�r�I�y���[�^�[
 */
bool __stdcall operator!=(CDevString &str1, const char* pszText){
	CDevString str2;
	str2 = pszText;
	if(str1.Compare(str2)){
		return true;
	}else{
		return false;
	}
}

/**
 * @brief CDevString�̔�r�I�y���[�^�[
 */
bool __stdcall operator!=(const char* pszText, CDevString &str2){
	CDevString str1;
	str1 = pszText;
	if(str1.Compare(str2)){
		return true;
	}else{
		return false;
	}
}


//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

/**
 * @brief �R���X�g���N�^
 */
CDevString::CDevString(){
	m_pszChar = NULL;
	m_pString = (void*)new string;
}

/**
 * @brief �R�s�[�R���X�g���N�^
 *
 * @param strString �R�s�[����CDevString
 */
CDevString::CDevString(CDevString &strString){
	m_pszChar = NULL;
	m_pString = (void*)new string;
	string* pStr = (string*)m_pString;
	*pStr = strString;
}

/**
 * @brief �R�s�[�R���X�g���N�^
 *
 * @param pszText �R�s�[���镶����
 */
CDevString::CDevString(const char* pszText){
	m_pszChar = NULL;
	m_pString = (void*)new string;
	string* pStr = (string*)m_pString;
	*pStr = pszText;
}

/**
 * @brief �R�s�[�R���X�g���N�^
 *
 * @param pszText �R�s�[���镶����
 */
CDevString::CDevString(char* pszText){
	m_pszChar = NULL;
	m_pString = (void*)new string;
	string* pStr = (string*)m_pString;
	*pStr = pszText;
}

/**
 * @brief �f�X�g���N�^
 */
CDevString::~CDevString(){
	if(m_pszChar){
		delete m_pszChar;
		m_pszChar = NULL;
	}
	if(m_pString){
		OutputDebugString("����������m_pString release����������\n");
		delete m_pString;
		m_pString = NULL;
	}

}

//-----------------------------------------------------------------
//�����񑀍�

/**
 * @brief ������nLen�����擾����
 *
 * @param nLen �擾������
 * @return �����o����������
 */
CDevString CDevString::Left(int nLen) const{
	CDevString strReturn = "";
	string* pStr = (string*)m_pString;
	strReturn = pStr->substr(0, nLen).c_str();
	return strReturn;
}

/**
 * @brief �E����nLen�����擾����
 * @param nLen �擾������
 * @return �����o����������
 */
CDevString CDevString::Right(int nLen) const{
	CDevString strReturn = "";
	string* pStr = (string*)m_pString;
	strReturn = pStr->substr(pStr->length() - nLen, nLen).c_str();
	return strReturn;
}

/**
 * @brief nPos������̕����擾����
 * @param nPos �J�n�ʒu
 * @return �����o����������
 */
CDevString CDevString::Mid(int nPos) const{
	CDevString strReturn = "";
	string* pStr = (string*)m_pString;
	strReturn = pStr->substr(nPos).c_str();
	return strReturn;
}

/**
 * @brief nStart����nLen�܂ł͈̔͂̕�������擾����
 * @param nStart �J�n�ʒu
 * @param nLen �����B-1�̏ꍇ�͖����܂�
 * @return �����o����������
 */
CDevString CDevString::SubString(int nStart, int nLen /*= -1*/) const{
	CDevString strReturn = "";
	string* pStr = (string*)m_pString;
	if(nLen >= 0){
		strReturn = pStr->substr(nStart, nLen).c_str();
	}else{
		strReturn = pStr->substr(nStart).c_str();
	}

	return strReturn;
}

/**
 * @brief �S�p�Ɣ��p���ӎ�����Left�֐�
 * @param nLen �擾������
 * @return �����o����������
 */
CDevString CDevString::LeftText(int nLen){
	string* pStr = (string*)m_pString;
	CDevString strRet = pStr->c_str();
	CDevString strReturn = "";
	for(int i = 0; i < nLen; i++){
		GetTextAt(i, strRet);
		strReturn += strRet;
	}
	return strReturn;
}

/**
 * @brief �S�p�Ɣ��p���ӎ�����Right�֐�
 * @param nLen �擾������
 * @return �����o����������
 */
CDevString CDevString::RightText(int nLen){
	string* pStr = (string*)m_pString;
	CDevString strRet = pStr->c_str();
	CDevString strReturn = "";
	int nMax = GetTextLength();
	
	for(int i = (nMax - nLen); i < nMax; i++){
		GetTextAt(i, strRet);
		strReturn += strRet;
	}
	return strReturn;
}

/**
 * @brief �S�p�Ɣ��p���ӎ�����Mid�֐�
 * @param nFirst �J�n�ʒu
 * @return �����o����������
 */
CDevString CDevString::MidText(int nFirst){
	string* pStr = (string*)m_pString;
	CDevString strRet = pStr->c_str();
	CDevString strReturn = "";
	int nLen = GetTextLength();
	for(int i = nFirst; i < nLen; i++){
		GetTextAt(i, strRet);
		strReturn += strRet;
	}
	return strReturn;
}

/**
 * @brief �S�p�Ɣ��p���ӎ�����SubString�֐�
 * @param nFirst �J�n�ʒu
 * @param nLen ����
 * @return �����o����������
 */
CDevString CDevString::SubStringText(int nFirst, int nLen){
	string* pStr = (string*)m_pString;
	CDevString strRet = pStr->c_str();
	CDevString strReturn = "";
	for(int i = nFirst; i < (nFirst + nLen); i++){
		GetTextAt(i, strRet);
		strReturn += strRet;
	}
	return strReturn;
}

/**
 * @brief ������̍��E�̔��p�󔒂���������
 */
void CDevString::Trim(){
	TrimLeft();
	TrimRight();
}

/**
 * @brief ������̍��̔��p�󔒂���������
 */
void CDevString::TrimLeft(){
	string* pStr = (string*)m_pString;
	int nLen = pStr->length();
	int nTrimPos = 0;
	for(int i = 0; i < nLen; i++){
		if((*pStr)[i] != ' '){
			break;
		}
		nTrimPos++;
	}

	if(!nTrimPos){
		return;
	}

	*pStr = pStr->substr(nTrimPos);
}

/**
 * @brief ������̉E�̔��p�󔒂���������
 */
void CDevString::TrimRight(){
	string* pStr = (string*)m_pString;
	int nLen = pStr->length();
	int nTrimPos = 0;
	for(int i = nTrimPos; i < nLen; --i){
		if((*pStr)[i] != ' '){
			break;
		}
		nTrimPos++;
	}

	if(!nTrimPos){
		return;
	}

	*pStr = pStr->substr(0, nLen - nTrimPos);
}

/**
 * @brief ���������ɂ���
 */
void CDevString::Empty(){
	string* pStr = (string*)m_pString;
	pStr->empty();
}

/**
 * @brief �����񂪋󂩂ǂ����̃`�F�b�N
 */
bool CDevString::IsEmpty(){
	string* pStr = (string*)m_pString;
	return pStr->length() == 0 ? true : false;
}

/**
 * @brief �C�ӂ̈ʒu�ɕ�����ݒ肷��
 * @param nIndex �ʒu
 * @param ch �Z�b�g���镶��
 */
void CDevString::SetAt(int nIndex, char ch){
	string* pStr = (string*)m_pString;
	(*pStr)[nIndex] = ch;
}
	

//-----------------------------------------------------------------
//����/�u��

/**
 * @brief ���������������
 * @param pszFind ����������
 * @param nStart �����J�n�ʒu�B
 * @return �o���ʒu�B������Ȃ��ꍇ��-1
 */
int CDevString::Find(char* pszFind, int nStart /* = 0*/){
	string* pStr = (string*)m_pString;
	return pStr->find(pszFind, nStart);
}

/**
 * @brief ���������������
 * @param pszFind ����������
 * @param nStart �����J�n�ʒu�B
 * @return �o���ʒu�B������Ȃ��ꍇ��-1
 */
int CDevString::Find(const char* pszFind, int nStart /* = 0*/){
	string* pStr = (string*)m_pString;
	return pStr->find(pszFind, nStart);
}

/**
 * @brief ���������������
 * @param strFind ����������
 * @param nStart �����J�n�ʒu�B
 * @return �o���ʒu�B������Ȃ��ꍇ��-1
 */
int CDevString::Find(CDevString &strFind, int nStart /* = 0*/){
	string* pStr = (string*)m_pString;
	return pStr->find(strFind, nStart);
}

/**
 * @brief �S�p���p���ӎ�����Find�֐�
 * @param pszFind ����������
 * @param nStart �����J�n�ʒu�B
 * @return �o���ʒu�B������Ȃ��ꍇ��-1
 */
int CDevString::FindText(char* pszFind, int nStart){
	CDevString strFind = pszFind;
	int nLen = GetTextLength();
	if(nLen <= nStart){
		return -1;
	}
	int nFindLen = strFind.GetTextLength();
	for(int i = nStart; i < nLen; i++){
		CDevString &strAt = SubStringText(i, nFindLen);
		if(!strFind.Compare(strAt)){
			return i;
		}
	}
	return -1;
}

/**
 * @brief �S�p���p���ӎ�����Find�֐�
 * @param pszFind ����������
 * @param nStart �����J�n�ʒu�B
 * @return �o���ʒu�B������Ȃ��ꍇ��-1
 */
int CDevString::FindText(const char* pszFind, int nStart){
	CDevString strFind = pszFind;
	int nLen = GetTextLength();
	if(nLen <= nStart){
		return -1;
	}
	int nFindLen = strFind.GetTextLength();
	for(int i = nStart; i < nLen; i++){
		CDevString &strAt = SubStringText(i, nFindLen);
		if(!strFind.Compare(strAt)){
			return i;
		}
	}
	return -1;

}

/**
 * @brief �S�p���p���ӎ�����Find�֐�
 * @param strFind ����������
 * @param nStart �����J�n�ʒu�B
 * @return �o���ʒu�B������Ȃ��ꍇ��-1
 */
int CDevString::FindText(CDevString &strFind, int nStart){
	int nLen = GetTextLength();
	if(nLen <= nStart){
		return -1;
	}
	int nFindLen = strFind.GetTextLength();
	for(int i = nStart; i < nLen; i++){
		CDevString &strAt = SubStringText(i, nFindLen);
		if(!strFind.Compare(strAt)){
			return i;
		}
	}
	return -1;

}

/**
 * @brief ������𖖔����猟������
 * @param pszFind ����������
 * @return �o���ʒu�B������Ȃ��ꍇ��-1
 */
int CDevString::ReverseFind(char* pszFind){
	string* pStr = (string*)m_pString;
	return pStr->rfind(pszFind);
}

/**
 * @brief ������𖖔����猟������
 * @param pszFind ����������
 * @return �o���ʒu�B������Ȃ��ꍇ��-1
 */
int CDevString::ReverseFind(const char* pszFind){
	string* pStr = (string*)m_pString;
	return pStr->rfind(pszFind);
}

/**
 * @brief ������𖖔����猟������
 * @param strFind ����������
 * @return �o���ʒu�B������Ȃ��ꍇ��-1
 */
int CDevString::ReverseFind(CDevString &strFind){
	string* pStr = (string*)m_pString;
	return pStr->rfind(strFind);
}

/**
 * @brief �S�p���p���ӎ�����ReverseFind�֐�
 * @param pszFind ����������
 * @return �o���ʒu�B������Ȃ��ꍇ��-1
 */
int CDevString::ReverseFindText(char* pszFind){
	CDevString strFind = pszFind;
	return ReverseFindText(pszFind);
}

/**
 * @brief �S�p���p���ӎ�����ReverseFind�֐�
 * @param pszFind ����������
 * @return �o���ʒu�B������Ȃ��ꍇ��-1
 */
int CDevString::ReverseFindText(const char* pszFind){
	CDevString strFind = pszFind;
	return ReverseFindText(pszFind);
}

/**
 * @brief �S�p���p���ӎ�����ReverseFind�֐�
 * @param strFind ����������
 * @return �o���ʒu�B������Ȃ��ꍇ��-1
 */
int CDevString::ReverseFindText(CDevString &strFind){
	int nLen = GetTextLength();
	if(nLen <= 0){
		return -1;
	}
	int nFindLen = strFind.GetTextLength();
	for(int i = nLen-1; i >= 0; i++){
		CDevString &strAt = SubStringText(i, nFindLen);
		if(!strFind.Compare(strAt)){
			return i;
		}
	}
	return -1;
}

/**
 * @brief �ŏ��Ɉ�v���镶�����u��������
 * @param pszNew �u�������Ώە�����
 * @param pszOld �u�������镶����
 * @return �u���������������B�u���������������Ȃ������ꍇ��0
 */
int CDevString::Replace(const char* pszNew, const char* pszOld){
	string* pStr = (string*)m_pString;
	if(!pszNew || !pszOld){
		return 0;
	
	}

	int nPos = pStr->find(pszOld);
	if(nPos == -1){
		return 0;
	}

	int nLen = strlen(pszOld);
	pStr->replace(nPos, nLen, pszNew);
	
	return nLen;
}

/**
 * @brief ��v���镶��������ׂĒu��������
 * @param pszNew �u�������Ώە�����
 * @param pszOld �u�������镶����
 * @return �u���������������B�u���������������Ȃ������ꍇ��0
 */
int CDevString::ReplaceAll(const char* pszNew, const char* pszOld){
	string* pStr = (string*)m_pString;
	if(!pszNew || !pszOld){
		return 0;
	
	}

	int nPos = 0;
	int nLen = strlen(pszOld);
	bool bFirst = true;
	while(nPos != -1){
		nPos = pStr->find(pszOld, nPos);
		if(nPos != -1){
			pStr->replace(nPos, nLen, pszNew);
		}else{
			if(bFirst){
				return 0;
			}
		}
		bFirst = false;
	}
	return nLen;

}

/**
 * @brief �S�p���p���ӎ�����Replace�֐�
 * @param pszNew �u�������Ώە�����
 * @param pszOld �u�������镶����
 * @return �u���������������B�u���������������Ȃ������ꍇ��0
 */
int CDevString::ReplaceText(const char* pszNew, const char* pszOld, int nFindPos){
	string* pStr = (string*)m_pString;
	if(!pszNew || !pszOld){
		return 0;
	
	}

	CDevString strOld = pszOld;
	int nPos = FindText(pszOld, nFindPos);
	if(nPos == -1){
		return -1;
	}
	CDevString &strLeft = LeftText(nPos);
	int nOldLen = strOld.GetTextLength();
	int nLen = GetTextLength();
	int nRight = nLen - nPos - nOldLen;
	if(nRight < 0){
		return -1;
	}
	CDevString &strRight = RightText(nRight);
	CDevString strAfter;
	strAfter  = strLeft;
	strAfter += pszNew;
	strAfter += strRight;

	*pStr = strAfter;

	return nLen;
}

/**
 * @brief �S�p���p���ӎ�����ReplaceAll�֐�
 * @param pszNew �u�������Ώە�����
 * @param pszOld �u�������镶����
 * @return �u���������������B�u���������������Ȃ������ꍇ��0
 */
int CDevString::ReplaceAllText(const char* pszNew, const char* pszOld){
	if(!pszNew || !pszOld){
		return 0;
	
	}

	CDevString strOld = pszOld;
	int nPos = 0;
	int nLen = strOld.GetTextLength();
	bool bFirst = true;
	while(nPos != -1){
		nPos = FindText(strOld, nPos);
		if(nPos != -1){
			if(ReplaceText(pszNew, pszOld, nPos) == -1){
				break;
			}
		}else{
			if(bFirst){
				return 0;
			}
		}
		bFirst = false;
	}
	return nLen;
}

//-----------------------------------------------------------------
//��r

/**
 * @brief ��������r����
 * @param pszTarget ��r���镶��
 * @return -1 pszTarget���������ꍇ<br>0 ����<br>1 pszTarget���傫���ꍇ
 */
int CDevString::Compare(const char* pszTarget){
	string* pStr = (string*)m_pString;
	const char *pszText = pStr->c_str();

	int nLen1 = strlen(pszText);
	int nLen2 = strlen(pszTarget);
	if(nLen1 > nLen2){
		return 1;
	}
	if(nLen1 < nLen2){
		return -1;
	}
	
	return memcmp(pszText, pszTarget, nLen1);
}

/**
 * @brief �������啶������������ʂ�����r����
 * @param pszTarget ��r���镶��
 * @return -1 pszTarget���������ꍇ<br>0 ����<br>1 pszTarget���傫���ꍇ
 */
int CDevString::CompareNoCase(const char* pszTarget){
	string* pStr = (string*)m_pString;
	const char *pszText = pStr->c_str();
	int nLen1 = strlen(pszText);
	int nLen2 = strlen(pszTarget);
	if(nLen1 > nLen2){
		return 1;
	}
	if(nLen1 < nLen2){
		return -1;
	}

	char ch1;
	char ch2;
	for(int i = 0; i < nLen1; i++){
		ch1 = pszText[1];
		ch2 = pszTarget[1];
		ch1 = (char)tolower(ch1);
		ch2 = (char)tolower(ch2);
		int nCmp = memcmp(&ch1, &ch2, 1);
		if(nCmp){
			return nCmp;
		}
	}
	return 0;
}


//-----------------------------------------------------------------
//�擾

/**
 * @brief ������̒������擾����
 * @return ������̒���
 */
int CDevString::GetLength(){
	string* pStr = (string*)m_pString;
	return pStr->length();
}

/**
 * @brief �S�p���p���ӎ�����GetLength�֐�
 * @return ������̒���
 */
int CDevString::GetTextLength(){
	//���������擾����
	int nLen = 0;
	const unsigned char * pszText = (const unsigned char *)GetBuffer();
	int nMulti;
	int nMultiPos = 0;
	int nChCnt = 0;
	while(GetLength() > nChCnt){
		nMulti = _ismbslead(&pszText[nMultiPos], &pszText[nChCnt]);
		if(nMulti){
			nMultiPos = nChCnt;
		}else{
			nLen++;
		}
		nChCnt++;
	}
	return nLen;
}

/**
 * @brief �������char*�^�Ŏ擾����
 * @attention ReleaseBuffer()�֐��Ŏ擾�����߂�l��������Ă��������B
 * @return ������
 * @see CDevString::ReleaseBuffer()
 */
char* CDevString::GetBuffer(){
	string* pStr = (string*)m_pString;
	if(m_pszChar){
		delete m_pszChar;
		m_pszChar = NULL;
	}
	const char *pszChar = pStr->c_str();
	m_pszChar = new char[pStr->length() + 1];
	memset(m_pszChar, 0, pStr->length() + 1);
	strcpy(m_pszChar, pszChar);
	return m_pszChar;
}

/**
 * G@brief etBuffer�Ŏ擾������������������<BR>
 * ���̊֐��𗘗p���Ȃ��ꍇ�A�����GetBuffer()���f�X�g���N�^�œ����I�ɉ�����܂�
 */
void CDevString::ReleaseBuffer(){
	if(m_pszChar){
		delete m_pszChar;
		m_pszChar = NULL;
	}
}

/**
 * @brief �C�ӂ̈ʒu�̕������擾����
 * @param nIndex �ʒu
 * @return ����
 */
char CDevString::GetAt(int nIndex){
	string* pStr = (string*)m_pString;
	return (*pStr)[nIndex];
}


/**
 * @brief �S�p���p���ӎ�����GetAt�֐�
 * @param nPos �ʒu
 * @param strRet nPos�̈ʒu�ɂ��镶��(OUT)
 * @return �擾�ł����ꍇ�� true�B�����łȂ��ꍇ�� false
 */
bool CDevString::GetTextAt(int nPos, CDevString &strRet){
	//�������擾����
	string* pStr = (string*)m_pString;
	strRet.Empty();
	if(GetTextLength() < nPos){
		return FALSE;
	}

	int nLen = 0;

	//const unsigned char * pszText = (const unsigned char *)(LPCTSTR)m_strText;
	const char* pszText = pStr->c_str();
	int nMulti;
	int nMulti2;
	int nMultiPos = 0;
	int nChCnt = 0;
	bool bPreMulti = FALSE;
	char ch;
	char szBuff[256];
	memset(szBuff, 0, 256);
	int nChPos = 0;
	while(GetLength() > nChCnt){
		nMulti	= _ismbslead((const unsigned char *)&pszText[nMultiPos], (const unsigned char *)&pszText[nChCnt]);
		nMulti2	= _ismbstrail((const unsigned char *)&pszText[nMultiPos], (const unsigned char *)&pszText[nChCnt]);
		ch = GetAt(nChCnt);
		if(nMulti){
			//�J�n
			nMultiPos = nChCnt;
			szBuff[nChPos] = ch;
			nChPos++;
			bPreMulti = TRUE;
		}else if(nMulti2){
			//�I���
			szBuff[nChPos] = ch;
			nChPos++;
//			strRet += ch;
			if(nLen == nPos){
//				strRet += '\0';
				strRet = szBuff;
				return TRUE;
			}
			memset(szBuff, 0, 256);
			strRet.Empty();
			nChPos = 0;
			nLen++;
			bPreMulti = FALSE;
		}else{
			if(bPreMulti){
				szBuff[nChPos] = ch;
				nChPos++;
//				strRet += ch;
			}else{
				if(nLen == nPos){
					strRet = ch;
					return TRUE;
				}
				memset(szBuff, 0, 256);
				strRet.Empty();
				nChPos = 0;
				nLen++;
				bPreMulti = FALSE;
			}
		}
		nChCnt++;
	}
	strRet.Empty();
	return false;
}

/**
 * @brief ����I�y���[�^
 */
CDevString& CDevString::operator=(const char* pszText){
	string* pStr = (string*)m_pString;
	*pStr = pszText;
	return *this;
}

/**
 * @brief ����I�y���[�^
 */
CDevString& CDevString::operator=(const char ch){
	string* pStr = (string*)m_pString;
	*pStr = ch;
	return *this;
}

/**
 * @brief ����I�y���[�^
 */

CDevString& CDevString::operator=(char *pszText){
	string* pStr = (string*)m_pString;
	*pStr = pszText;
	return *this;
}

/**
 * @brief ����I�y���[�^
 */

CDevString& CDevString::operator=(CDevString *strString){
	string* pStr = (string*)m_pString;
	*pStr = strString->GetBuffer();
	return *this;
}

/**
 * @brief ����I�y���[�^
 */

CDevString& CDevString::operator=(CDevString &strString){
	string* pStr = (string*)m_pString;
	*pStr = strString.GetBuffer();
	return *this;
}

/**
 * @brief const char�I�y���[�^
 */
CDevString::operator const char*() const{
	string* pStr = (string*)m_pString;
	return pStr->c_str();
}

/**
 * @brief �z��I�y���[�^
 */
char CDevString::operator[](int nIndex){
	string* pStr = (string*)m_pString;
	return (*pStr)[nIndex];
}

/**
 * @brief ����I�y���[�^
 */
CDevString& CDevString::operator+=(const char* pszText){
	string* pStr = (string*)m_pString;
	pStr->append(pszText);
	return *this;
}

/**
 * @brief ����I�y���[�^
 */
CDevString& CDevString::operator+=(char* pszText){
	string* pStr = (string*)m_pString;
	pStr->append(pszText);
	return *this;
}

/**
 * @brief ����I�y���[�^
 */
CDevString& CDevString::operator+=(char ch){
	string* pStr = (string*)m_pString;
	pStr->append(&ch);
	return *this;
}

/**
 * @brief ����I�y���[�^
 */

CDevString& CDevString::operator+=(CDevString *strString){
	string* pStr = (string*)m_pString;
	pStr->append((const char*)*strString);
	return *this;
}

/**
 * @brief ����I�y���[�^
 */

CDevString& CDevString::operator+=(CDevString &strString){
	string* pStr = (string*)m_pString;
	pStr->append((const char*)strString);
	return *this;
}