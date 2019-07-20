// FindFile.cpp: CFindFile クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FindFile.h"
#include "LogFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CFindFile::CFindFile(){
	FindCallBack = NULL;
	PreFindNextCallBack = NULL;
}

CFindFile::~CFindFile(){

}

BOOL CFindFile::IsExistFile(LPCTSTR pszFile){
	WIN32_FIND_DATA wfd;
	HANDLE hRet = ::FindFirstFile(pszFile, &wfd);
	BOOL bRet = TRUE;
	if(hRet == INVALID_HANDLE_VALUE){
		bRet = FALSE;
	}
	
	::FindClose(hRet);
	return bRet;
}


void CFindFile::SetCallBack(PFindCallBack pCallBack, PPreFindNextCallBack pPreFindNextBack){
	FindCallBack = pCallBack;
	PreFindNextCallBack = pPreFindNextBack;
}

int CFindFile::FindFile(LPCTSTR pszDir, LPCTSTR pszFind, BOOL bFileOnly /*= FALSE*/, BOOL bSubDir /*= FALSE*/){
	if(!pszDir || !pszFind){
		return -1;
	}
	PrivateFindFile(pszDir, NULL, pszFind, bFileOnly, bSubDir);
	return m_arrFindFile.GetSize();
}

int CFindFile::PrivateFindFile(LPCTSTR pszDir, LPCTSTR pszSubDir, LPCTSTR pszFind, BOOL bFileOnly /*= FALSE*/, BOOL bSubDir /*= FALSE*/){

	WIN32_FIND_DATA wfd;
	HANDLE hRet = NULL;
	memset(&wfd, 0, sizeof(WIN32_FIND_DATA));
	BOOL bFirst = TRUE;
	m_arrFindFile.RemoveAll();

	CString strFindPath;
	CString strDir = pszDir;
	if(strDir.Right(1).Compare("\\")){
		strDir += "\\";
	}
	if(pszSubDir){
		strDir += pszSubDir;
		if(strDir.Right(1).Compare("\\")){
			strDir += "\\";
		}
	}
	CLogFile::SaveAppLog(strDir);
	strFindPath.Format("%s%s", strDir, pszFind);

	while(TRUE){
		if(PreFindNextCallBack){
			PreFindNextCallBack();
		}
		if(bFirst){
			hRet = ::FindFirstFile(strFindPath, &wfd);
			if(hRet == INVALID_HANDLE_VALUE){
				break;
			}
			bFirst = FALSE;
		}else{
			if(!::FindNextFile(hRet, &wfd)){
				break;
			}
		}
		CString strFile = wfd.cFileName;
		if(strFile.IsEmpty() || !strFile.Compare(".") || !strFile.Compare("..")){
			continue;
		}
	
		if((bFileOnly && !IsDirectory(&wfd)) || !bFileOnly){
			CString strAddFile;
			if(pszSubDir){
				strAddFile.Format("%s\\%s", pszSubDir, wfd.cFileName);
			}else{
				strAddFile = wfd.cFileName;
			}
			if(FindCallBack){
				if(FindCallBack(strDir, wfd)){
					m_arrFindFile.Add(strAddFile);
				}
			}else{
				m_arrFindFile.Add(strAddFile);
			}
		}
	}
	::FindClose(hRet);

	strFindPath.Format("%s*", strDir);

	if(bSubDir){
		WIN32_FIND_DATA subWfd;
		HANDLE hSubRet = NULL;
		BOOL bSubFirst = TRUE;
		memset(&subWfd, 0, sizeof(WIN32_FIND_DATA));
		while(TRUE){
			if(bSubFirst){
				hSubRet = ::FindFirstFile(strFindPath, &subWfd);
				if(hSubRet == INVALID_HANDLE_VALUE){
					break;
				}
				bSubFirst = FALSE;
			}else{
				if(!::FindNextFile(hSubRet, &subWfd)){
					break;
				}
			}
			CString strFile = subWfd.cFileName;
			if(strFile.IsEmpty() || !strFile.Compare(".") || !strFile.Compare("..")){
				continue;
			}
			if(IsDirectory(&subWfd)){
				PrivateFindFile(strDir, subWfd.cFileName, pszFind, bFileOnly, bSubDir);
			}
		}
		::FindClose(hSubRet);
	}	
	return m_arrFindFile.GetSize();
}

BOOL CFindFile::IsDirectory(WIN32_FIND_DATA *wfd){
	if((wfd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY){
		return TRUE;
	}
	return FALSE;
}

int CFindFile::GetCount(){
	return m_arrFindFile.GetSize();
}

BOOL CFindFile::GetFileName(int nIndex, CString &strFileName){
	strFileName = "";
	if((nIndex < 0) || (m_arrFindFile.GetSize() <= nIndex)){
		return FALSE;
	}

	strFileName = m_arrFindFile.GetAt(nIndex);
	return TRUE;
}
