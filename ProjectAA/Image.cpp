#include "pch.h"
#include"Image.h"
#include "TypeDef.h"
#include "ProjectAA.h"
#include "HisFX3Platform.h"

#include "HisFX3CCMAlg.h"

#if (defined _WIN64) 
#pragma comment(lib,"HisFX3CCMAlg64.lib")
#else
#pragma comment(lib,"HisFX3CCMAlg32.lib")
#endif
#define HisReleaseMalloc(x)  {if(x!=NULL) {_aligned_free(x); x = NULL;}}
CHisFX3CCMAlg myImageAlg;


Output::Output()
{
	hbitmap = NULL;
	bi_buf = new BYTE[sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)];
}

Output::~Output()
{
	delete[] bi_buf;
}

int Output::Display(HWND hwnd, const BYTE * bmp_source, int img_w, int img_h, int img_ch, int start_x, int start_y, int is_full_sized, int stretch_mode, LPVOID temp)
{
	HDC hdc = GetDC(hwnd);
	if (bmp_source == NULL || img_w == 0 || img_h == 0) {
		char err_str[MAX_PATH] = { 0 };
		//sprintf(err_str, "Invalid Image! bmp_source:%d, img_w:%d, img_h:%d", bmp_source, img_w, img_h);
		//MessageBoxA(NULL, err_str, "Error", 0);
		return FALSE;
	}

	int origin = TRUE;
	int bitmap_depth = 8 * img_ch;
	BITMAPINFO *binfo = (BITMAPINFO *)bi_buf;

	assert(binfo && img_w >= 0 && img_h >= 0 && (bitmap_depth == 8 || bitmap_depth == 24 || bitmap_depth == 32));

	BITMAPINFOHEADER* bmih = &(binfo->bmiHeader);

	memset(bmih, 0, sizeof(*bmih));
	bmih->biSize = sizeof(BITMAPINFOHEADER);
	bmih->biWidth = img_w;
	bmih->biHeight = origin ? abs(img_h) : -abs(img_h);
	bmih->biPlanes = 1;
	bmih->biBitCount = (unsigned short)bitmap_depth;
	bmih->biCompression = BI_RGB;

	if (bitmap_depth == 8) {
		RGBQUAD* palette = binfo->bmiColors;
		for (int i = 0; i < 256; i++) {
			palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
			palette[i].rgbReserved = 0;
		}
	}
	hbitmap = CreateCompatibleBitmap(hdc, img_w, img_h);

	HDC memory_dc = CreateCompatibleDC(hdc);
	HBITMAP old_bitmap = (HBITMAP)SelectObject(memory_dc, hbitmap);

	::SetDIBitsToDevice(memory_dc, 0, 0, img_w, img_h,
		0, 0, 0, img_h,
		bmp_source,
		binfo, DIB_RGB_COLORS);

	DrawOnWnd(memory_dc, temp);
	SetStretchBltMode(hdc, stretch_mode);

	RECT rt_wnd;
	GetClientRect(hwnd, &rt_wnd);

	int wnd_w = rt_wnd.right - rt_wnd.left;
	int wnd_h = rt_wnd.bottom - rt_wnd.top;
	if (is_full_sized) {
		StretchBlt(hdc, 0, 0, wnd_w, wnd_h, memory_dc, start_x, start_y, wnd_w, wnd_h, SRCCOPY);
	}
	else StretchBlt(hdc, 0, 0, wnd_w, wnd_h, memory_dc, start_x, start_y, img_w, img_h, SRCCOPY);

	SelectObject(memory_dc, old_bitmap);
	DeleteObject(memory_dc);
	ReleaseDC(hwnd, hdc);

	//DeleteObject(hbitmap);
	//hbitmap = NULL;
	return 0;
}

BOOL Output::SaveLayers(const char * path, int img_w, int img_h)
{
	HDC hdc = ::GetDC(NULL);
	BITMAP bitmap;
	GetObject(hbitmap, sizeof(BITMAP), &bitmap);

	BITMAPINFOHEADER ih;
	ih.biSize = sizeof(BITMAPINFOHEADER);
	ih.biWidth = bitmap.bmWidth = img_w;
	ih.biHeight = bitmap.bmHeight = img_h;
	ih.biPlanes = 1;
	ih.biBitCount = bitmap.bmPlanes*bitmap.bmBitsPixel;
	ih.biCompression = BI_RGB;
	ih.biSizeImage = 0;
	ih.biXPelsPerMeter = 0;
	ih.biYPelsPerMeter = 0;
	ih.biClrUsed = 0;
	ih.biClrImportant = 0;
	if (ih.biBitCount > 8) ih.biBitCount = 24;

	int palette_size = (ih.biBitCount == 24 ? 0 : (1 << ih.biBitCount) * sizeof(RGBQUAD));

	BITMAPINFO *bitmap_info = (BITMAPINFO *)malloc(ih.biSize + palette_size);
	bitmap_info->bmiHeader = ih;

	GetDIBits(hdc, hbitmap, 0, bitmap.bmHeight, NULL, bitmap_info, DIB_RGB_COLORS);
	ih = bitmap_info->bmiHeader;

	if (ih.biSizeImage == 0) {
		ih.biSizeImage = ((((ih.biWidth*ih.biBitCount) + 31) & ~31) >> 3) * ih.biHeight;
	}

	DWORD new_size = ih.biSize + palette_size + ih.biSizeImage;
	bitmap_info = (BITMAPINFO *)realloc(bitmap_info, new_size);

	GetDIBits(hdc, hbitmap, 0, bitmap.bmHeight, (PBYTE)bitmap_info + ih.biSize + palette_size, bitmap_info, DIB_RGB_COLORS);

	BITMAPFILEHEADER fh;
	fh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + palette_size;
	fh.bfReserved1 = 0;
	fh.bfReserved2 = 0;
	fh.bfSize = new_size + sizeof(BITMAPFILEHEADER);
	fh.bfType = 0x4d42;

	char mypath[MAX_PATH] = { 0 };
	strcpy(mypath, path);
	if (strcmp((path + strlen(path) - 4), ".bmp") != 0) {
		strcat(mypath, ".bmp");
	}

	DWORD writen;
	HANDLE file = CreateFileA(mypath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, &fh, sizeof(fh), &writen, NULL);
	WriteFile(file, bitmap_info, new_size, &writen, NULL);

	CloseHandle(file);
	ReleaseDC(NULL, hdc);
	free(bitmap_info);
	return 0;
}

void Output::ClearStream(void)
{
	DeleteObject(hbitmap);
}

