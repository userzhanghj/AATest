#include "pch.h"
#include"chart.h"
#include "SystemManager.h"
extern CSystemLog          gSystemLog;

extern CSystemManager    gSystemMgr;

void Recognition::get_cross_xy(double slope0, double offset0, double slope1, double offset1, double & cross_x, double & cross_y)
{
	cross_x = (offset0 - offset1) / (slope1 - slope0);
	cross_y = (offset1*slope0 - offset0 * slope1) / (slope0 - slope1);
}

int Recognition::get_target_center(BYTE * bin, int w, int h, int pattern_size, int corner_size, int & center_x, int & center_y, int * edge_x, int * edge_y)
{
	int x1 = 0, x2 = 0;
	int y1 = 0, y2 = 0;
	BYTE *p = NULL;

	for (int j = 0; j < h - (pattern_size - 1); j++) {
		for (int i = 0; i < w - (pattern_size - 1); i++) {
			p = bin + j * w + i;
			if (is_pattern_qualified(p, w, h, pattern_size, corner_size, FALSE)) {
				get_pattern_center(p, w, h, pattern_size, center_x, center_y, edge_x, edge_y);
				center_x += i; edge_x[0] += i; edge_x[1] += i; edge_x[2] += i; edge_x[3] += i;
				center_y += j; edge_y[0] += j; edge_y[1] += j; edge_y[2] += j; edge_y[3] += j;
				return TRUE;
			}
		}
	}

	for (int j = 0; j < h - (pattern_size - 1); j++) {
		for (int i = 0; i < w - (pattern_size - 1); i++) {
			p = bin + j * w + i;
			if (is_pattern_qualified(p, w, h, pattern_size, corner_size, TRUE)) {
				get_pattern_center(p, w, h, pattern_size, center_x, center_y, edge_x, edge_y);
				center_x += i; edge_x[0] += i; edge_x[1] += i; edge_x[2] += i; edge_x[3] += i;
				center_y += j; edge_y[0] += j; edge_y[1] += j; edge_y[2] += j; edge_y[3] += j;
				return TRUE;
			}
		}
	}

	return 0;
}

int Recognition::is_pattern_qualified(BYTE *p, int w, int h, int pattern_size, int corner_size, int s_white)
{
	if ((corner_size * 2) >= pattern_size) return FALSE;

	int result = TRUE;
	if (s_white == FALSE) {
		for (int j = 0; j < corner_size; j++) {
			for (int i = 0; i < corner_size; i++) {
				if (p[j*w + i] == ABS_WHITE) return FALSE;
				if (p[j*w + i + (pattern_size - corner_size)] == ABS_BLACK) return FALSE;
				if (p[(j + (pattern_size - corner_size))*w + i] == ABS_BLACK) return FALSE;
				if (p[(j + (pattern_size - corner_size))*w + i + (pattern_size - corner_size)] == ABS_WHITE) return FALSE;
			}
		}
	}
	else {
		for (int j = 0; j < corner_size; j++) {
			for (int i = 0; i < corner_size; i++) {
				if (p[j*w + i] == ABS_BLACK) return FALSE;
				if (p[j*w + i + (pattern_size - corner_size)] == ABS_WHITE) return FALSE;
				if (p[(j + (pattern_size - corner_size))*w + i] == ABS_WHITE) return FALSE;
				if (p[(j + (pattern_size - corner_size))*w + i + (pattern_size - corner_size)] == ABS_BLACK) return FALSE;
			}
		}
	}

	return TRUE;
}

void Recognition::get_pattern_center(BYTE * p, int w, int h, int p_size, int & x, int & y, int * px, int * py)
{
	int x1 = 0, y1 = 0;
	int x2 = 0, y2 = 0;

	for (int m = 0; m < p_size - 1; m++) {
		if (p[m] != p[m + 1]) { x1 = m; break; }
	}
	for (int m = 0; m < p_size - 1; m++) {
		if (p[(p_size - 1)*w + m] != p[(p_size - 1)*w + m + 1]) { x2 = m; break; }
	}

	x = (x1 + x2) / 2;
	px[0] = x1;
	px[1] = p_size - 1;
	px[2] = x2;
	px[3] = 0;

	for (int m = 0; m < p_size - 1; m++) {
		if (p[m*w] != p[(m + 1)*w]) { y1 = m; break; }
	}
	for (int m = 0; m < p_size - 1; m++) {
		if (p[m*w + (p_size - 1)] != p[(m + 1)*w + (p_size - 1)]) { y2 = m; break; }
	}
	y = (y1 + y2) / 2;
	py[0] = 0;
	py[1] = y2;
	py[2] = p_size - 1;
	py[3] = y1;

}

void Recognition::Release(void)
{
	delete[] buf;
}

//Paint

Paint::Paint()
{
	font_size = 10;
	axis_x_offset[0] = -5;
	axis_x_offset[1] = 5;
	axis_x_offset[2] = 10;
	axis_x_offset[3] = 5;

	axis_y_offset[0] = -30;
	axis_y_offset[1] = -6;
	axis_y_offset[2] = -30;
	axis_y_offset[3] = -20;
}

