
#include "stdafx.h"
#include "devlib.h"
#include <string>
#include <vector>
#include "DevString.h"
using namespace std;

/**
 * @brief Ini�t�@�C����1�Z�N�V�������擾����
 *
 * @param strSecsion �Z�N�V������
 * @param strBuff    ini�t�@�C���̃f�[�^��ێ�����string�N���X
 * @param strReturn  �擾�����Z�N�V�������i�[����string�N���X
 * @return �擾�ɐ��������TRUE
 */
BOOL GetSection(string &strSecsion, string &strBuff, string &strReturn){
	//�Z�N�V�������擾����
	int nStart = strBuff.find(strSecsion);
	if(nStart == -1){
		return FALSE;
	}

	LPCTSTR pszSep = "[";
	int nLen = nStart + strSecsion.size();

	//�Z�N�V������1�̂Ƃ��ɖ������}���`�o�C�g�̏ꍇ
	//string.find(strSep, nLen)
	//���ƁA�l���ςɂȂ�(nEnd��-1�ɂȂ�Ȃ�)
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
 * @brief ������\��ǉ�����B
 *
 * ������\�������邱�Ƃ��l�����Ē�����+1���Ă����K�v������B
 * @param pszDir \��ǉ�����p�X
 * @return �Ȃ�
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
 * @brief �f�B���N�g�����쐬����
 *
 * @param lpPathName           �쐬����p�X
 * @param lpSecurityAttributes LPSECURITY_ATTRIBUTES
 * @return �쐬�ɐ��������TRUE
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
			//����̓h���C�u�̂͂��Ȃ̂Ŗ���
			nFirst = 0;
			continue;
		}

		WIN32_FIND_DATA wfd;
		HANDLE hRet;
		hRet = ::FindFirstFile(pszDir, &wfd);
		if(hRet == INVALID_HANDLE_VALUE){
			//�t�H���_����
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

	//�p�X�̕���
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

	//�p�X���m�F���Ȃ���f�B���N�g�����쐬���Ă���
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
			//�t�H���_����
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
 * @brief �t�@�C�����폜����
 *
 * @param pszFileName �폜����t�@�C���̃p�X
 * @return �폜�ɐ��������TRUE
 */
BOOL WINAPI DeleteFileEx(LPCTSTR pszFileName){
	if(!IsFileExsist(pszFileName)){
		//���݂��Ȃ��ꍇ�͏I��
		return TRUE;
	}

	BOOL bRet = ::DeleteFile(pszFileName);
	if(!bRet){
		Sleep(1000);	//�����҂��čĒ���
		bRet = ::DeleteFile(pszFileName);
	
	}
	return bRet;
}

/**
 * @brief �t�@�C���̑��݃`�F�b�N
 *
 * @param pszFileName �`�F�b�N����t�@�C���̃p�X
 * @return ���݂��Ă����TRUE
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
 * @brief �f�B���N�g�����ǂ����̊m�F
 *
 * @param pszFileName �m�F����p�X
 * @return �f�B���N�g���ł����TRUE
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
 * @brief �t�@�C�����폜����
 *
 * @param lpDir        �폜����p�X
 * @param bChildDelete lpDir�Ɏq�K�w�����݂���ꍇ�Ɏq�K�w���폜����ꍇ��TRUE
 * @return �폜�ɐ��������TRUE
 */
BOOL WINAPI RemoveDirectoryEx(LPCTSTR lpDir, BOOL bChildDelete){
	if(!IsFileExsist(lpDir)){
		return FALSE;		
	}

	if(!bChildDelete){
		return ::RemoveDirectory(lpDir);
	}

	//�q�K�w�����ǂ��ď����Ă���
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
				//�q�K�w�����ǂ�
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


	//�T�u�f�B���N�g���̍폜
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
				//�q�K�w�����ǂ�
				
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
 * @brief ini�t�@�C�����當�����ǂݍ���
 *
 * Windows API��GetPrivateProfileString�̂悤�Ɉ�����
 * @param lpAppName        �Z�N�V������
 * @param lpKeyName        �L�[��
 * @param lpDefault        �f�t�H���g�l
 * @param lpRetValue       �l�̊i�[�p����
 * @param nLen             lpRetValue�̒���
 * @param lpFileName       ini�t�@�C����
 * @return �擾�ɐ�������΂��̎擾�����f�[�^�̒�����Ԃ��B���s�����ꍇ��0
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
			//�I�[�v�����s
			if(lpRetValue){
				strcpy(lpRetValue, lpDefault);
				return strlen(lpDefault);
			}
			return 0;
		}

		//�t�@�C���T�C�Y�擾
		if(fseek(f, 0, SEEK_END)){
			//���s
			if(lpRetValue){
				strcpy(lpRetValue, lpDefault);
				return strlen(lpDefault);
			}
			return 0;
		}

		long lSize = ftell(f);

		//�t�@�C���ǂݍ���
		if(fseek(f, 0, SEEK_SET)){
			//���s
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

		//�Z�N�V�����̌���
		int nSecPos = strbuff.find_first_of(strApp);
		if(nSecPos == -1){
			memset(lpRetValue, 0, strlen(lpRetValue));
			return 0;
		}

		//�L�[�̌���
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
		
		//�l���擾
		int nPos = nKeyPos + strKey.length();
		int nEnd = strbuff.find_first_of("\n", nPos);
		string strValue = "";
		if(nEnd == -1){
			//�s���Ƃ݂Ȃ��ď�������
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
 * @brief ini�t�@�C�����琮���l���擾����
 *
 * Windows API��GetPrivateProfileInt�̂悤�Ɉ�����
 * @param lpAppName        �Z�N�V������
 * @param lpKeyName        �L�[��
 * @param nDefault         �f�t�H���g�l
 * @param lpFileName       ini�t�@�C����
 * @return �擾�ɐ�������΂��̎擾�����f�[�^��Ԃ��B���s�����ꍇ�̓f�t�H���g��Ԃ�
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
 * @brief ini�t�@�C���ɕ��������������
 *
 * Windows API��WritePrivateProfileString�̂悤�Ɉ�����
 * ������̒����̐����͖����B
 * @param lpAppName        �Z�N�V������
 * @param lpKeyName        �L�[��
 * @param lpString         �������ޒl
 * @param lpFileName       ini�t�@�C����
 * @return �擾�ɐ��������TRUE��Ԃ��B
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

		//�e�L�X�g���[�h�ł̃I�[�v��
		f = fopen(lpFileName, "rt");
		if(f){

			//�t�@�C���T�C�Y�̎擾
			if(fseek(f, 0, SEEK_END)){
				//���s
				return FALSE;
			}

			long lLen = ftell(f);

			//�t�@�C���̐擪�Ɉړ�
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

		//�Z�N�V�����̌���
		int nPos = strBlock.Find(strApp);
		if(nPos == -1){
			//�����ɃZ�N�V������ǉ�
			if(strbuff.GetLength()){
				strbuff += "\r\n";
			}
			strbuff += strApp;
			strbuff += strKey;
			strbuff += strValue;
		}else{
			//�L�[�̌���
			int nLen = strBlock.GetLength();
			nPos = strBlock.Find(strKey, nPos);
			if(nPos == -1){
				strBlock += strKey;
				strBlock += strValue;
			}else if(nPos == nLen){
				strBlock += strKey;
				strBlock += strValue;
			}else{
				//�l���擾
				nPos += strKey.GetLength();
				int nEnd = strBlock.Find("\n", nPos);
				CDevString strOldValue = "";
				if(nLen < nPos){
					return FALSE;
				}else{
					if(nEnd <= -1){
						//�s���Ƃ݂Ȃ��ď�������
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
	
		//��������
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

    //Ini�t�@�C���I�ɖ��̂��镶�����%xx�ɕύX����

	FILE *f = NULL;
	try{
		string strBlock = "";
		string strOldBlock = "";
		string strbuff = "";

		//�e�L�X�g���[�h�ł̃I�[�v��
		f = fopen(lpFileName, "rt");
		if(f){

			//�t�@�C���T�C�Y�̎擾
			if(fseek(f, 0, SEEK_END)){
				//���s
				return FALSE;
			}

			long lLen = ftell(f);

			//�t�@�C���̐擪�Ɉړ�
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

		//�Z�N�V�����̌���
		int nPos = strBlock.find_first_of(strApp);
		if(nPos == -1){
			//�����ɃZ�N�V������ǉ�
			if(strbuff.length()){
				strbuff.append("\r\n");
			}
			strbuff.append(strApp);
			strbuff.append(strKey);
			strbuff.append(strValue);
		}else{
			//�L�[�̌���
			int nLen = strBlock.length();
			nPos = strBlock.find(strKey, nPos);
			if(nPos == -1){
				strBlock.append(strKey);
				strBlock.append(strValue);
			}else if(nPos == nLen){
				strBlock.append(strKey);
				strBlock.append(strValue);
			}else{
				//�l���擾
				nPos += strKey.length();
				int nEnd = strBlock.find_first_of("\n", nPos);
				string strOldValue = "";
				if(nLen < nPos){
					return FALSE;
				}else{
					if(nEnd <= -1){
						//�s���Ƃ݂Ȃ��ď�������
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
	
		//��������
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
 * @brief ini�t�@�C���ɐ����l����������
 *
 * Windows API��WritePrivateProfileString�̂悤�Ɉ�����
 * @param lpAppName        �Z�N�V������
 * @param lpKeyName        �L�[��
 * @param nValue           �������ޒl
 * @param lpFileName       ini�t�@�C����
 * @return �擾�ɐ��������TRUE��Ԃ��B
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
 * @brief �t�@�C����񋓂���B
 *
 * �����P�ɁAFindFirstFile��FindNextFile���Ăяo������<BR>
 * EnumWindows�̃t�@�C����
 * <ul>
 * <li>EnumFilesProc�̈����̉��</li>
 *   <ul>
 *   <li>��1���� EnumFiles�̑�2�����Ɠ���</li>
 *   <li>��2���� WIN32_FIND_DATA�̃|�C���^</li>
 *   <li>��3���� EnumFiles�̑�3�����Ɠ���</li>
 *   </ul>
 * <li>EnumFilesProc�̖߂�l�̉��</li>
 *   <ul>
 *   <li>�����𑱂���ꍇ��TRUE,���~����ꍇ��FALSE��Ԃ�</li>
 *   </ul>
 * </ul>
 * @param EnumFilesProc     �R�[���o�b�N�֐�
 * @param strFileName       ��������t�@�C����
 * @param lParam			  �f�[�^
 * @return �擾�ɐ��������TRUE��Ԃ��B�擾�Ɏ��s�����ꍇ��FALSE��Ԃ�
 * FindFirstFile��INVALID_HANDLE_VALUE���Ԃ��Ă��Ă�FALSE��Ԃ��܂�)
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