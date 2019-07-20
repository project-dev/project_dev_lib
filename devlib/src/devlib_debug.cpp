#include "stdafx.h"
#include "devlib.h"
/*
//VC++ 6 にデフォルトではない構造体とAPI
typedef struct _PROCESS_MEMORY_COUNTERS {
	DWORD cb;
	DWORD PageFaultCount;
	SIZE_T PeakWorkingSetSize;
	SIZE_T WorkingSetSize;
	SIZE_T QuotaPeakPagedPoolUsage;
	SIZE_T QuotaPagedPoolUsage;
	SIZE_T QuotaPeakNonPagedPoolUsage;
	SIZE_T QuotaNonPagedPoolUsage;
	SIZE_T PagefileUsage;
	SIZE_T PeakPagefileUsage;
} PROCESS_MEMORY_COUNTERS;
typedef PROCESS_MEMORY_COUNTERS *PPROCESS_MEMORY_COUNTERS;

typedef	BOOL (WINAPI *GetProcessMemoryInfoProc)(HANDLE ,PPROCESS_MEMORY_COUNTERS, DWORD );

GetProcessMemoryInfoProc	GetProcessMemoryInfo;
*/

void WINAPI ShowError(DWORD errID){
	char szMsg[MAX_PATH];
	::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
					0,
					errID,
					0,
					szMsg,
					MAX_PATH,
					NULL);
	MessageBox(NULL, szMsg, "", MB_OK);
}

void WINAPI ShowSysMsg(DWORD error, char *pszMsg /* = NULL*/){
	TCHAR szMsg[MAX_PATH];
	TCHAR szShowMsg[1024];
	memset(szMsg, 0, MAX_PATH);
	memset(szShowMsg, 0, 1024);
	::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
					NULL,
					error,
					0,
					szMsg,
					MAX_PATH,
					NULL);
	if(pszMsg){
		sprintf(szShowMsg, "%s\n\n【 詳 細 】 %s", pszMsg, szMsg);
	}else{
		strcpy(szShowMsg, szMsg);
	}
	::MessageBox(NULL, szShowMsg, "エラー", MB_OK | MB_ICONWARNING);
}