HDC Paint::create(HWND hdlg, int cx, int cy, int first_x, int last_x, int first_y, int last_y, COLORREF cr)
{
	RECT rt;
	GetClientRect(hdlg, &rt);

	drawing_size[0] = cx;
	drawing_size[1] = cy;
	begin_offset[0] = first_x;
	begin_offset[1] = first_y;
	end_offset[0] = last_x;
	end_offset[1] = last_y;
	full_size[0] = begin_offset[0] + drawing_size[0] + end_offset[0];
	full_size[1] = begin_offset[1] + drawing_size[1] + end_offset[1];
	dlg_size[0] = rt.right - rt.left;
	dlg_size[1] = rt.bottom - rt.top;

	hdc = GetDC(hdlg);
	//DeleteObject(hbitmap);
	hbitmap = CreateCompatibleBitmap(hdc, dlg_size[0], dlg_size[1]);
	HDC memdc = CreateCompatibleDC(hdc);
	HBITMAP old_bitmap = (HBITMAP)SelectObject(memdc, hbitmap);

	HBRUSH mybrush = CreateSolidBrush(cr);
	FillRect(memdc, &rt, mybrush);
	DeleteObject(mybrush);

	old_map_mode = SetMapMode(memdc, MM_ANISOTROPIC);
	SetViewportOrgEx(memdc, 0, 0, NULL);
	SetViewportExtEx(memdc, dlg_size[0], dlg_size[1], NULL);
	SetWindowExtEx(memdc, full_size[0], full_size[1], NULL);

	SetBkMode(memdc, TRANSPARENT);
	SelectObject(memdc, GetStockObject(NULL_BRUSH));

	//hbitmap = NULL;
	return memdc;
}

void Paint::draw_axis_x_int(HDC hdc, int factor, int interval, const char * str, int start_x, int multi, COLORREF cr)
{
	assert(factor != 0 && interval != 0);
	HPEN pen = CreatePen(PS_DOT, 1, cr);
	HPEN old_pen = (HPEN)SelectObject(hdc, pen);
	HFONT font = CreateFont(font_size, 0, 0, 0, FW_BLACK, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, L"Arial");
	HFONT old_font = (HFONT)SelectObject(hdc, font);

	char buffer[10] = { 0 };
	int cnt = drawing_size[0] / (factor*interval);

	//draw x;
	for (int i = 0; i < cnt + 1; i++) {
		if (str != NULL) {
			sprintf(buffer, "%02d", (start_x + i * interval)*multi);
			TextOutA(hdc, begin_offset[0] + i * factor*interval + axis_x_offset[0], full_size[1] - begin_offset[1] + axis_x_offset[1], buffer, strlen(buffer));
		}

		MoveToEx(hdc, begin_offset[0] + i * interval*factor, full_size[1] - begin_offset[1], NULL);
		LineTo(hdc, begin_offset[0] + i * factor*interval, full_size[1] - (begin_offset[1] + drawing_size[1]));
	}
	if (str != NULL) {
		strcpy(buffer, str);
		TextOutA(hdc, begin_offset[0] + drawing_size[0] + axis_x_offset[2], full_size[1] - begin_offset[1] + axis_x_offset[3], buffer, strlen(buffer));
	}

	DeleteObject(pen);
	DeleteObject(font);
}

void Paint::draw_axis_x_int_interval(HDC hdc, int factor, int interval, const char * str, int start_x, int multi, COLORREF cr)
{
	assert(factor != 0 && interval != 0);
	HPEN pen = CreatePen(PS_DOT, 1, cr);
	HPEN old_pen = (HPEN)SelectObject(hdc, pen);
	HFONT font = CreateFont(font_size, 0, 0, 0, FW_BLACK, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, L"Arial");
	HFONT old_font = (HFONT)SelectObject(hdc, font);

	char buffer[10] = { 0 };
	int cnt = drawing_size[0] / (factor*interval);

	//draw x;
	for (int i = 0; i < cnt + 1; i++) {
		if (str != NULL && (i % 2 == 0)) {
			sprintf(buffer, "%02d", start_x + i * multi);
			TextOutA(hdc, begin_offset[0] + i * factor*interval + axis_x_offset[0], full_size[1] - begin_offset[1] + axis_x_offset[1], buffer, strlen(buffer));
		}

		MoveToEx(hdc, begin_offset[0] + i * interval*factor, full_size[1] - begin_offset[1], NULL);
		LineTo(hdc, begin_offset[0] + i * factor*interval, full_size[1] - (begin_offset[1] + drawing_size[1]));
	}
	if (str != NULL) {
		strcpy(buffer, str);
		TextOutA(hdc, begin_offset[0] + drawing_size[0] + axis_x_offset[2], full_size[1] - begin_offset[1] + axis_x_offset[3], buffer, strlen(buffer));
	}

	DeleteObject(pen);
	DeleteObject(font);
}

