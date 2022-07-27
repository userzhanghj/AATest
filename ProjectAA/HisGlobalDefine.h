//
#ifndef HISGLOBALDEFINE_H
#define HISGLOBALDEFINE_H

#include <string>
#include <vector>

#define _RMAX_BOXS 8
#define _RMAX_CHANNEL 16
#define _RMAX_STREAM_ROI_NUMS 17

#define _HisFX3V2_CURRENTCAL_COUNT	36
#define _HisFX3_OS_PinName_MaxByte	12

enum _HisFX3_Platform_Type
{
	_HisFX3_Platform_Type_UnKnowed		=	0x0,
	_HisFX3_Platform_Type_R2R3					=	0x2, /*! 此版SDK不支持*/
	_HisFX3_Platform_Type_R5						=	0x4, /*! 此版SDK暂不支持*/
	_HisFX3_Platform_Type_R3X					=	0x5,
	_HisFX3_Platform_Type_UVC					=	0x6, /*! 标准协议UVC 模组*/
	_HisFX3_Platform_Type_RTSPM				=	0x7, /*! RTSP网络相机*/
	_HisFX3_Platform_Type_R5X					=	0x8,
	_HisFX3_Platform_Type_HDMI					=	0x9,  /*! HDMI PCIE卡*/
	_HisFX3_Platform_Type_R6						=	0xA,  /*! C-PHY双摄 */
	_HisFX3_Platform_Type_R6_Sunny			 = 0xF,  /*! C-PHY双摄 Sunny版本*/
	_HisFX3_Platform_Type_R10_Sunny			= 0xB,		/*! 万兆*/
	_HisFX3_Platform_Type_R8						= 0xC,		/*! 万兆 */
	_HisFX3_Platform_Type_R2C					= 0xD, /*! USB3.0 DPHY/DVP/LVDS 不带OS*/
	_HisFX3_Platform_Type_R5_Sunny			= 0xE,	/*! DPHY双摄 Sunny版本*/
	_HisFX3_Platform_Type_R11					= 0x10, /*! 2CPHY/2DPHY + 2DPHY光纤*/
	_HisFX3_Platform_Type_R12					= 0x11, /*! 1CPHY/1DPHY 光纤*/
	_HisFX3_Platform_Type_R15					= 0x12, /*! 4C4D		光纤x2*/
	_HisFX3_Platform_Type_R12S				= 0x13, /*! 1CPHY/1DPHY 光纤*/
	_HisFX3_Platform_Type_R19					= 0x14,  /*! 4C4D		光纤x2*/
	_HisFX3_Platform_Type_VC8D				=	0x15, 
	_HisFX3_Platform_Type_R12C				=	0x16,  /*! 1CPHY/1DPHY 光纤*/
	_HisFX3_Platform_Type_VM16F			= 0x17,
	_HisFX3_Platform_Type_R30					= 0x18,  /*! AGX */
	_HisFX3_Platform_Type_R20					= 0x19  /*! MINI PC*/
};

enum _HisFX3_CommunicationProtocal{
	_HisFX3_CommProtocal_I2C		=	0x0,
	_HisFX3_CommProtocal_SPI		=	0x1,
	_HisFX3_CommProtocal_I3C		= 0x2,
	_HisFX3_CommProtocal_UART = 0x3,
	_HisFX3_CommProtocal_Float	= 0x10,
	_HisFX3_CommProtocal_GND	= 0x11
};

enum UVC_CAPTURE_PROPETIES
{
	CAPTURE_BRIGHTNESS,
	CAPTURE_CONTRAST,
	CAPTURE_HUE,
	CAPTURE_SATURATION,
	CAPTURE_SHARPNESS,
	CAPTURE_GAMMA,
	CAPTURE_COLORENABLE,
	CAPTURE_WHITEBALANCE,
	CAPTURE_BACKLIGHTCOMPENSATION,
	CAPTURE_GAIN,
	CAPTURE_PAN,
	CAPTURE_TILT,
	CAPTURE_ROLL,
	CAPTURE_ZOOM,
	CAPTURE_EXPOSURE,
	CAPTURE_IRIS,
	CAPTURE_FOCUS,
	CAPTURE_PROP_MAX
};

enum _HisFX3_ImageSenor_Factory{
	_HisFX3_ImageSenor_Factory_OV								=	0x00,
	_HisFX3_ImageSenor_Factory_SONY							=	0x10,
	_HisFX3_ImageSenor_Factory_SANSUNG					=	0x20,
	_HisFX3_ImageSenor_Factory_HYNIX							=	0x30,
	_HisFX3_ImageSenor_Factory_APTINA						=	0x40,
	_HisFX3_ImageSenor_Factory_ST								=	0x50,
	_HisFX3_ImageSenor_Factory_TOSHIBA						=	0x60,
	_HisFX3_ImageSenor_Factory_GCOREINC					=	0x70,
	_HisFX3_ImageSenor_Factory_SUPERPIX					=	0x80,
	_HisFX3_ImageSenor_Factory_DONGBU						=	0x90,
	_HisFX3_ImageSenor_Factory_DESERIALIZER			= 0x91,
	_HisFX3_ImageSenor_Factory_CUSTOM						=	0xFE,
	_HisFX3_ImageSenor_Factory_OTHER						=	0xFF
};

enum _HisFX3_ImageSenor_DataType{
	_HisFX3_ImageSenor_DataType_RAW_U8			=	0x00,
	_HisFX3_ImageSenor_DataType_RAW_U10			=	0x01,
	_HisFX3_ImageSenor_DataType_RAW_U12			=	0x02,
	_HisFX3_ImageSenor_DataType_LYUV420_U8	=	0x03,
	_HisFX3_ImageSenor_DataType_YUV420_U8		=	0x04,
	_HisFX3_ImageSenor_DataType_YUV420_U10	=	0x05,
	_HisFX3_ImageSenor_DataType_YUV422_U8		=	0x06,
	_HisFX3_ImageSenor_DataType_YUV422_U10	=	0x07,
	_HisFX3_ImageSenor_DataType_OTHER				=	0xFF
};

/*! 接口及协议*/
enum _HisFX3_MIPILane_Stream
{
	_HisFX3_MIPILane_Stream_DVP									=	0x0,
	_HisFX3_MIPILane_Stream_Lane1_FPGA					=	0x1,
	_HisFX3_MIPILane_Stream_Lane2_FPGA					=	0x2,
	_HisFX3_MIPILane_Stream_Lane3_FPGA					=	0x3,
	_HisFX3_MIPILane_Stream_Lane4_FPGA					=	0x4,
	_HisFX3_MIPILane_Stream_Lane8_FPGA					=	0x8,
	_HisFX3_MIPILane_Stream_Lane1_ST							=	0x5,
	_HisFX3_MIPILane_Stream_Lane2_ST							=	0x6,
	_HisFX3_MIPILane_Stream_DPHY									= 0x0F,
	_HisFX3_MIPILane_Stream_SubLVDS_SONY				=	0x10,
	_HisFX3_MIPILane_Stream_SubLVDS_CMOSIS			=	0x11,
	_HisFX3_MIPILane_Stream_SubLVDS_OV					= 0x12,
	_HisFX3_MIPILane_Stream_SubLVDS_PANASONIC	= 0x13,
	_HisFX3_MIPILane_Stream_SubLVDS_END					=	0x1F,
	_HisFX3_MIPILane_Stream_Analog_Interleave				=	0x20,
	_HisFX3_MIPILane_Stream_Analog_Progressive			=	0x21,
	_HisFX3_MIPILane_Stream_SPI_BT656_Lane1			=	0x22, //BT656
	_HisFX3_MIPILane_Stream_SPI_BT656_Lane2			=	0x23,
	_HisFX3_MIPILane_Stream_SPI_BT656_Lane4			=	0x24,
	_HisFX3_MIPILane_Stream_BT1120M1_Interleave		=	0x26, //mode 1
	_HisFX3_MIPILane_Stream_BT1120M1_Progressive	=	0x27,
	_HisFX3_MIPILane_Stream_BT1120M2_Interleave		=	0x28, //mode2
	_HisFX3_MIPILane_Stream_BT1120M2_Progressive	=	0x2A,
	_HisFX3_MIPILane_Stream_SPI_MTK_Lane1				=	0x2B, //MTK
	_HisFX3_MIPILane_Stream_SPI_MTK_Lane2				=	0x2C,
	_HisFX3_MIPILane_Stream_SPI_MTK_Lane4				=	0x2D,
	_HisFX3_MIPILane_Stream_DVP_HDMI						=	0xFF,
	_HisFX3_MIPILane_Stream_UVC									=	0x30,
	_HisFX3_MIPILane_Stream_HDMI									=	0x31,
	_HisFX3_MIPILane_Stream_RTSP								=	0x34,
	_HisFX3_MIPILane_Stream_Jigboard							=	0x40,
	_HisFX3_MIPILane_Stream_HiSPI_Packetized_SP		=	0x50,
	_HisFX3_MIPILane_Stream_HiSPI_Streaming_SP		=	0x51,
	_HisFX3_MIPILane_Stream_HiSPI_Streaming_S			=	0x52,
	_HisFX3_MIPILane_Stream_HiSPI_ActiveStart_SP8	=	0x53,
	_HisFX3_MIPILane_Stream_HiSPI_END						= 0x5F,
	_HisFX3_MIPILane_Stream_CPHY								=	0x60
	
};

