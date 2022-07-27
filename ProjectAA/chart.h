#pragma once
//一些类
#include<Windows.h>

#define ABS_WHITE							255
#define ABS_BLACK							0

#define FFT_NUM												1024	//2^FFT_COFF

#define PI						(acos(-1.0))

//
#define DLGTYPE_INPUT_INT				1
#define DLGTYPE_INPUT_FLOAT			2
#define DLGTYPE_INPUT_STRING			3

class Recognition {
public:
	static void get_cross_xy(double slope0, double offset0, double slope1, double offset1, double &cross_x, double &cross_y);
	int get_target_center(BYTE *bin, int w, int h, int pattern_size, int corner_size, int &center_x, int &center_y, int *edge_x, int *edge_y);
	int is_pattern_qualified(BYTE * p, int w, int h, int pattern_size, int corner_size, int s_white);
	void get_pattern_center(BYTE *p, int w, int h, int p_size, int &x, int &y, int *px, int *py);
	void Release(void);
private:
	const BYTE*buf = new BYTE[5000000];
	int iWidth;
	int iHeight;
	int iCenterX;
	int iCenterY;
};

class  Paint
{
public:
	Paint();
	HDC create(HWND hdlg, int cx, int cy, int first_x, int last_x, int first_y, int last_y, COLORREF cr = RGB(0xdd, 0xdd, 0xdd));
	void draw_axis_x_int(HDC hdc, int factor, int interval, const char *str, int start_x = 0, int multi = 1, COLORREF cr = RGB(0x88, 0x88, 0x88));
	void draw_axis_x_int_interval(HDC hdc, int factor, int interval, const char *str, int start_x = 0, int multi = 1, COLORREF cr = RGB(0x88, 0x88, 0x88));
	void draw_axis_y_int(HDC hdc, int factor, int interval, const char *str, int start_y = 0, int mutli = 1, COLORREF cr = RGB(0x88, 0x88, 0x88));
	void draw_axis_x_float(HDC hdc, float factor, float interval, const char *str, float start_x = 0.0f, float multi = 1.0f, COLORREF cr = RGB(0x88, 0x88, 0x88));
	void draw_axis_y_float(HDC hdc, float factor, float interval, const char *str, float start_y = 0.0f, float multi = 1.0f, COLORREF cr = RGB(0x88, 0x88, 0x88));
	void release(HWND hdlg, HDC memdc);
	void set_axis(int my_font_size, int *my_axis_x_offset, int *my_axis_y_offset);

private:
	HDC hdc;
	int drawing_size[2];
	int begin_offset[2];
	int end_offset[2];
	int full_size[2];
	int old_map_mode;
	int dlg_size[2];
	HBITMAP hbitmap;

	int font_size;
	int axis_x_offset[4];
	int axis_y_offset[4];
};

typedef struct _INIEdit
{
	int idc;
	int type;
	void *var;
	char name[50];
}INIEdit;

class DirPath {
public:
	virtual void LoadKey(const char *path, const char *section, HWND hdlg, INIEdit *edit, int item_count);
	virtual void SaveKey(const char *path, const char *section, HWND hdlg, INIEdit *edit, int item_count);
	virtual void GetCurrentDir(char * path);
	BOOL SearchFile(const char *path, const char *name);
private:
	char buffer[20] = { 0 };
};

class CDrawCurve
{
public:
	CDrawCurve();
	~CDrawCurve();

public:
	HDC CreateChart(HWND hChart, int nChartWidth, int nChartHeight, int begin_x, int end_x, int begin_y, int end_y);
	void DrawAxisXInt(HDC hdc, int nXCount, CString cstrTitle);
	void DrawAxisYFloat(HDC hdc, int nYCount, CString cstrTitle);
	void CloseChart(HWND hChart, HDC hMemdc);

private:
	HDC hdc;
	int m_nChartWidth = 0;
	int m_nChartHeight = 0;
	int m_nEndX = 0;
	int m_nEndY = 0;
	int m_nBeginX = 0;
	int m_nBeginY = 0;
	int m_nFontSize = 10;


	int m_nOldMapMode;
	int m_nChartSize[2];//chart在控件的大小
	HBITMAP hbitmap;

};

//串口
#define SERIAL_ERROR_COMPORTNUM		-1
#define SERIAL_ERROR_BAUDRATE		-2
#define SERIAL_ERROR_PARITY			-3
#define SERIAL_ERROR_STOPBIT		-4
#define SERIAL_ERROR_READEVENT		-5
#define SERIAL_ERROR_WRITEEVENT		-6
#define SERIAL_ERROR_COMPORT		-7
#define SERIAL_ERROR_COMCLOSE		-10
#define COM_BUFFER_SIZE				4192

class  RS232
{
public:
	RS232();
	virtual ~RS232();
	int com_open(int port, int baud_rate, int parity = NOPARITY, int stop_bit = ONESTOPBIT);
	int com_close(void);

	DWORD receive_data(unsigned char *buffer, DWORD limited_data_size, COMSTAT &cs);
	DWORD receive_data_loop(unsigned char *buffer, DWORD limit_data_size, int &mode);
	DWORD send_data(const unsigned char *buffer, DWORD sending_data_size);
	DWORD send_data_feedback(const unsigned char *input, DWORD input_size, unsigned char *output, DWORD output_size);

	HANDLE get_com_port(void) { return hcom; }
	LPOVERLAPPED get_olread(void) { return &olread; }
	LPOVERLAPPED get_olwrite(void) { return &olwrite; }

	WORD generate_crc(BYTE *cmd, WORD data_length);

private:
	int port;
	int baudrate;
	int is_linked;
	HANDLE hcom;
	OVERLAPPED olread, olwrite;

	BOOL check_com_port(int port, char *com_name);
	BOOL check_baud_rate(int baud_rate);
	BOOL check_parity(int parity);
	BOOL check_stop_bit(int stop_bit);
};