void Paint::draw_axis_y_int(HDC hdc, int factor, int interval, const char * str, int start_y, int multi, COLORREF cr)
{
	assert(factor != 0 && interval != 0);
	HPEN pen = CreatePen(PS_DOT, 1, cr);
	HPEN old_pen = (HPEN)SelectObject(hdc, pen);
	HFONT font = CreateFont(font_size, 0, 0, 0, FW_BLACK, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, L"Arial");
	HFONT old_font = (HFONT)SelectObject(hdc, font);

	char buffer[10] = { 0 };
	int cnt = drawing_size[1] / (int)(factor*interval);
	//draw y;
	for (int i = 0; i < cnt + 1; i++) {
		if (str != NULL) {
			sprintf(buffer, "%d", (start_y + i * interval)*multi);
			TextOutA(hdc, begin_offset[0] + axis_y_offset[0], full_size[1] - (begin_offset[1] + i * factor*interval) + axis_y_offset[1], buffer, strlen(buffer));
		}
		MoveToEx(hdc, begin_offset[0], full_size[1] - (begin_offset[1] + i * factor*interval), NULL);
		LineTo(hdc, begin_offset[0] + drawing_size[0], full_size[1] - (begin_offset[1] + i * factor*interval));
	}
	if (str != NULL) {
		strcpy(buffer, str);
		TextOutA(hdc, begin_offset[0] + axis_y_offset[2], full_size[1] - (begin_offset[1] + drawing_size[1]) + axis_y_offset[3], buffer, strlen(buffer));
	}

	DeleteObject(pen);
	DeleteObject(font);
}

void Paint::draw_axis_x_float(HDC hdc, float factor, float interval, const char * str, float start_x, float multi, COLORREF cr)
{
	assert(factor != 0.0f && interval != 0.0f);
	HPEN pen = CreatePen(PS_DOT, 1, cr);
	HPEN old_pen = (HPEN)SelectObject(hdc, pen);
	HFONT font = CreateFont(font_size, 0, 0, 0, FW_BLACK, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, L"Arial");
	HFONT old_font = (HFONT)SelectObject(hdc, font);

	char buffer[10] = { 0 };
	int cnt = drawing_size[0] / (int)(factor*interval);
	//	XTRACE("axis_x_offset[0]=%d\n", axis_x_offset[0]);
		//draw x;
	for (int i = 0; i < cnt + 1; i++) {
		if (str != NULL) {
			sprintf(buffer, "%.2f", (start_x + (float)i*interval)*multi);
			TextOutA(hdc, begin_offset[0] + (int)(i*factor*interval) + axis_x_offset[0], full_size[1] - begin_offset[1] + axis_x_offset[1], buffer, strlen(buffer));
			//	XTRACE("x=%f, ", factor);
		}
		MoveToEx(hdc, begin_offset[0] + (int)(i*factor*interval), full_size[1] - begin_offset[1], NULL);
		LineTo(hdc, begin_offset[0] + (int)(i*factor*interval), full_size[1] - (begin_offset[1] + drawing_size[1]));
	}
	//	XTRACE("\n");
	if (str != NULL) {
		strcpy(buffer, str);
		TextOutA(hdc, begin_offset[0] + drawing_size[0] + axis_x_offset[2], full_size[1] - begin_offset[1] + axis_x_offset[3], buffer, strlen(buffer));
	}

	DeleteObject(pen);
	DeleteObject(font);
}

void Paint::draw_axis_y_float(HDC hdc, float factor, float interval, const char * str, float start_y, float multi, COLORREF cr)
{
	assert(factor != 0.0f && interval != 0.0f);
	HPEN pen = CreatePen(PS_DOT, 1, cr);
	HPEN old_pen = (HPEN)SelectObject(hdc, pen);
	HFONT font = CreateFont(font_size, 0, 0, 0, FW_BLACK, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, L"Arial");
	HFONT old_font = (HFONT)SelectObject(hdc, font);

	char buffer[10] = { 0 };
	int cnt = drawing_size[1] / (int)(factor*interval);
	//draw y;
	for (int i = 0; i < cnt + 1; i++) {
		if (str != NULL) {
			sprintf(buffer, "%.2f", (start_y + (float)i*interval)*multi);
			TextOutA(hdc, begin_offset[0] + axis_y_offset[0], full_size[1] - (begin_offset[1] + (int)(i*factor*interval)) + axis_y_offset[1], buffer, strlen(buffer));
		}
		MoveToEx(hdc, begin_offset[0], full_size[1] - (begin_offset[1] + (int)(i*factor*interval)), NULL);
		LineTo(hdc, begin_offset[0] + drawing_size[0], full_size[1] - (begin_offset[1] + (int)(i*factor*interval)));
	}
	if (str != NULL) {
		strcpy(buffer, str);
		TextOutA(hdc, begin_offset[0] + axis_y_offset[2], full_size[1] - (begin_offset[1] + drawing_size[1]) + axis_y_offset[3], buffer, strlen(buffer));
	}

	DeleteObject(pen);
	DeleteObject(font);
}

void Paint::release(HWND hdlg, HDC memdc)
{
	SetMapMode(memdc, old_map_mode);
	SetStretchBltMode(hdc, HALFTONE);
	BitBlt(hdc, 0, 0, dlg_size[0], dlg_size[1], memdc, 0, 0, SRCCOPY);

	DeleteObject(hbitmap);
	DeleteDC(memdc);
	ReleaseDC(hdlg, hdc);
}

void Paint::set_axis(int my_font_size, int * my_axis_x_offset, int * my_axis_y_offset)
{
	font_size = my_font_size;
	for (int i = 0; i < 4; i++) {
		axis_x_offset[i] = my_axis_x_offset[i];
		axis_y_offset[i] = my_axis_y_offset[i];
	}
}