enum _HisFX3_Deinterlace_Method{
	_HisFX3_Deinterlace_Overlap	=	0x0
};

enum _HisFX3_BaylorMode{
	HisBaylor8_BGGR				=	0x01,
	HisBaylor8_RGGB				=	0x02,
	HisBaylor8_GRBG				=	0x03, 
	HisBaylor8_GBRG				=	0x04,
	HisBaylor8_MONO				=	0x07,
	HisBaylor8_END					= 0x0F,
	HisBaylor10_BGGR			=	0x11,
	HisBaylor10_RGGB			=	0x12,
	HisBaylor10_GRBG			=	0x13, 
	HisBaylor10_GBRG			=	0x14,
	HisBaylor10_MONO			=	0x17,
	HisBaylor10_END				= 0x1F,
	HisBaylor12_BGGR			=	0x41,
	HisBaylor12_RGGB			=	0x42,
	HisBaylor12_GRBG			=	0x43, 
	HisBaylor12_GBRG			=	0x44,
	HisBaylor12_MONO			=	0x47,
	HisBaylor12_END				= 0x4F,
	HisBaylor14_BGGR			=	0x51,
	HisBaylor14_RGGB			=	0x52,
	HisBaylor14_GRBG			=	0x53, 
	HisBaylor14_GBRG			=	0x54,
	HisBaylor14_MONO			=	0x57,
	HisBaylor14_END				= 0x5F,
	HisBaylor16_BGGR            =   0x61,
	HisBaylor16_RGGB            =   0x62,
	HisBaylor16_GRBG            =   0x63,
	HisBaylor16_GBRG            =   0x64,
	HisBaylor16_MONO            =   0x67,
	HisBaylor16_END				= 0x6F,
	HisBaylor_Compact			 = 0x80000000, /*! 数据排列变成高位在前，低位合并为1个Byte */
	HisYUV8_422_YUYV			=	0x21, //YUYV
	HisYUV8_422_UYVY			=	0x22,
	HisYUV8_422_YVYU			=	0x23,
	HisYUV8_422_VYUY			=	0x24,
	HisYUV8_422P					=	0x25,
	HisYUV8_420P					=	0x26,
	HisRGB_RGB24					=	0x30,
	HisRGB_BGR24					= 0x31,
	HisGray_Y8							= 0x71,
	HisRGB_Bilinear					=0x10000000, /*! 双线性差值算法，和HisRGB_RGB24, HisRGB_BGR24一起使用，eg: HisRGB_RGB24 | HisRGB_Bilinear*/
	HisOutputAddInfo				=0x20000000
};

enum _HisFX3_Platform_VoltFlag{
	_HisFX3_Platform_VlotOn_NONE = 0x0000,
	_HisFX3_Platform_VlotOn_AVDD = 0x0001,
	_HisFX3_Platform_VlotOn_DVDD = 0x0002,
	_HisFX3_Platform_VlotOn_DOVDD = 0x0004,
	_HisFX3_Platform_VlotOn_AF = 0x0008,
	_HisFX3_Platform_VlotOn_OTP = 0x0010,
	_HisFX3_Platform_VlotOn_POW = 0x0020,
	_HisFX3_Platform_VlotOn_IODD = 0x0040,
	_HisFX3_Platform_VlotOn_V5 = 0x0080,
	_HisFX3_Platform_VlotOn_V12					= 0x0100
};

enum _HisFX3_Deserializer {
	_HisFX3_Deserializer_UNKNOWN							= 0,
	_HisFX3_Deserializer_TI954									= 1,
	_HisFX3_Deserializer_MAXIM9296						= 2,
	_HisFX3_Deserializer_TI972									= 3,
	_HisFX3_Deserializer_MAXIM96706						= 4,
	_HisFX3_Deserializer_MAXIM9280						= 5
};

enum _HisFX3_Deserializer_Connect_Type{
	_HisFX3_Deserializer_COAX	=	0,
	_HisFX3_Deserializer_STP		=	1
};

enum _HisFX3_Deserializer_Mode{
	_HisFX3_Deserializer_TI_LF												=	0,
	_HisFX3_Deserializer_TI_HF												=	1,
	_HisFX3_Deserializer_TI_BackChannel								=	2,
	_HisFX3_Deserializer_MAXIM_GMSL1_HIM_Disable		=  3,
	_HisFX3_Deserializer_MAXIM_GMSL1_HIM_Enable		=  4,
	_HisFX3_Deserializer_MAXIM_GMSL2_3Gbps					=  5,
	_HisFX3_Deserializer_MAXIM_GMSL2_6Gbps					=  6
};

enum _HisFX3_Statistics_Type
{
	_HisFX3_Statistics_FPGA_Frame_Count		= 0x1,
	_HisFX3_Statistics_FPGA_PASS_LOCK		=	0x2
};

typedef struct _RRect
{
	int    left; /*！包含此坐标*/
	int    top; /*! 包含此坐标*/
	int    right;  /*！不包含此坐标*/
	int    bottom; /*！不包含此坐标*/

	_RRect() { left = top = right = bottom = 0; }
	_RRect(int left2, int top2, int right2, int bottom2)
	{
		this->left = left2;
		this->top = top2;
		this->right = right2;
		this->bottom = bottom2;
	}

	_RRect(const _RRect& src)
	{
		this->left = src.left;
		this->top = src.top;
		this->right = src.right;
		this->bottom = src.bottom;
	}

	_RRect& operator = (const _RRect& src)
	{
		this->left = src.left;
		this->top = src.top;
		this->right = src.right;
		this->bottom = src.bottom;
		return *this;
	}

	bool IsEqual(const _RRect& d)
	{
		return (this->left == d.left) && (this->right == d.right) && (this->top == d.top) && (this->bottom == d.bottom);
	}
} RRect, *PRRect;
 