HBITMAP Output::get_hbitmap(void)
{
	DeleteObject(hbitmap);
	return HBITMAP();
}

void Output::DrawCrossline(HDC memdc, int center_x, int center_y, int width, int height)
{
	MoveToEx(memdc, center_x - width / 2, center_y, NULL);
	LineTo(memdc, center_x + width / 2, center_y);

	MoveToEx(memdc, center_x, center_y - height / 2, NULL);
	LineTo(memdc, center_x, center_y + height / 2);
}

void Output::DrawRect(HDC memdc, int center_x, int center_y, int width, int height)
{
	int line_w = width / 20;
	int line_h = height / 20;

	MoveToEx(memdc, center_x - width / 2, center_y - height / 2, NULL);
	LineTo(memdc, center_x - width / 2, center_y - height / 2 + line_h);
	MoveToEx(memdc, center_x - width / 2, center_y - line_h, NULL);
	LineTo(memdc, center_x - width / 2, center_y + line_h);
	MoveToEx(memdc, center_x - width / 2, center_y + height / 2 - line_h, NULL);
	LineTo(memdc, center_x - width / 2, center_y + height / 2);
	LineTo(memdc, center_x - width / 2 + line_w, center_y + height / 2);
	MoveToEx(memdc, center_x - line_w, center_y + height / 2, NULL);
	LineTo(memdc, center_x + line_w, center_y + height / 2);
	MoveToEx(memdc, center_x + width / 2 - line_w, center_y + height / 2, NULL);
	LineTo(memdc, center_x + width / 2, center_y + height / 2);
	LineTo(memdc, center_x + width / 2, center_y + height / 2 - line_h);
	MoveToEx(memdc, center_x + width / 2, center_y - line_h, NULL);
	LineTo(memdc, center_x + width / 2, center_y + line_h);
	MoveToEx(memdc, center_x + width / 2, center_y - height / 2 + line_h, NULL);
	LineTo(memdc, center_x + width / 2, center_y - height / 2);
	LineTo(memdc, center_x + width / 2 - line_w, center_y - height / 2);
	MoveToEx(memdc, center_x + line_w, center_y - height / 2, NULL);
	LineTo(memdc, center_x - line_w, center_y - height / 2);
	MoveToEx(memdc, center_x - width / 2 + line_w, center_y - height / 2, NULL);
	LineTo(memdc, center_x - width / 2, center_y - height / 2);
}

void OutputImage::DrawOnWnd(HDC memdc, LPVOID temp) {

	SetBkMode(memdc, TRANSPARENT);
	SelectObject(memdc, GetStockObject(NULL_BRUSH));

	hfont = CreateFont(20, 0, 0, 0, 20, 0, 0, 0, ANSI_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, L"ºÚÌå");
	old_font = (HFONT)SelectObject(memdc, hfont);
	pen = CreatePen(PS_SOLID, 3, COLOR_BLUE);
	old_pen = (HPEN)SelectObject(memdc, pen);

	switch (gSystemMgr.m_nTestMode) {
	case SHOW_IMAGE:
		break;
	case SFR_TEST:
		gSystemMgr.DrawTestResultChart(memdc);
		break;
	}

	DeleteObject(hfont);
	SelectObject(memdc, (HFONT)old_font);

	DeleteObject(pen);
	SelectObject(memdc, (HPEN)old_pen);
}

Convert::Convert()
{
	is_table_inited = FALSE;

	table_y = new BYTE[256 * 256 * 256];
	table_r = new BYTE[256 * 256];
	table_g = new BYTE[256 * 256 * 256];
	table_b = new BYTE[256 * 256];
}

Convert::~Convert()
{
	if (table_y != NULL) delete[] table_y;
	if (table_r != NULL) delete[] table_r;
	if (table_g != NULL) delete[] table_g;
	if (table_b != NULL) delete[] table_b;
}

BOOL Convert::init_lib()
{
	if (table_y == NULL) {
		is_table_inited = FALSE;
		return FALSE;
	}
	else {
		is_table_inited = TRUE;
	}
	create_yuv_table();

	if (table_r == NULL || table_g == NULL || table_b == NULL) {
		is_table_inited = FALSE;
		return FALSE;
	}
	else {
		is_table_inited = TRUE;
	}
	create_rgb_table();

	return is_table_inited;
	return 0;
}