void DirPath::LoadKey(const char *path, const char *section, HWND hdlg, INIEdit *edit, int item_count)
{
	char buffer[MAX_PATH] = { 0 };
	int hex_val = 0;
	for (int i = 0; i < item_count; i++)
	{
		if (edit[i].idc == NULL && edit[i].type == NULL && edit[i].var == NULL && edit[i].var == NULL) break;
		GetPrivateProfileStringA(section, edit[i].name, NULL, buffer, MAX_PATH, path);
		switch (edit[i].type)
		{
		//case DLGTYPE_CHECK_BOOL:
		//	*((int *)(edit[i].var)) = atoi(buffer);
		//	if (hdlg == NULL) break;
		//	SendDlgItemMessage(hdlg, edit[i].idc, BM_SETCHECK, atoi(buffer) ? BST_CHECKED : BST_UNCHECKED, 0);
		//	break;

		case DLGTYPE_INPUT_INT:
			*((int *)(edit[i].var)) = atoi(buffer);
			if (hdlg == NULL) break;
			SetDlgItemTextA(hdlg, edit[i].idc, buffer);
			break;

		case DLGTYPE_INPUT_FLOAT:
			*((float *)(edit[i].var)) = (float)atof(buffer);
			if (hdlg == NULL) break;
			SetDlgItemTextA(hdlg, edit[i].idc, buffer);
			break;

		//case DLGTYPE_INPUT_DOUBLE:
		//	*((double *)(edit[i].var)) = atof(buffer);
		//	if (hdlg == NULL) break;
		//	SetDlgItemTextA(hdlg, edit[i].idc, buffer);
		//	break;

		case DLGTYPE_INPUT_STRING:
			strcpy((char *)(edit[i].var), buffer);
			if (hdlg == NULL) break;
			SetDlgItemTextA(hdlg, edit[i].idc, buffer);
			break;

		//case DLGTYPE_INPUT_HEX:
		//	sscanf(buffer, "%hx", &hex_val);
		//	*((int *)(edit[i].var)) = hex_val;
		//	memset(buffer, 0, sizeof(buffer));
		//	sprintf(buffer, "%02x", hex_val);
		//	if (hdlg == NULL) break;
		//	SetDlgItemTextA(hdlg, edit[i].idc, buffer);
		//	break;

		//case DLGTYPE_COMBO_INT:
		//	*((int *)(edit[i].var)) = atoi(buffer);
		//	if (hdlg == NULL) break;
		//	SendDlgItemMessage(hdlg, edit[i].idc, CB_SETCURSEL, atoi(buffer), 0L);
		//	break;

		//case DLGTYPE_INPUT_HEX4:
		//	sscanf(buffer, "%hx", &hex_val);
		//	*((int *)(edit[i].var)) = hex_val;
		//	memset(buffer, 0, sizeof(buffer));
		//	sprintf(buffer, "%04x", hex_val);
		//	if (hdlg == NULL) break;
		//	SetDlgItemTextA(hdlg, edit[i].idc, buffer);
		//	break;

		//case DLGTYPE_RADIO_BOOL:
		//{
		//	int idc_1 = LOWORD(edit[i].idc);
		//	int idc_2 = HIWORD(edit[i].idc);
		//	*((int *)(edit[i].var)) = atoi(buffer);
		//	if (hdlg == NULL) break;
		//	if (atoi(buffer) == 0) {
		//		SET_CHECKER_ON(hdlg, idc_1);
		//		SET_CHECKER_OFF(hdlg, idc_2);
		//	}
		//	else {
		//		SET_CHECKER_ON(hdlg, idc_2);
		//		SET_CHECKER_OFF(hdlg, idc_1);
		//	}
		//}
		//break;
		}
	}
}

