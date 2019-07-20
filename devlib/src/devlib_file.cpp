
#include "stdafx.h"
#include "devlib.h"
#include <string>
#include <vector>
#include "DevString.h"
using namespace std;

/**
 * @brief Iniファイルの1セクションを取得する
 *
 * @param strSecsion セクション名
 * @param strBuff    iniファイルのデータを保持するstringクラス
 * @param strReturn  取得したセクションを格納するstringクラス
 * @return 取得に成功すればTRUE
 */
BOOL GetSection(string &strSecsion, string &strBuff, string &strReturn){
	//セクションを取得する
	int nStart = strBuff.find(strSecsion);
	if(nStart == -1){
		return FALSE;
	}

	LPCTSTR pszSep = "[";
	int nLen = nStart + strSecsion.size();

	//セクションが1つのときに末尾がマルチバイトの場合
	//string.find(strSep, nLen)
	//だと、値が変になる(nEndが-1にならない)
	int nEnd = strBuff.find(pszSep, nLen, strSecsion.size());
	nLen = nEnd - nStart;

	if((nLen <= 0) && (nEnd > -1)){
		return FALSE;
	}
	
	if(nEnd != -1){
		strReturn = strBuff.substr(nStart, nLen);
	}else{
		strReturn = strBuff.substr(nStart, -1);
	}
	return TRUE;
}

/**
 * @brief 末尾に\を追加する。
 *
 * 引数は\を加えることを考慮して長さを+1しておく必要がある。
 * @param pszDir \を追加するパス
 * @return なし
 */
void WINAPI AddDirLastSepalator(char *pszDir){
	string strDir = pszDir;
	int nLen = strDir.length() - 1;
	const char *pszCh = strDir.substr(nLen-1).c_str();
	if(pszCh[0] != '\\'){
		strDir += "\\";
	}
	const char *pszAddDir = strDir.c_str();
	strcpy(pszDir, pszAddDir);
}


/**
 * @brief ディレクトリを作成する
 *
 * @param lpPathName           作成するパス
 * @param lpSecurityAttributes LPSECURITY_ATTRIBUTES
 * @return 作成に成功すればTRUE
*/
BOOL WINAPI CreateDir(LPCTSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes){
#if 1
	int nLen = strlen(lpPathName);
	char* pszDir = new char[nLen + 1];
	memset(pszDir, 0, nLen + 1);
	LPCTSTR pFind = lpPathName;

	int nEnd = 0;
	int nFirst = 1;
	while(!nEnd){
		pFind = strchr(pFind, '\\');
		if(pFind){
			int nLen = pFind - lpPathName;
			strncpy(pszDir, lpPathName, nLen);
			pFind++;
			if(nLen == strlen(lpPathName)){
				nEnd = 1;
			}
		}else{
			strcpy(pszDir, lpPathName);
			nEnd = 1;
		}
		if(nFirst == 1){
			//初回はドライブのはずなので無視
			nFirst = 0;
			continue;
		}

		WIN32_FIND_DATA wfd;
		HANDLE hRet;
		hRet = ::FindFirstFile(pszDir, &wfd);
		if(hRet == INVALID_HANDLE_VALUE){
			//フォルダ生成
			if(!::CreateDirectory(pszDir, lpSecurityAttributes)){
				delete pszDir;
				return FALSE;
			}
		}else{
			::FindClose(hRet);
			if(!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){
				if(!::CreateDirectory(pszDir, lpSecurityAttributes)){
					delete pszDir;
					return FALSE;
				}
			}
		}
	}
	delete pszDir;
#else
	CDevString strPath = lpPathName;
	int nPos;
//	do{
		nPos = strPath.FindText("\\\\");
		if(nPos != -1){
			strPath.ReplaceAllText("\\", "\\\\");
		}
//	}while(nPos != -1);

	CDevString strDir;
	vector<string> arrDirs;

	//パスの分解
	int pos = 0;
	int nLen;
	LPCTSTR pszText = NULL;
	while((pos != -1) && strPath.GetLength()){
		pos = strPath.FindText("\\");
		if(pos == -1){
			pszText = strPath;
			arrDirs.push_back(pszText);
			break;
		}
		
		strDir = strPath.LeftText(pos);
//		strDir = strPath.SubStringText(0, pos);
		pszText = strDir;
		arrDirs.push_back(pszText);
		int nLen = strPath.GetTextLength();
		strPath = strPath.RightText(nLen - pos - 1);
//		strPath = strPath.SubStringText(pos + 1);
	}

	//パスを確認しながらディレクトリを作成していく
	nLen = arrDirs.size();
	strPath = "";
	WIN32_FIND_DATA wfd;
	HANDLE hRet;
	string strPathText = "";
	for(int i = 0; i < nLen; i++){
		if(i == 0){
			strPathText = arrDirs.at(i);
			strPath = strPathText.c_str();
			continue;
		}else{
			strPathText = arrDirs.at(i);
			strPath += "\\";
			strPath += strPathText.c_str();
		}
		hRet = ::FindFirstFile(strPath, &wfd);
		if(hRet == INVALID_HANDLE_VALUE){
			//フォルダ生成
			if(!::CreateDirectory(strPath, lpSecurityAttributes)){
				return FALSE;
			}
		}else{
			::FindClose(hRet);
			if(!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){
				if(!::CreateDirectory(strPath, lpSecurityAttributes)){
					return FALSE;
				}
			}
		}
	}
#endif
	return TRUE;
}