typedef struct _HisFX3_PreviewStruct
{
	unsigned int ver; /*! 结构体版本号， 固定值， 不要修改*/
	unsigned int uiVoltSetFlag; /*!< 设置要操作的电压，eg. 只操作AVDD和DVDD:  _HisFX3_Platform_VlotOn_AVDD |  _HisFX3_Platform_VlotOn_DVDD； 全操作：0xFFFFFFFF*/
	float volt_DOVDD; /*!< 设置DOVDD电压，0.0~3.5范围可调, 实际所设电压 =  volt_DOVDD */
	float volt_DVDD; /*!< 设置DVDD电压，0.0~3.5范围可调, 实际所设电压 =  volt_DVDD */
	float volt_AVDD; /*!< 设置AVDD电压，0.0~3.5范围可调, 实际所设电压 =  volt_AVDD */
	float volt_AF; /*!< 设置AF电压，0.0~3.5范围可调, 实际所设电压 =  volt_AF */
	float volt_OTP; /*!< 设置DOVDD电压，0.0~10.0范围可调, 实际所设电压 =  volt_VFuse */
	float volt_POW; /*!< 设置POW电压，0.0~3.5范围可调, 实际所设电压 =  volt_POW */
	float volt_IODD; /*!< 设置IODD电压【板卡内部IO电平】【R5】，0.0~3.5范围可调, 实际所设电压 =  volt_IODD */
	float maxVoltDiff;  /*!< 每路电压设置后回读电压值，差异过大则断电返回错误； 单位：V； (maxVoltDiff < 10)时生效 */
	float volt_5V; /*!< 设置5V电压开关，0：不输出  1：输出 其他：不操作  */
	float volt_12V; /*!< 设置12V电压开关，0：不输出  1：输出  其他：不操作  */
	bool bIsSetRST; /*!< 是否设置bReset_ActiveLow */
	bool bReset_ActiveLow; /*!< true: 低电平有效，出图时拉高；   false: 高电平有效，出图时拉低 */
	bool bIsSetPWDN; /*!< 是否设置bPWND_ActiveLow */
	bool bPWND_ActiveLow; /*!< true: 低电平有效，出图时拉高；   false: 高电平有效，出图时拉低 */
	bool bIsSetMCLK; /*!< 是否设置MCLK*/
	double mclk; /*!< 设置mclk。 0~136MHz范围可调*/
	unsigned char onlyRightFrame; /*!< 是否只输出正确帧	b0: 设置FPGA;  b1: 设置上位机; */
	unsigned char ddr; /*!< 是否开启DDR缓存功能   0：关闭；1：开启；2：:不设置 */
	/*! 设置点亮时的上电时序
	 \sa _HisFX3_ImageSenor_Factory
	*/
	_HisFX3_ImageSenor_Factory sensorFactory;
	/*! 
	当工装类型 == _HisFX3_Platform_Type_RTSPM时， 表示URL；
	当sensorFactory == _HisFX3_ImageSenor_Factory_CUSTOM时， 由用户自定义上电时序；
	*/
	char powerUpSequence[256]; 
	/*! 设置板卡上传的数据格式
	\sa _HisFX3_BaylorMode
	*/
	_HisFX3_BaylorMode dataFormat;
	unsigned int iWidth; /*!< 设置一帧的图像宽，单位：像素 */
	unsigned int iHeight; /*!< 设置一帧的图像高，单位：像素 */
	unsigned int uiDummyLeft; /*!< 设置图像左边的Dummy Line */
	unsigned int uiDummyRight; /*!< 设置图像右边的Dummy Line */
	unsigned int uiDummyTop; /*!< 设置图像上边的Dummy Line */
	unsigned int uiDummyBottom; /*!< 设置图像下边的Dummy Line */
	int customTotalFrameBytes; /*! 用户自定义一帧数据大小，用于虚拟通道开启的情况*/
	RRect streamROI[_RMAX_STREAM_ROI_NUMS]; /*! 分块上传数据流，区块坐标设置*/
	unsigned int streamROINums; /*! 分块上传数据流，块数量，范围：[0,_RMAX_STREAM_ROI_NUMS]；0表示不分块*/
	/*! 设置Sensor数据接口
	\sa _HisFX3_MIPILane_Stream
	*/
	_HisFX3_MIPILane_Stream port;
	unsigned char ucLaneNum; /*!< 设置C-PHY, D-PHY, LVDS 数据Lane数 */


	unsigned char ucCommProtocal; /*!< 设置命令通讯协议。  0:I2C； 1:SPI; 2: I3C0；3:UART*/
	bool bCheckDeviceAck; /*!< true:IIC通信时侦测是否有ACK回馈； false: 不侦测 */
	bool bSPICSLow; /*!< 设置读写SPI时，CS电平(R5有效)。 true:CS电平为低； false: CS电平为高 */
	bool bSPILittleEndian; /*!< 设置读写SPI时，低位在前还是高位在前(R5有效)。 true:低位在前； false: 高位在前 */
	bool bSPIClkHigh; /*! 设置SPI时钟  true: CLK默认是在高电平；false: CLK默认是在低电平；需要R2C >= 3506 */
	unsigned int usI2CSpeed;  /*!< 设置IIC通信速率，1KHz~1MHz范围可调 */
	unsigned short usI2CIntervalTime; /*!< 设置下发IIC命令的间隔时间，单位：us */
	unsigned int usI2CCount; /*!< 设置IIC或者SPI的命令条数 */
	unsigned char* pucSlave; /*!< 指向设备地址数组指针 */
	unsigned int* puiReg; /*!< 指向寄存器地址数组指针 */
	unsigned int* puiData; /*!< 指向数据数组指针 */
	unsigned short* pusType; /*!< 指向命令类型数组指针，包括0x0816, 0x0808,0x1608,0x1616,0x1632 */

	unsigned int timeout; /*!< 等待图像数据的时间(单位:ms), 0为不等待*/
	bool virtualChannel; /*!< 设置是否开启虚拟通道解码 。 true:开启虚拟通道解码； false: 不开启虚拟通道 */
	unsigned int virtualSize; /*!< 保留 */

	unsigned short i2cByteDelay; /*!< I2C 每个字节之间的等待时间(单位：半个SCL时钟周期)。 如果设为0，则为批量下发模式；非0，则为单条下发模式*/
	unsigned char glReserve[46];

	//D-PHY
	unsigned char ucSignalMode; /*!< 设置DPHY信号模式 0: Power Down 1: SLVS 2:D-PHY */
	bool outputXVSXHS_DPHY; /*!< 设置解码D-PHY时是否输出XS, VS信号(从机模式) */
	unsigned int XHS_DPHY; /*!< 设置解码D-PHY的HS同步信号 */
	unsigned int XVS_DPHY; /*!< 设置解码D-PHY的VS同步信号 */
	unsigned char dphyReserve[48];

	//DVP
	bool bDVP_VS_ActiveHigh; /*!< DVP VS 同步信号设置。   true: 高电平有效；   false: 低电平有效 */
	bool bDVP_HS_ActiveHigh; /*!< DVP HS 同步信号设置。   true: 高电平有效；   false: 低电平有效 */
	unsigned char ucDVP_LineFormat; /*!< DVP数据线设置  0：采9:2   1: 采7:0   2：采15:0   3：采9:0  4：采11:0   5：采13:0 */
	int DVP_PhaseShift; /*!<设置并口采集同步信号相移  0:不相移;  1: 90度;  2: 180度;  3: 270度; */
	unsigned char dvpReserve[48];

	//LVDS
	bool bOutputXSVS; /*!< 设置解码LVDS时是否输出XS, VS信号 */
	unsigned int LVDS_XHS; /*!< 设置解码LVDS的HS同步信号 */
	unsigned int LVDS_XVS; /*!< 设置解码LVDS的VS同步信号 */
	unsigned int LVDSAlign; /*!< 设置解码LVDS的对齐方式 */
	unsigned char lvdsReserve[48];

	char strSensorName[64]; /*!< 设置Sensor名称，比如：imx234,imx081, */

	//CPHY
	unsigned int cphyMode; /*!< 0x0: SENSOR输出参考时钟; 0x1:SENSOR不输出参考时钟(9线模式) */
	double cphyRate;  /*!< CPHY速率， 在cphyMode==0x1时设置；单位：Gbps；支持范围：(0.1~1.6)(1.96~2.5) */
	
	unsigned int cphy2ndI2CCount;  /*!< 设置第2批次下发给SENSOR的寄存器数量 */
	unsigned char* cphy2ndSlave; /*!< 指向设备地址数组指针 */
	unsigned int* cphy2ndReg; /*!< 指向寄存器地址数组指针 */
	unsigned int* cphy2ndData; /*!< 指向数据数组指针 */
	unsigned short* cphy2ndType; /*!< 指向命令类型数组指针，包括0x0816, 0x0808,0x1608,0x1616,0x1632 */
	
	unsigned int cphySigI2CCount; /*!< 配置CPHY信号加强寄存器的数量*/
	unsigned char* cphySigSlave; /*!< 指向设备地址数组指针 */
	unsigned int* cphySigReg; /*!< 指向寄存器地址数组指针 */
	unsigned int* cphySigData; /*!< 指向数据数组指针 */
	unsigned short* cphySigType; /*!< 指向命令类型数组指针，包括0x0816, 0x0808,0x1608,0x1616,0x1632 */
	unsigned char cphyReserve[48];

	//R30
	unsigned int embedHeight;
	unsigned char agxReserve[64];

	//解串芯片
	_HisFX3_Deserializer_Connect_Type deserializerConnectType; /*! 解串芯片连接类型*/
	_HisFX3_Deserializer_Mode deserializerMode; /*! 解串芯片工作模式*/
	unsigned char deserializerSlaveAddress; /*! 解串芯片设备地址*/
	bool deserializerMasterMode; /*! 是否工作在主模式*/
	double deserializerSlaveModeVSyncRate; /*! 从模式场同步速率*/
	double deserializerSlaveModeVSyncDuty; /*! 从模式场同步占空比*/
	double deserializerSlaveModeHSyncRate;  /*! 从模式场行步速率*/
	double deserializerSlaveModeHSyncDuty;  /*! 从模式场行步占空比*/
	unsigned char sampleImageWidth_VC8D; /*! 图像宽抽点，只对VC8D生效*/
	unsigned char sampleImageHeight_VC8D; /*! 图像高抽点， 只对VC8D生效*/
	unsigned char deserializerReserve[44];

	//UVC
	char uvcLocation[64]; /*! UVC 位置信息*/
	unsigned char uvcReserve[64];

	unsigned char otherReserve[512];

	_HisFX3_PreviewStruct()
	{
		memset(this, 0, sizeof(_HisFX3_PreviewStruct));
		ver = 3;
		onlyRightFrame = 0x03;
		embedHeight =streamROINums =customTotalFrameBytes =virtualSize =LVDSAlign = timeout = DVP_PhaseShift = ucDVP_LineFormat = iWidth = iHeight =0;
		i2cByteDelay = 0;
		bSPILittleEndian =bDVP_VS_ActiveHigh = virtualChannel = false;
		deserializerMasterMode =bSPIClkHigh =bSPICSLow =bDVP_HS_ActiveHigh = bIsSetMCLK = bIsSetPWDN = bIsSetRST = bCheckDeviceAck = true;
		bReset_ActiveLow = bPWND_ActiveLow = false;
		ddr	=ucSignalMode = 2;
		sensorFactory = _HisFX3_ImageSenor_Factory_OV;
		dataFormat = HisBaylor10_BGGR;
		ucCommProtocal = _HisFX3_CommProtocal_I2C;
		uiVoltSetFlag = 0xFFFFFFFF;
		mclk =volt_DOVDD = volt_DVDD = volt_AVDD = volt_AF = volt_OTP = volt_POW = volt_IODD = 0.0f;
		maxVoltDiff = 1000.0f;
		cphyRate = -1.0;
		volt_5V = volt_12V = -1.0f;
		outputXVSXHS_DPHY	=bOutputXSVS = false;
		XHS_DPHY = LVDS_XHS = 1152;
		XVS_DPHY = LVDS_XVS = 3125;
		uiDummyLeft = uiDummyRight = uiDummyTop = uiDummyBottom = 0;
		cphyMode = 1;
		usI2CSpeed = 400;
		usI2CIntervalTime = 200;
		port = _HisFX3_MIPILane_Stream_DPHY;
		ucLaneNum = 4;
		cphySigI2CCount =usI2CCount = cphy2ndI2CCount = 0;
		cphySigSlave =pucSlave = cphy2ndSlave = 0;
		cphySigReg	=puiReg = cphy2ndReg = 0;
		cphySigData	=puiData = cphy2ndData = 0;
		cphySigType	=pusType = cphy2ndType = 0;
		uvcLocation[0] = powerUpSequence[0] = strSensorName[0] = '\0';
		deserializerSlaveAddress = 0x70;
	}

	~_HisFX3_PreviewStruct()
	{
		if (pucSlave) { delete[] pucSlave; pucSlave = 0; }
		if (puiReg) { delete[] puiReg; puiReg = 0; }
		if (puiData) { delete[] puiData; puiData = 0; }
		if (pusType) { delete[] pusType; pusType = 0; }

		if (cphy2ndSlave) { delete[] cphy2ndSlave; cphy2ndSlave = 0; }
		if (cphy2ndReg) { delete[] cphy2ndReg; cphy2ndReg = 0; }
		if (cphy2ndData) { delete[] cphy2ndData; cphy2ndData = 0; }
		if (cphy2ndType) { delete[] cphy2ndType; cphy2ndType = 0; }

		if (cphySigSlave) { delete[] cphySigSlave; cphySigSlave = 0; }
		if (cphySigReg) { delete[] cphySigReg; cphySigReg = 0; }
		if (cphySigData) { delete[] cphySigData; cphySigData = 0; }
		if (cphySigType) { delete[] cphySigType; cphySigType = 0; }
	}

	_HisFX3_PreviewStruct& operator = (const _HisFX3_PreviewStruct& src)
	{
		if (this == &src) return *this;

		if (this->pucSlave) { delete[] this->pucSlave; this->pucSlave = 0; }
		if (this->puiReg) { delete[] this->puiReg; this->puiReg = 0; }
		if (this->puiData) { delete[] this->puiData; this->puiData = 0; }
		if (this->pusType) { delete[] this->pusType; this->pusType = 0; }

		if (this->cphy2ndSlave) { delete[] this->cphy2ndSlave; this->cphy2ndSlave = 0; }
		if (this->cphy2ndReg) { delete[] this->cphy2ndReg; this->cphy2ndReg = 0; }
		if (this->cphy2ndData) { delete[] this->cphy2ndData; this->cphy2ndData = 0; }
		if (this->cphy2ndType) { delete[] this->cphy2ndType; this->cphy2ndType = 0; }

		if (this->cphySigSlave) { delete[] this->cphySigSlave; this->cphySigSlave = 0; }
		if (this->cphySigReg) { delete[] this->cphySigReg; this->cphySigReg = 0; }
		if (this->cphySigData) { delete[] this->cphySigData; this->cphySigData = 0; }
		if (this->cphySigType) { delete[] this->cphySigType; this->cphySigType = 0; }

		memcpy(this, &src, sizeof(_HisFX3_PreviewStruct));

		this->pucSlave					= 0;
		this->puiReg					= 0;
		this->puiData					= 0;
		this->pusType					= 0;
		this->cphy2ndSlave			= 0;
		this->cphy2ndReg			= 0;
		this->cphy2ndData			= 0;
		this->cphy2ndType			= 0;
		this->cphySigSlave			= 0;
		this->cphySigReg			= 0;
		this->cphySigData			= 0;
		this->cphySigType			= 0;

		if (src.usI2CCount && src.pucSlave && src.puiReg && src.puiData && src.pusType)
		{
			this->pucSlave = new unsigned char[src.usI2CCount];
			memcpy(this->pucSlave, src.pucSlave, src.usI2CCount * sizeof(unsigned char));
			this->puiReg = new unsigned int[src.usI2CCount];
			memcpy(this->puiReg, src.puiReg, src.usI2CCount * sizeof(unsigned int));
			this->puiData = new unsigned int[src.usI2CCount];
			memcpy(this->puiData, src.puiData, src.usI2CCount * sizeof(unsigned int));
			this->pusType = new unsigned short[src.usI2CCount];
			memcpy(this->pusType, src.pusType, src.usI2CCount * sizeof(unsigned short));
		}

		if (src.cphy2ndI2CCount && src.cphy2ndSlave && src.cphy2ndReg && src.cphy2ndData && src.cphy2ndType)
		{
			this->cphy2ndSlave = new unsigned char[src.cphy2ndI2CCount];
			memcpy(this->cphy2ndSlave, src.cphy2ndSlave, src.cphy2ndI2CCount * sizeof(unsigned char));
			this->cphy2ndReg = new unsigned int[src.cphy2ndI2CCount];
			memcpy(this->cphy2ndReg, src.cphy2ndReg, src.cphy2ndI2CCount * sizeof(unsigned int));
			this->cphy2ndData = new unsigned int[src.cphy2ndI2CCount];
			memcpy(this->cphy2ndData, src.cphy2ndData, src.cphy2ndI2CCount * sizeof(unsigned int));
			this->cphy2ndType = new unsigned short[src.cphy2ndI2CCount];
			memcpy(this->cphy2ndType, src.cphy2ndType, src.cphy2ndI2CCount * sizeof(unsigned short));
		}

		if (src.cphySigI2CCount && src.cphySigSlave && src.cphySigReg && src.cphySigData && src.cphySigType)
		{
			this->cphySigSlave = new unsigned char[src.cphySigI2CCount];
			memcpy(this->cphySigSlave, src.cphySigSlave, src.cphySigI2CCount * sizeof(unsigned char));
			this->cphySigReg = new unsigned int[src.cphySigI2CCount];
			memcpy(this->cphySigReg, src.cphySigReg, src.cphySigI2CCount * sizeof(unsigned int));
			this->cphySigData = new unsigned int[src.cphySigI2CCount];
			memcpy(this->cphySigData, src.cphySigData, src.cphySigI2CCount * sizeof(unsigned int));
			this->cphySigType = new unsigned short[src.cphySigI2CCount];
			memcpy(this->cphySigType, src.cphySigType, src.cphySigI2CCount * sizeof(unsigned short));
		}

		return *this;
	}
}HisFX3_PreviewStruct;

