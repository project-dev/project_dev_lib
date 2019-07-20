// DevString.cpp: CDevString クラスのインプリメンテーション
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
 * @brief CDevStringの比較オペレーター
 */
bool __stdcall operator==(CDevString &str1, CDevString &str2){
	if(str1.Compare(str2)){
		return false;
	}else{
		return true;
	}
}

/**
 * @brief CDevStringの比較オペレーター
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
 * @brief CDevStringの比較オペレーター
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
 * @brief CDevStringの比較オペレーター
 */
bool __stdcall operator!=(CDevString &str1, CDevString &str2){
	if(str1.Compare(str2)){
		return true;
	}else{
		return false;
	}
}

/**
 * @brief CDevStringの比較オペレーター
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
 * @brief CDevStringの比較オペレーター
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
// 構築/消滅
//////////////////////////////////////////////////////////////////////

/**
 * @brief コンストラクタ
 */
CDevString::CDevString(){
	m_pszChar = NULL;
	m_pString = (void*)new string;
}

/**
 * @brief コピーコンストラクタ
 *
 * @param strString コピーするCDevString
 */
CDevString::CDevString(CDevString &strString){
	m_pszChar = NULL;
	m_pString = (void*)new string;
	string* pStr = (string*)m_pString;
	*pStr = strString;
}

/**
 * @brief コピーコンストラクタ
 *
 * @param pszText コピーする文字列
 */
CDevString::CDevString(const char* pszText){
	m_pszChar = NULL;
	m_pString = (void*)new string;
	string* pStr = (string*)m_pString;
	*pStr = pszText;
}

/**
 * @brief コピーコンストラクタ
 *
 * @param pszText コピーする文字列
 */
CDevString::CDevString(char* pszText){
	m_pszChar = NULL;
	m_pString = (void*)new string;
	string* pStr = (string*)m_pString;
	*pStr = pszText;
}

/**
 * @brief デストラクタ
 */
CDevString::~CDevString(){
	if(m_pszChar){
		delete m_pszChar;
		m_pszChar = NULL;
	}
	if(m_pString){
		OutputDebugString("■■■■■m_pString release■■■■■\n");
		delete m_pString;
		m_pString = NULL;
	}

}

//-----------------------------------------------------------------
//文字列操作

/**
 * @brief 左からnLen文字取得する
 *
 * @param nLen 取得文字数
 * @return 抜き出した文字列
 */
CDevString CDevString::Left(int nLen) const{
	CDevString strReturn = "";
	string* pStr = (string*)m_pString;
	strReturn = pStr->substr(0, nLen).c_str();
	return strReturn;
}

/**
 * @brief 右からnLen文字取得する
 * @param nLen 取得文字数
 * @return 抜き出した文字列
 */
CDevString CDevString::Right(int nLen) const{
	CDevString strReturn = "";
	string* pStr = (string*)m_pString;
	strReturn = pStr->substr(pStr->length() - nLen, nLen).c_str();
	return strReturn;
}

/**
 * @brief nPosから後ろの文字取得する
 * @param nPos 開始位置
 * @return 抜き出した文字列
 */
CDevString CDevString::Mid(int nPos) const{
	CDevString strReturn = "";
	string* pStr = (string*)m_pString;
	strReturn = pStr->substr(nPos).c_str();
	return strReturn;
}

/**
 * @brief nStartからnLenまでの範囲の文字列を取得する
 * @param nStart 開始位置
 * @param nLen 長さ。-1の場合は末尾まで
 * @return 抜き出した文字列
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
 * @brief 全角と半角を意識したLeft関数
 * @param nLen 取得文字数
 * @return 抜き出した文字列
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
 * @brief 全角と半角を意識したRight関数
 * @param nLen 取得文字数
 * @return 抜き出した文字列
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
 * @brief 全角と半角を意識したMid関数
 * @param nFirst 開始位置
 * @return 抜き出した文字列
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
 * @brief 全角と半角を意識したSubString関数
 * @param nFirst 開始位置
 * @param nLen 長さ
 * @return 抜き出した文字列
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
 * @brief 文字列の左右の半角空白を除去する
 */
void CDevString::Trim(){
	TrimLeft();
	TrimRight();
}

/**
 * @brief 文字列の左の半角空白を除去する
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
 * @brief 文字列の右の半角空白を除去する
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
 * @brief 文字列を空にする
 */
void CDevString::Empty(){
	string* pStr = (string*)m_pString;
	pStr->empty();
}