/**
 * @brief ファイルを削除する
 *
 * @param pszFileName 削除するファイルのパス
 * @return 削除に成功すればTRUE
 */
BOOL WINAPI DeleteFileEx(LPCTSTR pszFileName){
	if(!IsFileExsist(pszFileName)){
		//存在しない場合は終了
		return TRUE;
	}

	BOOL bRet = ::DeleteFile(pszFileName);
	if(!bRet){
		Sleep(1000);	//少し待って再挑戦
		bRet = ::DeleteFile(pszFileName);
	
	}
	return bRet;
}

/**
 * @brief ファイルの存在チェック
 *
 * @param pszFileName チェックするファイルのパス
 * @return 存在していればTRUE
 */
BOOL WINAPI IsFileExsist(LPCTSTR pszFileName){
	WIN32_FIND_DATA wfd;
	HANDLE hRet = ::FindFirstFile(pszFileName, &wfd);
	if(hRet == INVALID_HANDLE_VALUE){
		return FALSE;		
	}
	::FindClose(hRet);
	return TRUE;
}

/**
 * @brief ディレクトリかどうかの確認
 *
 * @param pszFileName 確認するパス
 * @return ディレクトリであればTRUE
 */
BOOL WINAPI IsDir(LPCTSTR pszFileName){
	WIN32_FIND_DATA wfd;
	HANDLE hRet = ::FindFirstFile(pszFileName, &wfd);
	if(hRet == INVALID_HANDLE_VALUE){
		return FALSE;		
	}
	::FindClose(hRet);

	if((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY){
		return TRUE;
	}
	return FALSE;
}

/**
 * @brief ファイルを削除する
 *
 * @param lpDir        削除するパス
 * @param bChildDelete lpDirに子階層が存在する場合に子階層も削除する場合はTRUE
 * @return 削除に成功すればTRUE
 */
BOOL WINAPI RemoveDirectoryEx(LPCTSTR lpDir, BOOL bChildDelete){
	if(!IsFileExsist(lpDir)){
		return FALSE;		
	}

	if(!bChildDelete){
		return ::RemoveDirectory(lpDir);
	}

	//子階層をたどって消していく
	string strPath = lpDir;
	string strChildPath = lpDir;
	string strFindPath = "";
	strFindPath = strPath + "\\*";
	WIN32_FIND_DATA wfd;
	HANDLE hRet = NULL;
	BOOL bFirst = TRUE;
#if 0
	vector< string > arrSubDir;
	while(true){
		if(bFirst){
			hRet = ::FindFirstFile(strFindPath.data(), &wfd);
			bFirst = FALSE;
			if(hRet == INVALID_HANDLE_VALUE){
				break;
			}
		}else{
			if(!::FindNextFile(hRet, &wfd)){
				break;
			}

//			if(GetLastError() == ERROR_NO_MORE_FILES ){
//				break;
//			}
		}
		if((strcmp(wfd.cFileName, "." ) != 0) &&
		   (strcmp(wfd.cFileName, "..") != 0)){
			strChildPath = strPath + '\\' + wfd.cFileName;
			//strChildPath.Format("%s\\%s", lpDir, wfd.cFileName);
			if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
				//子階層をたどる
/*				
				BOOL bRet = ::RemoveDirectoryEx(strChildPath.data(), bChildDelete);
				if(!bRet){
//					DWORD dwError = GetLastError();
					::FindClose(hRet);
					return FALSE;
				}
*/
				arrSubDir.push_back(strChildPath);
			}else if(!::DeleteFile(strChildPath.data())){
//				DWORD dwError = GetLastError();
				::FindClose(hRet);
				return FALSE;
			}
		}
	}
	::FindClose(hRet);


	//サブディレクトリの削除
	int nSize = arrSubDir.size();
	for(int i = 0; i < nSize; i++){
		string strDir = arrSubDir[i];
		BOOL bRet = ::RemoveDirectoryEx(strDir.data(), bChildDelete);
		if(!bRet){
//			DWORD dwError = GetLastError();
			return FALSE;
		}
	}

	if(IsFileExsist(lpDir)){
		if(!::RemoveDirectory(lpDir)){
			DWORD dwError = GetLastError();
			return FALSE;
		}
	}

#else
	while(true){
		if(bFirst){
			hRet = ::FindFirstFile(strFindPath.data(), &wfd);
			bFirst = FALSE;
			if(hRet == INVALID_HANDLE_VALUE){
				break;
			}
		}else{
			if(!::FindNextFile(hRet, &wfd)){
				break;
			}

//			if(GetLastError() == ERROR_NO_MORE_FILES ){
//				break;
//			}
		}
		if((strcmp(wfd.cFileName, "." ) != 0) &&
		   (strcmp(wfd.cFileName, "..") != 0)){
			strChildPath = strPath + '\\' + wfd.cFileName;
			//strChildPath.Format("%s\\%s", lpDir, wfd.cFileName);
			if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
				//子階層をたどる
				
				BOOL bRet = ::RemoveDirectoryEx(strChildPath.data(), bChildDelete);
				if(!bRet){
//					DWORD dwError = GetLastError();
					::FindClose(hRet);
					return FALSE;
				}
			}else if(!::DeleteFile(strChildPath.data())){
//				DWORD dwError = GetLastError();
				::FindClose(hRet);
				return FALSE;
			}
		}
	}
	::FindClose(hRet);
	if(IsFileExsist(lpDir)){
		if(!::RemoveDirectory(lpDir)){
			DWORD dwError = GetLastError();
			return FALSE;
		}
	}