struct _HisFX3_Current_Calibration
{
	float flWorkAVDD[_HisFX3V2_CURRENTCAL_COUNT];
	float flWorkDVDD[_HisFX3V2_CURRENTCAL_COUNT];
	float flWorkDOVDD[_HisFX3V2_CURRENTCAL_COUNT];
	float flWorkAF[_HisFX3V2_CURRENTCAL_COUNT];
	float flWorkOTP[100];
	float flWorkPOW[_HisFX3V2_CURRENTCAL_COUNT];
	float flStandbyAVDD[_HisFX3V2_CURRENTCAL_COUNT];
	float flStandbyDVDD[_HisFX3V2_CURRENTCAL_COUNT];
	float flStandbyDOVDD[_HisFX3V2_CURRENTCAL_COUNT];
	float flStandbyAF[_HisFX3V2_CURRENTCAL_COUNT];
	float flStandbyPOW[_HisFX3V2_CURRENTCAL_COUNT];

	_HisFX3_Current_Calibration()
	{
		memset(flWorkAVDD, 0, sizeof(float) *_HisFX3V2_CURRENTCAL_COUNT);
		memset(flWorkDVDD, 0, sizeof(float) *_HisFX3V2_CURRENTCAL_COUNT);
		memset(flWorkDOVDD, 0, sizeof(float) *_HisFX3V2_CURRENTCAL_COUNT);
		memset(flWorkAF, 0, sizeof(float) *_HisFX3V2_CURRENTCAL_COUNT);
		memset(flWorkOTP, 0, sizeof(float) *100);
		memset(flStandbyAVDD, 0, sizeof(float) *_HisFX3V2_CURRENTCAL_COUNT);
		memset(flStandbyDVDD, 0, sizeof(float) *_HisFX3V2_CURRENTCAL_COUNT);
		memset(flStandbyDOVDD, 0, sizeof(float) *_HisFX3V2_CURRENTCAL_COUNT);
		memset(flStandbyAF, 0, sizeof(float) *_HisFX3V2_CURRENTCAL_COUNT);
		memset(flWorkPOW, 0, sizeof(float) *_HisFX3V2_CURRENTCAL_COUNT);
		memset(flStandbyPOW, 0, sizeof(float) *_HisFX3V2_CURRENTCAL_COUNT);
	}
};