/**
 * @brief 文字列が空かどうかのチェック
 */
bool CDevString::IsEmpty(){
	string* pStr = (string*)m_pString;
	return pStr->length() == 0 ? true : false;
}

/**
 * @brief 任意の位置に文字を設定する
 * @param nIndex 位置
 * @param ch セットする文字
 */
void CDevString::SetAt(int nIndex, char ch){
	string* pStr = (string*)m_pString;
	(*pStr)[nIndex] = ch;
}
	

//-----------------------------------------------------------------
//検索/置換

/**
 * @brief 文字列を検索する
 * @param pszFind 検索文字列
 * @param nStart 検索開始位置。
 * @return 出現位置。見つからない場合は-1
 */
int CDevString::Find(char* pszFind, int nStart /* = 0*/){
	string* pStr = (string*)m_pString;
	return pStr->find(pszFind, nStart);
}

/**
 * @brief 文字列を検索する
 * @param pszFind 検索文字列
 * @param nStart 検索開始位置。
 * @return 出現位置。見つからない場合は-1
 */
int CDevString::Find(const char* pszFind, int nStart /* = 0*/){
	string* pStr = (string*)m_pString;
	return pStr->find(pszFind, nStart);
}

/**
 * @brief 文字列を検索する
 * @param strFind 検索文字列
 * @param nStart 検索開始位置。
 * @return 出現位置。見つからない場合は-1
 */
int CDevString::Find(CDevString &strFind, int nStart /* = 0*/){
	string* pStr = (string*)m_pString;
	return pStr->find(strFind, nStart);
}

/**
 * @brief 全角半角を意識したFind関数
 * @param pszFind 検索文字列
 * @param nStart 検索開始位置。
 * @return 出現位置。見つからない場合は-1
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
 * @brief 全角半角を意識したFind関数
 * @param pszFind 検索文字列
 * @param nStart 検索開始位置。
 * @return 出現位置。見つからない場合は-1
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
 * @brief 全角半角を意識したFind関数
 * @param strFind 検索文字列
 * @param nStart 検索開始位置。
 * @return 出現位置。見つからない場合は-1
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
 * @brief 文字列を末尾から検索する
 * @param pszFind 検索文字列
 * @return 出現位置。見つからない場合は-1
 */
int CDevString::ReverseFind(char* pszFind){
	string* pStr = (string*)m_pString;
	return pStr->rfind(pszFind);
}

/**
 * @brief 文字列を末尾から検索する
 * @param pszFind 検索文字列
 * @return 出現位置。見つからない場合は-1
 */
int CDevString::ReverseFind(const char* pszFind){
	string* pStr = (string*)m_pString;
	return pStr->rfind(pszFind);
}

/**
 * @brief 文字列を末尾から検索する
 * @param strFind 検索文字列
 * @return 出現位置。見つからない場合は-1
 */
int CDevString::ReverseFind(CDevString &strFind){
	string* pStr = (string*)m_pString;
	return pStr->rfind(strFind);
}

/**
 * @brief 全角半角を意識したReverseFind関数
 * @param pszFind 検索文字列
 * @return 出現位置。見つからない場合は-1
 */
int CDevString::ReverseFindText(char* pszFind){
	CDevString strFind = pszFind;
	return ReverseFindText(pszFind);
}

/**
 * @brief 全角半角を意識したReverseFind関数
 * @param pszFind 検索文字列
 * @return 出現位置。見つからない場合は-1
 */
int CDevString::ReverseFindText(const char* pszFind){
	CDevString strFind = pszFind;
	return ReverseFindText(pszFind);
}

/**
 * @brief 全角半角を意識したReverseFind関数
 * @param strFind 検索文字列
 * @return 出現位置。見つからない場合は-1
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
 * @brief 最初に一致する文字列を置き換える
 * @param pszNew 置き換え対象文字列
 * @param pszOld 置き換える文字列
 * @return 置き換えた文字数。置き換えが発生しなかった場合は0
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
 * @brief 一致する文字列をすべて置き換える
 * @param pszNew 置き換え対象文字列
 * @param pszOld 置き換える文字列
 * @return 置き換えた文字数。置き換えが発生しなかった場合は0
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
 * @brief 全角半角を意識したReplace関数
 * @param pszNew 置き換え対象文字列
 * @param pszOld 置き換える文字列
 * @return 置き換えた文字数。置き換えが発生しなかった場合は0
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
 * @brief 全角半角を意識したReplaceAll関数
 * @param pszNew 置き換え対象文字列
 * @param pszOld 置き換える文字列
 * @return 置き換えた文字数。置き換えが発生しなかった場合は0
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
//比較

/**
 * @brief 文字列を比較する
 * @param pszTarget 比較する文字
 * @return -1 pszTargetが小さい場合<br>0 同じ<br>1 pszTargetが大きい場合
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
 * @brief 文字列を大文字小文字を区別せず比較する
 * @param pszTarget 比較する文字
 * @return -1 pszTargetが小さい場合<br>0 同じ<br>1 pszTargetが大きい場合
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
//取得

/**
 * @brief 文字列の長さを取得する
 * @return 文字列の長さ
 */
