// DebugSupport.cpp: CDebugSupport クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DebugSupport.h"
#include "EnvInfo.h"
#include <stdio.h>
#include <string.h>
#include "devlib.h"
#include "LogFile.h"

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////
static bool m_bDebug;
static char m_szLastErrText[1024];
static FILE *m_pFile;
static char m_szLogFilePath[MAX_PATH];

/**
 * @brief コンストラクタ
 */
CDebugSupport::CDebugSupport(){

}

/**
 * @brief デストラクタ
 */
CDebugSupport::~CDebugSupport(){

}

/**
 * @brief デバッグの開始
 *
 * @param pszLogFIlePath ログ出力ファイルパス
 * @return デバッグモードを開始できた場合はTRUE
 */
bool CDebugSupport::StartDebugMode(char *pszLogFIlePath){
	m_bDebug = TRUE;
	m_pFile = NULL;

	memset(m_szLastErrText, 0, 1024);

	if(pszLogFIlePath){
		strcpy(m_szLogFilePath, pszLogFIlePath);	
		m_pFile = fopen(m_szLogFilePath, "w+");
		if(!m_pFile){
			EndDebugMode();
			return FALSE;
		}

		//DATE dt;
		char *pszCurTime = GetNowTimeText();
		char szMsg[1024];
		memset(szMsg, 0, 1024);
		sprintf(szMsg, "■■Debug Start %s\n", pszCurTime);
		CDebugSupport::OutputDebugLog(szMsg);
		//システムの情報を出力する
		CDebugSupport::OutputSystemInfo();

	}else{
		memset(m_szLogFilePath, 0, MAX_PATH);
	}
	return TRUE;
}

/**
 * @brief デバッグの終了
 *
 */
void CDebugSupport::EndDebugMode(){
	if(!m_bDebug ){
		return;
	}
	char *pszCurTime = GetNowTimeText();
	char szMsg[1024];
	memset(szMsg, 0, 1024);
	sprintf(szMsg, "■■Debug End %s\n", pszCurTime);
	CDebugSupport::OutputDebugLog(szMsg);

	m_bDebug = FALSE;
	if(m_pFile){
		fclose(m_pFile);
	}
	m_pFile = NULL;
	memset(m_szLastErrText, 0, 1024);
	memset(m_szLogFilePath, 0, MAX_PATH);
}

/**
 * @brief デバッグモードを取得
 *
 * @return デバッグ中の場合はTRUE
 */
bool CDebugSupport::GetDebugMode(){
	return m_bDebug;

}

/**
 * @brief GetLastError APIの戻り値に対応するメッセージを出力する
 *
 * OutputDebugStringで出力を行うため、モニタする必要がある
 * @param dwID GetLastError APIの戻り値
 */
void CDebugSupport::OutputGetLastErrorMsg(DWORD dwID){
	GetLastErrorText(dwID);
	OutputDebugLog(m_szLastErrText);
}

/** 
 * @brief GetLastError APIの戻り値に対応するメッセージを取得する
 *
 * @param dwID GetLastError APIの戻り値
 * @return GetLastError APIの戻り値に対応する文字列
*/
char* CDebugSupport::GetLastErrorText(DWORD dwID){
	::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
					0,
					dwID,
					0,
					m_szLastErrText,
					1024,
					NULL);
	return m_szLastErrText;
}

/**
 * @brief デバッグログファイルに文字列を出力
 *
 * StartDebugModeでファイル名を指定しておく必要がある
 * @param pszMsg ログファイルに出力する文字列
 */
void CDebugSupport::OutputDebugLog(char *pszMsg){
	if(!m_bDebug){
		return;
	}
	if(m_pFile){
		fwrite(pszMsg, strlen(pszMsg), 1, m_pFile);
		fflush(m_pFile);
	}
	::OutputDebugString(pszMsg);
}

/**
 * @brief OSやプロセッサ、GetDeviceCapsで取得できる情報を出力する
 */