void DirPath::SaveKey(const char *path, const char *section, HWND hdlg, INIEdit *edit, int item_count)
{
	char buffer[MAX_PATH] = { 0 };
	BOOL is_checked = FALSE;
	char hex[20] = { 0 };
	for (int i = 0; i < item_count; i++)
	{
		if (edit[i].idc == NULL && edit[i].type == NULL && edit[i].var == NULL && edit[i].var == NULL) break;

		switch (edit[i].type)
		{
		//case DLGTYPE_CHECK_BOOL:
		//	if (edit[i].idc != NULL) {
		//		is_checked = (int)SendDlgItemMessage(hdlg, edit[i].idc, BM_GETCHECK, 0, 0);
		//		*((int *)(edit[i].var)) = (is_checked ? 1 : 0);
		//		WritePrivateProfileStringA(section, edit[i].name, (is_checked ? "1" : "0"), path);
		//	}
		//	break;

		case DLGTYPE_INPUT_INT:
			if (edit[i].idc != NULL) {
				GetDlgItemTextA(hdlg, edit[i].idc, buffer, MAX_PATH);
				*((int *)(edit[i].var)) = atoi(buffer);
				WritePrivateProfileStringA(section, edit[i].name, buffer, path);
			}
			//else {
			//	WritePrivateProfileString(section, edit[i].name, *((int *)(edit[i].var)), path);
			//}
			break;

		case DLGTYPE_INPUT_FLOAT:
			if (edit[i].idc != NULL) {
				GetDlgItemTextA(hdlg, edit[i].idc, buffer, MAX_PATH);
				*((float *)(edit[i].var)) = (float)atof(buffer);
				WritePrivateProfileStringA(section, edit[i].name, buffer, path);
			}
			//else {
			//	write_float_key(path, section, edit[i].name, *((float *)(edit[i].var)));
			//}
			break;

		//case DLGTYPE_INPUT_DOUBLE:
		//	if (edit[i].idc != NULL) {
		//		GetDlgItemTextA(hdlg, edit[i].idc, buffer, MAX_PATH);
		//		*((double *)(edit[i].var)) = atof(buffer);
		//		WritePrivateProfileStringA(section, edit[i].name, buffer, path);
		//	}
		//	//else {
		//	//	write_float_key(path, section, edit[i].name, *((float *)(edit[i].var)));
		//	//}
		//	break;

		case DLGTYPE_INPUT_STRING:
			if (edit[i].idc != NULL) {
				GetDlgItemTextA(hdlg, edit[i].idc, buffer, MAX_PATH);
				strcpy((char *)(edit[i].var), buffer);
				WritePrivateProfileStringA(section, edit[i].name, buffer, path);
			}
			//else {
			//	write_string_key(path, section, edit[i].name, (char *)(edit[i].var));
			//}

			break;

		//case DLGTYPE_INPUT_HEX:
		//case DLGTYPE_INPUT_HEX4:
		//	if (edit[i].idc != NULL) {
		//		GetDlgItemTextA(hdlg, edit[i].idc, buffer, MAX_PATH);
		//		sprintf(hex, "0X%s", buffer);
		//		WritePrivateProfileStringA(section, edit[i].name, hex, path);
		//	}
		//	break;

		//case DLGTYPE_COMBO_INT:
		//	if (edit[i].idc != NULL) {
		//		*((int *)(edit[i].var)) = COMBO_GETCURSEL(hdlg, edit[i].idc);
		//		sprintf(buffer, "%d", *((int *)(edit[i].var)));
		//		WritePrivateProfileStringA(section, edit[i].name, buffer, path);
		//	}
		//	else {
		//		sprintf(buffer, "%d", *((int *)(edit[i].var)));
		//		WritePrivateProfileStringA(section, edit[i].name, buffer, path);
		//	}
		//	break;
		//case DLGTYPE_RADIO_BOOL:
		//	if (edit[i].idc != NULL) {
		//		int b = GET_CHECKER(hdlg, LOWORD(edit[i].idc));
		//		*((int *)(edit[i].var)) = (b ? 0 : 1);
		//		sprintf(buffer, "%d", *((int *)(edit[i].var)));
		//		WritePrivateProfileStringA(section, edit[i].name, buffer, path);
		//	}
		//	break;
		}
	}
}

void DirPath::GetCurrentDir(char *path)
{
	if (path == NULL) return;
	GetModuleFileNameA(NULL, path, MAX_PATH);
	char *p = strrchr(path, '\\');
	*p = '\0';
}

BOOL DirPath::SearchFile(const char * path, const char * name)
{
	WIN32_FIND_DATAA wfd;

	char search_path[MAX_PATH] = { 0 };
	sprintf(search_path, "%s\\*.*", path);
	HANDLE search = FindFirstFileA(search_path, &wfd);

	char search_name[MAX_PATH] = { 0 };
	strcpy(search_name, name);

	BOOL finding = TRUE;
	while (finding) {
		if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY) {
			int n = strlen(wfd.cFileName);
			for (int i = 0; i < n; i++) {
				wfd.cFileName[i] = (char)toupper((int)wfd.cFileName[i]);
			}
			
			n = strlen(search_name);
			for (int i = 0; i < n; i++) {
				search_name[i] = (char)toupper((int)search_name[i]);
			}
			//uppercase(wfd.cFileName);
			//uppercase(search_name);
			if (!strcmp(wfd.cFileName, search_name)) {
				FindClose(search);
				return TRUE;
			}
		}
		finding = FindNextFileA(search, &wfd);
	}

	FindClose(search);
	return 0;
}


CDrawCurve::CDrawCurve()
{
}

CDrawCurve::~CDrawCurve()
{
}

HDC CDrawCurve::CreateChart(HWND hChart, int nChartWidth, int nChartHeight, int begin_x, int end_x, int begin_y, int end_y)
{

	RECT rt;
	GetClientRect(hChart, &rt);
	m_nChartSize[0] = rt.right - rt.left;
	m_nChartSize[1] = rt.bottom - rt.top;

	m_nChartWidth = nChartWidth;
	m_nChartHeight = nChartHeight;
	m_nEndX = end_x;
	m_nEndY = end_y;
	m_nBeginX = begin_x;
	m_nBeginY = begin_y;

	hdc = GetDC(hChart);
	hbitmap = CreateCompatibleBitmap(hdc, m_nChartSize[0], m_nChartSize[1]);
	HDC memdc = CreateCompatibleDC(hdc);
	HBITMAP old_bitmap = (HBITMAP)SelectObject(memdc, hbitmap);

	COLORREF cr = RGB(156, 170, 193);//图表背景色
	HBRUSH mybrush = CreateSolidBrush(cr);
	FillRect(memdc, &rt, mybrush);
	DeleteObject(mybrush);

	m_nOldMapMode = SetMapMode(memdc, MM_ANISOTROPIC);
	SetViewportOrgEx(memdc, 0, 0, NULL);
	SetViewportExtEx(memdc, m_nChartSize[0], m_nChartSize[1], NULL);
	SetWindowExtEx(memdc, m_nChartWidth, m_nChartHeight, NULL);

	SetBkMode(memdc, TRANSPARENT);
	SelectObject(memdc, GetStockObject(NULL_BRUSH));

	return memdc;
}