int CDevString::GetLength(){
	string* pStr = (string*)m_pString;
	return pStr->length();
}

/**
 * @brief 全角半角を意識したGetLength関数
 * @return 文字列の長さ
 */
int CDevString::GetTextLength(){
	//文字数を取得する
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
 * @brief 文字列をchar*型で取得する
 * @attention ReleaseBuffer()関数で取得した戻り値を解放してください。
 * @return 文字列
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
 * G@brief etBufferで取得した文字列を解放する<BR>
 * この関数を利用しない場合、次回のGetBuffer()かデストラクタで内部的に解放します
 */
void CDevString::ReleaseBuffer(){
	if(m_pszChar){
		delete m_pszChar;
		m_pszChar = NULL;
	}
}

/**
 * @brief 任意の位置の文字を取得する
 * @param nIndex 位置
 * @return 文字
 */
char CDevString::GetAt(int nIndex){
	string* pStr = (string*)m_pString;
	return (*pStr)[nIndex];
}


/**
 * @brief 全角半角を意識したGetAt関数
 * @param nPos 位置
 * @param strRet nPosの位置にある文字(OUT)
 * @return 取得できた場合は true。そうでない場合は false
 */
bool CDevString::GetTextAt(int nPos, CDevString &strRet){
	//文字を取得する
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
			//開始
			nMultiPos = nChCnt;
			szBuff[nChPos] = ch;
			nChPos++;
			bPreMulti = TRUE;
		}else if(nMulti2){
			//終わり
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
 * @brief 代入オペレータ
 */
CDevString& CDevString::operator=(const char* pszText){
	string* pStr = (string*)m_pString;
	*pStr = pszText;
	return *this;
}

/**
 * @brief 代入オペレータ
 */
CDevString& CDevString::operator=(const char ch){
	string* pStr = (string*)m_pString;
	*pStr = ch;
	return *this;
}

/**
 * @brief 代入オペレータ
 */

CDevString& CDevString::operator=(char *pszText){
	string* pStr = (string*)m_pString;
	*pStr = pszText;
	return *this;
}

/**
 * @brief 代入オペレータ
 */

CDevString& CDevString::operator=(CDevString *strString){
	string* pStr = (string*)m_pString;
	*pStr = strString->GetBuffer();
	return *this;
}

/**
 * @brief 代入オペレータ
 */

CDevString& CDevString::operator=(CDevString &strString){
	string* pStr = (string*)m_pString;
	*pStr = strString.GetBuffer();
	return *this;
}

/**
 * @brief const charオペレータ
 */
CDevString::operator const char*() const{
	string* pStr = (string*)m_pString;
	return pStr->c_str();
}

/**
 * @brief 配列オペレータ
 */
char CDevString::operator[](int nIndex){
	string* pStr = (string*)m_pString;
	return (*pStr)[nIndex];
}

/**
 * @brief 代入オペレータ
 */
CDevString& CDevString::operator+=(const char* pszText){
	string* pStr = (string*)m_pString;
	pStr->append(pszText);
	return *this;
}

/**
 * @brief 代入オペレータ
 */
CDevString& CDevString::operator+=(char* pszText){
	string* pStr = (string*)m_pString;
	pStr->append(pszText);
	return *this;
}

/**
 * @brief 代入オペレータ
 */
CDevString& CDevString::operator+=(char ch){
	string* pStr = (string*)m_pString;
	pStr->append(&ch);
	return *this;
}

/**
 * @brief 代入オペレータ
 */

CDevString& CDevString::operator+=(CDevString *strString){
	string* pStr = (string*)m_pString;
	pStr->append((const char*)*strString);
	return *this;
}

/**
 * @brief 代入オペレータ
 */

CDevString& CDevString::operator+=(CDevString &strString){
	string* pStr = (string*)m_pString;
	pStr->append((const char*)strString);
	return *this;
}