void Convert::YCbCrITUToBmp(int iMode, BYTE * pYuvBuffer, BYTE * pBmpBuffer, int size_x, int size_y)
{
	DWORD		 Y0, Y1, Cb, Cr; //speed up!!!
	int			 tmp;
	int			 i, j;
	LPBYTE       pImageData, pImageTemp;

	pImageData = pYuvBuffer + size_x * 2 * (size_y - 1);

	switch (iMode) {
	case 3: //CbYCrY
		for (i = 0; i < size_y; i++) {
			pImageTemp = pImageData;
			for (j = 0; j < size_x; j += 2) {
				Y0 = pImageTemp[1];
				Cr = pImageTemp[2];
				Y1 = pImageTemp[3];
				Cb = pImageTemp[0];
				*pBmpBuffer++ = BtblITU[Y0][Cb];    //B
				tmp = (int)(1192 * (Y0 - 16) - 832 * (Cr - 128) - 400 * (Cb - 128)) >> 10;
				if (tmp > 255)  tmp = 255;
				if (tmp < 0)    tmp = 0;
				*pBmpBuffer++ = tmp;				//G
				*pBmpBuffer++ = RtblITU[Y0][Cr];	//R

				*pBmpBuffer++ = BtblITU[Y1][Cb];	 //B
				tmp = (int)(1192 * (Y1 - 16) - 832 * (Cr - 128) - 400 * (Cb - 128)) >> 10;
				if (tmp > 255)  tmp = 255;
				if (tmp < 0)    tmp = 0;
				*pBmpBuffer++ = tmp;				 //G
				*pBmpBuffer++ = RtblITU[Y1][Cr];	 //R
				pImageTemp += 4;  //next pair.
			}
			pImageData -= size_x * 2;
		}
		break;
	case 2: //YCrYCb
		for (i = 0; i < size_y; i++) {
			pImageTemp = pImageData;
			for (j = 0; j < size_x; j += 2) {
				Y0 = pImageTemp[0];
				Cr = pImageTemp[1];
				Y1 = pImageTemp[2];
				Cb = pImageTemp[3];
				*pBmpBuffer++ = BtblITU[Y0][Cb];		 //B
				tmp = (int)(1192 * (Y0 - 16) - 832 * (Cr - 128) - 400 * (Cb - 128)) >> 10;
				if (tmp > 255)  tmp = 255;
				if (tmp < 0)    tmp = 0;
				*pBmpBuffer++ = tmp;				 //G
				*pBmpBuffer++ = RtblITU[Y0][Cr];     //R

				*pBmpBuffer++ = BtblITU[Y1][Cb];	 //B	
				tmp = (int)(1192 * (Y1 - 16) - 832 * (Cr - 128) - 400 * (Cb - 128)) >> 10;
				if (tmp > 255)  tmp = 255;
				if (tmp < 0)    tmp = 0;
				*pBmpBuffer++ = tmp;				 //G
				*pBmpBuffer++ = RtblITU[Y1][Cr];     //R
				pImageTemp += 4;	//next  pair.
			}
			pImageData -= size_x * 2;
		}
		break;
	case 1: //YCbYCr
		for (i = 0; i < size_y; i++) {
			pImageTemp = pImageData;
			for (j = 0; j < size_x; j += 2) {
				Y0 = pImageTemp[0];
				Cr = pImageTemp[3];
				Y1 = pImageTemp[2];
				Cb = pImageTemp[1];
				*pBmpBuffer++ = BtblITU[Y0][Cb];		 //B
				tmp = (int)(1192 * (Y0 - 16) - 832 * (Cr - 128) - 400 * (Cb - 128)) >> 10;
				if (tmp > 255)  tmp = 255;
				if (tmp < 0)    tmp = 0;
				*pBmpBuffer++ = tmp;				 //G
				*pBmpBuffer++ = RtblITU[Y0][Cr];	 //R

				*pBmpBuffer++ = BtblITU[Y1][Cb];	 //B
				tmp = (int)(1192 * (Y1 - 16) - 832 * (Cr - 128) - 400 * (Cb - 128)) >> 10;
				if (tmp > 255)  tmp = 255;
				if (tmp < 0)    tmp = 0;
				*pBmpBuffer++ = tmp;				 //G
				*pBmpBuffer++ = RtblITU[Y1][Cr];	 //R
				pImageTemp += 4;  //next YCbYCr pair.
			}
			pImageData -= size_x * 2;
		}
		break;
	case 4: //CrYCbY
		for (i = 0; i < size_y; i++) {
			pImageTemp = pImageData;
			for (j = 0; j < size_x; j += 2) {
				Y0 = pImageTemp[1];
				Cr = pImageTemp[0];
				Y1 = pImageTemp[3];
				Cb = pImageTemp[2];
				*pBmpBuffer++ = BtblITU[Y0][Cb];     //B
				tmp = (int)(1192 * (Y0 - 16) - 832 * (Cr - 128) - 400 * (Cb - 128)) >> 10;
				if (tmp > 255)  tmp = 255;
				if (tmp < 0)    tmp = 0;
				*pBmpBuffer++ = tmp;				 //G
				*pBmpBuffer++ = RtblITU[Y0][Cr];	 //R

				*pBmpBuffer++ = BtblITU[Y1][Cb];   //B
				tmp = (int)(1192 * (Y1 - 16) - 832 * (Cr - 128) - 400 * (Cb - 128)) >> 10;
				if (tmp > 255)  tmp = 255;
				if (tmp < 0)    tmp = 0;
				*pBmpBuffer++ = tmp;				 //G
				*pBmpBuffer++ = RtblITU[Y1][Cr];	 //R
				pImageTemp += 4;  //next  pair
			}
			pImageData -= size_x * 2;
		}
		break;
	}
}

void Convert::bmp24_to_y8(const BYTE *bmp_source, int bmp_w, int bmp_h, RECT *y_rect, BYTE *y_data)
{
	if (is_table_inited == FALSE) {
		MessageBox(NULL, L"bmp lib need to init first.", L"Warning", 0);
		return;
	}

	int x_offset = 0, y_offset = 0, offset = 0;
	int w = 0, h = 0, top = 0, bottom = 0, left = 0, right = 0;

	if (y_rect == NULL) {
		w = bmp_w;
		h = bmp_h;
		top = 0;
		left = 0;
		bottom = bmp_h;
		right = bmp_w;
	}
	else {
		w = y_rect->right - y_rect->left;
		h = y_rect->bottom - y_rect->top;
		top = y_rect->top;
		bottom = y_rect->bottom;
		left = y_rect->left;
		right = y_rect->right;
	}

	//	int x_cnt = (bmp_w*24+31)/32*4;
	int x_cnt = bmp_w * 3;

	for (int y = top; y < bottom; y++) {
		y_offset = (bmp_h - y - 1)*x_cnt;

		offset = w * (h - (y - top) - 1) - left;

		for (int x = left; x < right; x++) {
			x_offset = y_offset + x * 3;
			y_data[offset + x] = table_y[(bmp_source[x_offset + 2] << 16) + (bmp_source[x_offset + 1] << 8) + bmp_source[x_offset + 0]];
		}
	}
}

void Convert::bmp24_to_b24(const BYTE * bmp_source, int bmp_w, int bmp_h, RECT * y_rect, BYTE * bmp_data)
{
	if (is_table_inited == FALSE) {
		MessageBox(NULL, L"bmp lib need to init first.", L"Warning", 0);
		return;
	}

	int x_offset = 0, y_offset = 0, offset = 0;
	int w = 0, h = 0, top = 0, bottom = 0, left = 0, right = 0;

	if (y_rect == NULL) {
		w = bmp_w;
		h = bmp_h;
		top = 0;
		left = 0;
		bottom = bmp_h;
		right = bmp_w;
	}
	else {
		w = y_rect->right - y_rect->left;
		h = y_rect->bottom - y_rect->top;
		top = y_rect->top;
		bottom = y_rect->bottom;
		left = y_rect->left;
		right = y_rect->right;
	}

	int x_cnt = bmp_w * 3;

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			bmp_data[y * 3 * w + x * 3 + 0] = bmp_source[(top + y) * bmp_w * 3 + (left + x) * 3 + 0];
			bmp_data[y * 3 * w + x * 3 + 1] = bmp_source[(top + y) * bmp_w * 3 + (left + x) * 3 + 1];
			bmp_data[y * 3 * w + x * 3 + 2] = bmp_source[(top + y) * bmp_w * 3 + (left + x) * 3 + 2];
		}
	}
}