#endif
	return TRUE;

}

/**
 * @brief iniファイルから文字列を読み込む
 *
 * Windows APIのGetPrivateProfileStringのように扱える
 * @param lpAppName        セクション名
 * @param lpKeyName        キー名
 * @param lpDefault        デフォルト値
 * @param lpRetValue       値の格納用引数
 * @param nLen             lpRetValueの長さ
 * @param lpFileName       iniファイル名
 * @return 取得に成功すればその取得したデータの長さを返す。失敗した場合は0
 */
DWORD WINAPI GetInifileString( const char* lpAppName,
							   const char* lpKeyName,
							   const char* lpDefault,
							   char*	   lpRetValue,
							   int			nLen,
							   const char* lpFileName){
	if(!::IsFileExsist(lpFileName)){
		strcpy(lpRetValue, lpDefault);
		return strlen(lpDefault);
	}

	FILE *f = NULL;
	string strApp = "[";
	strApp += lpAppName;
	strApp += "]";
	string strKey = lpKeyName;
	strKey += "=";

	if(!strlen(lpAppName) || !strlen(lpKeyName)){
		strcpy(lpRetValue, lpDefault);
		return strlen(lpDefault);
	}
	
	try{
		string strbuff = "";

		f = fopen(lpFileName, "rt");
		if(!f){
			//オープン失敗
			if(lpRetValue){
				strcpy(lpRetValue, lpDefault);
				return strlen(lpDefault);
			}
			return 0;
		}

		//ファイルサイズ取得
		if(fseek(f, 0, SEEK_END)){
			//失敗
			if(lpRetValue){
				strcpy(lpRetValue, lpDefault);
				return strlen(lpDefault);
			}
			return 0;
		}

		long lSize = ftell(f);

		//ファイル読み込み
		if(fseek(f, 0, SEEK_SET)){
			//失敗
			if(lpRetValue){
				strcpy(lpRetValue, lpDefault);
				return strlen(lpDefault);
			}
			return 0;
		}
		char *pBuff = new char[lSize + 1];
		memset(pBuff, 0, lSize+1);
		fread(pBuff, sizeof(char), lSize, f);
		strbuff = pBuff;
		delete pBuff;
		fclose(f);

		int nSize = strbuff.size();

		if(!nSize){
			return 0;
		}

		GetSection(strApp, strbuff, strbuff);

		//セクションの検索
		int nSecPos = strbuff.find_first_of(strApp);
		if(nSecPos == -1){
			memset(lpRetValue, 0, strlen(lpRetValue));
			return 0;
		}

		//キーの検索
		int nKeyPos = strbuff.find(strKey, nSecPos);
		if(nKeyPos == -1){
			if((lpRetValue) && (lpDefault)){
				strcpy(lpRetValue, lpDefault);
				return strlen(lpRetValue);
			}if(lpRetValue){
				strcpy(lpRetValue, "");
			}
			return 0;
		}
		
		//値を取得
		int nPos = nKeyPos + strKey.length();
		int nEnd = strbuff.find_first_of("\n", nPos);
		string strValue = "";
		if(nEnd == -1){
			//行末とみなして処理する
			int nMax = strbuff.length();
			strValue = strbuff.substr(nPos, nMax);
		}else{
			strValue = strbuff.substr(nPos, nEnd - nPos);
		}

		if(lpRetValue){
			strcpy(lpRetValue, strValue.c_str());
			nSize = strValue.length();
		}
		return nSize;
	
	}catch(void* e){
		if(f){
			fclose(f);
		}
		delete e;
	}

	if(lpRetValue){
		strcpy(lpRetValue, lpDefault);
		return strlen(lpRetValue);
	}
	return 0;
}


