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
	_HisFX3_Platform_Type_R2R3					=	0x2, /*! �˰�SDK��֧��*/
	_HisFX3_Platform_Type_R5						=	0x4, /*! �˰�SDK�ݲ�֧��*/
	_HisFX3_Platform_Type_R3X					=	0x5,
	_HisFX3_Platform_Type_UVC					=	0x6, /*! ��׼Э��UVC ģ��*/
	_HisFX3_Platform_Type_RTSPM				=	0x7, /*! RTSP�������*/
	_HisFX3_Platform_Type_R5X					=	0x8,
	_HisFX3_Platform_Type_HDMI					=	0x9,  /*! HDMI PCIE��*/
	_HisFX3_Platform_Type_R6						=	0xA,  /*! C-PHY˫�� */
	_HisFX3_Platform_Type_R6_Sunny			 = 0xF,  /*! C-PHY˫�� Sunny�汾*/
	_HisFX3_Platform_Type_R10_Sunny			= 0xB,		/*! ����*/
	_HisFX3_Platform_Type_R8						= 0xC,		/*! ���� */
	_HisFX3_Platform_Type_R2C					= 0xD, /*! USB3.0 DPHY/DVP/LVDS ����OS*/
	_HisFX3_Platform_Type_R5_Sunny			= 0xE,	/*! DPHY˫�� Sunny�汾*/
	_HisFX3_Platform_Type_R11					= 0x10, /*! 2CPHY/2DPHY + 2DPHY����*/
	_HisFX3_Platform_Type_R12					= 0x11, /*! 1CPHY/1DPHY ����*/
	_HisFX3_Platform_Type_R15					= 0x12, /*! 4C4D		����x2*/
	_HisFX3_Platform_Type_R12S				= 0x13, /*! 1CPHY/1DPHY ����*/
	_HisFX3_Platform_Type_R19					= 0x14,  /*! 4C4D		����x2*/
	_HisFX3_Platform_Type_VC8D				=	0x15, 
	_HisFX3_Platform_Type_R12C				=	0x16,  /*! 1CPHY/1DPHY ����*/
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