void Convert::bmp24_to_y24(const BYTE *bmp_source, int bmp_w, int bmp_h, RECT *y_rect, BYTE *y_data)
{
	if (is_table_inited == FALSE) {
		MessageBox(NULL, L"bmp lib need to init first.", L"Warning", 0);
		return;
	}

	int x_offset = 0, y_offset = 0, offset = 0;
	int w = 0, h = 0, top = 0, bottom = 0, left = 0, right = 0;

	if (y_rect == NULL) {
		w = bmp_w;
		h = bmp_h;
		top = 0;
		left = 0;
		bottom = bmp_h;
		right = bmp_w;
	}
	else {
		w = y_rect->right - y_rect->left;
		h = y_rect->bottom - y_rect->top;
		top = y_rect->top;
		bottom = y_rect->bottom;
		left = y_rect->left;
		right = y_rect->right;
	}

	//	int x_cnt = (bmp_w*24+31)/32*4;
	int x_cnt = bmp_w * 3;

	for (int y = top; y < bottom; y++) {
		y_offset = (bmp_h - y - 1)*x_cnt;

		offset = w * (h - (y - top) - 1) - left;

		for (int x = left; x < right; x++) {
			x_offset = y_offset + x * 3;
			y_data[(offset + x) * 3] = table_y[(bmp_source[x_offset + 2] << 16) + (bmp_source[x_offset + 1] << 8) + bmp_source[x_offset + 0]];
			y_data[(offset + x) * 3 + 1] = y_data[(offset + x) * 3];
			y_data[(offset + x) * 3 + 2] = y_data[(offset + x) * 3];
		}
	}

}

void Convert::yuv422_to_bmp24(int data_order, BYTE *yuv, BYTE *bmp, int img_w, int img_h)
{
	if (is_table_inited == FALSE) {
		MessageBox(NULL, L"bmp lib need to init first.", L"Warning", 0);
		return;
	}

	if (data_order < 0 || data_order>3) {
		MessageBox(NULL, L"select data order from 0~3", L"Warning", 0);
		return;
	}

	DWORD y0, y1, cb, cr;
	int i, j;

	unsigned char *begin_line = yuv + img_w * 2 * (img_h - 1);
	unsigned char *f0;

	switch (data_order)
	{
	case YUV_OUTPUT_YCBYCR:
		for (i = 0; i < img_h; i++) {
			f0 = begin_line;
			for (j = 0; j < img_w; j += 2) {
				y0 = f0[0]; cb = f0[1]; y1 = f0[2]; cr = f0[3];

				*bmp++ = table_b[(y0 << 8) + cb];
				*bmp++ = table_g[(y0 << 16) + (cr << 8) + cb];
				*bmp++ = table_r[(y0 << 8) + cr];

				*bmp++ = table_b[(y1 << 8) + cb];
				*bmp++ = table_g[(y1 << 16) + (cr << 8) + cb];
				*bmp++ = table_r[(y1 << 8) + cr];

				f0 += 4;
			}
			begin_line -= img_w * 2;
		}
		break;

	case YUV_OUTPUT_YCRYCB:
		for (i = 0; i < img_h; i++) {
			f0 = begin_line;
			for (j = 0; j < img_w; j += 2) {
				y0 = f0[0]; cr = f0[1]; y1 = f0[2]; cb = f0[3];

				*bmp++ = table_b[(y0 << 8) + cb];
				*bmp++ = table_g[(y0 << 16) + (cr << 8) + cb];
				*bmp++ = table_r[(y0 << 8) + cr];

				*bmp++ = table_b[(y1 << 8) + cb];
				*bmp++ = table_g[(y1 << 16) + (cr << 8) + cb];
				*bmp++ = table_r[(y1 << 8) + cr];

				f0 += 4;
			}
			begin_line -= img_w * 2;
		}
		break;

	case YUV_OUTPUT_CBYCRY:
		for (i = 0; i < img_h; i++) {
			f0 = begin_line;
			for (j = 0; j < img_w; j += 2) {
				cb = f0[0]; y0 = f0[1]; cr = f0[2]; y1 = f0[3];

				*bmp++ = table_b[(y0 << 8) + cb];
				*bmp++ = table_g[(y0 << 16) + (cr << 8) + cb];
				*bmp++ = table_r[(y0 << 8) + cr];

				*bmp++ = table_b[(y1 << 8) + cb];
				*bmp++ = table_g[(y1 << 16) + (cr << 8) + cb];
				*bmp++ = table_r[(y1 << 8) + cr];

				f0 += 4;
			}
			begin_line -= img_w * 2;
		}
		break;

	case YUV_OUTPUT_CRYCBY:
		for (i = 0; i < img_h; i++) {
			f0 = begin_line;
			for (j = 0; j < img_w; j += 2) {
				cr = f0[0]; y0 = f0[1]; cb = f0[2]; y1 = f0[3];

				*bmp++ = table_b[(y0 << 8) + cb];
				*bmp++ = table_g[(y0 << 16) + (cr << 8) + cb];
				*bmp++ = table_r[(y0 << 8) + cr];

				*bmp++ = table_b[(y1 << 8) + cb];
				*bmp++ = table_g[(y1 << 16) + (cr << 8) + cb];
				*bmp++ = table_r[(y1 << 8) + cr];

				f0 += 4;
			}
			begin_line -= img_w * 2;
		}
		break;
	}
}

