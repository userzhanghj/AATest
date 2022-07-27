#pragma once
#include<Windows.h>

#define HIGH_CLIP(x,limit)		( ((x)>(limit)) ? (limit):(x) )
#define LOW_CLIP(x,limit)			( ((x)<(limit)) ? (limit):(x) )
#define CLIP(x,l,h)						HIGH_CLIP(LOW_CLIP(x,l),h)

#define PIXEL_R(x,y,w,h)					((((h)-(y)-1)*(w)+(x))*3+2)
#define PIXEL_G(x,y,w,h)					((((h)-(y)-1)*(w)+(x))*3+1)
#define PIXEL_B(x,y,w,h)					((((h)-(y)-1)*(w)+(x))*3)
#define PIXEL_Y(x,y,w,h)					(((h)-(y)-1)*(w)+(x))

#define B_CHANNEL								0
#define G_CHANNEL								1
#define R_CHANNEL								2

#define YUV_OUTPUT_YCBYCR				0
#define YUV_OUTPUT_YCRYCB				1
#define YUV_OUTPUT_CBYCRY				2
#define YUV_OUTPUT_CRYCBY				3

#define RAW_OUTPUT_BGGR				0
#define RAW_OUTPUT_RGGB				1
#define RAW_OUTPUT_GBRG				2
#define RAW_OUTPUT_GRBG				3

#define IMG_RAW								0
#define IMG_BMP									1
#define IMG_JPG									2
#define IMG_PNG									3
#define IMG_TIFF									4
#define IMG_GIF									5
#define IMG_MIPIRAW							6

#define RAW_YUV								0
#define RAW_8BIT								1
#define RAW_10BIT								2
#define RAW_12BIT								3
#define RAW_MIPI10BIT						4

class  Output
{
public:
	Output();
	~Output();
	virtual void DrawOnWnd(HDC memdc, LPVOID temp) { return; }
	int Display(HWND hwnd, const BYTE *bmp_source, int img_w, int img_h, int img_ch = 3, int start_x = 0, int start_y = 0, int is_full_sized = FALSE, int stretch_mode = HALFTONE, LPVOID temp = NULL);

	BOOL SaveLayers(const char *path, int img_w, int img_h);
	void ClearStream(void);
	HBITMAP get_hbitmap(void);

	static void DrawCrossline(HDC memdc, int center_x, int center_y, int width, int height);
	static void DrawRect(HDC memdc, int center_x, int center_y, int width, int height);

protected:
	HBITMAP hbitmap;
	BYTE *  bi_buf;
};

class OutputImage :public Output
{
public:
	virtual void DrawOnWnd(HDC memdc, LPVOID temp);
private:
	HPEN pen, old_pen;
	HFONT hfont, old_font;
};
extern OutputImage ShowImg;

class  Convert
{
public:
	Convert();
	~Convert();
	BOOL init_lib();
	virtual void YCbCrITUToBmp(int iMode, BYTE *pYuvBuffer, BYTE *pBmpBuffer, int size_x, int size_y);
	virtual void bmp24_to_y8(const BYTE *bmp_source, int bmp_w, int bmp_h, RECT *y_rect, BYTE *y_data);
	virtual void bmp24_to_b24(const BYTE *bmp_source, int bmp_w, int bmp_h, RECT *y_rect, BYTE *bmp_data);
	virtual void bmp24_to_y24(const BYTE *bmp_source, int bmp_w, int bmp_h, RECT *y_rect, BYTE *y_data);
	virtual void yuv422_to_bmp24(int data_order, BYTE *yuv, BYTE *bmp, int img_w, int img_h);
	virtual void raw8_to_bmp24_y(int data_order, BYTE *raw8, BYTE *bmp_y, int img_w, int img_h);
	virtual BOOL get_bmp_roi_avg_val(const BYTE *bmp_source, int bmp_w, int bmp_h, RECT *roi, float &avg_y, float &avg_cb, float &avg_cr);
	virtual BOOL save_bmp24_image(const char *img_path, BYTE *bmp, int img_w, int img_h);
	virtual BOOL save_jpg24_image(const char *img_path, BYTE *bmp, int img_w, int img_h);
	virtual BOOL save_bmp8_image(const char *img_path, BYTE *bmp, int img_w, int img_h);

	virtual void toBGRImage(unsigned char* pSrcBuffer, int SizeX, int SizeY, unsigned char* _pDestBuffer);
	virtual void ConverttoBGRBMP(int ucDataFormat, unsigned char* pSrc, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight);
private:
	BYTE *table_y;
	BYTE *table_r;
	BYTE *table_g;
	BYTE *table_b;
	int is_table_inited = true;

	void  create_yuv_table(void);
	void  create_rgb_table(void);
	BYTE	RtblITU[256][256];
	BYTE	GtblITU[256][256][256];
	BYTE	BtblITU[256][256];
};
//extern Convert changeImg;

extern void roi_column_to_row(BYTE *roi_data, int roi_w, int roi_h);