/**
 * @brief iniファイルから整数値を取得する
 *
 * Windows APIのGetPrivateProfileIntのように扱える
 * @param lpAppName        セクション名
 * @param lpKeyName        キー名
 * @param nDefault         デフォルト値
 * @param lpFileName       iniファイル名
 * @return 取得に成功すればその取得したデータを返す。失敗した場合はデフォルトを返す
 */
int WINAPI GetInifileInt(	const char* lpAppName,
							const char* lpKeyName,
							int          nDefault,
							const char* lpFileName){
	if(!::IsFileExsist(lpFileName)){
		return nDefault;
	}

	DWORD dwLen = ::GetInifileString(lpAppName, lpKeyName, NULL, NULL, 0, lpFileName);
	if(!dwLen){
		return nDefault;
	}
	
	char *pszBuff = new char[dwLen];
	dwLen = ::GetInifileString(lpAppName, lpKeyName, NULL, pszBuff, dwLen, lpFileName);

	int nRet = nDefault;
	if(dwLen){
		nRet = atoi(pszBuff);
	}
	delete pszBuff;
	return nRet;
}

/**
 * @brief iniファイルに文字列を書き込む
 *
 * Windows APIのWritePrivateProfileStringのように扱える
 * 文字列の長さの制限は無い。
 * @param lpAppName        セクション名
 * @param lpKeyName        キー名
 * @param lpString         書き込む値
 * @param lpFileName       iniファイル名
 * @return 取得に成功すればTRUEを返す。
 */
