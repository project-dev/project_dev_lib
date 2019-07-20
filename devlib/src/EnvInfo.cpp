// EnvInfo.cpp: CEnvInfo クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "EnvInfo.h"
#include <windows.h>


//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

/**
 * @brief コンストラクタ
 */
CEnvInfo::CEnvInfo()
{

}

/**
 * @brief デストラクタ
 */
CEnvInfo::~CEnvInfo()
{

}

/**
 * @brief OSのバージョンなどを文字列などで取得する
 * @param pszOSName OS名(OUT)
 * @param dwBuild   ビルド番号(OUT)
 * @param pszCSD    CSDバージョン(OUT)
 * @return OSの種別を表す値を返す(CEnvInfo::eWIN_VERの値)
 */
int CEnvInfo::GetOSInfo(char *pszOSName, DWORD &dwBuild, char *pszCSD){
	int nRet = UNKNOW;
	OSVERSIONINFO osInfo;
	osInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	::GetVersionEx(&osInfo);
	int nMajor = osInfo.dwMajorVersion;
	int nMiner = osInfo.dwMinorVersion;

	strcpy(pszOSName, "UNKNOW");
	dwBuild  = osInfo.dwBuildNumber;
	strcpy(pszCSD, osInfo.szCSDVersion);

	if(nMajor == 3){
		if(nMiner == 51){
			strcpy(pszOSName, "Windows NT 3.51");
			nRet = WINNT3;
		}
	}else if(nMajor == 4){
		switch(nMiner){
		case 0:
			if(osInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS){
				strcpy(pszOSName, "Windows 95");
				nRet = WIN95;
			}else if(osInfo.dwPlatformId == VER_PLATFORM_WIN32_NT){
				strcpy(pszOSName, "Windows NT 4.0");
				nRet = WINNT4;
			}else{
				strcpy(pszOSName, "Windows 95 or NT 4.0");
				nRet = WIN95;
			}
			break;
		case 10:
			strcpy(pszOSName, "Windows 98");
			nRet = WIN98;
			break;
		case 90:
			strcpy(pszOSName, "Windows ME");
			nRet = WINME;
			break;
		}
	}else if(nMajor == 5){
		switch(nMiner){
		case 0:
			strcpy(pszOSName, "Windows 2000");
			nRet = WIN2K;
			break;
		case 1:
			strcpy(pszOSName, "Windows XP or .NET Server");
			nRet = WINXP;
			break;
		}
	}
	return nRet;
}

/**
 * @brief プロセッサの情報を文字列で取得する
 * @param pszVender  ベンダー(Out)
 * @param pszType    タイプ(Out)
 * @param pszLevel   レベル(Out)
 * @param pszRevison リビジョン(Out)
 */