void Convert::raw8_to_bmp24_y(int data_order, BYTE *raw8, BYTE *bmp_y, int img_w, int img_h)
{
	if (is_table_inited == FALSE) {
		MessageBox(NULL, L"bmp lib need to init first.", L"Warning", 0);
		return;
	}

	if (data_order < 0 || data_order>3) {
		MessageBox(NULL, L"select data order from 0~3", L"Warning", 0);
		return;
	}

	unsigned char *begin_line = raw8 + img_w * (img_h - 1);
	unsigned char *f0, *f1;
	unsigned char *bmp0 = bmp_y;
	unsigned char r = 0, g = 0, b = 0, y = 0;

	int i = 0, j = 0;
	switch (data_order)
	{
	case RAW_OUTPUT_BGGR:
		for (j = 0; j < img_h - 2; j += 2) {
			f0 = begin_line;
			f1 = f0 - img_w;

			for (i = 0; i < img_w - 2; i += 2) {
				y = table_y[(f0[1] << 16) + (((f0[0] + f1[1]) >> 1) << 8) + f1[0]];
				*bmp0++ = y;
				*bmp0++ = y;
				*bmp0++ = y;
				f0 += 1; f1 += 1;

				y = table_y[(f0[0] << 16) + (((f0[1] + f1[0]) >> 1) << 8) + f1[1]];
				*bmp0++ = y;
				*bmp0++ = y;
				*bmp0++ = y;
				f0 += 1; f1 += 1;
			}

			for (i = 0; i < 2; i++) {
				y = table_y[(f0[1] << 16) + (((f0[0] + f1[1]) >> 1) << 8) + f1[0]];
				*bmp0++ = y;
				*bmp0++ = y;
				*bmp0++ = y;
			}

			begin_line -= img_w;
			f0 = begin_line;
			f1 = f0 - img_w;

			for (i = 0; i < img_w - 2; i += 2) {
				y = table_y[(f1[1] << 16) + (((f0[1] + f1[0]) >> 1) << 8) + f0[0]];
				*bmp0++ = y;
				*bmp0++ = y;
				*bmp0++ = y;
				f0 += 1; f1 += 1;

				y = table_y[(f1[0] << 16) + (((f0[0] + f1[1]) >> 1) << 8) + f0[1]];
				*bmp0++ = y;
				*bmp0++ = y;
				*bmp0++ = y;
				f0 += 1; f1 += 1;

			}
			for (i = 0; i < 2; i++) {
				y = table_y[(f1[1] << 16) + (((f0[1] + f1[0]) >> 1) << 8) + f0[0]];
				*bmp0++ = y;
				*bmp0++ = y;
				*bmp0++ = y;
			}
			begin_line -= img_w/**2*/;
		}

		for (i = 0; i < img_w * 3; i++)	*bmp0++ = *(bmp0 - img_w * 3);
		for (i = 0; i < img_w * 3; i++)	*bmp0++ = *(bmp0 - img_w * 3);
		break;

	case RAW_OUTPUT_RGGB:
		for (j = 0; j < img_h - 2; j += 2) {
			f0 = begin_line;
			f1 = f0 - img_w;

			for (i = 0; i < img_w - 2; i += 2) {
				y = table_y[(f1[0] << 16) + (((f0[0] + f1[1]) >> 1) << 8) + f0[1]];
				*bmp0++ = y;
				*bmp0++ = y;
				*bmp0++ = y;
				f0 += 1; f1 += 1;

				y = table_y[(f1[1] << 16) + (((f0[1] + f1[0]) >> 1) << 8) + f0[0]];
				*bmp0++ = y;
				*bmp0++ = y;
				*bmp0++ = y;
				f0 += 1; f1 += 1;
			}

			for (i = 0; i < 2; i++) {
				y = table_y[(f1[0] << 16) + (((f0[0] + f1[1]) >> 1) << 8) + f0[1]];
				*bmp0++ = y;
				*bmp0++ = y;
				*bmp0++ = y;
			}

			begin_line -= img_w;
			f0 = begin_line;
			f1 = f0 - img_w;

			for (i = 0; i < img_w - 2; i += 2) {
				y = table_y[(f0[0] << 16) + (((f0[1] + f1[0]) >> 1) << 8) + f1[1]];
				*bmp0++ = y;
				*bmp0++ = y;
				*bmp0++ = y;
				f0 += 1; f1 += 1;

				y = table_y[(f0[1] << 16) + (((f0[0] + f1[1]) >> 1) << 8) + f1[0]];
				*bmp0++ = y;
				*bmp0++ = y;
				*bmp0++ = y;
				f0 += 1; f1 += 1;

			}
			for (i = 0; i < 2; i++) {
				y = table_y[(f0[0] << 16) + (((f0[1] + f1[0]) >> 1) << 8) + f1[1]];
				*bmp0++ = y;
				*bmp0++ = y;
				*bmp0++ = y;

			}
			begin_line -= img_w/**2*/;
		}

		for (i = 0; i < img_w * 3; i++)	*bmp0++ = *(bmp0 - img_w * 3);
		for (i = 0; i < img_w * 3; i++)	*bmp0++ = *(bmp0 - img_w * 3);

		break;
	case RAW_OUTPUT_GBRG:
		for (j = 0; j < img_h - 2; j += 2) {
			f0 = begin_line;
			f1 = f0 - img_w;

			for (i = 0; i < img_w - 2; i += 2) {
				y = table_y[(f0[0] << 16) + (((f0[1] + f1[0]) >> 1) << 8) + f1[1]];
				*bmp0++ = y;
				*bmp0++ = y;
				*bmp0++ = y;
				f0 += 1; f1 += 1;

				y = table_y[(f0[1] << 16) + (((f0[0] + f1[1]) >> 1) << 8) + f1[0]];
				*bmp0++ = y;
				*bmp0++ = y;
				*bmp0++ = y;
				f0 += 1; f1 += 1;
			}

			for (i = 0; i < 2; i++) {
				y = table_y[(f0[0] << 16) + (((f0[1] + f1[0]) >> 1) << 8) + f1[1]];
				*bmp0++ = y;
				*bmp0++ = y;
				*bmp0++ = y;
			}

			begin_line -= img_w;
			f0 = begin_line;
			f1 = f0 - img_w;

			for (i = 0; i < img_w - 2; i += 2) {
				y = table_y[(f1[0] << 16) + (((f0[0] + f1[1]) >> 1) << 8) + f0[1]];
				*bmp0++ = y;
				*bmp0++ = y;
				*bmp0++ = y;
				f0 += 1; f1 += 1;

				y = table_y[(f1[1] << 16) + (((f0[1] + f1[0]) >> 1) << 8) + f0[0]];
				*bmp0++ = y;
				*bmp0++ = y;
				*bmp0++ = y;
				f0 += 1; f1 += 1;

			}
			for (i = 0; i < 2; i++) {
				y = table_y[(f1[0] << 16) + (((f0[0] + f1[1]) >> 1) << 8) + f0[1]];
				*bmp0++ = y;
				*bmp0++ = y;
				*bmp0++ = y;
			}
			begin_line -= img_w/**2*/;
		}

		for (i = 0; i < img_w * 3; i++)	*bmp0++ = *(bmp0 - img_w * 3);
		for (i = 0; i < img_w * 3; i++)	*bmp0++ = *(bmp0 - img_w * 3);
		break;

	case RAW_OUTPUT_GRBG:
		//BGBGBG
		//GRGRGR
		//BGBGBG
		for (j = 0; j < img_h - 2; j += 2) {
			f0 = begin_line;
			f1 = f0 - img_w;

			for (i = 0; i < img_w - 2; i += 2) {
				y = table_y[(f1[1] << 16) + (((f0[1] + f1[0]) >> 1) << 8) + f0[0]];
				*bmp0++ = y;
				*bmp0++ = y;
				*bmp0++ = y;
				f0 += 1; f1 += 1;

				y = table_y[(f1[0] << 16) + (((f0[0] + f1[1]) >> 1) << 8) + f0[1]];
				*bmp0++ = y;
				*bmp0++ = y;
				*bmp0++ = y;
				f0 += 1; f1 += 1;
			}

			for (i = 0; i < 2; i++) {
				y = table_y[(f1[1] << 16) + (((f0[1] + f1[0]) >> 1) << 8) + f0[0]];
				*bmp0++ = y;
				*bmp0++ = y;
				*bmp0++ = y;
			}

			begin_line -= img_w;
			f0 = begin_line;
			f1 = f0 - img_w;
			//GRGRGR
			//BGBGBG			
			for (i = 0; i < img_w - 2; i += 2) {
				y = table_y[(f0[1] << 16) + (((f0[0] + f1[1]) >> 1) << 8) + f1[0]];
				*bmp0++ = y;
				*bmp0++ = y;
				*bmp0++ = y;
				f0 += 1; f1 += 1;

				y = table_y[(f0[0] << 16) + (((f0[1] + f1[0]) >> 1) << 8) + f1[1]];
				*bmp0++ = y;
				*bmp0++ = y;
				*bmp0++ = y;
				f0 += 1; f1 += 1;
			}
			for (i = 0; i < 2; i++) {
				y = table_y[(f0[1] << 16) + (((f0[0] + f1[1]) >> 1) << 8) + f1[0]];
				*bmp0++ = y;
				*bmp0++ = y;
				*bmp0++ = y;
			}
			begin_line -= img_w/**2*/;
		}

		for (i = 0; i < img_w * 3; i++)	*bmp0++ = *(bmp0 - img_w * 3);
		for (i = 0; i < img_w * 3; i++)	*bmp0++ = *(bmp0 - img_w * 3);

		break;
	}
}

