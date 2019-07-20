#include "stdafx.h"
#include "devlib.h"
#include <time.h>

/**
 *@brief 書式化された時間を取得する
 *
 *@return 時間文字列
 */
char* WINAPI GetNowTimeText(){
	time_t curTime;
	time(&curTime);
	tm *objCurTm = localtime(&curTime);
	return asctime(objCurTm);
}