void CEnvInfo::GetProcesserInfo(char *pszVender, char *pszType, char *pszLevel, char *pszRevison){
	SYSTEM_INFO sysInfo;
	::GetSystemInfo(&sysInfo);

	strcpy(pszVender,	"UNKNOW");
	strcpy(pszType,		"UNKNOW");
	strcpy(pszLevel,	"UNKNOW");
	strcpy(pszRevison,	"UNKNOW");
	
	sprintf(pszVender, "Vender %d", sysInfo.wProcessorArchitecture);
	sprintf(pszType,   "Type %d", sysInfo.dwProcessorType);
	sprintf(pszLevel,  "Level %d", sysInfo.wProcessorLevel);
	sprintf(pszRevison,"Revision %d", sysInfo.wProcessorRevision);

	DWORD dwArc = sysInfo.wProcessorArchitecture;
	DWORD dwRevison = sysInfo.wProcessorRevision;
	DWORD dwXX;
	DWORD dwYY;
	DWORD dwZZ;

	switch(dwArc){

	case PROCESSOR_ARCHITECTURE_INTEL:
		{
			strcpy(pszVender, "Intel");
			switch(sysInfo.dwProcessorType){
			case PROCESSOR_INTEL_386:
				strcpy(pszType, "386");
				break;
			case PROCESSOR_INTEL_486:
				strcpy(pszType, "486");
				break;
			case PROCESSOR_INTEL_PENTIUM:
				strcpy(pszType, "Pentium");
				break;
			}
	
			switch(sysInfo.wProcessorLevel){
			case 3:
				strcpy(pszLevel, "80386");
				dwXX = (0xFF00 & dwRevison) >> 8;
				dwYY = (0x00F0 & dwRevison) >> 4;
				dwZZ = 0x000F & dwRevison;
				sprintf(pszRevison, "model %d stepping %d %d", dwXX, dwYY, dwZZ);
				break;
			case 4:
				strcpy(pszLevel, "80486");
				dwXX = (0xFF00 & dwRevison) >> 8;
				dwYY = (0x00F0 & dwRevison) >> 4;
				dwZZ = 0x000F & dwRevison;
				sprintf(pszRevison, "model %d stepping %d %d", dwXX, dwYY, dwZZ);
				break;
			case 5:
				strcpy(pszLevel, "Pentium");
				dwXX = (0xFF00 & dwRevison) >> 8;
				dwYY = (0x00FF & dwRevison);
				sprintf(pszRevison, "model %d stepping %d", dwXX, dwYY);
				break;
			case 6:
				strcpy(pszLevel, "Pentium Pro, Pentium II and later.");
				dwXX = (0xFF00 & dwRevison) >> 8;
				dwYY = (0x00FF & dwRevison);
				sprintf(pszRevison, "model %d stepping %d", dwXX, dwYY);
				break;
			}
		}
		break;

	case PROCESSOR_ARCHITECTURE_MIPS:
		{
			strcpy(pszVender, "MIPS");
			switch(sysInfo.wProcessorLevel){
			case 4:
				strcpy(pszLevel, "R4000");
				break;
			}
			dwXX = (0x00FF & dwRevison);
			sprintf(pszRevison, "%d%d", dwXX);
		}
		break;

	case PROCESSOR_ARCHITECTURE_ALPHA:
		{
			strcpy(pszVender, "Alpha");
			switch(sysInfo.wProcessorLevel){
			case 21064:
				strcpy(pszLevel, "21064");
				break;
			case 21066:
				strcpy(pszLevel, "21066");
				break;
			case 21164:
				strcpy(pszLevel, "21164");
				break;
			}
			dwXX = (0xFF00 & dwRevison) >> 8;
			dwYY = (0x00FF & dwRevison);
			sprintf(pszRevison, "model A%d pass %d", dwXX, dwYY);
		}
		break;

	case PROCESSOR_ARCHITECTURE_PPC:
		{
			strcpy(pszVender, "PPC");
			switch(sysInfo.wProcessorLevel){
			case 1:
				strcpy(pszLevel, "601");
				break;
			case 3:
				strcpy(pszLevel, "603");
				break;
			case 4:
				strcpy(pszLevel, "604");
			case 6:
				strcpy(pszLevel, "PPC 603+");
				break;
			case 9:
				strcpy(pszLevel, "604+");
				break;
			case 20:
				strcpy(pszLevel, "620");
				break;
			}
			dwXX = (0xFF00 & dwRevison) >> 8;
			dwYY = (0x00FF & dwRevison);
			sprintf(pszRevison, "%d.%d", dwXX, dwYY);
		}
		break;

	case PROCESSOR_ARCHITECTURE_IA64:
		{
			strcpy(pszVender, "IA64");
		}
		break;
//	case PROCESSOR_ARCHITECTURE_IA32_ON_WIN64:
//		break;
//	case PROCESSOR_ARCHITECTURE_AMD64 :
//		break;

	case PROCESSOR_ARCHITECTURE_UNKNOWN:
	default:
		{

		}
		break;
	}
}

/**
 * @brief GetDeviceCaps APIで取得できる情報をすべて取得する
 * @param hWnd ウィンドウハンドル
 * @param pDev 情報を取得するためのDEVICEINFO構造体のポインタ
 * @deprecated この関数はいずれ削除されます
 */