struct _HisFX3_Voltage_Calibration
{
	float flVlotAVDD[_HisFX3V2_CURRENTCAL_COUNT];
	float flVlotDVDD[_HisFX3V2_CURRENTCAL_COUNT];
	float flVlotDOVDD[_HisFX3V2_CURRENTCAL_COUNT];
	float flVlotAF[_HisFX3V2_CURRENTCAL_COUNT];
	float flVlotOTP[_HisFX3V2_CURRENTCAL_COUNT];
	float flVlotPOW[_HisFX3V2_CURRENTCAL_COUNT];

	_HisFX3_Voltage_Calibration()
	{
		memset(flVlotAVDD, 0, sizeof(float) *_HisFX3V2_CURRENTCAL_COUNT);
		memset(flVlotDVDD, 0, sizeof(float) *_HisFX3V2_CURRENTCAL_COUNT);
		memset(flVlotDOVDD, 0, sizeof(float) *_HisFX3V2_CURRENTCAL_COUNT);
		memset(flVlotAF, 0, sizeof(float) *_HisFX3V2_CURRENTCAL_COUNT);
		memset(flVlotOTP, 0, sizeof(float) *_HisFX3V2_CURRENTCAL_COUNT);
		memset(flVlotPOW, 0, sizeof(float) *_HisFX3V2_CURRENTCAL_COUNT);
	}
};

struct _HisFX3R2_OSCal_Item
{
	unsigned char ucSwitch;
	char str1stName[_HisFX3_OS_PinName_MaxByte];
	char str2ndName[_HisFX3_OS_PinName_MaxByte];
	float flOffset;

	_HisFX3R2_OSCal_Item()
	{
		ucSwitch	=	0; //0-MIPI  1-DVP 2- MIPI C2
		str1stName[0]		=	'\0';
		str2ndName[0]	=	'\0';
		flOffset		=	0.0f;
	}
};


enum _HisFX3_Current_Switch{
	_HisFX3_Current_DVDD		=	0x0,
	_HisFX3_Current_DOVDD		=	0x1,
	_HisFX3_Current_AVDD		=	0x2,
	_HisFX3_Current_AF				=	0x3
};

enum _HisFX3_OS_PIN_INDEX{
	_HisFX3_OS_PIN_VPPS		=	0x0,
	_HisFX3_OS_PIN_AVDDS		=	0x1,
	_HisFX3_OS_PIN_DOVDDS	=	0x2,
	_HisFX3_OS_PIN_DVDDS		=	0x3,
	_HisFX3_OS_PIN_AFS			=	0x4,
	_HisFX3_OS_PIN_SGND		=	0x5,
	_HisFX3_OS_PIN_MCLK1		=	0x6,
	_HisFX3_OS_PIN_MCLK2		=	0x7,
	_HisFX3_OS_PIN_RST			=	0x8,
	_HisFX3_OS_PIN_PWDN		=	0x9,
	_HisFX3_OS_PIN_SCL			=	0xa,
	_HisFX3_OS_PIN_SDA			=	0xb
};

struct _HisFX3OS_Positive_Item
{
	/*! PIN脚名称, 可以调用HisFX3GetOSPinNameList查看所有的PIN脚名称
	\sa HisFX3GetOSPinNameList
	*/
	char strName[_HisFX3_OS_PinName_MaxByte];
	/*! GND脚名称
	\sa HisFX3GetOSPinNameList
	*/
	char strGNDName[_HisFX3_OS_PinName_MaxByte];	
	float flSpecMin; /*!< 可设可不设， 库内部没有用到 */
	float flSpecMax; /*!< 可设可不设， 库内部没有用到 */
	float flVoltValue; /*!< 测试完成之后，此PIN脚的电压值会存入flVoltValue，单位：mV*/
	bool bTest; /*!< true：测试		false：不测试 */
	int cam; /*! -1:默认 其他：模组编号*/
	int port; /*! -1: 默认  0：DPHY  1:CPHY  2:DVP 3:LVDS*/
	unsigned int reserve; /*! 保留*/

	_HisFX3OS_Positive_Item()
	{
		flVoltValue	=	0.0f;
		strName[0]	= strGNDName[0] = '\0';
		port = cam = -1;
		reserve = 0;
		bTest = true;
	}

	_HisFX3OS_Positive_Item& operator = (const _HisFX3OS_Positive_Item& src)
	{
		memcpy(this->strName, src.strName, _HisFX3_OS_PinName_MaxByte * sizeof(char));
		memcpy(this->strGNDName, src.strGNDName, _HisFX3_OS_PinName_MaxByte * sizeof(char));
		this->flSpecMin = src.flSpecMin;
		this->flSpecMax = src.flSpecMax;
		this->flVoltValue = src.flVoltValue;
		this->bTest = src.bTest;
		this->cam = src.cam;
		this->port = src.port;
		this->reserve = src.reserve;
		return *this;
	}
};

struct _HisFX3OS_Negtive_Item
{
	/*! PIN脚名称, 可以调用HisFX3GetOSPinNameList查看所有的PIN脚名称
	\sa HisFX3GetOSPinNameList
	*/
	char strName[_HisFX3_OS_PinName_MaxByte];
	/*! DOVDD脚名称
	\sa HisFX3GetOSPinNameList
	*/
	char strDOVDDName[_HisFX3_OS_PinName_MaxByte];
	float flSpecMin; /*!< 可设可不设， 库内部没有用到 */
	float flSpecMax;  /*!< 可设可不设， 库内部没有用到 */
	float flVoltValue; /*!< 测试完成之后，此PIN脚的电压值会存入flVoltValue，单位：mV*/
	bool bTest; /*!< true：测试		false：不测试 */
	int cam; /*! -1:默认 其他：模组编号*/
	int port; /*! -1: 默认  0：DPHY  1:CPHY  2:DVP 3:LVDS*/
	unsigned int reserve; /*! 保留*/

	_HisFX3OS_Negtive_Item()
	{
		flVoltValue	=	0.0f;
		strName[0]		= strDOVDDName[0] = '\0';
		port = cam = -1;
		reserve = 0;
		bTest = true;
	}

	_HisFX3OS_Negtive_Item& operator = (const _HisFX3OS_Negtive_Item& src)
	{
		memcpy(this->strName, src.strName, _HisFX3_OS_PinName_MaxByte * sizeof(char));
		memcpy(this->strDOVDDName, src.strDOVDDName, _HisFX3_OS_PinName_MaxByte * sizeof(char));
		this->flSpecMin = src.flSpecMin;
		this->flSpecMax = src.flSpecMax;
		this->flVoltValue = src.flVoltValue;
		this->bTest = src.bTest;
		this->cam = src.cam;
		this->port = src.port;
		this->reserve = src.reserve;
		return *this;
	}
};

struct _HisFX3OS_Short_Item
{
	/*! PIN脚名称, 可以调用HisFX3GetOSPinNameList查看所有的PIN脚名称
	\sa HisFX3GetOSPinNameList
	*/
	char strName[_HisFX3_OS_PinName_MaxByte];
	/*! 当shortIndex != 0时，可以查看strShortName得到与此PIN脚短路的PIN脚名称
	\sa HisFX3GetOSPinNameList
	*/
	char strShortName[_HisFX3_OS_PinName_MaxByte];
	float flShortSpec; /*!< 小于flShortSpec，则为短路， 单位：mV */
	float flVoltValue; /*!< 测试完成之后，此PIN脚的电压值会存入flVoltValue，单位：mV*/
	unsigned int shortIndex; /*!< ucShortIndex != 0, 就表示此PIN脚有短路  */
	bool bTest; /*!< true：测试		false：不测试 */
	int cam; /*! -1:默认 其他：模组编号(如果|0x8000 为单摄模式, 否则为双摄模式)*/
	int port; /*! -1: 默认  0：DPHY  1:CPHY  2:DVP 3:LVDS*/
	unsigned int reserve; /*! 保留*/