BOOL Convert::get_bmp_roi_avg_val(const BYTE *bmp_source, int bmp_w, int bmp_h, RECT *roi, float &avg_y, float &avg_cb, float &avg_cr)
{
	int roi_w = roi->right - roi->left;
	int roi_h = roi->bottom - roi->top;

	int r, g, b;
	float y, cb, cr;
	float sum_y = 0, sum_cb = 0, sum_cr = 0;

	for (int j = roi->top; j < roi->bottom; j++) {
		for (int i = roi->left; i < roi->right; i++) {
			r = bmp_source[PIXEL_R(i, j, bmp_w, bmp_h)];
			g = bmp_source[PIXEL_G(i, j, bmp_w, bmp_h)];
			b = bmp_source[PIXEL_B(i, j, bmp_w, bmp_h)];

			y = (float)(0.299f*r + 0.587f*g + 0.114f*b);
			cb = (float)(b - y)*0.493f + 128;
			cr = (float)(r - y)*0.877f + 128;

			sum_y += y;
			sum_cb += cb;
			sum_cr += cr;
		}
	}

	avg_y = (float)sum_y / (roi_w*roi_h);
	avg_cb = (float)sum_cb / (roi_w*roi_h);
	avg_cr = (float)sum_cr / (roi_w*roi_h);

	return TRUE;
}

BOOL Convert::save_jpg24_image(const char * img_path, BYTE * bmp, int img_w, int img_h)
{
	HFILE			 file;
	BITMAPFILEHEADER bmp_header; // Header for Bitmap file
	BITMAPINFO		 bmp_info;
	char path[MAX_PATH] = { 0 };

	strcpy(path, img_path);
	int w_cnt = (img_w * 24 + 31) / 32 * 4;
	int shift_bits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	DWORD image_size = w_cnt * img_h;

	bmp_header.bfType = ((WORD)('M' << 8) | 'B');
	bmp_header.bfSize = shift_bits + image_size;
	bmp_header.bfReserved1 = 0;
	bmp_header.bfReserved2 = 0;
	bmp_header.bfOffBits = shift_bits;

	bmp_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmp_info.bmiHeader.biWidth = img_w;
	bmp_info.bmiHeader.biHeight = img_h;
	bmp_info.bmiHeader.biPlanes = 1;
	bmp_info.bmiHeader.biBitCount = 24;
	bmp_info.bmiHeader.biCompression = BI_RGB;
	bmp_info.bmiHeader.biSizeImage = 0;
	bmp_info.bmiHeader.biXPelsPerMeter = 0;
	bmp_info.bmiHeader.biYPelsPerMeter = 0;
	bmp_info.bmiHeader.biClrUsed = 0;
	bmp_info.bmiHeader.biClrImportant = 0;

	if (strcmp((path + strlen(path) - 4), ".jpg") != 0)
	{
		strcat_s(path, ".jpg");
	}

	file = _lcreat(path, 0);
	if (file < 0) return FALSE;


	UINT len;
	len = _lwrite(file, (LPSTR)&bmp_header, sizeof(BITMAPFILEHEADER));
	len = _lwrite(file, (LPSTR)&bmp_info, sizeof(BITMAPINFOHEADER));
	for (int j = 0; j < img_h; j++)
	{
		len = _lwrite(file, (LPSTR)bmp + w_cnt * j, w_cnt);
	}
	//	len = _lwrite(file, "0000", 4);
	//	len = _lwrite(file, (LPSTR)bmp, bmp_header.bfSize - sizeof(bmp_header) - sizeof(bmp_info)+4);  //+4 is for exact filesize
	_lclose(file);

	return 0;
}