/*! �ӿڼ�Э��*/
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
	HisBaylor_Compact			 = 0x80000000, /*! �������б�ɸ�λ��ǰ����λ�ϲ�Ϊ1��Byte */
	HisYUV8_422_YUYV			=	0x21, //YUYV
	HisYUV8_422_UYVY			=	0x22,
	HisYUV8_422_YVYU			=	0x23,
	HisYUV8_422_VYUY			=	0x24,
	HisYUV8_422P					=	0x25,
	HisYUV8_420P					=	0x26,
	HisRGB_RGB24					=	0x30,
	HisRGB_BGR24					= 0x31,
	HisGray_Y8							= 0x71,
	HisRGB_Bilinear					=0x10000000, /*! ˫���Բ�ֵ�㷨����HisRGB_RGB24, HisRGB_BGR24һ��ʹ�ã�eg: HisRGB_RGB24 | HisRGB_Bilinear*/
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
	int    left; /*������������*/
	int    top; /*! ����������*/
	int    right;  /*��������������*/
	int    bottom; /*��������������*/

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
	unsigned int ver; /*! �ṹ��汾�ţ� �̶�ֵ�� ��Ҫ�޸�*/
	unsigned int uiVoltSetFlag; /*!< ����Ҫ�����ĵ�ѹ��eg. ֻ����AVDD��DVDD:  _HisFX3_Platform_VlotOn_AVDD |  _HisFX3_Platform_VlotOn_DVDD�� ȫ������0xFFFFFFFF*/
	float volt_DOVDD; /*!< ����DOVDD��ѹ��0.0~3.5��Χ�ɵ�, ʵ�������ѹ =  volt_DOVDD */
	float volt_DVDD; /*!< ����DVDD��ѹ��0.0~3.5��Χ�ɵ�, ʵ�������ѹ =  volt_DVDD */
	float volt_AVDD; /*!< ����AVDD��ѹ��0.0~3.5��Χ�ɵ�, ʵ�������ѹ =  volt_AVDD */
	float volt_AF; /*!< ����AF��ѹ��0.0~3.5��Χ�ɵ�, ʵ�������ѹ =  volt_AF */
	float volt_OTP; /*!< ����DOVDD��ѹ��0.0~10.0��Χ�ɵ�, ʵ�������ѹ =  volt_VFuse */
	float volt_POW; /*!< ����POW��ѹ��0.0~3.5��Χ�ɵ�, ʵ�������ѹ =  volt_POW */
	float volt_IODD; /*!< ����IODD��ѹ���忨�ڲ�IO��ƽ����R5����0.0~3.5��Χ�ɵ�, ʵ�������ѹ =  volt_IODD */
	float maxVoltDiff;  /*!< ÿ·��ѹ���ú�ض���ѹֵ�����������ϵ緵�ش��� ��λ��V�� (maxVoltDiff < 10)ʱ��Ч */
	float volt_5V; /*!< ����5V��ѹ���أ�0�������  1����� ������������  */
	float volt_12V; /*!< ����12V��ѹ���أ�0�������  1�����  ������������  */
	bool bIsSetRST; /*!< �Ƿ�����bReset_ActiveLow */
	bool bReset_ActiveLow; /*!< true: �͵�ƽ��Ч����ͼʱ���ߣ�   false: �ߵ�ƽ��Ч����ͼʱ���� */
	bool bIsSetPWDN; /*!< �Ƿ�����bPWND_ActiveLow */
	bool bPWND_ActiveLow; /*!< true: �͵�ƽ��Ч����ͼʱ���ߣ�   false: �ߵ�ƽ��Ч����ͼʱ���� */
	bool bIsSetMCLK; /*!< �Ƿ�����MCLK*/
	double mclk; /*!< ����mclk�� 0~136MHz��Χ�ɵ�*/
	unsigned char onlyRightFrame; /*!< �Ƿ�ֻ�����ȷ֡	b0: ����FPGA;  b1: ������λ��; */
	unsigned char ddr; /*!< �Ƿ���DDR���湦��   0���رգ�1��������2��:������ */
	/*! ���õ���ʱ���ϵ�ʱ��
	 \sa _HisFX3_ImageSenor_Factory
	*/
	_HisFX3_ImageSenor_Factory sensorFactory;
	/*! 
	����װ���� == _HisFX3_Platform_Type_RTSPMʱ�� ��ʾURL��
	��sensorFactory == _HisFX3_ImageSenor_Factory_CUSTOMʱ�� ���û��Զ����ϵ�ʱ��
	*/
	char powerUpSequence[256]; 
	/*! ���ð忨�ϴ������ݸ�ʽ
	\sa _HisFX3_BaylorMode
	*/
	_HisFX3_BaylorMode dataFormat;
	unsigned int iWidth; /*!< ����һ֡��ͼ�����λ������ */
	unsigned int iHeight; /*!< ����һ֡��ͼ��ߣ���λ������ */
	unsigned int uiDummyLeft; /*!< ����ͼ����ߵ�Dummy Line */
	unsigned int uiDummyRight; /*!< ����ͼ���ұߵ�Dummy Line */
	unsigned int uiDummyTop; /*!< ����ͼ���ϱߵ�Dummy Line */
	unsigned int uiDummyBottom; /*!< ����ͼ���±ߵ�Dummy Line */
	int customTotalFrameBytes; /*! �û��Զ���һ֡���ݴ�С����������ͨ�����������*/
	RRect streamROI[_RMAX_STREAM_ROI_NUMS]; /*! �ֿ��ϴ���������������������*/
	unsigned int streamROINums; /*! �ֿ��ϴ�������������������Χ��[0,_RMAX_STREAM_ROI_NUMS]��0��ʾ���ֿ�*/
	/*! ����Sensor���ݽӿ�
	\sa _HisFX3_MIPILane_Stream
	*/
	_HisFX3_MIPILane_Stream port;
	unsigned char ucLaneNum; /*!< ����C-PHY, D-PHY, LVDS ����Lane�� */


	unsigned char ucCommProtocal; /*!< ��������ͨѶЭ�顣  0:I2C�� 1:SPI; 2: I3C0��3:UART*/
	bool bCheckDeviceAck; /*!< true:IICͨ��ʱ����Ƿ���ACK������ false: ����� */
	bool bSPICSLow; /*!< ���ö�дSPIʱ��CS��ƽ(R5��Ч)�� true:CS��ƽΪ�ͣ� false: CS��ƽΪ�� */
	bool bSPILittleEndian; /*!< ���ö�дSPIʱ����λ��ǰ���Ǹ�λ��ǰ(R5��Ч)�� true:��λ��ǰ�� false: ��λ��ǰ */
	bool bSPIClkHigh; /*! ����SPIʱ��  true: CLKĬ�����ڸߵ�ƽ��false: CLKĬ�����ڵ͵�ƽ����ҪR2C >= 3506 */
	unsigned int usI2CSpeed;  /*!< ����IICͨ�����ʣ�1KHz~1MHz��Χ�ɵ� */
	unsigned short usI2CIntervalTime; /*!< �����·�IIC����ļ��ʱ�䣬��λ��us */
	unsigned int usI2CCount; /*!< ����IIC����SPI���������� */
	unsigned char* pucSlave; /*!< ָ���豸��ַ����ָ�� */
	unsigned int* puiReg; /*!< ָ��Ĵ�����ַ����ָ�� */
	unsigned int* puiData; /*!< ָ����������ָ�� */
	unsigned short* pusType; /*!< ָ��������������ָ�룬����0x0816, 0x0808,0x1608,0x1616,0x1632 */

	unsigned int timeout; /*!< �ȴ�ͼ�����ݵ�ʱ��(��λ:ms), 0Ϊ���ȴ�*/
	bool virtualChannel; /*!< �����Ƿ�������ͨ������ �� true:��������ͨ�����룻 false: ����������ͨ�� */
	unsigned int virtualSize; /*!< ���� */

	unsigned short i2cByteDelay; /*!< I2C ÿ���ֽ�֮��ĵȴ�ʱ��(��λ�����SCLʱ������)�� �����Ϊ0����Ϊ�����·�ģʽ����0����Ϊ�����·�ģʽ*/
	unsigned char glReserve[46];

	//D-PHY
	unsigned char ucSignalMode; /*!< ����DPHY�ź�ģʽ 0: Power Down 1: SLVS 2:D-PHY */
	bool outputXVSXHS_DPHY; /*!< ���ý���D-PHYʱ�Ƿ����XS, VS�ź�(�ӻ�ģʽ) */
	unsigned int XHS_DPHY; /*!< ���ý���D-PHY��HSͬ���ź� */
	unsigned int XVS_DPHY; /*!< ���ý���D-PHY��VSͬ���ź� */
	unsigned char dphyReserve[48];

	//DVP
	bool bDVP_VS_ActiveHigh; /*!< DVP VS ͬ���ź����á�   true: �ߵ�ƽ��Ч��   false: �͵�ƽ��Ч */
	bool bDVP_HS_ActiveHigh; /*!< DVP HS ͬ���ź����á�   true: �ߵ�ƽ��Ч��   false: �͵�ƽ��Ч */
	unsigned char ucDVP_LineFormat; /*!< DVP����������  0����9:2   1: ��7:0   2����15:0   3����9:0  4����11:0   5����13:0 */
	int DVP_PhaseShift; /*!<���ò��ڲɼ�ͬ���ź�����  0:������;  1: 90��;  2: 180��;  3: 270��; */
	unsigned char dvpReserve[48];

	//LVDS
	bool bOutputXSVS; /*!< ���ý���LVDSʱ�Ƿ����XS, VS�ź� */
	unsigned int LVDS_XHS; /*!< ���ý���LVDS��HSͬ���ź� */
	unsigned int LVDS_XVS; /*!< ���ý���LVDS��VSͬ���ź� */
	unsigned int LVDSAlign; /*!< ���ý���LVDS�Ķ��뷽ʽ */
	unsigned char lvdsReserve[48];

	char strSensorName[64]; /*!< ����Sensor���ƣ����磺imx234,imx081, */

	//CPHY
	unsigned int cphyMode; /*!< 0x0: SENSOR����ο�ʱ��; 0x1:SENSOR������ο�ʱ��(9��ģʽ) */
	double cphyRate;  /*!< CPHY���ʣ� ��cphyMode==0x1ʱ���ã���λ��Gbps��֧�ַ�Χ��(0.1~1.6)(1.96~2.5) */
	
	unsigned int cphy2ndI2CCount;  /*!< ���õ�2�����·���SENSOR�ļĴ������� */
	unsigned char* cphy2ndSlave; /*!< ָ���豸��ַ����ָ�� */
	unsigned int* cphy2ndReg; /*!< ָ��Ĵ�����ַ����ָ�� */
	unsigned int* cphy2ndData; /*!< ָ����������ָ�� */
	unsigned short* cphy2ndType; /*!< ָ��������������ָ�룬����0x0816, 0x0808,0x1608,0x1616,0x1632 */
	
	unsigned int cphySigI2CCount; /*!< ����CPHY�źż�ǿ�Ĵ���������*/
	unsigned char* cphySigSlave; /*!< ָ���豸��ַ����ָ�� */
	unsigned int* cphySigReg; /*!< ָ��Ĵ�����ַ����ָ�� */
	unsigned int* cphySigData; /*!< ָ����������ָ�� */
	unsigned short* cphySigType; /*!< ָ��������������ָ�룬����0x0816, 0x0808,0x1608,0x1616,0x1632 */
	unsigned char cphyReserve[48];

	//R30
	unsigned int embedHeight;
	unsigned char agxReserve[64];

	//�⴮оƬ
	_HisFX3_Deserializer_Connect_Type deserializerConnectType; /*! �⴮оƬ��������*/
	_HisFX3_Deserializer_Mode deserializerMode; /*! �⴮оƬ����ģʽ*/
	unsigned char deserializerSlaveAddress; /*! �⴮оƬ�豸��ַ*/
	bool deserializerMasterMode; /*! �Ƿ�������ģʽ*/
	double deserializerSlaveModeVSyncRate; /*! ��ģʽ��ͬ������*/
	double deserializerSlaveModeVSyncDuty; /*! ��ģʽ��ͬ��ռ�ձ�*/
	double deserializerSlaveModeHSyncRate;  /*! ��ģʽ���в�����*/
	double deserializerSlaveModeHSyncDuty;  /*! ��ģʽ���в�ռ�ձ�*/
	unsigned char sampleImageWidth_VC8D; /*! ͼ����㣬ֻ��VC8D��Ч*/
	unsigned char sampleImageHeight_VC8D; /*! ͼ��߳�㣬 ֻ��VC8D��Ч*/
	unsigned char deserializerReserve[44];

	//UVC
	char uvcLocation[64]; /*! UVC λ����Ϣ*/
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
	/*! PIN������, ���Ե���HisFX3GetOSPinNameList�鿴���е�PIN������
	\sa HisFX3GetOSPinNameList
	*/
	char strName[_HisFX3_OS_PinName_MaxByte];
	/*! GND������
	\sa HisFX3GetOSPinNameList
	*/
	char strGNDName[_HisFX3_OS_PinName_MaxByte];	
	float flSpecMin; /*!< ����ɲ��裬 ���ڲ�û���õ� */
	float flSpecMax; /*!< ����ɲ��裬 ���ڲ�û���õ� */
	float flVoltValue; /*!< �������֮�󣬴�PIN�ŵĵ�ѹֵ�����flVoltValue����λ��mV*/
	bool bTest; /*!< true������		false�������� */
	int cam; /*! -1:Ĭ�� ������ģ����*/
	int port; /*! -1: Ĭ��  0��DPHY  1:CPHY  2:DVP 3:LVDS*/
	unsigned int reserve; /*! ����*/

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
	/*! PIN������, ���Ե���HisFX3GetOSPinNameList�鿴���е�PIN������
	\sa HisFX3GetOSPinNameList
	*/
	char strName[_HisFX3_OS_PinName_MaxByte];
	/*! DOVDD������
	\sa HisFX3GetOSPinNameList
	*/
	char strDOVDDName[_HisFX3_OS_PinName_MaxByte];
	float flSpecMin; /*!< ����ɲ��裬 ���ڲ�û���õ� */
	float flSpecMax;  /*!< ����ɲ��裬 ���ڲ�û���õ� */
	float flVoltValue; /*!< �������֮�󣬴�PIN�ŵĵ�ѹֵ�����flVoltValue����λ��mV*/
	bool bTest; /*!< true������		false�������� */
	int cam; /*! -1:Ĭ�� ������ģ����*/
	int port; /*! -1: Ĭ��  0��DPHY  1:CPHY  2:DVP 3:LVDS*/
	unsigned int reserve; /*! ����*/

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
	/*! PIN������, ���Ե���HisFX3GetOSPinNameList�鿴���е�PIN������
	\sa HisFX3GetOSPinNameList
	*/
	char strName[_HisFX3_OS_PinName_MaxByte];
	/*! ��shortIndex != 0ʱ�����Բ鿴strShortName�õ����PIN�Ŷ�·��PIN������
	\sa HisFX3GetOSPinNameList
	*/
	char strShortName[_HisFX3_OS_PinName_MaxByte];
	float flShortSpec; /*!< С��flShortSpec����Ϊ��·�� ��λ��mV */
	float flVoltValue; /*!< �������֮�󣬴�PIN�ŵĵ�ѹֵ�����flVoltValue����λ��mV*/
	unsigned int shortIndex; /*!< ucShortIndex != 0, �ͱ�ʾ��PIN���ж�·  */
	bool bTest; /*!< true������		false�������� */
	int cam; /*! -1:Ĭ�� ������ģ����(���|0x8000 Ϊ����ģʽ, ����Ϊ˫��ģʽ)*/
	int port; /*! -1: Ĭ��  0��DPHY  1:CPHY  2:DVP 3:LVDS*/
	unsigned int reserve; /*! ����*/

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
	/*! PIN������, ���Ե���HisFX3GetOSPinNameList�鿴���е�PIN������
	\sa HisFX3GetOSPinNameList
	*/
	char strName[_HisFX3_OS_PinName_MaxByte];
	/*! ��openIndex != 0ʱ�����Բ鿴strOpenName�õ����PIN�ſ�·��PIN������
	\sa _HisFX3OS_Positive_Item
	*/
	char strOpenName[_HisFX3_OS_PinName_MaxByte];
	float flOpenSpec; /*!> ����flOpenSpec����Ϊ��·�� ��λ��mV */
	float flVoltValue; /*!< �������֮�󣬴�PIN�ŵĵ�ѹֵ�����flVoltValue����λ��mV*/
	unsigned int openIndex; /*!< ucOpenIndex != 0, �ͱ�ʾ��PIN�ſ�·  */
	bool bTest; /*!< true������		false�������� */
	int cam; /*! -1:Ĭ�� ������ģ����*/
	int port; /*! -1: Ĭ��  0��DPHY  1:CPHY  2:DVP 3:LVDS*/
	unsigned int reserve; /*! ����*/

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
	/*! PIN��1 ����, ���Ե���HisFX3GetOSPinNameList�鿴���е�PIN������
	\sa HisFX3GetOSPinNameList
	*/
	char str1stName[_HisFX3_OS_PinName_MaxByte];
	/*! PIN��2 ����, ���Ե���HisFX3GetOSPinNameList�鿴���е�PIN������
	\sa HisFX3GetOSPinNameList
	*/
	char str2ndName[_HisFX3_OS_PinName_MaxByte];
	float flOhmValue; /*!< �������֮�󣬴�PIN�ŵ���ֵ�����flOhmValue����λ��ŷķ*/
	float flSpecMin; /*!< ����ɲ��裬 ���ڲ�û���õ� */
	float flSpecMax; /*!< ����ɲ��裬 ���ڲ�û���õ� */
	int cam; /*! -1:Ĭ�� ������ģ����*/
	int port; /*! -1: Ĭ��  0��DPHY  1:CPHY  2:DVP 3:LVDS*/
	unsigned int reserve; /*! ����*/

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
	/*! PIN��1 ����, ���Ե���HisFX3GetOSPinNameList�鿴���е�PIN������
	\sa HisFX3GetOSPinNameList
	*/
	char dutName[_HisFX3_OS_PinName_MaxByte];
	/*! PIN��2 ����, ���Ե���HisFX3GetOSPinNameList�鿴���е�PIN������
	\sa HisFX3GetOSPinNameList
	*/
	char gndName[_HisFX3_OS_PinName_MaxByte];

	float current; /*!< �������õ���ֵ����λ��uA*/
	int cam; /*! -1:Ĭ�� ������ģ����*/
	int port; /*! -1: Ĭ��  0��DPHY  1:CPHY  2:DVP 3:LVDS*/
	unsigned int reserve; /*! ����*/

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
	/*! �ӵ�����Դ��PIN������
	\sa HisFX3GetOSPinNameList
	*/
	char dutName[_HisFX3_OS_PinName_MaxByte];
	/*! �ӵ�GND��PIN������
	\sa HisFX3GetOSPinNameList
	*/
	char gndName[_HisFX3_OS_PinName_MaxByte];
	float voltLimit; /*!< ��ѹ����ֵ, ��λ:mV */
	float smoothLineVoltDiff; /*! ����ƽ��ѹ���� ��һ��ʱ���ڵĵ�ѹ��С�ڴ˹��ʱ�������˳��� ��λ:mV*/
	unsigned int upTime; /*! ����ʱ�����*/
	double pinVolt; /*! ���յ�ѹֵ*/
	int cam; /*! -1:Ĭ�� ������ģ����*/
	int port; /*! -1: Ĭ��  0��DPHY  1:CPHY  2:DVP 3:LVDS*/
	unsigned int reserve; /*! ����*/

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
	HisFX3Error_Construct			=	0x0100,	/*!< �๹��ʧ��*/
	HisFX3Error_CloseUSB3		=	0x0200,	/*!< �ر�usb3.0ʧ�� */
	HisFX3Error_Timeout				=	0x0300,	/*!< ������ʱ */
	HisFX3Error_Parameter			=	0x0400,	/*!< �������� */
	HisFX3Error_IsNotOpen			=	0x0500,	/*!< �豸��δ��*/
	HisFX3Error_IsNotPreview		=	0x0600,	/*!< ��δ��ͼ*/
	HisFX3Error_MallocBuffer		=	0x0700,	/*!< �����ڴ�ʧ�� */
	HisFX3Error_USBDataOut		=	0x0800,	/*!< �·�����ʧ�� */
	HisFX3Error_Hardware			=	0x0900,	/*!< ����Ӳ������ */
	HisFX3Error_Other					=	0x0A00,	/*!< ��������*/
	HisFX3Error_NotSuperSpeed	=	0x0B00,	/*!< ���ǳ���ģʽ*/
	HisFX3Error_CreateThread	=	0x0C00,		/*!< �����߳�ʧ�� */
	HisFX3Error_License				=	0x0D00,		/*!< license ���� */
	HisFX3Error_NoRespond		=	0x0E00,		/*!< IICû��Ӧ*/
	HisFX3Error_WirteIIC				=	0x0F00,	/*!< дIICʧ��*/
	HisFX3Error_Check				=	0x1000	,	/*!< У������� */
	HisFX3Error_AlgData				=	0x1100,				//�����㷨�����ݲ�����Ҫ��
	HisFX3Error_CreateEvent		=	0x1200,	/*!< �����¼�ʧ��*/
	HisFX3Error_MemNotEnough	=	0x1300,	/*!< �ڴ�ռ䲻����Ҫ��*/
	HisFX3Error_FuntionNotSupport	=	0x1400,	/*!< �˺�����֧��*/
	HisFX3Error_ShortTestAbort	=	0x1500,	/*!< OS��·�����쳣*/
	HisFX3Error_NegOpenTestAbort	=	0x1600,	/*!< OS��������쳣*/
	HisFX3Error_PosOpenTestAbort	=	0x1700, /*!< OS��������쳣*/
	HisFX3Error_ImgBufConvert			=	0x1800,	/*!< ͼ���ʽת������*/
	HisFX3Error_NoHardware				=	0x1900,	/*!< û��Ӳ��*/
	HisFX3Error_Connect					=	0x1A00,
	HisFX3Error_CameraON					=	0x1B00,
	HisFX3Error_GrabFrame					=	0x1C00,	/*!< ץ֡ʧ��*/
	HisFX3Error_OSAbort						=	0x1D00,	/*!< OS�����쳣*/
	HisFX3Error_VersionNotMatch		=	0x1E00,	/*!< �汾��ƥ��*/
	HisFX3Error_UpdateHW					=	0x1F00,	/*!< �����̼�ʧ��*/
	HisFX3Error_NoGrabber					=	0x2000,	/*!< û���ҵ���װ*/
	HisFX3Error_GrabberClosing			=	0x2100,  //grabber is closing
	HisFX3Error_StreamInReset			=	0x2200,  //stream in error, and reseting
	HisFX3Error_StreamExit				=	0x2300	,	//stream thread exit timeout
	HisFX3Error_AVDDVDiffBig			=	0x2400,	/*! AVDD���õĵ�ѹ�Ͳ����ĵ�ѹ���� */
	HisFX3Error_DVDDVDiffBig = 0x2401,	/*! DVDD���õĵ�ѹ�Ͳ����ĵ�ѹ���� */
	HisFX3Error_DOVDDVDiffBig = 0x2402,	/*! DOVDD���õĵ�ѹ�Ͳ����ĵ�ѹ���� */
	HisFX3Error_IODDVDiffBig = 0x2403,	/*! IODD���õĵ�ѹ�Ͳ����ĵ�ѹ���� */
	HisFX3Error_AFVDiffBig = 0x2404,	/*! AF���õĵ�ѹ�Ͳ����ĵ�ѹ���� */
	HisFX3Error_POWVDiffBig = 0x2405,	/*! POW���õĵ�ѹ�Ͳ����ĵ�ѹ���� */
	HisFX3Error_OTPVDiffBig = 0x2406,	/*! OTP���õĵ�ѹ�Ͳ����ĵ�ѹ���� */
	HisFX3Error_Preivewing					=	0x2500,		/*!< ��ͼ��*/
	HisFX3Error_OSNotCalibration							=	0x2600, /*!< OS��û��У׼*/
	HisFX3Error_VoltageNotCalibration					=	0x2700, /*!< ��ѹ��δУ׼*/
	HisFX3Error_CurrentNotCalibration			=	0x2800, /*!< ������δУ׼*/
	HisFX3Error_IsNotStart								 =	 0x2900,
	HisFX3Error_OSPinName = 0x2A00,
	HisFX3Error_CPUNotMeet	=	0x2A01,
	HisFX3Error_InvalidLineSize	=	0x2A2,
	HisFX3Error_InvalidImageSize	=	0x2A03,
	HisFX3Error_OutofMemrory	=	0x2A04,
	HisFX3Error_InvalidFormat	=	0x2A05,
	HisFX3Error_OpenDev = 0x2A06, /*!< �򿪹�װʧ��*/
	HisFX3Error_NoImageData = 0x2A07, /*!< û��ͼ������*/
	HisFX3Error_OpenFile = 0x2A08, /*!< ���ļ�ʧ��*/
	HisFX3Error_OSNotSupported = 0x2A09, /*!< OS���ܲ�֧��*/
	HisFX3Error_USBDataIn = 0x2A0A, 	/*!< �ϴ�����ʧ�� */
	HisFX3Error_LoadDLL = 0x2A0B, /*! ��̬����DLL�ļ�ʧ��*/
	HisFX3Error_LoadAPI = 0x2A0C, /*! ��̬����DLL �е�APIʧ��*/
	HisFX3Error_CRC = 0x2A0D,  /*! У�������*/
	HisFX3Error_AF = 0x2A0E, /*! �Խ�ʧ��*/
	HisFX3Error_FlashMemNotEnough	=	0x2A0F, /*! Flash�ռ䲻��*/
	HisFX3Error_PtIsNULL	=	0x2A10,  /*! ָ��ΪNULL*/
	HisFX3Error_WaitEventAbort	=	0x2A11,  /*! �ȴ��¼��쳣�˳�*/
	HisFX3Error_DecodeWidthHeight = 0x2A12,  /*! ͼ���߽��벻ƥ��*/
	HisFX3Error_UpFrame = 0x2A13, 	/*! �ϴ�����֡*/
	HisFX3Error_DecodeDataFormat = 0x2A14,  /*! �������ݸ�ʽ����ȷ*/
	HisFX3Error_DecodeLaneNum = 0x2A15, 	/*! ����LANE������ȷ*/
	HisFX3Error_MeasureCPHYRate = 0x2A16, /*! ���CPHY����ʧ��*/
	HisFX3Error_OperateRegister = 0x2A17, /*! ����ע���ʧ��*/
	HisFX3Error_AdapterCPUBand = 0x2A18, /*! ����CPU�󶨴���*/
	HisFX3Error_ProcessCPUBand = 0x2A19, /*! ���̰�CPUʧ��*/
	HisFX3Error_VoltNotOff = 0x2A1A,  /*! ��ѹδ�ر�*/
	HisFX3Error_ConnectSOC = 0x2A1B,  /*! ����SOCʧ��*/
	HisFX3Error_AE = 0x2A1C,  /*! �Զ��ع�ʧ��*/
	HisFX3Error_CreateFile = 0x2A1D,
	HisFX3Error_DriverVerTooLow = 0x2A1E,	/*! �汾����*/
	HisFX3Error_GrabberVerTooLow = 0x2A1F, /*! ͼ��װ�̼��汾����*/
	HisFX3Error_GrabberSerialNotMatch= 0x2A20, /*! ��װ���кŲ�ƥ��*/
	HisFX3Error_OSVerTooLow = 0x2A21, /*! OS�̼��汾����*/
	HisFX3Error_VoltCalibrationBeyondSepc = 0x2A22, /*! ��ԴУ׼�������*/
	HisFX3Error_BoxTypeNotMatch = 0x2A23, /*! ��װ�ͺŲ�ƥ��*/
	HisFX3Error_CommandCommunication = 0x2A24, /*! ����ͨѶʧ��*/
	HisFX3Error_CableConnection	 = 0x2A25, /*! ���ߴ���*/
	HisFX3Error_DeserializerTypeNotSet = 0x2A26,  /*! �⴮оƬ�ͺ�û������*/
	HisFX3Error_FunctionNotImplemented = 0x2A27, /*! ����û�ж�Ӧ��ʵ��*/
	HisFX3Error_PreviewStructVerNotMatch = 0x2A28, /*! _HisFX3_PreviewStruct �汾�Ų�ƥ��*/
	HisFX3Error_ImageInfoNotMatch = 0x2A29, /*! ͼ����Ϣ��ƥ��*/
	HisFX3Error_WorkRCalibrationBeyondSepc = 0x2A2A, /*! ����������ֵ�������*/
	HisFX3Error_CurrentCalibrationBeyondSepc = 0x2A2B, /*! ��������У׼�������*/
	HisFX3Error_VCMDriverTypeNotCorrect = 0x2A2C,		/*! AF ����ͺŲ���ȷ*/
	HisFX3Error_AESensorTypeNotCorrect = 0x2A2D,		/*! AE SENSOR�ͺŲ���ȷ*/
	HisFX3Error_I2CSlaveConflic = 0x2A2E,						/*! I2C�豸��ַ��ͻ*/
	HisFX3Error_DeserailizerBoardNotRight = 0x2A2F      /*! ����˽⴮��*/
}; 