void CDebugSupport::OutputSystemInfo(){
	if(!m_bDebug){
		return;
	}

	char szOSName[128];
	char szCSD[128];
	DWORD dwBuild;
	char szVender[128];
	char szType[128];
	char szLevel[128];
	char szRevison[128];

	CEnvInfo::GetOSInfo(szOSName, dwBuild, szCSD);
	CEnvInfo::GetProcesserInfo(szVender, szType, szLevel, szRevison);

	char szMsg[1024];
	sprintf(szMsg, "OS           : %s build %u %s\n", szOSName, dwBuild, szCSD);
	CDebugSupport::OutputDebugLog(szMsg);

	sprintf(szMsg, "Processer    : %s (%s) %s %s\n", szVender, szType, szLevel, szRevison);
	CDebugSupport::OutputDebugLog(szMsg);

	CDebugSupport::OutputDebugLog("GetDevice    : ");
	DEVICEINFO dev;
	CEnvInfo::GetDeviceInfo(NULL, &dev);

	sprintf(szMsg, "  Device Version   : %d\n", dev.nDrvVersion);
	CDebugSupport::OutputDebugLog("  TECHNOLOGY       : ");
	sprintf(szMsg, "     DT_PLOTTER    : %s\n", dev.gdcTech.bPlotter		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     DT_RASDISPLAY : %s\n", dev.gdcTech.bRasDisplay		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     DT_RASPRINTER : %s\n", dev.gdcTech.bRasPrinter		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     DT_RASCAMERA  : %s\n", dev.gdcTech.bRasCamera		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     DT_CHARSTREAM : %s\n", dev.gdcTech.bCharStream		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     DT_METAFILE   : %s\n", dev.gdcTech.bMetaFile		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     DT_DISPFILE   : %s\n", dev.gdcTech.bDispFile		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);

	sprintf(szMsg, "  HORZSIZE         : %d\n", dev.nHorzSize);
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "  VERTSIZE         : %d\n", dev.nVertSize);
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "  HORZRES          : %d\n", dev.nHorzRes);
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "  VERTRES          : %d\n", dev.nVertRes);
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "  LOGPIXELSX       : %d\n", dev.nVertRes);
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "  LOGPIXELSY       : %d\n", dev.nVertRes);
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "  BITSPIXEL        : %d\n", dev.nVertRes);
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "  PLANES           : %d\n", dev.nVertRes);
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "  NUMBRUSHES       : %d\n", dev.nVertRes);
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "  NUMPENS          : %d\n", dev.nVertRes);
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "  NUMFONTS         : %d\n", dev.nVertRes);
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "  NUMCOLORS        : %d\n", dev.nVertRes);
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "  ASPECTX          : %d\n", dev.nVertRes);
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "  ASPECTY          : %d\n", dev.nVertRes);
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "  ASPECTXY         : %d\n", dev.nVertRes);
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "  PDEVICESIZE      : %d\n", dev.nVertRes);
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "  CLIPCAPS         : %d\n", dev.nVertRes);
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "  SIZEPALETTE      : %d\n", dev.nVertRes);
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "  NUMRESERVED      : %d\n", dev.nVertRes);
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "  COLORRES         : %d\n", dev.nVertRes);
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "  PHYSICALWIDTH    : %d\n", dev.nVertRes);
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "  PHYSICALHEIGH    : %d\n", dev.nVertRes);
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "  PHYSICALOFFSETX  : %d\n", dev.nVertRes);
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "  PHYSICALOFFSETY  : %d\n", dev.nVertRes);
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "  VREFRESH         : %d\n", dev.nVertRes);
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "  SCALINGFACTORX   : %d\n", dev.nVertRes);
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "  SCALINGFACTORY   : %d\n", dev.nVertRes);
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "  BLTALIGNMENT     : %d\n", dev.nVertRes);
	CDebugSupport::OutputDebugLog(szMsg);