BOOL WINAPI WriteInifileString(const char* lpAppName,
								const char* lpKeyName,
								const char* lpString,
								const char* lpFileName ){
#if 0
	CDevString strApp = "";
	strApp = "[";
	strApp += lpAppName;
	strApp += "]";

	CDevString strKey = "";
	strKey = "\n";
	strKey += lpKeyName;
	strKey += "=";
	CDevString strValue = lpString;

	FILE *f = NULL;
	try{
		CDevString strBlock = "";
		CDevString strOldBlock = "";
		CDevString strbuff = "";

		//テキストモードでのオープン
		f = fopen(lpFileName, "rt");
		if(f){

			//ファイルサイズの取得
			if(fseek(f, 0, SEEK_END)){
				//失敗
				return FALSE;
			}

			long lLen = ftell(f);

			//ファイルの先頭に移動
			if(fseek(f, 0, SEEK_SET)){
				return FALSE;
			}
			char *pBuff = new char[lLen + 1];
			memset(pBuff, 0, lLen+1);
			fread(pBuff, sizeof(char), lLen, f);
			strbuff = pBuff;
			delete pBuff;
			fclose(f);

			string strAppStr = strApp;
			string strBuffStr = strbuff;
			string strBlockStr = strBlock;
			GetSection(strAppStr, strBuffStr, strBlockStr);
			strOldBlock = strBlockStr.c_str();
		}

		//セクションの検索
		int nPos = strBlock.Find(strApp);
		if(nPos == -1){
			//末尾にセクションを追加
			if(strbuff.GetLength()){
				strbuff += "\r\n";
			}
			strbuff += strApp;
			strbuff += strKey;
			strbuff += strValue;
		}else{
			//キーの検索
			int nLen = strBlock.GetLength();
			nPos = strBlock.Find(strKey, nPos);
			if(nPos == -1){
				strBlock += strKey;
				strBlock += strValue;
			}else if(nPos == nLen){
				strBlock += strKey;
				strBlock += strValue;
			}else{
				//値を取得
				nPos += strKey.GetLength();
				int nEnd = strBlock.Find("\n", nPos);
				CDevString strOldValue = "";
				if(nLen < nPos){
					return FALSE;
				}else{
					if(nEnd <= -1){
						//行末とみなして処理する
						int nMax = strBlock.GetLength();
						strOldValue = strBlock.SubString(nPos, nMax);
					}else{
						strOldValue = strBlock.SubString(nPos, nEnd - nPos);
					}
					strBlock.Replace(strValue, strOldValue);
				}
			}

			nPos = strbuff.Find(strOldBlock);
			if(nPos != -1){
				strbuff.Replace(strBlock, strOldBlock);
			}else{
				strbuff += strBlock;
			}
		}
	
		//書き込む
		f = fopen(lpFileName, "w+t");
		if(!f){
			return FALSE;
		}
		const char *pszBuff = strbuff.GetBuffer();
		int nLen = strlen(pszBuff);
		fwrite(pszBuff, sizeof(char), nLen, f);
		fflush(f);
		fclose(f);
		return TRUE;
	
	}catch(void *pe){
		delete pe;
		fclose(f);
	}
#else
	string strApp = "";
	strApp.append("[");
	strApp.append(lpAppName);
	strApp.append("]");

	string strKey = "";
	strKey.append("\n");
	strKey.append(lpKeyName);
	strKey.append("=");
	string strValue = lpString;

    //Iniファイル的に問題のある文字列を%xxに変更する

	FILE *f = NULL;
	try{
		string strBlock = "";
		string strOldBlock = "";
		string strbuff = "";

		//テキストモードでのオープン
		f = fopen(lpFileName, "rt");
		if(f){

			//ファイルサイズの取得
			if(fseek(f, 0, SEEK_END)){
				//失敗
				return FALSE;
			}

			long lLen = ftell(f);

			//ファイルの先頭に移動
			if(fseek(f, 0, SEEK_SET)){
				return FALSE;
			}
			char *pBuff = new char[lLen + 1];
			memset(pBuff, 0, lLen+1);
			fread(pBuff, sizeof(char), lLen, f);
			strbuff = pBuff;
			delete pBuff;
			fclose(f);

			GetSection(strApp, strbuff, strBlock);
			strOldBlock = strBlock;
		}

		//セクションの検索
		int nPos = strBlock.find_first_of(strApp);
		if(nPos == -1){
			//末尾にセクションを追加
			if(strbuff.length()){
				strbuff.append("\r\n");
			}
			strbuff.append(strApp);
			strbuff.append(strKey);
			strbuff.append(strValue);
		}else{
			//キーの検索
			int nLen = strBlock.length();
			nPos = strBlock.find(strKey, nPos);
			if(nPos == -1){
				strBlock.append(strKey);
				strBlock.append(strValue);
			}else if(nPos == nLen){
				strBlock.append(strKey);
				strBlock.append(strValue);
			}else{
				//値を取得
				nPos += strKey.length();
				int nEnd = strBlock.find_first_of("\n", nPos);
				string strOldValue = "";
				if(nLen < nPos){
					return FALSE;
				}else{
					if(nEnd <= -1){
						//行末とみなして処理する
						int nMax = strBlock.length();
						strOldValue = strBlock.substr(nPos, nMax);
					}else{
						strOldValue = strBlock.substr(nPos, nEnd - nPos);
					}
					strBlock.replace(nPos, strOldValue.length(), strValue);
				}
			}

			nPos = strbuff.find(strOldBlock);
			if(nPos != -1){
				strbuff.replace(nPos, strOldBlock.length(), strBlock);
			}else{
				strbuff.append(strBlock);
			}
		}
	
		//書き込む
		f = fopen(lpFileName, "w+t");
		if(!f){
			return FALSE;
		}
		const char *pszBuff = strbuff.c_str();
		int nLen = strlen(pszBuff);
		fwrite(pszBuff, sizeof(char), nLen, f);
		fflush(f);
		fclose(f);
		return TRUE;
	
	}catch(void *pe){
		delete pe;
		fclose(f);
	}
#endif
	return FALSE;
}