BOOL Convert::save_bmp24_image(const char * img_path, BYTE * bmp, int img_w, int img_h)
{
	HFILE			 file;
	BITMAPFILEHEADER bmp_header; // Header for Bitmap file
	BITMAPINFO		 bmp_info;
	char path[MAX_PATH] = { 0 };

	strcpy(path, img_path);
	int w_cnt = (img_w * 24 + 31) / 32 * 4;
	int shift_bits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	DWORD image_size = w_cnt * img_h;

	bmp_header.bfType = ((WORD)('M' << 8) | 'B');
	bmp_header.bfSize = shift_bits + image_size;
	bmp_header.bfReserved1 = 0;
	bmp_header.bfReserved2 = 0;
	bmp_header.bfOffBits = shift_bits;

	bmp_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmp_info.bmiHeader.biWidth = img_w;
	bmp_info.bmiHeader.biHeight = img_h;
	bmp_info.bmiHeader.biPlanes = 1;
	bmp_info.bmiHeader.biBitCount = 24;
	bmp_info.bmiHeader.biCompression = BI_RGB;
	bmp_info.bmiHeader.biSizeImage = 0;
	bmp_info.bmiHeader.biXPelsPerMeter = 0;
	bmp_info.bmiHeader.biYPelsPerMeter = 0;
	bmp_info.bmiHeader.biClrUsed = 0;
	bmp_info.bmiHeader.biClrImportant = 0;

	if (strcmp((path + strlen(path) - 4), ".bmp") != 0) {
		strcat_s(path, ".bmp");
	}

	file = _lcreat(path, 0);
	if (file < 0) return FALSE;


	UINT len;
	len = _lwrite(file, (LPSTR)&bmp_header, sizeof(BITMAPFILEHEADER));
	len = _lwrite(file, (LPSTR)&bmp_info, sizeof(BITMAPINFOHEADER));
	for (int j = 0; j < img_h; j++) {
		len = _lwrite(file, (LPSTR)bmp + w_cnt * j, w_cnt);
	}
	//	len = _lwrite(file, "0000", 4);
	//	len = _lwrite(file, (LPSTR)bmp, bmp_header.bfSize - sizeof(bmp_header) - sizeof(bmp_info)+4);  //+4 is for exact filesize
	_lclose(file);

	return 0;
}
BOOL Convert::save_bmp8_image(const char *img_path, BYTE *bmp, int img_w, int img_h)
{
	FILE *BinFile;
	BITMAPFILEHEADER FileHeader;
	BITMAPINFOHEADER BmpHeader;
	int i, extend;
	bool Suc = true;
	BYTE p[4], *pCur;

	char path[MAX_PATH] = { 0 };
	strcpy(path, img_path);
	if (strcmp((img_path + strlen(img_path) - 4), ".bmp") != 0) {
		strcat(path, ".bmp");
	}
	//Create File
	if ((BinFile = fopen(path, "w+b")) == NULL) return false;
	//Fill the FileHeader
	FileHeader.bfType = ((WORD)('M' << 8) | 'B');
	FileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 256 * 4L;
	FileHeader.bfSize = FileHeader.bfOffBits + img_w * img_h;
	FileHeader.bfReserved1 = 0;
	FileHeader.bfReserved2 = 0;
	if (fwrite((void *)&FileHeader, 1, sizeof(FileHeader), BinFile) != sizeof(FileHeader)) Suc = false;

	//Fill the ImgHeader
	BmpHeader.biSize = 40;
	BmpHeader.biWidth = img_w;
	BmpHeader.biHeight = img_h;
	BmpHeader.biPlanes = 1;
	BmpHeader.biBitCount = 8;
	BmpHeader.biCompression = 0;
	BmpHeader.biSizeImage = 0;
	BmpHeader.biXPelsPerMeter = 0;
	BmpHeader.biYPelsPerMeter = 0;
	BmpHeader.biClrUsed = 0;
	BmpHeader.biClrImportant = 0;
	if (fwrite((void *)&BmpHeader, 1, sizeof(BmpHeader), BinFile) != sizeof(BmpHeader))  Suc = false;
	//write Pallete
	for (i = 0, p[3] = 0; i < 256; i++) {
		p[3] = 0;
		p[0] = p[1] = p[2] = i;
		if (fwrite((void *)p, 1, 4, BinFile) != 4) { Suc = false; break; };
	}

	extend = (img_w + 3) / 4 * 4 - img_w;
	if (extend == 0) {
		for (pCur = bmp; pCur <= bmp + (img_h - 1)*img_w; pCur += img_w) {
			if (fwrite((void *)pCur, 1, img_w, BinFile) != (unsigned int)img_w) Suc = false;
		}
	}
	else {
		for (pCur = bmp; pCur <= bmp + (img_h - 1)*img_w; pCur += img_w) {
			if (fwrite((void *)pCur, 1, img_w, BinFile) != (unsigned int)img_w) Suc = false;
			for (i = 0; i < extend; i++) {
				if (fwrite((void *)(pCur + img_w - 1), 1, 1, BinFile) != 1)  Suc = false;
			}
		}
	}
	fclose(BinFile);
	return Suc;
}

void Convert::create_yuv_table(void)
{
	int val_y = 0;
	for (int i = 0; i < 256; i++) { //r
		for (int j = 0; j < 256; j++) { //g
			for (int k = 0; k < 256; k++) { //b
				//	val_y = 0.299*(float)r + 0.587*(float)g + 0.114*(float)b + 0.5;		
				//	val_u = 128.0 + (-37.797 * r -  74.203 * g + 112    * b ) / 255.0;
				//	val_v = 128.0 + ( 112.0  * r -  93.786 * g - 18.214 * b ) / 255.0;
				val_y = (int)((1225 * i + 2404 * j + 467 * k) >> 12);
				table_y[(i << 16) + (j << 8) + k] = CLIP(val_y, 0, 255);
			}
		}
	}
}

void Convert::create_rgb_table(void)
{
	int temp = 0;
	for (int y = 0; y < 256; y++) {
		for (int cr = 0; cr < 256; cr++) {
			for (int cb = 0; cb < 256; cb++) {
				//			temp = (int)(1.164*(y-16)+2.018*(cb-128)); //b
				temp = (int)((4768 * y + 8266 * cb - 1134336) >> 12);
				table_b[(y << 8) + cb] = CLIP(temp, 0, 255);

				//			temp = (int)(1.164*(y-16)-0.813*(cr-128)-0.391*(cb-128)); //g
				temp = (int)((4768 * y - 3330 * cr - 1602 * cb + 555008) >> 12);
				table_g[(y << 16) + (cr << 8) + cb] = CLIP(temp, 0, 255);

				//			temp = (int)(1.164*(y-16)+1.596*(cr-128)); //r
				temp = (int)((4768 * y + 6537 * cr - 913024) >> 12);
				table_r[(y << 8) + cr] = CLIP(temp, 0, 255);
			}
		}
	}
}

void roi_column_to_row(BYTE *roi_data, int roi_w, int roi_h)
{
	assert(roi_data != NULL && roi_w != 0 && roi_h != 0);
	BYTE *buffer = new BYTE[roi_w*roi_h];
	int i = 0, j = 0;

	for (i = 0; i < roi_w; i++) {
		for (j = 0; j < roi_h; j++) {
			(buffer)[(i*(long)roi_h) + j] = (roi_data)[((long)roi_w*j) + i];
		}
	}
	for (i = 0; i < roi_w; i++) {
		for (j = 0; j < roi_h; j++) {
			(roi_data)[(i*(long)roi_h) + j] = (buffer)[(i*(long)roi_h) + j];
		}
	}

	delete[] buffer;
}