void CEnvInfo::GetDeviceInfo(HWND hWnd, PDEVICEINFO pDev){
	HDC hDC = ::GetDC(hWnd);
	if(!hDC){
		return;
	}
	
	pDev->nDrvVersion			= ::GetDeviceCaps(hDC, DRIVERVERSION);
	
	int nTech				= ::GetDeviceCaps(hDC, TECHNOLOGY);
	pDev->gdcTech.bPlotter	= nTech & DT_PLOTTER ? true : false;
	pDev->gdcTech.bRasDisplay	= nTech & DT_RASDISPLAY ? true : false;
	pDev->gdcTech.bRasPrinter	= nTech & DT_RASPRINTER ? true : false;
	pDev->gdcTech.bRasCamera	= nTech & DT_RASCAMERA ? true : false;
	pDev->gdcTech.bCharStream	= nTech & DT_CHARSTREAM ? true : false;
	pDev->gdcTech.bMetaFile	= nTech & DT_METAFILE ?	true : false;
	pDev->gdcTech.bDispFile	= nTech & DT_DISPFILE ? true : false;

	pDev->nHorzSize			= ::GetDeviceCaps(hDC, HORZSIZE);
	pDev->nVertSize			= ::GetDeviceCaps(hDC, VERTSIZE);
	pDev->nHorzRes			= ::GetDeviceCaps(hDC, HORZRES);
	pDev->nVertRes			= ::GetDeviceCaps(hDC, VERTRES);
	pDev->nLogPixelsX		= ::GetDeviceCaps(hDC, LOGPIXELSX);
	pDev->nLogPixelsY		= ::GetDeviceCaps(hDC, LOGPIXELSY);
	pDev->nBitsPixel		= ::GetDeviceCaps(hDC, BITSPIXEL);
	pDev->nPlanes			= ::GetDeviceCaps(hDC, PLANES);
	pDev->nNumBrushes		= ::GetDeviceCaps(hDC, NUMBRUSHES);
	pDev->nNumPens			= ::GetDeviceCaps(hDC, NUMPENS);
	pDev->nNumFonts			= ::GetDeviceCaps(hDC, NUMFONTS);
	pDev->nNumColors		= ::GetDeviceCaps(hDC, NUMCOLORS);
	pDev->nAspectX			= ::GetDeviceCaps(hDC, ASPECTX);
	pDev->nAspectY			= ::GetDeviceCaps(hDC, ASPECTY);
	pDev->nAspectXY			= ::GetDeviceCaps(hDC, ASPECTXY);
	pDev->nPDeviceSize		= ::GetDeviceCaps(hDC, PDEVICESIZE);
	pDev->nClipCaps			= ::GetDeviceCaps(hDC, CLIPCAPS);
	pDev->nSizePalette		= ::GetDeviceCaps(hDC, SIZEPALETTE);
	pDev->nNumReserved		= ::GetDeviceCaps(hDC, NUMRESERVED);
	pDev->nColorRes			= ::GetDeviceCaps(hDC, COLORRES);
	pDev->nPhysicalWidth	= ::GetDeviceCaps(hDC, PHYSICALWIDTH);
	pDev->nPhysicalHeight	= ::GetDeviceCaps(hDC, PHYSICALHEIGHT);
	pDev->nPhysicalOffsetX	= ::GetDeviceCaps(hDC, PHYSICALOFFSETX);
	pDev->nPhysicalOffsetY	= ::GetDeviceCaps(hDC, PHYSICALOFFSETY);
#if 1
	pDev->nVRefresh			= ::GetDeviceCaps(hDC, VREFRESH);
#endif
	pDev->nScalingFactorX	= ::GetDeviceCaps(hDC, SCALINGFACTORX);
	pDev->nScalingFactorY	= ::GetDeviceCaps(hDC, SCALINGFACTORY);
#if 1
	pDev->nBltAlignment		= ::GetDeviceCaps(hDC, BLTALIGNMENT);
#endif
#if 0
	pDev->nShadeBlendCaps	= ::GetDeviceCaps(hDC, SHADEBLENDCAPS);
#endif
	int nRas = ::GetDeviceCaps(hDC, RASTERCAPS);
	pDev->RasTerCaps.bBANDING		= nRas & RC_BANDING ? true : false;
	pDev->RasTerCaps.bBITBLT		= nRas & RC_BITBLT ? true : false;
	pDev->RasTerCaps.bBITMAP64		= nRas & RC_BITMAP64 ? true : false;
	pDev->RasTerCaps.bDI_BITMAP		= nRas & RC_DI_BITMAP ? true : false;
	pDev->RasTerCaps.bDIBTODEV		= nRas & RC_DIBTODEV ? true : false;
	pDev->RasTerCaps.bFLOODFILL		= nRas & RC_FLOODFILL ? true : false;
	pDev->RasTerCaps.bGDI20_OUTPUT	= nRas & RC_GDI20_OUTPUT ? true : false;
	pDev->RasTerCaps.bPALETTE		= nRas & RC_PALETTE ? true : false;
	pDev->RasTerCaps.bSCALING		= nRas & RC_SCALING ? true : false;
	pDev->RasTerCaps.bSTRETCHBLT	= nRas & RC_STRETCHBLT ? true : false;
	pDev->RasTerCaps.bSTRETCHDIB	= nRas & RC_STRETCHDIB ? true : false;
	
	int nCur = ::GetDeviceCaps(hDC, CURVECAPS);
	pDev->CurVeCaps.bNONE			= nCur & CC_NONE ? true : false;
	pDev->CurVeCaps.bCHORD			= nCur & CC_CHORD ? true : false;
	pDev->CurVeCaps.bCIRCLES		= nCur & CC_CIRCLES ? true : false;
	pDev->CurVeCaps.bELLIPSES		= nCur & CC_ELLIPSES ? true : false;
	pDev->CurVeCaps.bINTERIORS		= nCur & CC_INTERIORS ? true : false;
	pDev->CurVeCaps.bPIE			= nCur & CC_PIE ? true : false;
	pDev->CurVeCaps.bROUNDRECT		= nCur & CC_ROUNDRECT ? true : false;
	pDev->CurVeCaps.bSTYLED			= nCur & CC_STYLED ? true : false;
	pDev->CurVeCaps.bWIDE			= nCur & CC_WIDE ? true : false;
	pDev->CurVeCaps.bWIDESTYLED		= nCur & CC_WIDESTYLED ? true : false;

	int nLine = ::GetDeviceCaps(hDC, LINECAPS);
	pDev->LineCaps.bNONE			= nLine & LC_NONE ? true : false;
	pDev->LineCaps.bINTERIORS		= nLine & LC_INTERIORS ? true : false;
	pDev->LineCaps.bMARKER			= nLine & LC_MARKER ? true : false;
	pDev->LineCaps.bPOLYLINE		= nLine & LC_POLYLINE ? true : false;
	pDev->LineCaps.bPOLYMARKER		= nLine & LC_POLYMARKER ? true : false;
	pDev->LineCaps.bSTYLED			= nLine & LC_STYLED ? true : false;
	pDev->LineCaps.bWIDE			= nLine & LC_WIDE ? true : false;
	pDev->LineCaps.bWIDESTYLED		= nLine & LC_WIDESTYLED ? true : false;

	int nPoly = ::GetDeviceCaps(hDC, POLYGONALCAPS);
	pDev->PolygonalCaps.bNONE			= nPoly & PC_NONE ? true : false;
	pDev->PolygonalCaps.bINTERIORS		= nPoly & PC_INTERIORS ? true : false;
	pDev->PolygonalCaps.bPOLYGON		= nPoly & PC_POLYGON ? true : false;
	pDev->PolygonalCaps.bRECTANGLE		= nPoly & PC_RECTANGLE ? true : false;
	pDev->PolygonalCaps.bSCANLINE		= nPoly & PC_SCANLINE ? true : false;
	pDev->PolygonalCaps.bSTYLED			= nPoly & PC_STYLED ? true : false;
	pDev->PolygonalCaps.bWIDE			= nPoly & PC_WIDE ? true : false;
	pDev->PolygonalCaps.bWIDESTYLED		= nPoly & PC_WIDESTYLED ? true : false;
	pDev->PolygonalCaps.bWINDPOLYGON	= nPoly & PC_WINDPOLYGON ? true : false;

	int nText = ::GetDeviceCaps(hDC, TEXTCAPS);
	pDev->TextCaps.bOP_CHARACTER	= nText & TC_OP_CHARACTER ? true : false;
	pDev->TextCaps.bOP_STROKE		= nText & TC_OP_STROKE ? true : false;
	pDev->TextCaps.bCP_STROKE		= nText & TC_CP_STROKE ? true : false;
	pDev->TextCaps.bCR_90			= nText & TC_CR_90 ? true : false;
	pDev->TextCaps.bCR_ANY			= nText & TC_CR_ANY ? true : false;
	pDev->TextCaps.bSF_X_YINDEP		= nText & TC_SF_X_YINDEP ? true : false;
	pDev->TextCaps.bSA_DOUBLE		= nText & TC_SA_DOUBLE ? true : false;
	pDev->TextCaps.bSA_INTEGER		= nText & TC_SA_INTEGER ? true : false;
	pDev->TextCaps.bSA_CONTIN		= nText & TC_SA_CONTIN ? true : false;
	pDev->TextCaps.bEA_DOUBLE		= nText & TC_EA_DOUBLE ? true : false;
	pDev->TextCaps.bIA_ABLE			= nText & TC_IA_ABLE ? true : false;
	pDev->TextCaps.bUA_ABLE			= nText & TC_UA_ABLE ? true : false;
	pDev->TextCaps.bSO_ABLE			= nText & TC_SO_ABLE ? true : false;
	pDev->TextCaps.bRA_ABLE			= nText & TC_RA_ABLE ? true : false;
	pDev->TextCaps.bVA_ABLE			= nText & TC_VA_ABLE ? true : false;
	pDev->TextCaps.bRESERVED		= nText & TC_RESERVED ? true : false;
	pDev->TextCaps.bSCROLLBLT		= nText & TC_SCROLLBLT ? true : false;
#if 0
	::GetDeviceCaps(hDC, COLORMGMTCAPS);
#endif
}