void CDrawCurve::DrawAxisXInt(HDC hdc, int nXCount, CString cstrTitle)
{
	COLORREF colorLine = RGB(136, 136, 136);
	HPEN pen = CreatePen(PS_DOT, 1, colorLine);
	HPEN old_pen = (HPEN)SelectObject(hdc, pen);
	HFONT font = CreateFont(5, 0, 0, 0, FW_BLACK, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, L"Arial");
	HFONT old_font = (HFONT)SelectObject(hdc, font);

	int nAxisXStep = (m_nChartWidth - m_nBeginX - m_nEndX) / nXCount;//X轴每一步步长
	//draw x;
	for (int i = 0; i < nXCount; i++)
	{
		CString cstr;
		if (i < 10)
		{
			cstr.Format(L"%d", i);
		}
		else
		{
			cstr.Format(L"%02d", i);
		}

		int nXPos = (int)i * nAxisXStep + m_nBeginX;

		MoveToEx(hdc, nXPos, m_nBeginY, NULL);
		LineTo(hdc, nXPos, m_nChartHeight - m_nEndY);
		//-3和+6是为了对齐，以及纵坐标在下面一点
		int nCstrX = (int)(nXPos - 3 * gSystemMgr.m_fScreenX);
		int nCstrY = (int)(m_nChartHeight - m_nEndY + 3 * gSystemMgr.m_fScreenY);

		TextOut(hdc, nCstrX, nCstrY, cstr, cstr.GetLength());
	}
	//X坐标抬头
	DeleteObject(font);
	font = CreateFont(10, 0, 0, 0, FW_BLACK, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, L"Arial");
	old_font = (HFONT)SelectObject(hdc, font);
	TextOut(hdc, m_nChartWidth - m_nEndX, m_nChartHeight - m_nEndY, cstrTitle, cstrTitle.GetLength());

	DeleteObject(pen);
	DeleteObject(font);
}

void CDrawCurve::DrawAxisYFloat(HDC hdc, int nYCount, CString cstrTitle)
{
	COLORREF colorLine = RGB(136, 136, 136);
	HPEN pen = CreatePen(PS_DOT, 1, colorLine);
	HPEN old_pen = (HPEN)SelectObject(hdc, pen);
	HFONT font = CreateFont(10, 0, 0, 0, FW_BLACK, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, L"Arial");
	HFONT old_font = (HFONT)SelectObject(hdc, font);

	int nAxisYStep = (m_nChartHeight - m_nBeginY - m_nEndY) / (nYCount - 1);//X轴每一步步长
	//draw x;
	CString cstr;
	for (int i = 0; i < nYCount; i++)
	{
		//CString cstr;
		cstr.Format(L"%.2f", (double)20 * i);

		int nYPos = (int)(m_nChartHeight - m_nBeginY - m_nEndY) - i * nAxisYStep + m_nBeginY;
		//图标上面点的纵坐标Y，靠上的部分
		//图标上面点的纵坐标Y，靠下的部分

		MoveToEx(hdc, m_nBeginX, nYPos, NULL);
		LineTo(hdc, m_nChartWidth - m_nEndX, nYPos);
		//-3和+6是为了对齐，以及纵坐标在下面一点
		int nCstrX = (int)(m_nBeginX - 220 * gSystemMgr.m_fScreenX);
		TextOut(hdc, nCstrX, nYPos, cstr, cstr.GetLength());
	}
	//y坐标抬头
	/*font = CreateFont(10, 0, 0, 0, FW_BLACK, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, L"Arial");
	old_font = (HFONT)SelectObject(hdc, font);
	TextOut(hdc, m_nBeginX - 220 * gSystemMgr.m_fScreenX,  m_nEndY, cstrTitle, cstrTitle.GetLength());*/

	DeleteObject(pen);
	DeleteObject(font);
}

void CDrawCurve::CloseChart(HWND hChart, HDC hMemdc)
{
	SetMapMode(hMemdc, m_nOldMapMode);
	SetStretchBltMode(hdc, HALFTONE);
	BitBlt(hdc, 0, 0, m_nChartSize[0], m_nChartSize[1], hMemdc, 0, 0, SRCCOPY);

	DeleteObject(hbitmap);
	DeleteDC(hMemdc);
	ReleaseDC(hChart, hdc);
}

//RS232
const BYTE auchCRCHi[] = {
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
	0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
	0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
	0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
	0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
	0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
	0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
	0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
	0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
	0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
	0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
	0x40
};