//Mat TransBufferToMat(unsigned char* pBuffer, int nWidth, int nHeight, int nBandNum, int nBPB = 1) {
//	Mat mDst;
//	if (nBandNum == 4) {
//		if (nBPB == 1) {
//			mDst = Mat::zeros(Size(nWidth, nHeight), CV_8UC4);
//		}
//		else {
//			mDst = Mat::zeros(Size(nWidth, nHeight), CV_16UC4);
//		}
//	}
//	else if (nBandNum == 3) {
//		if (nBPB == 1) {
//			mDst = Mat::zeros(Size(nWidth, nHeight), CV_8UC3);
//		}
//		else {
//			mDst = Mat::zeros(Size(nWidth, nHeight), CV_16UC3);
//		}
//	}
//	else {
//		if (nBPB == 1) {
//			mDst = Mat::zeros(Size(nWidth, nHeight), CV_8UC1);
//		}
//		else {
//			mDst = Mat::zeros(Size(nWidth, nHeight), CV_16UC1);
//		}
//	}
//
//	for (int j = 0; j < nHeight; j++) {
//		unsigned char* data = mDst.ptr<unsigned char>(j);
//		unsigned char* pSubBuffer = pBuffer + (nHeight - 1 - j)*nWidth * nBandNum*nBPB;
//		memcpy(data, pSubBuffer, nWidth*nBandNum*nBPB);
//	}
//	if (nBandNum == 1) {
//		cvtColor(mDst, mDst, COLOR_GRAY2BGR);
//	}
//	else if (nBandNum == 3) {
//		cvtColor(mDst, mDst, COLOR_RGB2BGR);
//	}
//	else if (nBandNum == 4) {
//		cvtColor(mDst, mDst, COLOR_RGBA2BGR);
//	}
//	return mDst;
//}

void Convert::ConverttoBGRBMP(int ucDataFormat, unsigned char* pSrc, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight)
{
#ifdef CONVTIMECHECK
	LARGE_INTEGER start, finish;
	LARGE_INTEGER ticksPerSec;
	double timeSec;
	if (!QueryPerformanceFrequency(&ticksPerSec))
	{
		return;
	}
	QueryPerformanceCounter(&start);
#endif

	//RAWTORGBBMP(pSrc,nWidth,nHeight,ucDataFormat,pDest);
	if (HisYUV8_422_YUYV == ucDataFormat || HisYUV8_422_UYVY == ucDataFormat || HisYUV8_422_YVYU == ucDataFormat || HisYUV8_422_VYUY == ucDataFormat)
	{
		myImageAlg.HisCCMYUV2RGB24(pSrc, pDest, nWidth, nHeight, ucDataFormat);
	}
	else if (HisBaylor8_MONO == ucDataFormat)
	{
		unsigned char* pucDes = pDest, *pucSrc = pSrc;
		unsigned int uiP = nWidth * nHeight;
		for (unsigned int x = 0; x < uiP; ++x) {
			*(pucDes + 2) = *(pucDes + 1) = *pucDes = *pucSrc++;
			pucDes += 3;
		}
	}
	else if (HisBaylor10_MONO == ucDataFormat || HisBaylor12_MONO == ucDataFormat || HisBaylor14_MONO == ucDataFormat || HisBaylor16_MONO == ucDataFormat)
	{
		switch (ucDataFormat)
		{
		case HisBaylor10_MONO:
		{
			unsigned short* pusSrc = (unsigned short*)pSrc;
			unsigned char* pucDes = pDest;
			unsigned int uiP = nWidth * nHeight;
			for (unsigned int x = 0; x < uiP; ++x)
			{
				*(pucDes + 2) = *(pucDes + 1) = *pucDes = ((*pusSrc >> 2) & 0xFF);
				pucDes += 3;
				++pusSrc;
			}
		}
		break;
		case HisBaylor12_MONO:
		{
			unsigned short* pusSrc = (unsigned short*)pSrc;
			unsigned char* pucDes = pDest;
			unsigned int uiP = nWidth * nHeight;
			for (unsigned int x = 0; x < uiP; ++x)
			{
				*(pucDes + 2) = *(pucDes + 1) = *pucDes = ((*pusSrc >> 4) & 0xFF);
				pucDes += 3;
				++pusSrc;
			}
		}
		break;
		case HisBaylor14_MONO:
		{
			unsigned short* pusSrc = (unsigned short*)pSrc;
			unsigned char* pucDes = pDest;
			unsigned int uiP = nWidth * nHeight;
			for (unsigned int x = 0; x < uiP; ++x)
			{
				*(pucDes + 2) = *(pucDes + 1) = *pucDes = ((*pusSrc >> 6) & 0xFF);
				pucDes += 3;
				++pusSrc;
			}
		}
		break;
		case HisBaylor16_MONO:
		{
			unsigned short* pusSrc = (unsigned short*)pSrc;
			unsigned char* pucDes = pDest;
			unsigned int uiP = nWidth * nHeight;
			for (unsigned int x = 0; x < uiP; ++x)
			{
				*(pucDes + 2) = *(pucDes + 1) = *pucDes = ((*pusSrc >> 8) & 0xFF);
				pucDes += 3;
				++pusSrc;
			}
		}
		break;
		}
	}
	else
	{
		myImageAlg.HisCCMBarlor2RGB24(pSrc, pDest, nWidth, nHeight, ucDataFormat);
	}
	unsigned char* pdisplayBuffer = (unsigned char*)_aligned_malloc(nWidth*nHeight * 3, 64);
	memcpy(pdisplayBuffer, pDest, sizeof(unsigned char)*nWidth*nHeight * 3);
	this->toBGRImage(pdisplayBuffer, nWidth, nHeight, pDest);
	HisReleaseMalloc(pdisplayBuffer);
#ifdef CONVTIMECHECK
	QueryPerformanceCounter(&finish);
	timeSec = (finish.QuadPart - start.QuadPart) / (double)ticksPerSec.QuadPart;
	TRACE("Display : %.6f\n", timeSec);
#endif
}

void Convert::toBGRImage(unsigned char* pSrcBuffer, int SizeX, int SizeY, unsigned char* _pDestBuffer)
{
	//-------------------------------------------------------------
	if ((pSrcBuffer == 0) || (_pDestBuffer == 0))
	{
		return;
	}

	//-------------------------------------------------------------
	unsigned char* _LineTmp = pSrcBuffer;
	unsigned char r, g, b;

	unsigned char* pDestBuffer = _pDestBuffer;

	unsigned char* DestBuf = pDestBuffer + ((SizeX*(SizeY - 1) * 3));

	for (int y = 0; y < SizeY; y++)
	{
		for (int x = 0; x < SizeX; x++)
		{
			r = _LineTmp[0];
			g = _LineTmp[1];
			b = _LineTmp[2];

			_LineTmp += 3;

			*(DestBuf++) = b;
			*(DestBuf++) = g;
			*(DestBuf++) = r;
		}
		DestBuf -= SizeX * 3;
		DestBuf -= SizeX * 3;
	}
}