//	CDebugSupport::OutputDebugLog("  SHADEBLENDCAPS   :");
	CDebugSupport::OutputDebugLog("  RASTERCAPS       :");
	sprintf(szMsg, "     RC_BANDING     : %s\n", dev.RasTerCaps.bBANDING		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     RC_BITBLT      : %s\n", dev.RasTerCaps.bBANDING		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     RC_BITMAP64    : %s\n", dev.RasTerCaps.bBANDING		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     RC_DI_BITMAP   : %s\n", dev.RasTerCaps.bBANDING		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     RC_DIBTODEV    : %s\n", dev.RasTerCaps.bBANDING		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     RC_FLOODFILL   : %s\n", dev.RasTerCaps.bBANDING		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     RC_GDI20_OUTPUT: %s\n", dev.RasTerCaps.bBANDING		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     RC_PALETTE     : %s\n", dev.RasTerCaps.bBANDING		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     RC_SCALING     : %s\n", dev.RasTerCaps.bBANDING		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     RC_STRETCHBLT  : %s\n", dev.RasTerCaps.bBANDING		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     RC_STRETCHDIB  : %s\n", dev.RasTerCaps.bBANDING		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);

	CDebugSupport::OutputDebugLog("  CURVECAPS        :");
	sprintf(szMsg, "     CC_NONE        : %s\n", dev.CurVeCaps.bNONE		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     CC_CHORD       : %s\n", dev.CurVeCaps.bNONE		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     CC_CIRCLES     : %s\n", dev.CurVeCaps.bNONE		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     CC_ELLIPSES    : %s\n", dev.CurVeCaps.bNONE		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     CC_INTERIORS   : %s\n", dev.CurVeCaps.bNONE		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     CC_PIE         : %s\n", dev.CurVeCaps.bNONE		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     CC_ROUNDRECT   : %s\n", dev.CurVeCaps.bNONE		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     CC_STYLED      : %s\n", dev.CurVeCaps.bNONE		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     CC_WIDE        : %s\n", dev.CurVeCaps.bNONE		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     CC_WIDE        : %s\n", dev.CurVeCaps.bNONE		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);

	CDebugSupport::OutputDebugLog("  LINECAPS         :");
	sprintf(szMsg, "     LC_NONE        : %s\n", dev.LineCaps.bNONE		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     LC_INTERIORS   : %s\n", dev.LineCaps.bNONE		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     LC_MARKER      : %s\n", dev.LineCaps.bNONE		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     LC_POLYLINE    : %s\n", dev.LineCaps.bNONE		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     LC_POLYMARKER  : %s\n", dev.LineCaps.bNONE		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     LC_STYLED      : %s\n", dev.LineCaps.bNONE		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     LC_WIDE        : %s\n", dev.LineCaps.bNONE		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     LC_WIDESTYLED  : %s\n", dev.LineCaps.bNONE		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);

	CDebugSupport::OutputDebugLog("  POLYGONALCAPS    :");
	sprintf(szMsg, "     PC_NONE        : %s\n", dev.PolygonalCaps.bNONE		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     PC_INTERIORS	: %s\n", dev.PolygonalCaps.bNONE		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     PC_POLYGON     : %s\n", dev.PolygonalCaps.bNONE		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     PC_RECTANGLE   : %s\n", dev.PolygonalCaps.bNONE		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     PC_SCANLINE    : %s\n", dev.PolygonalCaps.bNONE		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     PC_STYLED      : %s\n", dev.PolygonalCaps.bNONE		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     PC_WIDE        : %s\n", dev.PolygonalCaps.bNONE		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     PC_WIDESTYLED  : %s\n", dev.PolygonalCaps.bNONE		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     PC_WINDPOLYGON : %s\n", dev.PolygonalCaps.bNONE		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);

	CDebugSupport::OutputDebugLog("  TEXTCAPS         :");
	sprintf(szMsg, "     TC_OP_CHARACTER: %s\n", dev.TextCaps.bOP_CHARACTER		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     TC_OP_STROKE   : %s\n", dev.TextCaps.bOP_CHARACTER		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     TC_CP_STROKE   : %s\n", dev.TextCaps.bOP_CHARACTER		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     TC_CR_90       : %s\n", dev.TextCaps.bOP_CHARACTER		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     TC_CR_ANY      : %s\n", dev.TextCaps.bOP_CHARACTER		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     TC_SF_X_YINDEP : %s\n", dev.TextCaps.bOP_CHARACTER		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     TC_SA_DOUBLE   : %s\n", dev.TextCaps.bOP_CHARACTER		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     TC_SA_INTEGER  : %s\n", dev.TextCaps.bOP_CHARACTER		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     TC_SA_CONTIN   : %s\n", dev.TextCaps.bOP_CHARACTER		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     TC_EA_DOUBLE   : %s\n", dev.TextCaps.bOP_CHARACTER		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     TC_IA_ABLE     : %s\n", dev.TextCaps.bOP_CHARACTER		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     TC_UA_ABLE     : %s\n", dev.TextCaps.bOP_CHARACTER		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     TC_SO_ABLE     : %s\n", dev.TextCaps.bOP_CHARACTER		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     TC_RA_ABLE     : %s\n", dev.TextCaps.bOP_CHARACTER		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     TC_VA_ABLE     : %s\n", dev.TextCaps.bOP_CHARACTER		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     TC_RESERVED    : %s\n", dev.TextCaps.bOP_CHARACTER		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
	sprintf(szMsg, "     TC_SCROLLBLT   : %s\n", dev.TextCaps.bOP_CHARACTER		? "TRUE" : "FALSE");
	CDebugSupport::OutputDebugLog(szMsg);
}

/**
 * @brief モジュールのバージョンを出力する
 *
 * @param hMod バージョンを取得するモジュールのハンドル
 */
void CDebugSupport::OutputModuleVer(HMODULE hMod){
	if(!hMod){
		return;
	}
	char szVer[1024];
	char szFileName[MAX_PATH];
	memset(szVer, '\0', 1024);
	memset(szFileName, '\0', 1024);

	CDebugSupport::GetModuleVersionInfo(hMod, szVer);
	CDebugSupport::OutputDebugLog(szVer);
}

/**
 * @brief モジュールのバージョンを取得する
 *
 * @param hMod       バージョンを取得するモジュールのハンドル
 * @param pszOutBuff 情報を取得するためのバッファ
 */
void CDebugSupport::GetModuleVersionInfo(HMODULE hMod, char *pszOutBuff){
	if(!pszOutBuff){
		return;
	}

	//strcpy(pszOutBuff, '\0');
	if(!hMod){
		return;
	}

	char szFileName[MAX_PATH];
	DWORD dwSize = 0;
	DWORD dwHandle = 0;
	
	memset(szFileName, 0, MAX_PATH);
	::GetModuleFileName(hMod, szFileName, MAX_PATH);
	dwSize = ::GetFileVersionInfoSize(szFileName, &dwHandle);
	
	if(!dwSize){
		return;
	}
	
	char *pszInfo = new char[dwSize + 1];
	
	if(!pszInfo){
		return;
	}
	
	BOOL bRet = ::GetFileVersionInfo(szFileName, 0, dwSize, pszInfo);
	if(!bRet){
		delete pszInfo;
		return;
	}

	DWORD *dwLang;
	UINT uLen;
	bRet = ::VerQueryValue(pszInfo, "\\VarFileInfo\\Translation", (void**)&dwLang, &uLen);
	if(!bRet){
		delete pszInfo;
		return;
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
	
	sprintf(pszOutBuff, "Module Name    : %s\n"
						"FileVersion    : %s\n"
						"ProductVersion : %s\n"
						"PrivateBuild   : %s\n"
						"SpecialBuild   : %s\n",
						szFileName ? szFileName : "",
						pszFileVer ? pszFileVer : "",
						pszProdVer ? pszProdVer : "",
						pszPrivVer ? pszPrivVer : "",
						pszSpecVer ? pszSpecVer : "");
	delete pszInfo;
}

void CDebugSupport::Except(LPEXCEPTION_POINTERS pExp){
	CLogFile::SaveAppLog("致命的エラー発生(詳細はFatal.txt)");
   if(pExp){
	   char strExpCode[65];
	   memset(strExpCode, 0, 65);
         switch(pExp->ExceptionRecord->ExceptionCode){
        case EXCEPTION_ACCESS_VIOLATION:
            strcpy(strExpCode, "EXCEPTION_ACCESS_VIOLATION");
            break;
        case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
            strcpy(strExpCode, "EXCEPTION_ARRAY_BOUNDS_EXCEEDED");
            break;
        case EXCEPTION_BREAKPOINT:
            strcpy(strExpCode, "EXCEPTION_BREAKPOINT");
            break;
        case EXCEPTION_DATATYPE_MISALIGNMENT:
            strcpy(strExpCode, "EXCEPTION_DATATYPE_MISALIGNMENT");
            break;
        case EXCEPTION_FLT_DENORMAL_OPERAND:
            strcpy(strExpCode, "EXCEPTION_FLT_DENORMAL_OPERAND");
            break;
        case EXCEPTION_FLT_DIVIDE_BY_ZERO:
            strcpy(strExpCode, "EXCEPTION_FLT_DIVIDE_BY_ZERO");
            break;
        case EXCEPTION_FLT_INEXACT_RESULT:
            strcpy(strExpCode, "EXCEPTION_FLT_INEXACT_RESULT");
            break;
        case EXCEPTION_FLT_INVALID_OPERATION:
            strcpy(strExpCode, "EXCEPTION_FLT_INVALID_OPERATION");
            break;
        case EXCEPTION_FLT_OVERFLOW:
            strcpy(strExpCode, "EXCEPTION_FLT_OVERFLOW");
            break;
        case EXCEPTION_FLT_STACK_CHECK:
            strcpy(strExpCode, "EXCEPTION_FLT_STACK_CHECK");
            break;
        case EXCEPTION_FLT_UNDERFLOW:
            strcpy(strExpCode, "EXCEPTION_FLT_UNDERFLOW");
            break;
        case EXCEPTION_ILLEGAL_INSTRUCTION:
            strcpy(strExpCode, "EXCEPTION_ILLEGAL_INSTRUCTION");
            break;
        case EXCEPTION_IN_PAGE_ERROR:
            strcpy(strExpCode, "EXCEPTION_IN_PAGE_ERROR");
            break;
        case EXCEPTION_INT_DIVIDE_BY_ZERO:
            strcpy(strExpCode, "EXCEPTION_INT_DIVIDE_BY_ZERO");
            break;
        case EXCEPTION_INT_OVERFLOW:
            strcpy(strExpCode, "EXCEPTION_INT_OVERFLOW");
            break;
        case EXCEPTION_INVALID_DISPOSITION:
            strcpy(strExpCode, "EXCEPTION_INVALID_DISPOSITION");
            break;
        case EXCEPTION_NONCONTINUABLE_EXCEPTION:
            strcpy(strExpCode, "EXCEPTION_NONCONTINUABLE_EXCEPTION");
            break;
        case EXCEPTION_PRIV_INSTRUCTION:
            strcpy(strExpCode, "EXCEPTION_PRIV_INSTRUCTION");
            break;
        case EXCEPTION_SINGLE_STEP :
            strcpy(strExpCode, "EXCEPTION_SINGLE_STEP");
            break;
        case EXCEPTION_STACK_OVERFLOW:
            strcpy(strExpCode, "EXCEPTION_STACK_OVERFLOW");
            break;
        default:
             strcpy(strExpCode, "UNKNOW");
           break;
        }
		char szErrLog[1025];
		memset(szErrLog, 0, 1025);
		sprintf(szErrLog, "%d[0x%08X] : %s\r\n"
                          "           Flag = 0x%08X\r\n"
                          "           Address = 0x%08X\r\n"
                        ,pExp->ExceptionRecord->ExceptionCode
                        ,pExp->ExceptionRecord->ExceptionCode
                        ,strExpCode
                        ,pExp->ExceptionRecord->ExceptionFlags
                        ,pExp->ExceptionRecord->ExceptionAddress);
		CLogFile::SaveFatalLog(szErrLog);
		::MessageBox(NULL, szErrLog, "Exception", MB_OK);
    }
}
