#include "stdafx.h"
#include "devlib.h"
#include <time.h>

/**
 *@brief ���������ꂽ���Ԃ��擾����
 *
 *@return ���ԕ�����
 */
char* WINAPI GetNowTimeText(){
	time_t curTime;
	time(&curTime);
	tm *objCurTm = localtime(&curTime);
	return asctime(objCurTm);
}