enum _HisFX3_YUVCVTRGB_FLAG{
	_HisFX3_YUVCVTRGB_BT601				=	0x1,
	_HisFX3_YUVCVTRGB_BT709				=	0x2
};

struct _HisFX3_AF_Block
{
	int left; /*! ��λ������*/
	int top; /*! ��λ������*/
	int right; /*! ��λ������*/
	int bottom; /*! ��λ������*/
	int weight; /*! �Խ�����Ȩ��, 0~100*/

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
	char type[32]; /*! ����ͺ�, ����9714a,gt9762s,dw9814,vm149e,fp5510,sd12,9718s,ov5645,dw9763, 
				   dw9807,ad5823,bu64243,bu64297,bu64291,dw9767,dw9800,dw9810,fp5512,ak7375*/
	unsigned char slave; /*! �豸��ַ*/

	unsigned char iicCount; /*! IIC����*/
	unsigned char iicInterval; /*! IIC���ʱ��, ��λ��ms*/
	unsigned char regBytes; /*! �Ĵ���λ���ȣ���λ��Byte*/
	unsigned char dataBytes; /*! ����λ���ȣ� ��λ:Byte*/
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
	const unsigned int ver; /*! �ṹ��汾�ţ� �ڲ�ʹ�ã������޸�*/
	bool doCurveFit; /*! �Ƿ�Ҫ���������*/
	unsigned char afAlg; /*!�Խ��㷨*/
	unsigned char mtfAlg; /*! �������㷨��0��BAYER8���㣻1��Y8����*/
	unsigned char waitMotorStableMethod; /*! �ȴ�����ȶ�����ʱ������0:�ȴ��̶���֡��  1:�ȴ��̶���ʱ��*/
	unsigned char frames[2]; /*! �ȴ�����ȶ���֡��������0���󲽽���֡������1��:С������֡*/
	unsigned short waitms[2]; /*! �ȴ�����ȶ���ʱ�䣬 ��λ:ms������0���󲽽���ʱ������1��:С������ʱ*/
	unsigned int timeout; /*! �Խ�����timeoutʱ�䣬 ��λ:ms*/
	unsigned short steptimeout; /*! �����ȴ���ȷ֡��timeoutʱ�䣬��λ:ms*/
	unsigned char blockCount; /*! �������ROI��������Χ(1: 9)*/
	_HisFX3_AF_Block roi[9];
	_HisFX3_VCMDriver_Cfg motor;
	unsigned int bigStep; /*! ���Խ����Դ󲽲���*/
	unsigned int smallStep; /*! ���Խ�����С������*/
	double bsChangeMTF; /*! ����С�����л��Ľ�������ֵ*/
	int motorStart; /*! ���Խ��ķ�Χ��ʼλ��*/
	int motorEnd; /*! ���Խ��ķ�Χ����λ��*/
	double peakValidMTF; /*! PEAK�����СMTFֵ*/
	double curveDropMTF; /*! �ж������½���MTF���ֵ*/
	int luxDiffMin;	/*! ���Ȳ�ֵ��Χ��Сֵ*/
	int luxDiffMax;	/*! ���Ȳ�ֵ��Χ���ֵ*/
	double pixelNumsMin; /*! �����Ч���ر���*/

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
	int motorDec; /*! ���ֵ*/
	double mtf; /*! MTF Ȩ��ֵ*/
	double roiMTF[9]; /*! ֧��9��ROIȫ�������ϴ��İ汾��ʵ�ʵĶԽ��������ֻ�ܵ�180���� ��������ò���ʱ��Ҫ����*/

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
	int peakMotor[10]; /*! PEAK������ֵ, ����0��Ȩ�����ߵ����ֵ������1~9������ROI�����ֵ*/
	double peakMTF[10]; /*! PEAK���MTFֵ������0��Ȩ�����ߵ�MTFֵ������1~9������ROI��MTFֵ*/
	_HisFX3_AF_Curve curve[4096];
	unsigned int curvePtCount; /*! ���ߵĵ���*/
};