	_HisFX3OS_Short_Item()
	{
		shortIndex =	0;
		flVoltValue	=	0.0f;
		strName[0]	= strShortName[0] =  '\0';
		port = cam = -1;
		reserve = 0;
		bTest = true;
	}

	_HisFX3OS_Short_Item& operator = (const _HisFX3OS_Short_Item& src)
	{
		memcpy(this->strName, src.strName, _HisFX3_OS_PinName_MaxByte * sizeof(char));
		memcpy(this->strShortName, src.strShortName, _HisFX3_OS_PinName_MaxByte * sizeof(char));
		this->flShortSpec = src.flShortSpec;
		this->flVoltValue = src.flVoltValue;
		this->shortIndex = src.shortIndex;
		this->bTest = src.bTest;
		this->cam = src.cam;
		this->port = src.port;
		this->reserve = src.reserve;
		return *this;
	}
};

struct _HisFX3OS_Open_Item
{
	/*! PIN脚名称, 可以调用HisFX3GetOSPinNameList查看所有的PIN脚名称
	\sa HisFX3GetOSPinNameList
	*/
	char strName[_HisFX3_OS_PinName_MaxByte];
	/*! 当openIndex != 0时，可以查看strOpenName得到与此PIN脚开路的PIN脚名称
	\sa _HisFX3OS_Positive_Item
	*/
	char strOpenName[_HisFX3_OS_PinName_MaxByte];
	float flOpenSpec; /*!> 大于flOpenSpec，则为开路， 单位：mV */
	float flVoltValue; /*!< 测试完成之后，此PIN脚的电压值会存入flVoltValue，单位：mV*/
	unsigned int openIndex; /*!< ucOpenIndex != 0, 就表示此PIN脚开路  */
	bool bTest; /*!< true：测试		false：不测试 */
	int cam; /*! -1:默认 其他：模组编号*/
	int port; /*! -1: 默认  0：DPHY  1:CPHY  2:DVP 3:LVDS*/
	unsigned int reserve; /*! 保留*/

	_HisFX3OS_Open_Item()
	{
		openIndex =	0;
		flVoltValue	=	0.0f;
		strName[0]	= strOpenName[0] = '\0';
		port = cam = -1;
		reserve = 0;
		bTest = true;
	}

	_HisFX3OS_Open_Item& operator = (const _HisFX3OS_Open_Item& src)
	{
		memcpy(this->strName, src.strName, _HisFX3_OS_PinName_MaxByte * sizeof(char));
		memcpy(this->strOpenName, src.strOpenName, _HisFX3_OS_PinName_MaxByte * sizeof(char));
		this->flOpenSpec = src.flOpenSpec;
		this->flVoltValue = src.flVoltValue;
		this->openIndex = src.openIndex;
		this->bTest = src.bTest;
		this->cam = src.cam;
		this->port = src.port;
		this->reserve = src.reserve;
		return *this;
	}
};

struct _HisFX3OS_OHM_Item
{
	/*! PIN脚1 名称, 可以调用HisFX3GetOSPinNameList查看所有的PIN脚名称
	\sa HisFX3GetOSPinNameList
	*/
	char str1stName[_HisFX3_OS_PinName_MaxByte];
	/*! PIN脚2 名称, 可以调用HisFX3GetOSPinNameList查看所有的PIN脚名称
	\sa HisFX3GetOSPinNameList
	*/
	char str2ndName[_HisFX3_OS_PinName_MaxByte];
	float flOhmValue; /*!< 测试完成之后，此PIN脚的阻值会存入flOhmValue，单位：欧姆*/
	float flSpecMin; /*!< 可设可不设， 库内部没有用到 */
	float flSpecMax; /*!< 可设可不设， 库内部没有用到 */
	int cam; /*! -1:默认 其他：模组编号*/
	int port; /*! -1: 默认  0：DPHY  1:CPHY  2:DVP 3:LVDS*/
	unsigned int reserve; /*! 保留*/

	_HisFX3OS_OHM_Item()
	{
		str1stName[0] = str2ndName[0] = '\0';
		port = cam = -1;
		reserve = 0;
	}

	_HisFX3OS_OHM_Item& operator = (const _HisFX3OS_OHM_Item& src)
	{
		memcpy(this->str1stName, src.str1stName, _HisFX3_OS_PinName_MaxByte * sizeof(char));
		memcpy(this->str2ndName, src.str2ndName, _HisFX3_OS_PinName_MaxByte * sizeof(char));
		this->flOhmValue = src.flOhmValue;
		this->flSpecMin = src.flSpecMin;
		this->flSpecMax = src.flSpecMax;
		this->cam = src.cam;
		this->port = src.port;
		this->reserve = src.reserve;
		return *this;
	}
};

struct _HisFX3OS_LeakageCurrent_Item
{
	/*! PIN脚1 名称, 可以调用HisFX3GetOSPinNameList查看所有的PIN脚名称
	\sa HisFX3GetOSPinNameList
	*/
	char dutName[_HisFX3_OS_PinName_MaxByte];
	/*! PIN脚2 名称, 可以调用HisFX3GetOSPinNameList查看所有的PIN脚名称
	\sa HisFX3GetOSPinNameList
	*/
	char gndName[_HisFX3_OS_PinName_MaxByte];

	float current; /*!< 测试所得电流值，单位：uA*/
	int cam; /*! -1:默认 其他：模组编号*/
	int port; /*! -1: 默认  0：DPHY  1:CPHY  2:DVP 3:LVDS*/
	unsigned int reserve; /*! 保留*/

	_HisFX3OS_LeakageCurrent_Item()
	{
		dutName[0] = gndName[0] = '\0';
		port = cam = -1;
		reserve = 0;
	}

	_HisFX3OS_LeakageCurrent_Item& operator = (const _HisFX3OS_LeakageCurrent_Item& src)
	{
		memcpy(this, &src, sizeof(_HisFX3OS_LeakageCurrent_Item));
	}
};

struct _HisFX3OS_UpTime_Item
{
	/*! 接到恒流源的PIN脚名称
	\sa HisFX3GetOSPinNameList
	*/
	char dutName[_HisFX3_OS_PinName_MaxByte];
	/*! 接到GND的PIN脚名称
	\sa HisFX3GetOSPinNameList
	*/
	char gndName[_HisFX3_OS_PinName_MaxByte];
	float voltLimit; /*!< 电压上限值, 单位:mV */
	float smoothLineVoltDiff; /*! 曲线平滑压差规格， 当一段时间内的电压差小于此规格时，就退退出； 单位:mV*/
	unsigned int upTime; /*! 上升时间计数*/
	double pinVolt; /*! 最终电压值*/
	int cam; /*! -1:默认 其他：模组编号*/
	int port; /*! -1: 默认  0：DPHY  1:CPHY  2:DVP 3:LVDS*/
	unsigned int reserve; /*! 保留*/

	_HisFX3OS_UpTime_Item()
	{
		voltLimit = 3200.0f;
		smoothLineVoltDiff = 8.0f;
		dutName[0] = gndName[0] = '\0';
		port = cam = -1;
		upTime = reserve = 0;
		pinVolt = 0.0;
	}

	_HisFX3OS_UpTime_Item& operator = (const _HisFX3OS_UpTime_Item& src)
	{
		memcpy(this->dutName, src.dutName, _HisFX3_OS_PinName_MaxByte * sizeof(char));
		memcpy(this->gndName, src.gndName, _HisFX3_OS_PinName_MaxByte * sizeof(char));
		this->voltLimit = src.voltLimit;
		this->smoothLineVoltDiff = src.smoothLineVoltDiff;
		this->upTime = src.upTime;
		this->pinVolt = src.pinVolt;
		this->cam = src.cam;
		this->port = src.port;
		this->reserve = src.reserve;
		return *this;
	}
};