/**
 * @brief iniファイルに整数値を書き込む
 *
 * Windows APIのWritePrivateProfileStringのように扱える
 * @param lpAppName        セクション名
 * @param lpKeyName        キー名
 * @param nValue           書き込む値
 * @param lpFileName       iniファイル名
 * @return 取得に成功すればTRUEを返す。
 */
BOOL WINAPI WriteInifileInt(const char* lpAppName,
							const char* lpKeyName,
							int         nValue,
							const char* lpFileName ){
	char szBuff[256];
	memset(szBuff, 0, 256);
	itoa(nValue, szBuff, 10);
	return WriteInifileString(lpAppName, lpKeyName, szBuff, lpFileName );
}

/**
 * @brief ファイルを列挙する。
 *
 * ただ単に、FindFirstFileとFindNextFileを呼び出すだけ<BR>
 * EnumWindowsのファイル版
 * <ul>
 * <li>EnumFilesProcの引数の解説</li>
 *   <ul>
 *   <li>第1引数 EnumFilesの第2引数と同じ</li>
 *   <li>第2引数 WIN32_FIND_DATAのポインタ</li>
 *   <li>第3引数 EnumFilesの第3引数と同じ</li>
 *   </ul>
 * <li>EnumFilesProcの戻り値の解説</li>
 *   <ul>
 *   <li>検索を続ける場合はTRUE,中止する場合はFALSEを返す</li>
 *   </ul>
 * </ul>
 * @param EnumFilesProc     コールバック関数
 * @param strFileName       検索するファイル名
 * @param lParam			  データ
 * @return 取得に成功すればTRUEを返す。取得に失敗した場合はFALSEを返す
 * FindFirstFileでINVALID_HANDLE_VALUEが返ってきてもFALSEを返します)
 */
