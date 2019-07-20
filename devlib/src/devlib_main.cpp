#include "stdafx.h"
#include "devlib.h"
#include <time.h>

/**
 *@brief ‘®‰»‚³‚ê‚½ŠÔ‚ğæ“¾‚·‚é
 *
 *@return ŠÔ•¶š—ñ
 */
char* WINAPI GetNowTimeText(){
	time_t curTime;
	time(&curTime);
	tm *objCurTm = localtime(&curTime);
	return asctime(objCurTm);
}
