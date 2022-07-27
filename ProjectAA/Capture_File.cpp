#include "pch.h"
#include"Capture.h"

BOOL ImgFile::ReadBMPFile(const char *bmp_path, BYTE *bmp_source, int &bmp_w, int &bmp_h, int &bmp_channel)
{
	SetCursor(LoadCursor(NULL, IDC_WAIT));
	ShowCursor(TRUE);

	HANDLE hfile = CreateFileA(bmp_path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (hfile == INVALID_HANDLE_VALUE) return -1;

	DWORD high_order_file_size;
	DWORD file_size = GetFileSize(hfile, &high_order_file_size);

	if (high_order_file_size) {
		CloseHandle(hfile);
		return -2;
	}

	BITMAPFILEHEADER *pbmfh = (BITMAPFILEHEADER *)malloc(file_size);
	if (!pbmfh) {
		CloseHandle(hfile);
		return -3;
	}

	DWORD read_bytes = 0;
	BOOL is_successed = ::ReadFile(hfile, pbmfh, file_size, &read_bytes, NULL);
	CloseHandle(hfile);

	if (!is_successed || (read_bytes != file_size) ||
		(pbmfh->bfType != *(WORD *) "BM") || (pbmfh->bfSize != file_size)) {
		free(pbmfh);
		return -4;
	}

	ShowCursor(FALSE);
	SetCursor(LoadCursor(NULL, IDC_ARROW));

	// Get pointers to the info structure & the bits
	BITMAPINFO	*pbmi = (BITMAPINFO *)(pbmfh + 1);

	// Get the DIB width and height
	if (pbmi->bmiHeader.biSize == sizeof(BITMAPCOREHEADER)) {
		bmp_w = ((BITMAPCOREHEADER *)pbmi)->bcWidth;
		bmp_h = ((BITMAPCOREHEADER *)pbmi)->bcHeight;
		bmp_channel = ((BITMAPCOREHEADER *)pbmi)->bcBitCount / 8;
	}
	else {
		bmp_w = pbmi->bmiHeader.biWidth;
		bmp_h = abs(pbmi->bmiHeader.biHeight);
		bmp_channel = pbmi->bmiHeader.biBitCount / 8;
	}

	int x_cnt = (bmp_w*bmp_channel * 8 + 31) / 32 * 4;
	if (bmp_channel == 1) {
		BITMAPFILEHEADER bmHeader;
		BITMAPINFOHEADER bmInfohd;
		BYTE *bmp_t = new BYTE[bmp_w*bmp_h];
		FILE *fp = fopen(bmp_path, "rb");
		fread(&bmHeader, sizeof(BITMAPFILEHEADER), 1, fp);
		fread(&bmInfohd, sizeof(BITMAPINFOHEADER), 1, fp);
		fread(&pal, sizeof(pal), 1, fp);
		fread(bmp_t, bmp_w*bmp_h, 1, fp);
		fclose(fp);
		for (int i = 0, j = 0; i < bmp_w*bmp_h; i++) {
			bmp_source[j++] = pal[bmp_t[i]].b;
			bmp_source[j++] = pal[bmp_t[i]].g;
			bmp_source[j++] = pal[bmp_t[i]].r;
		}

		bmp_channel = 1;
		delete[] bmp_t;
	}
	else {
		//		memcpy(bmp_source, (BYTE *)(pbmfh) + pbmfh->bfOffBits, bmp_w*bmp_h*bmp_channel);
		for (int j = 0; j < bmp_h; j++) {
			memcpy(bmp_source + j * x_cnt, (BYTE *)(pbmfh)+pbmfh->bfOffBits + j * x_cnt, x_cnt);
		}

	}
	free(pbmfh);
	pbmfh = NULL;

	return TRUE;
}

BOOL ImgFile::init(void) {
	//logdlg.log("file image init");

	return TRUE;
}

int ImgFile::run() {
	int result = 0;
	CFileDialog dlg(TRUE, L"*.bmp;*.jpg;*.tif", NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		L"图片(*.bmp;*.jpg;*.tif;*.png)|*.bmp;*.jpg;*.tif;*.png||", NULL);// 选项图片的约定;  
	dlg.m_ofn.lpstrTitle = _T("打开图片");// 打开文件对话框的标题名;(*.bmp; *.jpg) |*.bmp; *.jpg | 

	if (dlg.DoModal() == IDOK)// 判断是否获得图片;  
	{
		if (dlg.GetFileExt() != "bmp" && dlg.GetFileExt() != "jpg"&&dlg.GetFileExt() != "tif"&&dlg.GetFileExt() != "png")
		{
			AfxMessageBox(_T("请选择正确的图片格式！"), MB_OK);
			return false;
		}

		CString mPath = dlg.GetPathName();// 获取图片路径;  
		USES_CONVERSION;
		char * Path = T2A(mPath);
		sprintf(cImgPath, "%s", Path);
		result = ReadBMPFile(cImgPath, bBmpBuf, iImgWidth, iImgHeight, iImgDepth);
	}
	//if (dlg.GetFileExt() != "bmp" && dlg.GetFileExt() != "jpg"&&dlg.GetFileExt() != "tif"&&dlg.GetFileExt() != "png")
	//{
	//	AfxMessageBox(_T("请选择正确的图片格式！"), MB_OK);
	//	return false;
	//}

	//CString mPath = dlg.GetPathName();// 获取图片路径;  
	//char * Path = (LPSTR)(LPCTSTR)mPath;
	//sprintf(cImgPath, "%s", Path);
	//int result = ReadBMPFile(cImgPath, bBmpBuf, iImgWidth, iImgHeight, iImgDepth);
	return result;
}

int ImgFile::cap(void)
{
	return true;
}

int ImgFile::stop() {
	//release();
	return true;
}