BOOL WINAPI EnumFiles(EnumFilesProcFunc EnumFilesProc, const char* strFileName, LPARAM lParam){
	WIN32_FIND_DATA wfd;
	HANDLE hRet = NULL;
	BOOL bFirst = TRUE;
	memset(&wfd, 0, sizeof(WIN32_FIND_DATA));
	while(TRUE){
		if(bFirst){
			bFirst = FALSE;
			hRet = ::FindFirstFile(strFileName, &wfd);
			if(hRet == INVALID_HANDLE_VALUE){
				return FALSE;
			}

		}else{
			if(!::FindNextFile(hRet, &wfd)){
				break;
			}
		}

		if(!EnumFilesProc(strFileName, &wfd, lParam)){
			::FindClose(hRet);
			return FALSE;
		}
	}
	::FindClose(hRet);
	return TRUE;
}

bool WINAPI GetFileVerInfo(HMODULE hMod, PFILEVERSION pfv){
	if(!pfv){
		return false;
	}

	memset(pfv, 0, sizeof(FILEVERSION));

	if(!hMod){
		return false;
	}

	char szFileName[MAX_PATH];
	DWORD dwSize = 0;
	DWORD dwHandle = 0;
	
	memset(szFileName, 0, MAX_PATH);
	::GetModuleFileName(hMod, szFileName, MAX_PATH);
	dwSize = ::GetFileVersionInfoSize(szFileName, &dwHandle);
	
	if(!dwSize){
		return false;
	}
	
	char *pszInfo = new char[dwSize + 1];
	
	if(!pszInfo){
		return false;
	}
	
	BOOL bRet = ::GetFileVersionInfo(szFileName, 0, dwSize, pszInfo);
	if(!bRet){
		delete pszInfo;
		return false;
	}

	DWORD *dwLang;
	UINT uLen;
	bRet = ::VerQueryValue(pszInfo, "\\VarFileInfo\\Translation", (void**)&dwLang, &uLen);
	if(!bRet){
		delete pszInfo;
		return false;
	}
	char lpLang[9];
	sprintf(lpLang, "%04x%04x", LOWORD(*dwLang), HIWORD(*dwLang));

	char *pszFileVer;
	char *pszProdVer;
	char *pszPrivVer;
	char *pszSpecVer;
	UINT uFileLen;
	UINT uProdLen;
	UINT uPrivLen;
	UINT uSpecLen;

	char szSubBlock[MAX_PATH];
	sprintf(szSubBlock, "\\StringFileInfo\\%s\\FileVersion", lpLang);
	bRet = ::VerQueryValue(pszInfo, szSubBlock, (void**)&pszFileVer, &uFileLen);
	if(!bRet){
		pszFileVer = NULL;
	}

	sprintf(szSubBlock, "\\StringFileInfo\\%s\\ProductVersion", lpLang);
	bRet = ::VerQueryValue(pszInfo, szSubBlock, (void**)&pszProdVer, &uProdLen);
	if(!bRet){
		pszProdVer = NULL;
	}

	sprintf(szSubBlock, "\\StringFileInfo\\%s\\PrivateBuild", lpLang);
	bRet = ::VerQueryValue(pszInfo, szSubBlock, (void**)&pszPrivVer, &uPrivLen);
	if(!bRet){
		pszPrivVer = NULL;
	}

	sprintf(szSubBlock, "\\StringFileInfo\\%s\\SpecialBuild", lpLang);
	bRet = ::VerQueryValue(pszInfo, szSubBlock, (void**)&pszSpecVer, &uSpecLen);
	if(!bRet){
		pszSpecVer = NULL;
	}

	if(pszFileVer){
		strncpy(pfv->szFileVersion,    pszFileVer, 32);
	}
	if(pszPrivVer){
		strncpy(pfv->szPrivateBuild,   pszPrivVer, 32);
	}
	if(pszProdVer){
		strncpy(pfv->szProductVersion, pszProdVer, 32);
	}
	if(pszSpecVer){
		strncpy(pfv->szSpecialBuild,   pszSpecVer, 32);
	}
	delete pszInfo;
	return true;
}

void WINAPI PumpMessage(UINT wMsgFilterMin /*= 0*/, UINT wMsgFilterMax /*= 0*/){
	MSG msg;
    if( ::PeekMessage(&msg, NULL, wMsgFilterMin, wMsgFilterMax, PM_REMOVE) ) {
        ::TranslateMessage( &msg );
        ::DispatchMessage( &msg );
    }
}