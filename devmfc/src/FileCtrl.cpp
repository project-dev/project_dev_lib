// FileCtrl.cpp: CFileCtrl クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CFileCtrl::CFileCtrl(){

}

CFileCtrl::~CFileCtrl(){

}
BOOL CFileCtrl::CreateDirectory(LPCTSTR pszDir){
	CString strCreDir = pszDir;
	while(!strCreDir.Right(1).Compare("\\")){
		strCreDir = strCreDir.Left(strCreDir.GetLength() - 1);
	}
	CString strDir = "";
	BOOL bEnd = FALSE;
	int nPos = -1;
	BOOL bRet = TRUE;
	while(!bEnd){
		nPos = strCreDir.Find("\\", nPos + 1);
		if(nPos == -1){
			strDir = strCreDir;
			bEnd = TRUE;
		}else{
			strDir = strCreDir.Left(nPos);
		}
		if(!IsExistDir(strDir) && strDir.Right(1).Compare(":")){
			if(!::CreateDirectory(strDir, NULL)){
				bRet = FALSE;
				break;
			}
		}
	}
	return bRet;
}

BOOL CFileCtrl::IsExistDir(LPCTSTR pszDir){
	WIN32_FIND_DATA wfd;
	BOOL bRet = FALSE;
	BOOL bFirst = TRUE;
	HANDLE hRet;
	while(TRUE){
		if(bFirst){
			hRet = ::FindFirstFile(pszDir, &wfd);
			bFirst = FALSE;
			if(hRet == INVALID_HANDLE_VALUE){
				break;
			}
		}else{
			if(!::FindNextFile(hRet, &wfd)){
				break;
			}
		}
		if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
			bRet = TRUE;
			break;
		}
	}
	::FindClose(hRet);
	return bRet;
}