/* Table of CRC values for low–order byte */
const BYTE auchCRCLo[] = {
	0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
	0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
	0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
	0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
	0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
	0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
	0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
	0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
	0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
	0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
	0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
	0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
	0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
	0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
	0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
	0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
	0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
	0x40
};

RS232::RS232()
{
	hcom = NULL;
}

RS232::~RS232()
{
	if (hcom != NULL) {
		CloseHandle(hcom);
	}
}

int RS232::com_open(int port, int baud_rate, int parity, int stop_bit)
{
	char com_name[10] = { 0 };

	if (!check_com_port(port, com_name))   return SERIAL_ERROR_COMPORTNUM;
	if (!check_baud_rate(baud_rate))	   return SERIAL_ERROR_BAUDRATE;
	if (!check_parity(parity))			   return SERIAL_ERROR_PARITY;
	if (!check_stop_bit(stop_bit))		   return SERIAL_ERROR_STOPBIT;

	olread.Offset = 0;
	olread.OffsetHigh = 0;
	if (olread.hEvent != NULL) {
		CloseHandle(olread.hEvent);
		olread.hEvent = NULL;
	}
	if (!(olread.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL))) {
		return SERIAL_ERROR_READEVENT;
	}

	olwrite.Offset = 0;
	olwrite.OffsetHigh = 0;
	if (olwrite.hEvent != NULL) {
		CloseHandle(olwrite.hEvent);
		olwrite.hEvent = NULL;
	}
	if (!(olwrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL))) {
		return SERIAL_ERROR_WRITEEVENT;
	}

	if (hcom != NULL) {
		CloseHandle(hcom);
		hcom = NULL;
	}

	hcom = CreateFileA(com_name, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
	if (hcom == INVALID_HANDLE_VALUE) return SERIAL_ERROR_COMPORT;

	if (SetCommMask(hcom, EV_RXCHAR)) {
		if (SetupComm(hcom, COM_BUFFER_SIZE, COM_BUFFER_SIZE)) {
			if (PurgeComm(hcom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR)) {
				COMMTIMEOUTS cts;
				cts.ReadIntervalTimeout = 0XFFFFFFFF;
				cts.ReadTotalTimeoutMultiplier = 0;
				cts.ReadTotalTimeoutConstant = 0;
				cts.WriteTotalTimeoutMultiplier = 0;
				cts.WriteTotalTimeoutConstant = 0;
				if (SetCommTimeouts(hcom, &cts)) {
					DCB dcb;
					if (GetCommState(hcom, &dcb)) {
						dcb.DCBlength = sizeof(DCB);
						dcb.BaudRate = baud_rate;
						dcb.ByteSize = 8;
						dcb.Parity = parity;
						dcb.StopBits = stop_bit;

						if (SetCommState(hcom, &dcb)) {
							return TRUE;
						}
					}
				} //SetCommTimeouts
			}
		} //SetupComm
	}
	return 0;
}

int RS232::com_close(void)
{
	if (hcom == NULL)	return TRUE;

	if (SetCommMask(hcom, 0)) {
		if (EscapeCommFunction(hcom, CLRDTR)) {
			if (PurgeComm(hcom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR)) {
				if (olwrite.hEvent != NULL) {
					CloseHandle(olread.hEvent);
					CloseHandle(olwrite.hEvent);
				}
				if (CloseHandle(hcom)) {
					hcom = NULL;
					olread.hEvent = NULL;
					olwrite.hEvent = NULL;

					//logdlg.log("result:%d ,out:%s", 1);
					return TRUE;
				}
			}
		}
	}

	return SERIAL_ERROR_COMCLOSE;
}

DWORD RS232::receive_data(unsigned char * buffer, DWORD limited_data_size, COMSTAT & cs)
{
	if (hcom == NULL) {
		return 0;
	}
	DWORD error_flag;
	DWORD received_data_size;

	if (!ReadFile(hcom, buffer, limited_data_size, &received_data_size, &olread)) {
		DWORD err_code = GetLastError();
		if (ERROR_IO_PENDING == err_code) {
			while (!GetOverlappedResult(hcom, &olread, &received_data_size, TRUE)) {
				if (ERROR_IO_INCOMPLETE != err_code) {
					received_data_size = 0;
					break;
				}
			}
		}
		else {
			received_data_size = 0;
		}
	}
	Sleep(10);
	::ClearCommError(hcom, &error_flag, &cs);
	PurgeComm(hcom, PURGE_RXCLEAR | PURGE_TXCLEAR);
	return received_data_size;
}


DWORD RS232::receive_data_loop(unsigned char * buffer, DWORD limit_data_size, int & mode)
{
	DWORD mask;
	DWORD error_flag = 0;
	int received_data_size = 0;

	BYTE *receive_buffer = new BYTE[limit_data_size];

	COMSTAT cs;

	WaitCommEvent(hcom, &mask, &olread);
	WaitForSingleObject(olread.hEvent, 1000);
	ResetEvent(olread.hEvent);
	if ((mask&EV_RXCHAR) == EV_RXCHAR) {
		::ClearCommError(hcom, &error_flag, &cs);
		while (cs.cbInQue) {
			Sleep(100);
			received_data_size = receive_data(receive_buffer, limit_data_size, cs);
			if (received_data_size > 0) {
				if (mode == 0) {
					for (int i = 0; i < received_data_size; i++) {
						//if (receive_buffer[i] == 0)
						//	buffer[i] = 61;
						//else
							buffer[i] = receive_buffer[i];
						//sprintf(buf, "0x%x ", receive_buffer[i]);
						//strncat((char *)buffer, buf, strlen((char *)buf));
					}
					//memcpy(buffer, receive_buffer, limit_data_size);
				}
				else {
					char buf[10] = { 0 };
					for (int i = 0; i < received_data_size; i++) {
						sprintf(buf, "0x%x ", receive_buffer[i]);
						strncat((char *)buffer, buf, strlen((char *)buf));
					}
				}
				//return received_data_size;
			}
		}
	}

	//logdlg.log("result ,out:%s", buffer);
	delete[] receive_buffer;
	return received_data_size;
}