enum _HisFX3Platform_ErrorCode{
	HisFX3Error_Construct			=	0x0100,	/*!< 类构造失败*/
	HisFX3Error_CloseUSB3		=	0x0200,	/*!< 关闭usb3.0失败 */
	HisFX3Error_Timeout				=	0x0300,	/*!< 操作超时 */
	HisFX3Error_Parameter			=	0x0400,	/*!< 参数错误 */
	HisFX3Error_IsNotOpen			=	0x0500,	/*!< 设备还未打开*/
	HisFX3Error_IsNotPreview		=	0x0600,	/*!< 还未出图*/
	HisFX3Error_MallocBuffer		=	0x0700,	/*!< 申请内存失败 */
	HisFX3Error_USBDataOut		=	0x0800,	/*!< 下发数据失败 */
	HisFX3Error_Hardware			=	0x0900,	/*!< 其他硬件错误 */
	HisFX3Error_Other					=	0x0A00,	/*!< 其他错误*/
	HisFX3Error_NotSuperSpeed	=	0x0B00,	/*!< 不是超速模式*/
	HisFX3Error_CreateThread	=	0x0C00,		/*!< 创建线程失败 */
	HisFX3Error_License				=	0x0D00,		/*!< license 错误 */
	HisFX3Error_NoRespond		=	0x0E00,		/*!< IIC没响应*/
	HisFX3Error_WirteIIC				=	0x0F00,	/*!< 写IIC失败*/
	HisFX3Error_Check				=	0x1000	,	/*!< 校验码出错 */
	HisFX3Error_AlgData				=	0x1100,				//导入算法的数据部符合要求
	HisFX3Error_CreateEvent		=	0x1200,	/*!< 创建事件失败*/
	HisFX3Error_MemNotEnough	=	0x1300,	/*!< 内存空间不满足要求*/
	HisFX3Error_FuntionNotSupport	=	0x1400,	/*!< 此函数不支持*/
	HisFX3Error_ShortTestAbort	=	0x1500,	/*!< OS短路测试异常*/
	HisFX3Error_NegOpenTestAbort	=	0x1600,	/*!< OS负向测试异常*/
	HisFX3Error_PosOpenTestAbort	=	0x1700, /*!< OS正向测试异常*/
	HisFX3Error_ImgBufConvert			=	0x1800,	/*!< 图像格式转换错误*/
	HisFX3Error_NoHardware				=	0x1900,	/*!< 没有硬件*/
	HisFX3Error_Connect					=	0x1A00,
	HisFX3Error_CameraON					=	0x1B00,
	HisFX3Error_GrabFrame					=	0x1C00,	/*!< 抓帧失败*/
	HisFX3Error_OSAbort						=	0x1D00,	/*!< OS测试异常*/
	HisFX3Error_VersionNotMatch		=	0x1E00,	/*!< 版本不匹配*/
	HisFX3Error_UpdateHW					=	0x1F00,	/*!< 升级固件失败*/
	HisFX3Error_NoGrabber					=	0x2000,	/*!< 没有找到工装*/
	HisFX3Error_GrabberClosing			=	0x2100,  //grabber is closing
	HisFX3Error_StreamInReset			=	0x2200,  //stream in error, and reseting
	HisFX3Error_StreamExit				=	0x2300	,	//stream thread exit timeout
	HisFX3Error_AVDDVDiffBig			=	0x2400,	/*! AVDD设置的电压和测量的电压过大 */
	HisFX3Error_DVDDVDiffBig = 0x2401,	/*! DVDD设置的电压和测量的电压过大 */
	HisFX3Error_DOVDDVDiffBig = 0x2402,	/*! DOVDD设置的电压和测量的电压过大 */
	HisFX3Error_IODDVDiffBig = 0x2403,	/*! IODD设置的电压和测量的电压过大 */
	HisFX3Error_AFVDiffBig = 0x2404,	/*! AF设置的电压和测量的电压过大 */
	HisFX3Error_POWVDiffBig = 0x2405,	/*! POW设置的电压和测量的电压过大 */
	HisFX3Error_OTPVDiffBig = 0x2406,	/*! OTP设置的电压和测量的电压过大 */
	HisFX3Error_Preivewing					=	0x2500,		/*!< 出图中*/
	HisFX3Error_OSNotCalibration							=	0x2600, /*!< OS还没有校准*/
	HisFX3Error_VoltageNotCalibration					=	0x2700, /*!< 电压还未校准*/
	HisFX3Error_CurrentNotCalibration			=	0x2800, /*!< 电流还未校准*/
	HisFX3Error_IsNotStart								 =	 0x2900,
	HisFX3Error_OSPinName = 0x2A00,
	HisFX3Error_CPUNotMeet	=	0x2A01,
	HisFX3Error_InvalidLineSize	=	0x2A2,
	HisFX3Error_InvalidImageSize	=	0x2A03,
	HisFX3Error_OutofMemrory	=	0x2A04,
	HisFX3Error_InvalidFormat	=	0x2A05,
	HisFX3Error_OpenDev = 0x2A06, /*!< 打开工装失败*/
	HisFX3Error_NoImageData = 0x2A07, /*!< 没有图像数据*/
	HisFX3Error_OpenFile = 0x2A08, /*!< 打开文件失败*/
	HisFX3Error_OSNotSupported = 0x2A09, /*!< OS功能不支持*/
	HisFX3Error_USBDataIn = 0x2A0A, 	/*!< 上传数据失败 */
	HisFX3Error_LoadDLL = 0x2A0B, /*! 动态加载DLL文件失败*/
	HisFX3Error_LoadAPI = 0x2A0C, /*! 动态加载DLL 中的API失败*/
	HisFX3Error_CRC = 0x2A0D,  /*! 校验码错误*/
	HisFX3Error_AF = 0x2A0E, /*! 对焦失败*/
	HisFX3Error_FlashMemNotEnough	=	0x2A0F, /*! Flash空间不足*/
	HisFX3Error_PtIsNULL	=	0x2A10,  /*! 指针为NULL*/
	HisFX3Error_WaitEventAbort	=	0x2A11,  /*! 等待事件异常退出*/
	HisFX3Error_DecodeWidthHeight = 0x2A12,  /*! 图像宽高解码不匹配*/
	HisFX3Error_UpFrame = 0x2A13, 	/*! 上传错误帧*/
	HisFX3Error_DecodeDataFormat = 0x2A14,  /*! 解码数据格式不正确*/
	HisFX3Error_DecodeLaneNum = 0x2A15, 	/*! 解码LANE数不正确*/
	HisFX3Error_MeasureCPHYRate = 0x2A16, /*! 检测CPHY速率失败*/
	HisFX3Error_OperateRegister = 0x2A17, /*! 操作注册表失败*/
	HisFX3Error_AdapterCPUBand = 0x2A18, /*! 网卡CPU绑定错误*/
	HisFX3Error_ProcessCPUBand = 0x2A19, /*! 进程绑定CPU失败*/
	HisFX3Error_VoltNotOff = 0x2A1A,  /*! 电压未关闭*/
	HisFX3Error_ConnectSOC = 0x2A1B,  /*! 链接SOC失败*/
	HisFX3Error_AE = 0x2A1C,  /*! 自动曝光失败*/
	HisFX3Error_CreateFile = 0x2A1D,
	HisFX3Error_DriverVerTooLow = 0x2A1E,	/*! 版本过低*/
	HisFX3Error_GrabberVerTooLow = 0x2A1F, /*! 图像工装固件版本过低*/
	HisFX3Error_GrabberSerialNotMatch= 0x2A20, /*! 工装序列号不匹配*/
	HisFX3Error_OSVerTooLow = 0x2A21, /*! OS固件版本过低*/
	HisFX3Error_VoltCalibrationBeyondSepc = 0x2A22, /*! 电源校准超过规格*/
	HisFX3Error_BoxTypeNotMatch = 0x2A23, /*! 工装型号不匹配*/
	HisFX3Error_CommandCommunication = 0x2A24, /*! 命令通讯失败*/
	HisFX3Error_CableConnection	 = 0x2A25, /*! 接线错误*/
	HisFX3Error_DeserializerTypeNotSet = 0x2A26,  /*! 解串芯片型号没有设置*/
	HisFX3Error_FunctionNotImplemented = 0x2A27, /*! 函数没有对应的实现*/
	HisFX3Error_PreviewStructVerNotMatch = 0x2A28, /*! _HisFX3_PreviewStruct 版本号不匹配*/
	HisFX3Error_ImageInfoNotMatch = 0x2A29, /*! 图像信息不匹配*/
	HisFX3Error_WorkRCalibrationBeyondSepc = 0x2A2A, /*! 工作电流阻值超过规格*/
	HisFX3Error_CurrentCalibrationBeyondSepc = 0x2A2B, /*! 工作电流校准超过规格*/
	HisFX3Error_VCMDriverTypeNotCorrect = 0x2A2C,		/*! AF 马达型号不正确*/
	HisFX3Error_AESensorTypeNotCorrect = 0x2A2D,		/*! AE SENSOR型号不正确*/
	HisFX3Error_I2CSlaveConflic = 0x2A2E,						/*! I2C设备地址冲突*/
	HisFX3Error_DeserailizerBoardNotRight = 0x2A2F      /*! 插错了解串板*/
}; 

enum _HisFX3_YUVCVTRGB_FLAG{
	_HisFX3_YUVCVTRGB_BT601				=	0x1,
	_HisFX3_YUVCVTRGB_BT709				=	0x2
};

struct _HisFX3_AF_Block
{
	int left; /*! 单位：像素*/
	int top; /*! 单位：像素*/
	int right; /*! 单位：像素*/
	int bottom; /*! 单位：像素*/
	int weight; /*! 对焦曲线权重, 0~100*/

