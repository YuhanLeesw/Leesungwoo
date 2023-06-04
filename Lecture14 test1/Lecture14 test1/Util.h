#pragma once
#include "Util.h"

void CheckError(int e)
{
	if (e == 1)
	{
		printf("\n[line:%d, %s]에러가 발생하였습니다.\n", __LINE__, __func__);
		exit(1);
	}
}