DWORD RS232::send_data(const unsigned char * buffer, DWORD sending_data_size)
{
	if (hcom == NULL)	return -1;

	DWORD write_data_size = 0;
	DWORD error_flags = 0;
	COMSTAT cs;
	if (!WriteFile(hcom, buffer, sending_data_size, &write_data_size, &olwrite)) {
		if (ERROR_IO_PENDING == GetLastError()) {
			while (!GetOverlappedResult(hcom, &olwrite, &write_data_size, TRUE)) {
				if (ERROR_IO_INCOMPLETE != GetLastError()) {
					write_data_size = -2;
					ClearCommError(hcom, &error_flags, &cs);
					break;
				}
			}
		}
		else {
			write_data_size = -3;
			ClearCommError(hcom, &error_flags, &cs);
		}
	}
	return write_data_size;
}

DWORD RS232::send_data_feedback(const unsigned char * input, DWORD input_size, unsigned char * output, DWORD output_size)
{
	int result = 0;
	if (hcom == NULL)	return -1;
	//Str2Hex(input, (BYTE*)input2);
	DWORD write_data_size = 0;
	DWORD error_flags = 0;
	COMSTAT cs;

	if (!WriteFile(hcom, input, input_size, &write_data_size, &olwrite)) {
		if (ERROR_IO_PENDING == GetLastError()) {
			while (!GetOverlappedResult(hcom, &olwrite, &write_data_size, TRUE)) {
				if (ERROR_IO_INCOMPLETE != GetLastError()) {
					result = -2;
					ClearCommError(hcom, &error_flags, &cs);
					break;
				}
			}
		}
		else {
			result = -3;
			ClearCommError(hcom, &error_flags, &cs);
		}
	}

	int timeout = 5;
	int length = 0;
	int mode = 0;//
	while ((timeout--) > 0) {
		length = receive_data_loop(output, output_size, mode);
		//CString cstr;
		//cstr.Format(L"length[%d]", length);
		//gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);
		if (length > 0) {
			result = TRUE;
			return TRUE;
		}
		Sleep(1);
	}
	
	if (timeout <= 0)
	{
		gSystemLog.DisplayLogAndSave(L"timeout error", LV_EVENT);
		result = FALSE;
	}
	//logdlg.log("result :%d,out:%s", result, output);
	return result;
}

WORD RS232::generate_crc(BYTE * cmd, WORD data_length)
{
	BYTE ucCRCHi = 0xFF;   /* high byte of CRC initialized */
	BYTE ucCRCLo = 0xFF;   /* low byte of CRC initialized */
	WORD uIndex = 0;       /* will index into CRC lookup table */
	BYTE byTmp = 0;

	while (data_length--)     /* pass through message buffer */
	{
		byTmp = *cmd++;
		uIndex = ucCRCHi ^ byTmp; /* calculate the CRC */

		ucCRCHi = ucCRCLo ^ auchCRCHi[uIndex];
		ucCRCLo = auchCRCLo[uIndex];
	}
	return (ucCRCHi << 8 | ucCRCLo);
}

BOOL RS232::check_com_port(int port, char * com_name)
{
	if (com_name == NULL)	return FALSE;

	memset(com_name, 0, sizeof(com_name));

	if (port <= 0 || port > 256) {
		return FALSE;
	}
	else {
		char buffer[10] = { 0 };
		if (port > 9)
			wsprintfA(buffer, "\\\\.\\COM%d", port);
		else
			wsprintfA(buffer, "COM%d", port);
		strcpy(com_name, buffer);

		return TRUE;
	}
	return 0;
}

BOOL RS232::check_baud_rate(int baud_rate)
{
	switch (baud_rate)
	{
	case 9600:
	case 14400:
	case 19200:
	case 38400:
	case 57600:
	case 115200:
	case 128000:
	case 256000:
	case 921600:
		return TRUE;

	default:
		return FALSE;
	}
}

BOOL RS232::check_parity(int parity)
{
	switch (parity)
	{
	case NOPARITY:
	case ODDPARITY:
	case EVENPARITY:
	case MARKPARITY:
	case SPACEPARITY:
		return TRUE;

	default:
		return FALSE;
	}
}

BOOL RS232::check_stop_bit(int stop_bit)
{
	switch (stop_bit)
	{
	case ONESTOPBIT:
	case ONE5STOPBITS:
	case TWOSTOPBITS:
		return TRUE;

	default:
		return FALSE;
	}
}