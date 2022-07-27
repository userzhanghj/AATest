#include "pch.h"
#include "capture.h"

void ImgCap::release(void)
{
	delete[] bImgBuf;
	delete[] bBmpBuf;
	delete[] bBmpTestBuf;
}