#if 0
int WINAPI GetProcessMemorry(HANDLE hProcess, char *pszInfo /* = NULL */){
	HMODULE hMod = ::LoadLibrary("psapi.dll");

	if(!hMod){
		return 0;
	}
	GetProcessMemoryInfo = (GetProcessMemoryInfoProc)::GetProcAddress(hMod, "GetProcessMemoryInfo");
	
	PROCESS_MEMORY_COUNTERS pmc;
	memset(&pmc, 0, sizeof(PPROCESS_MEMORY_COUNTERS));
	pmc.cb = sizeof(PROCESS_MEMORY_COUNTERS);
	GetProcessMemoryInfo(hProcess, &pmc, sizeof(PROCESS_MEMORY_COUNTERS));

	//情報を文字列化する
	char szPageFaultCount[1024];
	char szPeakWorkingSetSize[1024];
	char szWorkingSetSize[1024];
	char szQuotaPeakPagedPoolUsage[1024];
	char szQuotaPagedPoolUsage[1024];
	char szQuotaPeakNonPagedPoolUsage[1024];
	char szQuotaNonPagedPoolUsage[1024];
	char szPagefileUsage[1024];
	char szPeakPagefileUsage[1024];

	memset(szPageFaultCount,				'\0', 1024);
	memset(szPeakWorkingSetSize,			'\0', 1024);
	memset(szWorkingSetSize,				'\0', 1024);
	memset(szQuotaPeakPagedPoolUsage,		'\0', 1024);
	memset(szQuotaPagedPoolUsage,			'\0', 1024);
	memset(szQuotaPeakNonPagedPoolUsage,	'\0', 1024);
	memset(szQuotaNonPagedPoolUsage,		'\0', 1024);
	memset(szPagefileUsage,					'\0', 1024);
	memset(szPeakPagefileUsage,				'\0', 1024);

#if 0	
	long pfc	= 0;
	long pwss	= 0;
	long wss	= 0;
	long qpppu	= 0;
	long qppu	= 0;
	long qpnppu	= 0;
	long qnppu	= 0;
	long pu		= 0;
	long ppu	= 0;
	if(pmc.PageFaultCount){
		pfc		= (long)((float)pmc.PageFaultCount				/ (float)1024);
	}
	if(pmc.PeakWorkingSetSize){
		pwss	= (long)((float)pmc.PeakWorkingSetSize			/ (float)1024);
	}
	if(pmc.WorkingSetSize){
		wss		= (long)((float)pmc.WorkingSetSize				/ (float)1024);
	}
	if(pmc.QuotaPeakPagedPoolUsage){
		qpppu	= (long)((float)pmc.QuotaPeakPagedPoolUsage		/ (float)1024);
	}
	if(pmc.QuotaPagedPoolUsage){
		qppu	= (long)((float)pmc.QuotaPagedPoolUsage			/ (float)1024);
	}
	if(pmc.QuotaPeakNonPagedPoolUsage){
		qpnppu	= (long)((float)pmc.QuotaPeakNonPagedPoolUsage	/ (float)1024);
	}
	if(pmc.QuotaNonPagedPoolUsage){
		qnppu	= (long)((float)pmc.QuotaNonPagedPoolUsage		/ (float)1024);
	}
	if(pmc.PagefileUsage){
		pu		= (long)((float)pmc.PagefileUsage				/ (float)1024);
	}
	if(pmc.PeakPagefileUsage){
		ppu		= (long)((float)pmc.PeakPagefileUsage			/ (float)1024);
	}
	
	sprintf(szPageFaultCount,				"Page Fault Count               %u kb\r\n", pfc);
	sprintf(szPeakWorkingSetSize,			"Peak Working Set Size          %u kb\r\n", pwss);
	sprintf(szWorkingSetSize,				"Working Set Size               %u kb\r\n", wss);
	sprintf(szQuotaPeakPagedPoolUsage,		"Quoya Peak Paged Pool Size     %u kb\r\n", qpppu);
	sprintf(szQuotaPagedPoolUsage,			"Quota Paged Pool Usage         %u kb\r\n", qppu);
	sprintf(szQuotaPeakNonPagedPoolUsage,	"Quota PeakNon Paged Pool Usage %u kb\r\n", qpnppu);
	sprintf(szQuotaNonPagedPoolUsage,		"Quota Non Paged Pool Usage     %u kb\r\n", qnppu);
	sprintf(szPagefileUsage,				"Pagefile Usage                 %u kb\r\n", pu);
	sprintf(szPeakPagefileUsage,			"Peak Pagefile Usage            %u kb\r\n", ppu);
#else
	sprintf(szPageFaultCount,				"Page Fault Count               %u byte\r\n", pmc.PageFaultCount);
	sprintf(szPeakWorkingSetSize,			"Peak Working Set Size          %u byte\r\n", pmc.PeakWorkingSetSize);
	sprintf(szWorkingSetSize,				"Working Set Size               %u byte\r\n", pmc.WorkingSetSize);
	sprintf(szQuotaPeakPagedPoolUsage,		"Quoya Peak Paged Pool Size     %u byte\r\n", pmc.QuotaPeakPagedPoolUsage);
	sprintf(szQuotaPagedPoolUsage,			"Quota Paged Pool Usage         %u byte\r\n", pmc.QuotaPagedPoolUsage);
	sprintf(szQuotaPeakNonPagedPoolUsage,	"Quota PeakNon Paged Pool Usage %u byte\r\n", pmc.QuotaPeakNonPagedPoolUsage);
	sprintf(szQuotaNonPagedPoolUsage,		"Quota Non Paged Pool Usage     %u byte\r\n", pmc.QuotaNonPagedPoolUsage);
	sprintf(szPagefileUsage,				"Pagefile Usage                 %u byte\r\n", pmc.PagefileUsage);
	sprintf(szPeakPagefileUsage,			"Peak Pagefile Usage            %u byte\r\n", pmc.PeakPagefileUsage);
#endif
	size_t nSize = 0;

	nSize += strlen(szPageFaultCount);
	nSize += strlen(szPeakWorkingSetSize);
	nSize += strlen(szWorkingSetSize);
	nSize += strlen(szQuotaPeakPagedPoolUsage);
	nSize += strlen(szQuotaPagedPoolUsage);
	nSize += strlen(szQuotaPeakNonPagedPoolUsage);
	nSize += strlen(szQuotaNonPagedPoolUsage);
	nSize += strlen(szPagefileUsage);
	nSize += strlen(szPeakPagefileUsage);

	if(!pszInfo){
		return nSize;
	}

	strcat(pszInfo, szPageFaultCount);
	strcat(pszInfo, szPeakWorkingSetSize);
	strcat(pszInfo, szWorkingSetSize);
	strcat(pszInfo, szQuotaPeakPagedPoolUsage);
	strcat(pszInfo, szQuotaPagedPoolUsage);
	strcat(pszInfo, szQuotaPeakNonPagedPoolUsage);
	strcat(pszInfo, szQuotaNonPagedPoolUsage);
	strcat(pszInfo, szPagefileUsage);
	strcat(pszInfo, szPeakPagefileUsage);

	FreeLibrary(hMod);
	return 0;
}
#endif