	_HisFX3_AF_Block() {}
	_HisFX3_AF_Block(_HisFX3_AF_Block& src)
	{
		this->left = src.left;
		this->top = src.top;
		this->right = src.right;
		this->bottom = src.bottom;
		this->weight = src.weight;
	}

	_HisFX3_AF_Block& operator = (const _HisFX3_AF_Block& src)
	{
		this->left = src.left;
		this->top = src.top;
		this->right = src.right;
		this->bottom = src.bottom;
		this->weight = src.weight;
		return *this;
	}
};

struct _HisFX3_VCMDriver_Cfg
{
	char type[32]; /*! 马达型号, 内置9714a,gt9762s,dw9814,vm149e,fp5510,sd12,9718s,ov5645,dw9763, 
				   dw9807,ad5823,bu64243,bu64297,bu64291,dw9767,dw9800,dw9810,fp5512,ak7375*/
	unsigned char slave; /*! 设备地址*/

	unsigned char iicCount; /*! IIC数量*/
	unsigned char iicInterval; /*! IIC间隔时间, 单位：ms*/
	unsigned char regBytes; /*! 寄存器位长度，单位：Byte*/
	unsigned char dataBytes; /*! 数据位长度， 单位:Byte*/
	unsigned char regRightShift[2];
	unsigned char regLeftShift[2];
	unsigned short regAnd[2];
	unsigned short regOr[2];
	unsigned char dataRightShift[2];
	unsigned char dataLeftShift[2];
	unsigned short dataAnd[2];
	unsigned short dataOr[2];

	_HisFX3_VCMDriver_Cfg()
	{
		type[0] = '\0';
		iicCount = 0;
		iicInterval = 0;
	}
};

struct _HisFX3_FPGAAF_Cfg
{
	const unsigned int ver; /*! 结构体版本号， 内部使用，无需修改*/
	bool doCurveFit; /*! 是否要做曲线拟合*/
	unsigned char afAlg; /*!对焦算法*/
	unsigned char mtfAlg; /*! 解析力算法：0：BAYER8计算；1：Y8计算*/
	unsigned char waitMotorStableMethod; /*! 等待马达稳定的延时方法，0:等待固定的帧数  1:等待固定的时间*/
	unsigned char frames[2]; /*! 等待马达稳定的帧数；数组0：大步近延帧；数组1：:小步进延帧*/
	unsigned short waitms[2]; /*! 等待马达稳定的时间， 单位:ms；数组0：大步近延时；数组1：:小步进延时*/
	unsigned int timeout; /*! 对焦过程timeout时间， 单位:ms*/
	unsigned short steptimeout; /*! 单独等待正确帧的timeout时间，单位:ms*/
	unsigned char blockCount; /*! 算解析力ROI个数，范围(1: 9)*/
	_HisFX3_AF_Block roi[9];
	_HisFX3_VCMDriver_Cfg motor;
	unsigned int bigStep; /*! 马达对焦策略大步步数*/
	unsigned int smallStep; /*! 马达对焦策略小步步数*/
	double bsChangeMTF; /*! 马达大小步数切换的解析力阀值*/
	int motorStart; /*! 马达对焦的范围起始位置*/
	int motorEnd; /*! 马达对焦的范围结束位置*/
	double peakValidMTF; /*! PEAK点的最小MTF值*/
	double curveDropMTF; /*! 判断曲线下降的MTF落差值*/
	int luxDiffMin;	/*! 亮度差值范围最小值*/
	int luxDiffMax;	/*! 亮度差值范围最大值*/
	double pixelNumsMin; /*! 最低有效像素比例*/

	_HisFX3_FPGAAF_Cfg()
		: ver(1), doCurveFit(false)
	{
		blockCount =afAlg = mtfAlg =0;
		waitMotorStableMethod = 1;
		frames[0] = frames[1] = 2;
		waitms[0] = waitms[1] = 100;
		timeout = 10000;
		steptimeout = 500;
		bigStep = 20; smallStep = 5;
		motorStart = 0; motorEnd = 1023;
		luxDiffMin = 6; luxDiffMax = 200;
		pixelNumsMin = 0.0001;
	}
};

struct _HisFX3_AF_Curve
{
	int motorDec; /*! 马达值*/
	double mtf; /*! MTF 权重值*/
	double roiMTF[9]; /*! 支持9个ROI全部曲线上传的版本，实际的对焦步数最多只能到180步。 这个在设置参数时需要考虑*/

	_HisFX3_AF_Curve() {}
	_HisFX3_AF_Curve(const _HisFX3_AF_Curve& src)
	{
		this->motorDec = src.motorDec;
		this->mtf = src.mtf;
		memcpy(this->roiMTF, src.roiMTF, 9 * sizeof(double));
	}

	_HisFX3_AF_Curve& operator = (const _HisFX3_AF_Curve& src)
	{
		this->motorDec = src.motorDec;
		this->mtf = src.mtf;
		memcpy(this->roiMTF, src.roiMTF, 9 * sizeof(double));
		return *this;
	}
};

struct _HisFX3_FPGAAF_Rel
{
	int peakMotor[10]; /*! PEAK点的马达值, 索引0：权重曲线的马达值；索引1~9：各个ROI的马达值*/
	double peakMTF[10]; /*! PEAK点的MTF值，索引0：权重曲线的MTF值；索引1~9：各个ROI的MTF值*/
	_HisFX3_AF_Curve curve[4096];
	unsigned int curvePtCount; /*! 曲线的点数*/
};

struct _HisFX3_Exposure_Cfg
{
	char type[32]; /*! SENSOR型号, 内置ov1,ov2,sony,hynix,samsung,galaxycore,superpix,ov2775, ov2718,aptina,hi1336,hi545*/
	unsigned char slave; /*! 设备地址*/

	unsigned char iicCount; /*! IIC数量*/
	unsigned char iicInterval; /*! IIC间隔时间, 单位：ms*/
	unsigned char regBytes; /*! 寄存器位长度，单位：Byte*/
	unsigned char dataBytes; /*! 数据位长度， 单位:Byte*/
	unsigned char regRightShift[3];
	unsigned char regLeftShift[3];
	unsigned short regAnd[3];
	unsigned short regOr[3];
	unsigned char dataRightShift[3];
	unsigned char dataLeftShift[3];
	unsigned short dataAnd[3];
	unsigned short dataOr[3];

	_HisFX3_Exposure_Cfg()
	{
		type[0] = '\0';
		iicCount = 0;
		iicInterval = 0;
	}
};

struct _HisFX3_FPGAAE_Cfg
{
	const unsigned int ver; /*! 结构体版本号， 内部使用，无需修改*/
	unsigned char aeChannel; /*! 选择计算亮度的通道：0：BAYER8计算；1：Y8计算*/
	unsigned char waitMotorStableMethod; /*! 等待曝光稳定的延时方法，0:等待固定的帧数  1:等待固定的时间*/
	unsigned char frames; /*! 等待曝光稳定的帧数；*/
	unsigned short waitms; /*! 等待曝光稳定的时间， 单位:ms；*/
	unsigned int timeout; /*! 曝光过程timeout时间， 单位:ms*/
	unsigned short steptimeout; /*! 单独等待正确帧的timeout时间，单位:ms*/
	unsigned char maxSteps; /*! AE动作最多步数*/
	unsigned char luxMin; /*! AE目标：luxMin <= ae <= luxMax */
	unsigned char luxMax;
	_HisFX3_AF_Block roi;
	_HisFX3_Exposure_Cfg expCfg;

	_HisFX3_FPGAAE_Cfg()
		: ver(1)
	{
		aeChannel = 0;
		waitMotorStableMethod = 1;
		frames = 2;
		waitms = maxSteps = 100;
		timeout = 10000;
		steptimeout = 500;
		luxMin = 170;
		luxMax = 190;
	}
};

struct _HisFX3_AE_Curve
{
	unsigned int expValue; /*! 曝光时间*/
	unsigned char luxValue; /*! 亮度值*/

	_HisFX3_AE_Curve() {}
	_HisFX3_AE_Curve(const _HisFX3_AE_Curve& src)
	{
		this->expValue = src.expValue;
		this->luxValue = src.luxValue;
	}

	_HisFX3_AE_Curve& operator = (const _HisFX3_AE_Curve& src)
	{
		this->expValue = src.expValue;
		this->luxValue = src.luxValue;
		return *this;
	}
};

struct _HisFX3_FPGAAE_Rel
{
	unsigned int expValue; /*! 当前曝光时间*/
	unsigned char luxValue; /*! 当前亮度值*/
	_HisFX3_AE_Curve curve[255];
	unsigned int curvePtCount; /*! 曲线的点数*/
};

#endif