struct _HisFX3_Exposure_Cfg
{
	char type[32]; /*! SENSOR�ͺ�, ����ov1,ov2,sony,hynix,samsung,galaxycore,superpix,ov2775, ov2718,aptina,hi1336,hi545*/
	unsigned char slave; /*! �豸��ַ*/

	unsigned char iicCount; /*! IIC����*/
	unsigned char iicInterval; /*! IIC���ʱ��, ��λ��ms*/
	unsigned char regBytes; /*! �Ĵ���λ���ȣ���λ��Byte*/
	unsigned char dataBytes; /*! ����λ���ȣ� ��λ:Byte*/
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
	const unsigned int ver; /*! �ṹ��汾�ţ� �ڲ�ʹ�ã������޸�*/
	unsigned char aeChannel; /*! ѡ��������ȵ�ͨ����0��BAYER8���㣻1��Y8����*/
	unsigned char waitMotorStableMethod; /*! �ȴ��ع��ȶ�����ʱ������0:�ȴ��̶���֡��  1:�ȴ��̶���ʱ��*/
	unsigned char frames; /*! �ȴ��ع��ȶ���֡����*/
	unsigned short waitms; /*! �ȴ��ع��ȶ���ʱ�䣬 ��λ:ms��*/
	unsigned int timeout; /*! �ع����timeoutʱ�䣬 ��λ:ms*/
	unsigned short steptimeout; /*! �����ȴ���ȷ֡��timeoutʱ�䣬��λ:ms*/
	unsigned char maxSteps; /*! AE������ಽ��*/
	unsigned char luxMin; /*! AEĿ�꣺luxMin <= ae <= luxMax */
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
	unsigned int expValue; /*! �ع�ʱ��*/
	unsigned char luxValue; /*! ����ֵ*/

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
	unsigned int expValue; /*! ��ǰ�ع�ʱ��*/
	unsigned char luxValue; /*! ��ǰ����ֵ*/
	_HisFX3_AE_Curve curve[255];
	unsigned int curvePtCount; /*! ���ߵĵ���*/
};

#endif
