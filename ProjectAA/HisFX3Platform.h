//

#ifndef HISFX3PLATFORM_H
#define HISFX3PLATFORM_H

#ifdef HISFX3PLATFORM_EXPORTS
#define HISFX3PLATFORM_API __declspec(dllexport)
#else
#define HISFX3PLATFORM_API __declspec(dllimport)
#endif

#include "HisGlobalDefine.h"

#ifdef __cplusplus
extern "C"
{
#endif

namespace RBOXAPI
{
	//! 设置工装型号
	/*!
	\param[in] boxType 
	\param[in] camCount 模组数量
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3SetCurrentPlatformType(_HisFX3_Platform_Type boxType);

	HISFX3PLATFORM_API _HisFX3_Platform_Type HisFX3GetCurrentPlatformType();

	//! 设置实际用的光纤线数目
	/*! R8有效
	\param[in] num 实际用的光纤线数目
	\sa
	*/
	HISFX3PLATFORM_API void HisFX3SetFiberNum(int num);

	//! 设置是否要做CPU进程仿射
	/*! 此设置针对光纤工装+WIN10系统有效 
	\param[in] on
	\sa
	*/
	HISFX3PLATFORM_API void HisFX3CPUAffinity(bool on);

	//! 设置万兆网卡类型
	/*! 
	\param[in] type  0：标准万兆网卡；1：Rolongo自制PCIe加速卡 X1；
	\sa
	*/
	HISFX3PLATFORM_API void HisFX3SetGbEType(int type);

	//! 获取工装数量
	/*! 
	\return 工装个数
	\sa HisFX3EnumDev
	*/
	HISFX3PLATFORM_API int HisFX3GetDevCount();

	//! 枚举在线的工装设备
	/*! 之后必须调用HisFX3EnumFree释放资源，否则会造成内存泄漏
	\param[out] dev 工装唯一序列号列表
	\param[out] devCount 在线的工装数量
	\return 0:成功  非0:失败
	\sa HisFX3EnumFree
	*/
	HISFX3PLATFORM_API int HisFX3EnumDev(char*** dev, int* devCount);

	//! 释放HisFX3EnumDev中开辟的内存
	/*!
	\param[in] dev 工装唯一序列号列表
	\param[in] devCount 工装数量
	\sa HisFX3EnumDev
	*/
	HISFX3PLATFORM_API void HisFX3EnumFree(char** dev, int devCount);

	//! 枚举在线的工装设备，作用和HisFX3EnumDev一样，只是返回的格式不同
	/*! 
	\param[out] dev 工装唯一序列号列表，多个序列号之间用";"隔开；内存需要用户自己申请，建议不少于256Bytes;
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3EnumDevStr(char* dev);

	//! 打开工装dev, 编号为boxIndex, 编号不能超过_RMAX_BOXS-1
	/*!
	\param[in] boxIndex 工装编号
	\param[in] dev 工装唯一序列号, 如果为NULL，则不比对序列号，随机打开一个工装
	\return 0:成功  非0:失败
	\sa HisFX3CloseDevice
	*/
	HISFX3PLATFORM_API int HisFX3OpenDevice(int boxIndex = 0, char* dev = 0);

	//! 关闭工装
	/*!
	\param[in] boxIndex 工装编号, 如何为-1则关闭所有工装
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3CloseDevice(int boxIndex = 0);

	//! 获取HisFX3OpenDevice打开的工装的序列号
	/*!
	\param[out] dev 如果函数成功，返回当前的工装序列号；至少需要申请64Byte内存大小；
	\param[in] boxIndex 工装编号
	\return 0:成功  非0:失败
	\sa HisFX3EnumDev, HisFX3EnumFree
	*/
	HISFX3PLATFORM_API int HisFX3GetCurrentBoxSerial(char* dev, int boxIndex = 0);

	//! 在线升级FPGA固件
	/*!
	\param[in] binPath 升级文档路径
	\param[in] boxIndex 工装编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3UpdateFPGA(char* binPath, int boxIndex = 0);

	//! 在线升级PCIe光纤加速卡固件
	/*!
	\param[in] binPath 升级文档路径
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3UpdatePCIeFiber(char* binPath);

	//! 调节工装上传速率，对R10S, USB3.0工装有效(必须在OpenDevice成功之后调用)
	/*!
	\param[in] speed 0~10000, 0表示最小速率， 10000表示最大速率
	\param[in] boxIndex 工装编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3SetUSBSpeed(unsigned int speed, int boxIndex = 0);

	//! 设置USB收发包的大小(R5, S5)
	/*!
	\param[in] size 单位：16KB
	\param[in] boxIndex 工装编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3SetUSBPktSize(unsigned int size, int boxIndex = 0);

	//! 获取工装FPGA版本号
	/*!
	\param[in] boxIndex 工装编号
	\return 版本号
	\sa
	*/
	HISFX3PLATFORM_API unsigned int HisFX3GetFPGAVer(int boxIndex = 0);

	//! 获取工装开短路固件版本号
	/*!
	\param[in] boxIndex 工装编号
	\return 版本号
	\sa
	*/
	HISFX3PLATFORM_API unsigned int HisFX3GetOSVer(int boxIndex = 0);

	//! 获取工装FX3固件版本号
	/*!
	\param[in] boxIndex 工装编号
	\return 版本号
	\sa
	*/
	HISFX3PLATFORM_API unsigned int HisFX3GetFX3Ver(int boxIndex = 0);

	//! 获取PCIe加速卡固件版本号
	/*!
	\return 版本号
	\sa
	*/
	HISFX3PLATFORM_API unsigned int HisFX3GetPCIeFiberCardVer();

	//! 获取PCIe加速卡驱动版本号
	/*!
	\return 版本号
	\sa
	*/
	HISFX3PLATFORM_API unsigned int HisFX3GetPCIeCardDriverVer();

	//! 工装是否已经打开
	/*!
	\param[in] boxIndex 工装编号
	\return true: 已打开   false:还未打开
	\sa
	*/
	HISFX3PLATFORM_API bool HisFX3IsOpen(int boxIndex = 0);

	//! 测试通信链接是否正常
	/*! 一般情况用HisFX3IsOpen
	\param[in] boxIndex 工装编号
	\return true: 已打开   false:还未打开
	\sa
	*/
	HISFX3PLATFORM_API bool HisFX3IsConnected(int boxIndex = 0);


	//! 控制工装上LED的状态
	/*!
	\param[in] on true: 闪烁  false:灭
	\param[in] boxIndex 工装编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int  HisFX3LedControl(bool on, int boxIndex = 0);

	//! 控制工装上蜂鸣器的状态
	/*!
	\param[in] on true: 开  false:关
	\param[in] boxIndex 工装编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3BuzzerControl(bool on, int boxIndex = 0);

	//! 控制工装上风扇的运行模式
	/*!
	\param[in] mode 0：自动  1：开  2：关
	\param[in] boxIndex 工装编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3SetFanMode(unsigned int mode, int boxIndex = 0);

	//! 设置风扇自动模式的高/低温度
	/*! 
	\param[in] low 温度< low时关闭
	\param[in] high 温度> high时打开
	\param[in] boxIndex 工装编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3SetFanAutoRange(double low, double high, int boxIndex = 0);

	//! 设置风扇电压
	/*!
	\param[in] v 电压，单位：V
	\param[in] boxIndex 工装编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3SetFanVolt(double v, int boxIndex = 0);

	//! 测试当前工装总电流
	/*!
	\param[out] current 返回测试到的当前电流值，单位:mA
	\param[in] boxIndex 工装编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3MeasureBoxTotalCurrent(double* current, int boxIndex = 0);
	
	//! 获取工装内FPGA当前温度
	/*!
	\param[in] boxIndex 工装编号
	\return 温度， 单位：摄氏度
	\sa
	*/
	HISFX3PLATFORM_API double HisFX3GetFPGATemperature(int boxIndex = 0);

	//! 获取PCIe加速卡内FPGA当前温度
	/*!
	\return 温度， 单位：摄氏度
	\sa
	*/
	HISFX3PLATFORM_API double HisFX3GetPCIeFirberCardTemperature();

	//! 烧写用户自定义数据到工装Flash
	/*! 空间大小：8KB; 
	\param[in] reg 寄存器地址，从0x0开始
	\param[in] data 要烧写的数据Buffer
	\param[in] dataSize 数据长度
	\param[in] boxIndex 工装编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3BurnUserData(unsigned int reg, unsigned char* data, unsigned int dataSize, int boxIndex = 0);

	//! 从工装Flash读取用户数据
	/*! 空间大小：8KB;
	\param[in] reg 寄存器地址，从0x0开始
	\param[in] data 要烧写的数据Buffer
	\param[in] dataSize 数据长度
	\param[in] boxIndex 工装编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3ReadUserData(unsigned int reg, unsigned char* data, unsigned int dataSize, int boxIndex = 0);

	//! FPGA是否开启DDR缓存功能
	/*!
	\param[in] on true : 开启； false:关闭；
	\param[in] cam 模组编号
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3SetDDR(bool on, int cam = 0);

	//! 是否只输出正确帧
	/*!
	\param[in] onlyRightFrame b0: 设置FPGA;  b1: 设置上位机;
	\param[in] cam 模组编号
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3OnlyRightFrame(unsigned char onlyRightFrame, int cam = 0);

	//! 开始出图
	/*!
	\param[in] p 点亮相关参数
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa RBOX_PREVIEW_PARA
	*/
	HISFX3PLATFORM_API int HisFX3StartPreview(_HisFX3_PreviewStruct* p, int cam = 0);

	//! 停止出图
	/*!
	\param[in] sequence 下电时序，设置为NULL时，则采用默认下电时序
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3StopPreview(char *sequence, int cam);

	//! 不下电，切换图像尺寸
	/*!
	\param[in] p 必要的参数，按需配置, 一般需要配RESET,MCLK,port,iic,dataFormat,width,height,cphyRate
	\param[in] sequence 配置时序，如果设为NULL，则启用默认时序
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3SwitchImageSize(_HisFX3_PreviewStruct* p, char* sequence, int cam);


	//! 设置图像接口信息
	/*!
	\param[in] port 图像数据接口类型
	\param[in] lanes 图像数据通道数量
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa _HisFX3_MIPILane_Stream
	*/
	HISFX3PLATFORM_API int HisFX3SetPortCfg(_HisFX3_MIPILane_Stream port, unsigned char lanes, int cam = 0);

	//! 重置图像接口解码模块
	/*!
	\param[in] port 图像数据接口类型
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa _HisFX3_MIPILane_Stream
	*/
	HISFX3PLATFORM_API int HisFX3ResetPortDecoder(_HisFX3_MIPILane_Stream port, int cam = 0);

	//! 启动/停止图像接口解码模块, 通常建议使用HisFX3ResetPortDecoder
	/*!
	\param[in] port 图像数据接口类型
	\param[in] on 是否启动
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa _HisFX3_MIPILane_Stream
	*/
	HISFX3PLATFORM_API int HisFX3PortDecoderOnOff(_HisFX3_MIPILane_Stream port, bool on, int cam = 0);

	//! 获取图像接口解码解码信息
	/*!
	\param[in] port 图像数据接口类型
	\param[in][out] info 解码信息的字符串表示， 内存大小 >= 512Byte
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa _HisFX3_MIPILane_Stream
	*/
	HISFX3PLATFORM_API int HisFX3GetDecoderInfo(_HisFX3_MIPILane_Stream port, char* info, int cam = 0);

	//! 设置一帧的图像数据，若为0, 则SDK根据设置的图像宽高自动计算；若为非0，则以此作为判断条件
	/*!
	\param[in] frameBytes 一帧的图像数据大小，单位：Bytes
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa _HisFX3_BaylorMode
	*/
	HISFX3PLATFORM_API int HisFX3SetCustomFrameBytes(unsigned int frameBytes, int cam);

	//! 设置FPGA上传的数据类型，在开启虚拟通道上传时有效
	/*!
	\param[in] mode 上传模式，0：全部类型上传；1：只上传指定的数据类型
	\param[in] uploadType 指定上传的数据类型
	\param[in] typeCount 指定上传数据类型的数量
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3SetUploadPktType(unsigned char mode, unsigned char* uploadType, unsigned int typeCount, int cam);

	//! 设置上传图像数据的帧信息
	/*!
	\param[in] dataFormat 图像数据格式
	\param[in] width 图像宽， 不包含dummyLeft, dummyRight	
	\param[in] height 图像宽， 不包含dummyTop, dummyBottom
	\param[in] dummyLeft 图像左边需要裁掉的列数
	\param[in] dummyRight 图像右边需要裁掉的列数
	\param[in] dummyTop 图像上边需要裁掉的行数
	\param[in] dummyBottom 图像下边需要裁掉的行数
	\param[in] addInfoBytes; 保留，固定设为0
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa _HisFX3_BaylorMode
	*/
	HISFX3PLATFORM_API int HisFX3SetFrameCfg(_HisFX3_BaylorMode dataFormat, int width, int height,  \
		int dummyLeft=0, int dummyRight=0, int dummyTop=0, int dummyBottom=0, int addInfoBytes = 0, int cam = 0);
	
	//! 设置分区块上传的ROI，调此函数之前需调用HisFX3SetFrameCfg
	/*! 
	\param[in] streamROI ROI坐标，单位：像素；坐标必须为偶数；如果是HisFX3GrabFrame取Compact格式, 则必须满足Compact的格式需求
	\param[in] nums ROI数量，范围[0, _RMAX_STREAM_ROI_NUMS]
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa HisFX3SetFrameCfg
	*/
	HISFX3PLATFORM_API int HisFX3SetUpStreamROI(RRect* streamROI, int nums, int cam = 0);

	//! 开启图像数据抓取线程
	/*!
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3StartCapture(int cam = 0);

	//! 忽略frames帧之后开启图像数据抓取线程
	/*!
	\param[in] frames 忽略的帧数
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3StartCaptureWithSkip(unsigned int frames, int cam = 0);

	//! 停止图像数据抓取线程
	/*!
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3StopCapture(int cam = 0);

	//! 模组是否已开始出图
	/*!
	\param[in] cam 模组编号
	\return true: 正在出图 false: 没有出图
	\sa
	*/
	HISFX3PLATFORM_API bool HisFX3IsStart(int cam = 0);

	//! 图像数据是否正在上传
	/*!
	\param[in] waitTime 等待时间，单位:ms
	\param[in] cam 模组编号
	\return true: 正在上传 false: 没有正在上传
	\sa
	*/
	HISFX3PLATFORM_API bool HisFX3IsDataUploading(unsigned int waitTime, int cam = 0);

	//! 抓取一帧图像
	/*!
	\param[in] imageBuf 存取图像数据的内存指针
	\param[in] bufSize imageBuf大小， 单位：Byte
	\param[out] frameIndex 帧索引
	\param[out] errorFrame 是否为错误帧
	\param[out] recSize 收到的数据大小，单位：Byte
	\param[in] imageFormat 图像数据格式，如果和SENSOR格式不一致，会自动转化为imageFormat格式; 0表示和输入保持一致
	\param[in] timeout 等待时间
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3GrabFrame(unsigned char* imageBuf, int bufSize, unsigned int* frameIndex, bool* errorFrame, unsigned int* recSize, unsigned int imageFormat=0, unsigned int timeout = 2000, int cam = 0);

	//! 获取当前帧索引
	/*!
	\param[out] rightFrame 总的正确帧数
	\param[out] errFrame 总的错误帧数
	\param[in] flag 0: FPGA接收到的总帧数， 1：PC收到的总帧数
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3GetTotalFrame(unsigned int* rightFrame, unsigned int* errFrame, unsigned int flag, int cam = 0);

	//! 清除统计信息
	/*!
	\param[out] type 需要清除统计的信息类型，支持 | 操作; 支持变量请查看_HisFX3_Statistics_Type
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa _HisFX3_Statistics_Type
	*/
	HISFX3PLATFORM_API int HisFX3ClearStastisticInfomation(unsigned int type, int cam = 0);

	//! 获取连续帧， 注意：先要关闭DDR的功能，才能保证连续；
	/*!
	\param[in] imageBuf 一个指针数组的指针
	\param[in] frames 连续帧帧数
	\param[in] imageFormat 图像数据格式，如果和SENSOR格式不一致，会自动转化为imageFormat格式; 0表示和输入保持一致
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	sample code:
	unsigned char** buf = NULL;
	HisFX3GrabConsecutiveFrames(&buf, 5, 0, 0);
	*/
	HISFX3PLATFORM_API int HisFX3GrabConsecutiveFrames(unsigned char*** imageBuf, unsigned int frames, unsigned int imageFormat, int cam);

	//! 释放HisFX3GrabConsecutiveFrames中开启的连续帧内存
	/*!
	\param[in] imageBuf 一个指针数组的指针
	\param[in] frames 连续帧帧数
	\sa
	*/
	HISFX3PLATFORM_API void HisFX3ConsecutiveFramesFree(unsigned char*** imageBuf, unsigned int frames);

	//! 抓取同步帧
	/*!
	\param[in] imageBuf 一个指针数组, 用户需要自己开辟内存
	\param[in] imageFormat 图像数据格式，如果和SENSOR格式不一致，会自动转化为imageFormat格式; 0表示和输入保持一致
	\param[in] cams 需要抓取的模组通道，bit0表示cam 0，以此类推
	\param[in] boxIndex 工装编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3GrabSyncFrames(unsigned char* imageBuf[], unsigned int imageFormat, unsigned int cams, int boxIndex = 0);

	//! 开启IIC SCL低电平最大持续时间
	/*!
	\param[in] ms 单位：ms
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int SetSCLLowMaxTime(unsigned int ms, int cam);

	//! 开启IIC 自动ACK模式
	/*! 开启之后，当ACK没有响应时，会循环侦测一段时间，直到ACK有响应或者timeout
	\param[in] enable 开启/关闭 IIC自动ACK模式
	\param[in] timeout 单位：ms
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3EnableIICAutoAck(bool enable, unsigned int timeout, int cam = 0);

	//! 检测自动ACK模式是否已经开启
	/*! 
	\param[in] cam 模组编号
	\return 非0：开启，返回等待时间；0：未开启
	\sa
	*/
	HISFX3PLATFORM_API unsigned int HisFX3IsIICAutoAckEnabled(int cam = 0);

	//! 设置控制通道通信协议
	/*!
	\param[in] protocal 详见_HisFX3_CommunicationProtocal
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa _HisFX3_CommunicationProtocal
	*/
	HISFX3PLATFORM_API int HisFX3SetControlCommunicationProtocal(_HisFX3_CommunicationProtocal protocal, int cam = 0);

	//! 设置IIC速率
	/*!
	\param[in] speed IIC速率， 单位：KHz
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3SetIICSpeed(unsigned int speed, int cam = 0);

	//! 获取当前IIC速率
	/*!
	\param[in] cam 模组编号
	\return 当前IIC速率， 单位：KHz
	\sa
	*/
	HISFX3PLATFORM_API unsigned int HisFX3GetIICSpeed(int cam = 0);

	//! 测试IIC ACK是否有响应
	/*!
	\param[in] slave 设备地址
	\param[in] cam 模组编号
	\return true: 有响应， false: 没有响应
	\sa
	*/
	HISFX3PLATFORM_API bool HisFX3IICResponds(unsigned char slave, int cam = 0);

	//! 等待IIC响应， 直至timeout或者IIC有响应
	/*!
	\param[in] slave 设备地址
	\param[in] timeout 单位:ms
	\param[in] cam 模组编号
	\return true: 有响应， false: 没有响应
	\sa
	*/
	HISFX3PLATFORM_API bool HisFX3WaitIICResponds(unsigned char slave, unsigned int timeout, int cam = 0);

	//! 单条IIC写入
	/*!
	\param[in] slave 设备地址
	\param[in] reg 寄存器地址
	\param[in] data 数据
	\param[in] type 类型: 0x0808, 0x1608, 0x1632...
	\param[in] ack 是否判定ACK响应
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3WriteIIC(unsigned char slave, unsigned int reg, unsigned __int64 data, unsigned short type, bool ack = true, int cam = 0);

	//! 单条IIC读取
	/*!
	\param[in] slave 设备地址
	\param[in] reg 寄存器地址
	\param[out] data 数据
	\param[in] ack 是否判定ACK响应
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3ReadIIC(unsigned char slave, unsigned int reg, unsigned __int64* data, unsigned short type, int cam = 0);

	//! 批量IIC写入
	/*!
	\param[in] count IIC条数
	\param[in] slave 设备地址
	\param[in] reg 寄存器地址
	\param[in] data 数据
	\param[in] type 类型: 0x0808, 0x1608, 0x1632...
	\param[in] delay 每条IIC写入之间的间隔时间， 单位:us
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3BatchWriteIICNoLimit(unsigned int count, unsigned char* slave, unsigned int* reg, unsigned int* data, unsigned short* type, unsigned short delay = 10, int cam = 0);

	//! 批量IIC读取
	/*!
	\param[in] count IIC条数
	\param[in] slave 设备地址
	\param[in] reg 寄存器地址
	\param[out] data 数据
	\param[in] type 类型: 0x0808, 0x1608, 0x1632...
	\param[in] delay 每条IIC读取之间的间隔时间， 单位:us
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3BatchReadIICNoLimit(unsigned int count, unsigned char* slave, unsigned int* reg, unsigned int* data, unsigned short* type, unsigned short delay = 10, int cam = 0);

	//! 单条触发模组IIC写入
	/*!
	\param[in] slave 设备地址
	\param[in] reg 寄存器地址
	\param[in] regSize 寄存器地址大小， 单位： Byte
	\param[in] data 数据
	\param[in] dataSize 数据大小， 单位： Byte (R5X,R6:最大512)
	\param[in] delay 每个Byte之间的间隔延时， 单位：半个SCL时钟周期
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3PageWriteIIC(unsigned int slave, unsigned int reg, unsigned int regSize, unsigned char* data, unsigned int dataSize, unsigned short delay = 4, int cam = 0);

	//! 单条触发模组IIC读取
	/*!
	\param[in] slave 设备地址
	\param[in] reg 寄存器地址
	\param[in] regSize 寄存器地址大小， 单位： Byte
	\param[out] data 数据
	\param[in] dataSize 数据大小， 单位： Byte (R5X,R6:最大512)
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3PageReadIIC(unsigned int slave, unsigned int reg, unsigned int regSize, unsigned char* data, unsigned int dataSize, int cam = 0);

	//! 批量触发模组IIC写入
	/*!
	\param[in] slave 设备地址
	\param[in] reg 寄存器地址
	\param[in] regSize 寄存器地址大小， 单位： Byte
	\param[in] data 数据
	\param[in] dataSize 数据大小， 单位： Byte
	\param[in] pageSize 单次触发写入的数据大小， 单位： Byte (R5X,R6:最大512)
	\param[in] byteDelay 每个Byte之间的间隔延时， 单位：半个SCL时钟周期
	\param[in] pageDelay 每次触发写入之间的间隔时间，单位:ms
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3PageWriteIICNoLimit(unsigned int slave, unsigned int reg, unsigned int regSize, unsigned char* data, unsigned int dataSize, unsigned int pageSize, unsigned short byteDelay = 4, unsigned int pageDelay = 100, int cam = 0);

	//! 批量触发模组IIC读取
	/*!
	\param[in] slave 设备地址
	\param[in] reg 寄存器地址
	\param[in] regSize 寄存器地址大小， 单位： Byte
	\param[out] data 数据
	\param[in] dataSize 数据大小， 单位： Byte
	\param[in] pageSize 单次触发写入的数据大小， 单位： Byte (R5X,R6:最大512)
	\param[in] pageDelay 每次触发写入之间的间隔时间，单位:ms
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3PageReadIICNoLimit(unsigned int slave, unsigned int reg, unsigned int regSize, unsigned char* data, unsigned int dataSize, unsigned int pageSize, unsigned int pageDelay = 0, int cam = 0);

	//! SONY车载芯片Command IIC读写
	/*!
	\param[in] slave 设备地址
	\param[in] code 命令代码(Command Code)
	\param[in] writeBuf 需要写入的数据
	\param[in] writeSize 需要写入的数据大小， 单位: Byte
	\param[in] delay 写入和回读之间的延时等待时间， 单位:us
	\param[out] readBuf 如果是读操作，会把读取到的数据存到此buffer
	\param[in] readSize 如果是读操作，填读取的大小，否则填0； 单位: Byte
	\param[out] status 命令执行结果状态代码
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3SONYCommandIIC(unsigned int slave, unsigned char code, unsigned char* writeBuf, unsigned int writeSize, unsigned int delay, unsigned char* readBuf, unsigned int readSize, unsigned char* status, int cam = 0);
	
	//! 设置SPI的速率
	/*!
	\param[in] speed SPI速率，单位：KHz
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3SetSPISpeed(unsigned int speed, int cam = 0);

	//! 获取当前SPI的速率
	/*!
	\param[in] cam 模组编号
	\return 当前SPI速率，单位:KHz
	\sa
	*/
	HISFX3PLATFORM_API unsigned int HisFX3GetSPISpeed(int cam = 0);

	//! 单条SPI写入
	/*!
	\param[in] slave 设备地址，当设0xFF时， 不操作设备地址
	\param[in] reg 寄存器地址
	\param[in] data 数据
	\param[in] type 类型: 0x0808, 0x1608, 0x1632...
	\param[in] csLow CS信号是否拉低
	\param[in] littleEndian 1个BYTE内的BIT排序是否地位在前
	\param[in] clkHigh true: CLK默认是在高电平；false: CLK默认是在低电平；需要R2C >= 3506
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3WriteSPI(unsigned char slave, unsigned int reg, unsigned __int64 data, \
		unsigned short type, bool csLow = true, bool littleEndian = true, bool clkHigh = true, int cam = 0);

	//! 单条SPI读取
	/*!
	\param[in] slave 设备地址，当设0xFF时， 不操作设备地址
	\param[in] reg 寄存器地址
	\param[out] data 数据
	\param[in] type 类型: 0x0808, 0x1608, 0x1632...
	\param[in] csLow CS信号是否拉低
	\param[in] littleEndian 1个BYTE内的BIT排序是否地位在前
	\param[in] clkHigh true: CLK默认是在高电平；false: CLK默认是在低电平；需要R2C >= 3506
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3ReadSPI(unsigned char slave, unsigned int reg, unsigned __int64* data, \
		unsigned short type, bool csLow = true, bool littleEndian = true, bool clkHigh = true, int cam = 0);

	//! 单条触发SPI写入
	/*!
	\param[in] slave 设备地址，当设0xFF时， 不操作设备地址
	\param[in] reg 寄存器地址
	\param[in] regSize 寄存器地址大小， 单位： Byte
	\param[in] data 数据
	\param[in] dataSize 数据大小， 单位： Byte (R5X,R6:最大512)
	\param[in] csLow CS信号是否拉低
	\param[in] littleEndian 1个BYTE内的BIT排序是否地位在前
	\param[in] clkHigh true: CLK默认是在高电平；false: CLK默认是在低电平；需要R2C >= 3506
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3PageWriteSPI(unsigned char slave, unsigned int reg, unsigned int regSize, \
		unsigned char* data, unsigned int dataSize, bool csLow = true, bool littleEndian = true, bool clkHigh = true, int cam = 0);

	//! 单条触发SPI读取
	/*!
	\param[in] slave 设备地址，当设0xFF时， 不操作设备地址
	\param[in] reg 寄存器地址
	\param[in] regSize 寄存器地址大小， 单位： Byte
	\param[out] data 数据
	\param[in] dataSize 数据大小， 单位： Byte (R5X,R6:最大512)
	\param[in] csLow CS信号是否拉低
	\param[in] littleEndian 1个BYTE内的BIT排序是否地位在前
	\param[in] clkHigh true: CLK默认是在高电平；false: CLK默认是在低电平；需要R2C >= 3506
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int  HisFX3PageReadSPI(unsigned char slave, unsigned int reg, unsigned int regSize, \
		unsigned char* data, unsigned int dataSize, bool csLow = true, bool littleEndian = true, bool clkHigh = true, int cam = 0);

	//! 设置每路电压的连接模式
	/*!
	\param[in] standby BIT位 1: 是静态模式，连接电阻为100欧  0: 是工作模式，连接电阻为0.1欧
	\param[in] flag 通道选择,支持位|操作， _HisFX3_Platform_VoltFlag
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa _HisFX3_Platform_VoltFlag
	*/
	HISFX3PLATFORM_API int HisFX3SetVoltLinkMode(unsigned int standby, unsigned int flag, int cam = 0);

	//! 设置电压
	/*!
	\param[in] volt 电压, 单位：V。Ps. 5V,12V通道设置的方式： -1.0(不设置), 0.0(关闭), 1.0(打开)
	\param[in] flag 通道选择， _HisFX3_Platform_VoltFlag
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa _HisFX3_Platform_VoltFlag
	*/
	HISFX3PLATFORM_API int HisFX3SetVolt(float volt, unsigned int flag, int cam = 0);

	//! 获取当前设置的电压
	/*!
	\param[in] flag 通道选择， _HisFX3_Platform_VoltFlag
	\param[in] cam 模组编号
	\return 当前设置的电压, 单位：V
	\sa _HisFX3_Platform_VoltFlag
	*/
	HISFX3PLATFORM_API float HisFX3GetVoltSetted(_HisFX3_Platform_VoltFlag flag, int cam = 0);

	//! 测量当前的输出电压值
	/*!
	\param[in] flag 通道选择， _HisFX3_Platform_VoltFlag
	\param[in] cam 模组编号
	\return 当前设置的电压, 单位：V
	\sa _HisFX3_Platform_VoltFlag
	*/
	HISFX3PLATFORM_API float HisFX3ReadVolt(_HisFX3_Platform_VoltFlag flag, int cam = 0);

	//! 电源接地放电
	/*!
	\param[in] channel 保留
	\param[in] ms 放电时间，单位:ms
	\param[in] cam 模组编号
	\return 当前设置的电压, 单位：V
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3VoltDischarge(unsigned int channel, unsigned int ms, int cam = 0);

	//! 设置MCLK
	/*!
	\param[in] mclk频率， 单位:MHz
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3SetMCLK(double mclk, int cam = 0);

	//! 获取当前设置的MCLK
	/*!
	\param[in] cam 模组编号
	\return 当前设置的MCLK， 单位:MHz
	\sa
	*/
	HISFX3PLATFORM_API double HisFX3GetMCLK(int cam = 0);

	//! 设置RESET信号电平
	/*!
	\param[in] high 是否拉高
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3PullReset(bool high, int cam = 0);

	//! 设置PWDN信号电平
	/*!
	\param[in] high 是否拉高
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3PullPWDN(bool high, int cam = 0);

	//! 设置并口采集同步信号相移
	/*!
	\param[in] ps  0:不相移;  1: 90度;  2: 180度;  3: 270度;
	\param[in] cam 模组编号
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa _HisFX3Platform_ErrorCode
	*/
	HISFX3PLATFORM_API int HisFX3SetPhaseShift_DVP(int ps, int cam = 0);

	//! 设置并口参数
	/*!
	\param[in] dvpLineFormat   0：采9:2   1: 采7:0   2：采15:0   3：采9:0  4：采11:0   5：采13:0
	\param[in] vsHigh  VS 同步信号设置。   true: 高电平有效；   false: 低电平有效---[注1：VC8D无效]
	\param[in] ps  采集同步信号相移  0:不相移;  1: 90度;  2: 180度;  3: 270度;---[注1：VC8D无效]
	\param[in] cam 模组编号
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa _HisFX3Platform_ErrorCode
	*/
	HISFX3PLATFORM_API int HisFX3SetDVP(unsigned int dvpLineFormat, bool vsHigh, int ps, int cam = 0);

	//! 设置LVDS需要做数据对齐的通道
	/*!
	\param[in] pixAlign  b0:1表示通道1需要对齐， 以此类推...
	\param[in] cam 模组编号
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa _HisFX3Platform_ErrorCode
	*/
	HISFX3PLATFORM_API int HisFX3SetPixelAlign_LVDS(unsigned int pixAlign, int cam = 0);

	//! 设置LVDS XVS,XVS信号
	/*!
	\param[in] on  true:需要输出XHS, XVS;		false:不需要输出XHS, XVS;
	\param[in] xhs
	\param[in] xvs
	\param[in] cam 模组编号
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa _HisFX3Platform_ErrorCode
	*/
	HISFX3PLATFORM_API int HisFX3SetXVSXHS_LVDS(bool on, unsigned int xhs, unsigned int xvs, int cam = 0);

	//! 设置DPHY XVS,XVS信号(R5X支持)
	/*!
	\param[in] on  true:需要输出XHS, XVS;		false:不需要输出XHS, XVS;
	\param[in] xhs
	\param[in] xvs
	\param[in] cam 模组编号
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa _HisFX3Platform_ErrorCode
	*/
	HISFX3PLATFORM_API int HisFX3SetXVSXHS_DPHY(bool on, unsigned int xhs, unsigned int xvs, int cam = 0);

	//! 设置DPHY信号采集模式
	/*!
	\param[in] mode   0: Power Down  1: SLVS 2:D-PHY
	\param[in] cam 模组编号
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa _HisFX3Platform_ErrorCode
	*/
	HISFX3PLATFORM_API int HisFX3SetSignalMode_DPHY(unsigned int mode, int cam = 0);

	//! 设置HISPI协议的高低位bit是否需要反转
	/*! 支持的版本: R5X(ver>=2019)
	\param[in] on   true: 反转  false: 不反转
	\param[in] cam 模组编号
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa _HisFX3Platform_ErrorCode
	*/
	HISFX3PLATFORM_API int HisFX3SetBitReverse_HiSPI(bool on, int cam = 0);

	//! 设置是否解码MIPI信号的虚拟通道数据
	/*!
	\param[in] on  true: 解码  false:不解码
	\param[in] cam 模组编号
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa _HisFX3Platform_ErrorCode
	*/
	HISFX3PLATFORM_API int HisFX3SetVirtualChannel_MIPI(bool on, int cam = 0);

	//! 设置CPHY的速率
	/*!
	\param[in] rate  速率；单位：Gbps；支持范围：(0.1~1.6)(1.96~2.5)
	\param[in] cam 模组编号
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa _HisFX3Platform_ErrorCode
	*/
	HISFX3PLATFORM_API int HisFX3SetDataRate_CPHY(double rate, int cam = 0);

	//! 搜索CPHY的速率，只有在出图状态下，并且CPHY模式为9线模式才能调用
	/*!
	\param[in] rs  搜索范围的起始频率；单位：Gbps；支持范围：(0.1~1.6)(1.96~2.5)
	\param[in] re  搜索范围的结束频率；单位：Gbps；支持范围：(0.1~1.6)(1.96~2.5)
	\param[in] step  每次搜索步进的频率；单位：Gbps；
	\param[in] cam 模组编号
	\return CPHY的速率，单位：Gbps； <0表示搜索出错或者不满足条件 ==0表示搜索不到
	\sa
	*/
	HISFX3PLATFORM_API double HisFX3MeasureDataRate_CPHY(double rs, double re, double step, int cam = 0);

	//! 自动调整范围和STEP值搜索CPHY速率
	/*!
	\param[in] cam 模组编号
	\return CPHY的速率，单位：Gbps； <=0表示搜索不到
	\sa
	*/
	HISFX3PLATFORM_API double HisFX3AutoMeasureCPHYRate(int cam = 0);

	//! 设置CPHY信号寄存器
	/*!
	\param[in] slave 设备地址,第一级：0xA0,0xA2,0xA4; 第二级:0xB0,0xB2,0xB4
	\param[in] reg 寄存器地址
	\param[in] data 数据
	\param[in] type 类型: 0x0808, 0x1608, 0x1632...
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa _HisFX3Platform_ErrorCode
	*/
	HISFX3PLATFORM_API int HisFX3WriteSigCfg_CPHY(unsigned char slave, unsigned int reg, unsigned __int64 data, unsigned short type, int cam = 0);
	
	//! 读取CPHY信号寄存器
	/*!
	\param[in] slave 设备地址,第一级：0xA0,0xA2,0xA4; 第二级:0xB0,0xB2,0xB4
	\param[in] reg 寄存器地址
	\param[out] data 数据
	\param[in] type 类型: 0x0808, 0x1608, 0x1632...
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa _HisFX3Platform_ErrorCode
	*/
	HISFX3PLATFORM_API int HisFX3ReadSigCfg_CPHY(unsigned char slave, unsigned int reg, unsigned __int64* data, unsigned short type, int cam=0);
	
	//! 设置CPHY的工作模式
	/*!
	\param[in] mode 0:带参考时钟  1:不带参考时钟
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa _HisFX3Platform_ErrorCode
	*/
	HISFX3PLATFORM_API int HisFX3SetMode_CPHY(unsigned int mode, int cam = 0);

	//! 电流测量
	/*!
	\param[out] current 测试的电流数据，至少申请10个的数组大小，结果排序依次为AVDD,DVDD,DOVDD,AF,OTP,POW
	\param[in] flag 电源通道，_HisFX3_Platform_VoltFlag，支持 | 操作
	\param[in] precision 精度设置， 0：mA, 1:uA
	\param[in] samples 取平均值的采样次数
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa _HisFX3_Platform_VoltFlag
	*/
	HISFX3PLATFORM_API int HisFX3MeasureCurrent(double current[], unsigned int flag, unsigned int precision, unsigned int samples = 256, int cam = 0);

	//! 获取OS测试的PIN脚名称列表
	/*!
	\param[out] pin PIN脚名称， 用户申请的数组大小 >= 100
	\param[out] num 实际的PIN脚数量
	\param[in] port 接口设置， 0：DPHY  1:CPHY  2:DVP 3:LVDS
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
 	HISFX3PLATFORM_API int HisFX3GetOSPinNameList(char pin[][_HisFX3_OS_PinName_MaxByte], int* num, int port, int cam = 0);

	//! OS测试源选择
	/*!
	\param[in] src	0: 恒流源   1: 恒压源
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3SetOSSource(int src, int cam = 0);

	//! 正向测试
	/*!
	\param[in] port 接口设置， 0：DPHY  1:CPHY  2:DVP 3:LVDS
	\param[in] pin 测试PIN脚
	\param[in] num 测试PIN脚数量
	\param[in] delay 电流稳定延时, 单位: us
	\param[in] current 电源设置。如果为恒流源，单位为mA；如果为恒压源，单位为mV。
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa  _HisFX3OS_Positive_Item
	*/
 	HISFX3PLATFORM_API int HisFX3OSPositiveTest(int port, _HisFX3OS_Positive_Item pin[], int num, unsigned int delay = 1000, float current = 1.3, int cam = 0);

	//! 负向测试
	/*!
	\param[in] port 接口设置， 0：DPHY  1:CPHY  2:DVP 3:LVDS
	\param[in] pin 测试PIN脚
	\param[in] num 测试PIN脚数量
	\param[in] delay 电流稳定延时, 单位: us
	\param[in] current 电源设置。如果为恒流源，单位为mA；如果为恒压源，单位为mV。
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa _HisFX3OS_Negtive_Item
	*/
 	HISFX3PLATFORM_API int HisFX3OSNegtiveTest(int port, _HisFX3OS_Negtive_Item pin[], int num, unsigned int delay = 1000, float current = 1.3, int cam = 0);

	//! 短路测试
	/*!
	\param[in] port 接口设置， 0：DPHY  1:CPHY  2:DVP 3:LVDS
	\param[in] pin 测试PIN脚测试
	\param[in] num 测试PIN脚数量
	\param[in] delay 电流稳定延时, 单位: us
	\param[in] current 电源设置。如果为恒流源，单位为mA；如果为恒压源，单位为mV。
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa _RBOXOS_Short_Item
	*/
 	HISFX3PLATFORM_API int HisFX3OSShortTest(int port, _HisFX3OS_Short_Item pin[], int num, unsigned int delay = 1000, float current = 1.3, int cam = 0);

	//! 开路测试
	/*!
	\param[in] port 接口设置， 0：DPHY  1:CPHY  2:DVP 3:LVDS
	\param[in] pin 测试PIN脚测试
	\param[in] num 测试PIN脚数量
	\param[in] delay 电流稳定延时, 单位: us
	\param[in] current 电源设置。如果为恒流源，单位为mA；如果为恒压源，单位为mV。
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa _HisFX3OS_Open_Item
	*/
 	HISFX3PLATFORM_API int HisFX3OSOpenTest(int port, _HisFX3OS_Open_Item pin[], int num, unsigned int delay = 1000, float current = 1.3, int cam = 0);

	//! 电阻测试
	/*!
	\param[in] port 接口设置， 0：DPHY  1:CPHY  2:DVP 3:LVDS
	\param[in] pin 测试PIN脚测试
	\param[in] delay 电流稳定延时, 单位: us
	\param[in] current 电流大小设置，单位：mA
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa _HisFX3OS_OHM_Item
	*/
 	HISFX3PLATFORM_API int HisFX3OSOhmTest(int port, _HisFX3OS_OHM_Item* pin, unsigned int delay = 1000, float current = 1.3, int cam = 0);

	//! 电压值上升时间测试
	/*!
	\param[in] port 接口设置， 0：DPHY  1:CPHY  2:DVP 3:LVDS
	\param[in] pin 测试PIN脚测试
	\param[in] current 电流大小设置，单位：mA
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa _HisFX3OS_UpTime_Item
	*/
	HISFX3PLATFORM_API int HisFX3OSUpTimeTest(int port, _HisFX3OS_UpTime_Item* pin, float current = 0.1, int cam = 0);

	//! 用OS板测试漏电流
	/*!
	\param[in] port 接口设置， 0：DPHY  1:CPHY  2:DVP 3:LVDS
	\param[in] pin 待测PIN脚设置
	\param[in] num 待测PIN脚数量
	\param[in] delay 电流稳定延时, 单位: us
	\param[in] volt 恒压源电压，单位:mV, 范围：(200~3300mV)，精度：0.8058mV / LSB
	\param[in] currenRange 电流量程选择, 
							0: 量程：4uA, 精度：0.0009768uA / LSB
							1: 量程：40uA, 精度：0.009768uA / LSB
							2: 量程：400uA, 精度：0.09768uA / LSB
							3: 量程：4mA, 精度：0.9768uA / LSB
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa _HisFX3OS_LeakageCurrent_Item
	*/
	HISFX3PLATFORM_API int HisFX3OSLeakageCurrentTest(int port, _HisFX3OS_LeakageCurrent_Item pin[], int num, unsigned int delay, float volt, int currenRange, int cam = 0);

	//! 输出IO口控制， 拉高电平 == IODD
	/*!
	\param[in] status IO输出状态，以BIT位来管理， 1拉高， 0拉低
	\param[in] flag 要操作的输出IO， 以BIT位来管理， 1要操作， 0不操作
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3IO_OutPortWrite(unsigned int status, unsigned int flag, int cam = 0);

	//! 输出IO口状态读取， 拉高电平 == IODD
	/*!
	\param[out] status IO输出状态，以BIT位来管理， 1拉高， 0拉低
	\param[in] flag 要读取的输出IO， 以BIT位来管理， 1要读取， 0不读取
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3IO_OutPortRead(unsigned int* status, unsigned int flag, int cam = 0);

	//! 输入IO口状态读取， 拉高电平 == IODD
	/*!
	\param[out] status IO输出状态，以BIT位来管理， 1拉高， 0拉低
	\param[in] flag 要读取的输出IO， 以BIT位来管理， 1要读取， 0不读取
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3IO_InPortRead(unsigned int* status, unsigned int flag, int cam = 0);

	//! GPIO口输出PWM波形
	/*!
	\param[in] io 需要输入PWM的IO口索引，从0 开始计数
	\param[in] rate 波形频率，单位：KHz
	\param[in] duty 占空比百分比，比如占空比50%就设置50
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3SetIO_OutPortPWM(unsigned int io, double rate, double duty, int cam = 0);

	//! 设置SENSOR IIC线连接或断开
	/*!
	\param[in] on true: 链接； false: 断开
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3ConnectSensorIIC(bool on, int cam = 0);

	//! 设置SENSOR IIC线连接状态
	/*!
	\param[in] type
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa _HisFX3_CommunicationProtocal
	*/
	HISFX3PLATFORM_API int HisFX3SetSensorIICConnectType(_HisFX3_CommunicationProtocal type, int cam = 0);

	//! 电压校准， 校准值会自动写入工装寄存区
	/*!
	\param[in] boxIndex 工装编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3VoltCalibration(int boxIndex = 0);

	//! 电流校准， 校准值会自动写入工装寄存区
	/*!
	\param[in] boxIndex 工装编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3CurrentCalibration(int boxIndex = 0);

	//! 以字符串命令的形式执行非常规操作
	/*!
	\param[in] cmd eg: cmd:current calibration; 就是执行电流校准
	\param[in] p 根据cmd不同， 定义不同
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3CmdExec(char* cmd, void* p = NULL, int* size = NULL, int cam = 0);

	//! 多个进程操作同一个工装
	/*! 使用方法HisFX3SetCurrentPlatformType-->HisFX3SplitBox-->HisFX3OpenDevice
	\param[in] processCount 进程数量
	\param[in] processIndex 进程索引
	\return 0:成功  非0:失败
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3SplitBox(unsigned int processCount, unsigned int processIndex);

	//! 设置UVC数据源格式
	/*! 
	\param[in] srcFormat 必须大写 eg. "H264", "MJPG", "YUYV", "UYVY"
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	*/
	HISFX3PLATFORM_API int HisFX3SetSrcFormat_UVC(char* srcFormat, int cam = 0);

	//! 设置解串芯片型号
	/*!
	\param[in] type 解串芯片型号
	\sa _HisFX3_Deserializer
	*/
	HISFX3PLATFORM_API void HisFX3SetDeserializerType(_HisFX3_Deserializer type);

	//! 设置解串芯片连接方式
	/*!
	\param[in] type
	\param[in] cam 模组编号
	\sa _HisFX3_Deserializer_Connect_Type
	*/
	HISFX3PLATFORM_API int HisFX3SetDeserializerConnectType(_HisFX3_Deserializer_Connect_Type type, int cam = 0);

	//! 设置解串芯片工作模式
	/*!
	\param[in] mode
	\param[in] cam 模组编号
	\sa _HisFX3_Deserializer_Mode
	*/
	HISFX3PLATFORM_API int HisFX3SetDeserializerMode(_HisFX3_Deserializer_Mode mode, int cam = 0);

	//! 设置解串芯片设备地址
	/*!
	\param[in] slave: 设备地址。TI954包含{0x60,0x64,0x68,0x6C,0x70,0x74,0x78,0x7C}
	\param[in] cam 模组编号
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3SetDeserializerSlaveAddress(unsigned char slave, int cam = 0);

	//! 获取解串芯片的PASS/LOCK信号统计信息
	/*!
	\param[out] passCount:	PASS 信号触发次数
	\param[out] lockCount:	LOCK 信号触发次数
	\param[in] cam 模组编号
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3GetDeserializerPassLockStatistics(unsigned int* passCount, unsigned int* lockCount, int cam = 0);

	//! 开启/关闭 VM16F16模组模式
	/*!
	*/
	HISFX3PLATFORM_API void HisFX3SetCamMode16OnOff_VM16F(bool on);

	//! 设置图像上传抽点(VC8D)
	/*!
	\param[in] sampleWidth: 图像宽抽点，0-不抽点；其他：间隔sampleWidth个点抽一个点
	\param[in] sampleHeight: 图像高抽点，0-不抽点；其他：间隔sampleWidth个点抽一个点
	\param[in] cam 模组编号
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3SetImageSample_VC8D(unsigned char sampleWidth, unsigned char sampleHeight, int cam = 0);

	//! 改变工装内部器件的I2C设备地址， 避免和模组的I2C设备冲突(VC8D)
	/*!
	\param[in] group2: 是否启用第二组设备地址
	\param[in] cam 模组编号
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3ChangeInternelDeviceSlaveGroup_VC8D(bool group2, int cam = 0);


	//! 获取最后的错误描述
	/*! 在API返回错误的情况调用
	\param[in] cam 模组编号
	\return 错误信息指针
	*/
 	HISFX3PLATFORM_API const char* HisFX3GetLastError(int cam = 0);

	//! 设置离线图片模式
	/*! 
	\param[in] on 开启/关闭 离线图片模式
	\param[in] path 离线图片的路径
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	*/
	HISFX3PLATFORM_API int HisFX3SetOffLineMode(bool on, char* path = NULL, int cam = 0);

	//! FPGA自动对焦
	/*!
	\param[in] cfg 对焦参数
	\param[out] relt 对焦结果
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	*/
	HISFX3PLATFORM_API int HisFX3AF(_HisFX3_FPGAAF_Cfg* cfg, _HisFX3_FPGAAF_Rel* relt, int cam = 0);

	//! FPGA自动曝光
	/*!
	\param[in] cfg 自动曝光参数
	\param[out] relt 自动曝光结果
	\param[in] cam 模组编号
	\return 0:成功  非0:失败
	*/
	HISFX3PLATFORM_API int HisFX3AE(_HisFX3_FPGAAE_Cfg* cfg, _HisFX3_FPGAAE_Rel* relt, int cam = 0);

	//! 获取离线图片模式的信息
	/*! 在开启离线模式的情况下调用
	\param[out] width 图像宽
	\param[out] height 图像高
	\param[out] dataFormat 数据格式
	\param[out] frameBytes 一帧图像的数据量大小
	\param[in] cam 模组编号
	\return true:成功 false:失败
	*/
	HISFX3PLATFORM_API bool HisFX3GetOfflineModeInfo(unsigned int* width = NULL, unsigned int* height = NULL, _HisFX3_BaylorMode* dataFormat = NULL, unsigned int* frameBytes = NULL, int cam = 0);


	HISFX3PLATFORM_API int HisFX3PageOSPositiveTest_SUNNY(unsigned int *puiData, unsigned int uiData, unsigned int *puiData_S2, unsigned int uiData_S2,
		unsigned int *puiData_S3, unsigned int uiData_S3, unsigned int *puiData_S4, unsigned int uiData_S4, unsigned int uiCurrent, unsigned int uiVolt, int boxIndex);

	//! CAM ID转换
	/*!
	\param[in] cam_l 测试硬件ID,从0开始计数,工装1(boxindex(0))->测试盒通道1为0 通道2为1 通道3为2 通道4为3
	\工装2(boxindex(1))->测试盒通道1为4 通道2为5 通道3为6 通道4为7
	\以此类推
	\return  SDK内部cam id
	\sa
	*/
	HISFX3PLATFORM_API int LCamCvt(int cam_l);

	//! 开启工装图像通道
	/*!
	\param[in] boxIndex   工装编号, 设置为0; 仅当1个工装不拆分使用且一个进程拖多个工装才需区分;
	\param[in] processCount  1个工装拆分使用进程(AP)数，可设置4或者2；
	\                                           *当设置为2时(即一个进程2眼模式)，此接口需分时调用不可同时调用或者只调用一次且cam_l设置为偶数;
	\param[in] cam_l       模组ID,从0开始计数,工装1->测试盒通道1为0 通道2为1 通道3为2 通道4为3
	\                                                                      工装2->测试盒通道1为4 通道2为5 通道3为6 通道4为7  以此类推....
	\return  eturn 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa
	*/
	HISFX3PLATFORM_API int HisFX3OpenDevice_LuxVision(int boxIndex, unsigned int processCount, int cam_l);

}

namespace RISPAPI
{
	HISFX3PLATFORM_API void* malloc_r(size_t size);
	HISFX3PLATFORM_API void free_r(void* buf);
	HISFX3PLATFORM_API void safe_free_r(void** buf);

	/*! Compact格式的RAW10转成unsigned short表示一个像素的RAW10*/
	HISFX3PLATFORM_API void Cpt2B2_Raw10(void* cptBuf, int width, int height, void* b2Buf);

	/*! Compact格式的RAW转成unsigned short表示一个像素的RAW*/
	//! 开启工装图像通道
	/*!
	\param[in] cptBuf   compact raw数据指针；
	\param[in] width  图像宽；
	\param[in] height	 图像高
	\param[in] cptFormat	 RAW数据的具体格式，支持RAW8,RAW10,RAW12,RAW14
	\param[out] b2Buf	 2个BYTE表示一个像素的数据指针
	\return  eturn 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa
	*/
	HISFX3PLATFORM_API int Cpt2B2_RawX(void* cptBuf, int width, int height, _HisFX3_BaylorMode cptFormat, void* b2Buf);
}


#ifdef  __cplusplus
}
#endif


/*! 向后兼容C++接口*/

struct _HisFX3_PreviewStructCpp
{
	unsigned short usDeviceIndex; /*!< 设备序号，UVC用 */
	bool bIsSetRST; /*!< 是否设置bReset_ActiveLow */
	bool bReset_ActiveLow; /*!< true: 低电平有效，出图时拉高；   false: 高电平有效，出图时拉低 */
	bool bIsSetPWDN; /*!< 是否设置bPWND_ActiveLow */
	bool bPWND_ActiveLow; /*!< true: 低电平有效，出图时拉高；   false: 高电平有效，出图时拉低 */
	bool bDVP_VS_ActiveHigh; /*!< DVP VS 同步信号设置。   true: 高电平有效；   false: 低电平有效 */
	bool bDVP_HS_ActiveHigh; /*!< DVP HS 同步信号设置。   true: 高电平有效；   false: 低电平有效 */
	unsigned char ucDVP_LineFormat; /*!< DVP数据线设置  0：采9:2   1: 采7:0   2：采15:0   3：采9:0  4：采11:0   5：采13:0 */
	unsigned char ucDVP_PhaseShift; /*!<设置并口采集同步信号相移  0:不相移;  1: 90度;  2: 180度;  3: 270度; */
	bool bDebug; /*!< true:调试模式，会产生更多的调试信息到DebugView.exe； false: 非调试模式 */
	bool bCheckDeviceAck; /*!< true:IIC通信时侦测是否有ACK回馈； false: 不侦测 */
	bool bUseDDR; /*!< 设置是否使用DDR3(R5有效)。 true:使用DDR3； false: 不使用DDR3 */
	bool bSPICSLow; /*!< 设置读写SPI时，CS电平(R5有效)。 true:CS电平为低； false: CS电平为高 */
	bool bSPILittleEndian; /*!< 设置读写SPI时，低位在前还是高位在前(R5有效)。 true:低位在前； false: 高位在前 */
	bool bSPIClkHigh; /*! 设置SPI时钟  true: CLK默认是在高电平；false: CLK默认是在低电平；需要R2C >= 3506 */
	bool bVirtualChannel; /*!< 设置是否开启虚拟通道解码[R5有效] 。 true:开启虚拟通道解码； false: 不开启虚拟通道 */
	unsigned char ucSignalMode; /*!< 设置MIPI信号模式 1: SLVS 2:D-PHY */
	bool outputXVSXHS_DPHY; /*!< 设置解码D-PHY时是否输出XS, VS信号(从机模式) */
	unsigned int XHS_DPHY; /*!< 设置解码D-PHY的HS同步信号 */
	unsigned int XVS_DPHY; /*!< 设置解码D-PHY的VS同步信号 */

								/*! 设置点亮时的上电时序
								\sa _HisFX3_ImageSenor_Factory
								*/
	_HisFX3_ImageSenor_Factory sensorFactory;
	unsigned int uiVoltSetFlag; /*!< 设置要操作的电压，eg. 只操作AVDD和DVDD:  _HisFX3_Platform_VlotOn_AVDD |  _HisFX3_Platform_VlotOn_DVDD； 全操作：0xFFFFFFFF*/
	float ucVolt_DOVDD; /*!< 设置DOVDD电压，0.0~3.5范围可调, 实际所设电压 =  ucVolt_DOVDD *flVoltMultiple */
	float ucVolt_DVDD; /*!< 设置DVDD电压，0.0~3.5范围可调, 实际所设电压 =  ucVolt_DVDD *flVoltMultiple */
	float ucVolt_AVDD; /*!< 设置AVDD电压，0.0~3.5范围可调, 实际所设电压 =  ucVolt_AVDD *flVoltMultiple */
	float ucVolt_AF; /*!< 设置AF电压，0.0~3.5范围可调, 实际所设电压 =  ucVolt_AF *flVoltMultiple */
	float ucVolt_VFuse; /*!< 设置DOVDD电压，0.0~10.0范围可调, 实际所设电压 =  ucVolt_VFuse *flVoltMultiple */
	float ucVolt_POW; /*!< 设置POW电压，0.0~3.5范围可调, 实际所设电压 =  ucVolt_POW *flVoltMultiple */
	float ucVolt_IODD; /*!< 设置IODD电压【板卡内部IO电平】【R5】，0.0~3.5范围可调, 实际所设电压 =  ucVolt_IODD *flVoltMultiple */
	float flVoltMultiple;
	unsigned char ucVolt_5V; /*!< 设置5V电压开关，0：不输出  1：输出  其他：不操作  */
	unsigned char ucVolt_12V; /*!< 设置12V电压开关，0：不输出  1：输出  其他：不操作  */
	float flVoltageReadDiffMax; /*!< 保留 */
	unsigned char ucCommProtocal; /*!< 设置命令通讯协议。  0:IIC； 1:SPI */
	bool bIsSetMCLK; /*!< 是否设置MCLK*/
	float flMCLK; /*!< 设置flMCLK。 0~136MHz范围可调*/
				  /*! 设置板卡上传的数据格式
				  \sa _HisFX3_BaylorMode
				  */
	_HisFX3_BaylorMode ucDataFormat;
	unsigned short usI2CMode; /*!< 保留 */
	unsigned short usI2CSpeed;  /*!< 设置IIC通信速率，10KHz~1MHz范围可调 */
	unsigned short usI2CIntervalTime; /*!< 设置下发IIC命令的间隔时间，单位：us */
	unsigned short i2cByteDelay; /*!< I2C 每个字节之间的等待时间(单位：半个SCL时钟周期)。 如果设为0，则为批量下发模式；非0，则为单条下发模式*/
	unsigned char ucSlave; /*!< 保留 */
						   /*! 设置Sensor数据格式
						   \sa _HisFX3_MIPILane_Stream
						   */
	unsigned char ucMIPILane;
	unsigned char ucLaneNum; /*!< 设置C-PHY或者LVDS 数据Lane数 */
	unsigned int uiFrameByteCount; /*!< 设置一帧的数据量，单位: byte */
	unsigned int iWidth; /*!< 设置一帧的图像宽，单位：像素 */
	unsigned int iHeight; /*!< 设置一帧的图像高，单位：像素 */
	unsigned int uiDummyLeft; /*!< 设置图像左边的Dummy Line */
	unsigned int uiDummyRight; /*!< 设置图像右边的Dummy Line */
	unsigned int uiDummyTop; /*!< 设置图像上边的Dummy Line */
	unsigned int uiDummyBottom; /*!< 设置图像下边的Dummy Line */
	int customTotalFrameBytes; /*! 用户自定义一帧数据大小，用于虚拟通道开启的情况*/

	bool bOutputXSVS; /*!< 设置解码LVDS时是否输出XS, VS信号 */
	unsigned int uiLVDS_XHS; /*!< 设置解码LVDS的HS同步信号 */
	unsigned int uiLVDS_XVS; /*!< 设置解码LVDS的VS同步信号 */
	unsigned short usLVDSAlign; /*!< 设置解码LVDS的对齐方式 */

	char strSensorName[32]; /*!< 设置Sensor名称，比如：imx234,imx081, */

	unsigned short usI2CCount; /*!< 设置IIC或者SPI的命令条数 */
	unsigned char* pucSlave; /*!< 指向设备地址数组指针 */
	unsigned int* puiReg; /*!< 指向寄存器地址数组指针 */
	unsigned __int64* pui64Data; /*!< 指向数据数组指针 */
	unsigned short* pusType; /*!< 指向命令类型数组指针，包括0x0816, 0x0808,0x1608,0x1616,0x1632 */

							 //RTSP
	char pstrUrl[128];
	unsigned short usRTSPFrameDelay;
	unsigned short usRTSPValidTimeFromKey;

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

	/*********************SUNNY*********************/
	unsigned int iFullWidth;//增加大尺寸 用于开辟空间crossTalk
	unsigned int iFullHeight;
	/***************************************************/

	_HisFX3_PreviewStructCpp(void)
	{
		memset(this, 0, sizeof(_HisFX3_PreviewStructCpp));
		customTotalFrameBytes =cphyMode =usDeviceIndex = i2cByteDelay = 0;
		bUseDDR = bVirtualChannel = bDebug = false;
		bSPIClkHigh = bIsSetMCLK = bIsSetPWDN = bIsSetRST = bCheckDeviceAck = true;
		bDVP_HS_ActiveHigh = true;
		bDVP_VS_ActiveHigh = false;
		ucDVP_PhaseShift = ucDVP_LineFormat = 0;
		bReset_ActiveLow = bPWND_ActiveLow = false;
		bSPICSLow = true;
		bSPILittleEndian = false;
		ucSignalMode = 2;
		sensorFactory = _HisFX3_ImageSenor_Factory_OV;
		ucDataFormat = HisBaylor10_BGGR;
		ucCommProtocal = _HisFX3_CommProtocal_I2C;
		uiVoltSetFlag = 0xFFFFFFFF;
		ucVolt_DOVDD = ucVolt_DVDD = ucVolt_AVDD = ucVolt_AF = ucVolt_VFuse = ucVolt_POW = ucVolt_IODD = 0.0f;
		flVoltMultiple = 0.1f;
		ucVolt_5V = ucVolt_12V = 2;
		flVoltageReadDiffMax = 1000.0f;
		iWidth = iHeight = 0;
		outputXVSXHS_DPHY = bOutputXSVS = false;
		XHS_DPHY = uiLVDS_XHS = 1152;
		XVS_DPHY = uiLVDS_XVS = 3125;
		usLVDSAlign = 0x0;
		uiDummyLeft = uiDummyRight = uiDummyTop = uiDummyBottom = 0;
		flMCLK = 0.0f;
		usI2CMode = 0x1608;
		usI2CSpeed = 400;
		usI2CIntervalTime = 200;
		ucSlave = 0x6c;
		ucMIPILane = 6;
		ucLaneNum = 4;
		usI2CCount = cphy2ndI2CCount = cphySigI2CCount = 0;
		pucSlave = cphy2ndSlave = cphySigSlave = 0;
		puiReg = cphy2ndReg = cphySigReg = 0;
		pui64Data = 0;
		pusType = cphy2ndType = cphySigType = 0;
		cphy2ndData = cphySigData = 0;
		strSensorName[0] = pstrUrl[0] = '\0';
		usRTSPFrameDelay = 80;
		usRTSPValidTimeFromKey = 200;
		cphyRate = 1.0;
		iFullWidth = iFullHeight = 0;
	}

	~_HisFX3_PreviewStructCpp(void)
	{
		if (pucSlave) { delete[] pucSlave; pucSlave = 0; }
		if (puiReg) { delete[] puiReg; puiReg = 0; }
		if (pui64Data) { delete[] pui64Data; pui64Data = 0; }
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
};

class HISFX3PLATFORM_API CHisFX3Platform
{
public:
	CHisFX3Platform(void);
	~CHisFX3Platform(void);
	//!  打开工装， 在执行其他操作之间必须打开工装
	/*! 建议在程序一开始的时候打开工装，程序结束时关闭工装
	\param[in] usPID USB3.0设备PID， 此参数暂时保留，请固定设为0
	\param[in] usVID USB3.0设备VID， 此参数暂时保留，请固定设为0
	\param[in] pstrFriendlyName USB3.0设备描述名称， 此参数暂时保留，请固定设为0
	\param[in] ucDeviceIndex USB3.0设备序号， 此参数暂时保留，请固定设为0xFF
	\param[in] puiKey 工装唯一序列号， 当puiKey==NULL,函数打开连接到电脑的任一工装；
	当puiKey是指向 unsigned int[4]数组的指针时，函数打开和输入序列号匹配的工装。
	此参数主要用于1个电脑连接多个工装的情况。
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3CloseDevice()， _HisFX3Platform_ErrorCode
	*/
	int HisFX3OpenDevice(unsigned short usPID = 0, unsigned short usVID = 0, char* pstrFriendlyName = NULL, unsigned char ucDeviceIndex = 0xFF, unsigned int* puiKey = NULL, unsigned int uiTransformDelay = 110);

	//!  获取工装数量
	/*!
	\return 工装数量
	*/
	unsigned int HisFX3DeviceCount();

	//!  关闭工装
	/*!
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3OpenDevice()， _HisFX3Platform_ErrorCode
	*/
	int HisFX3CloseDevice();

	//! 通道1开始出图
	/*! 如果是双摄工装，此函数操作的是通道1
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa _HisFX3_PreviewStructCpp， HisFX3StopPreview()， _HisFX3Platform_ErrorCode
	*/
	int HisFX3StartPreview(struct _HisFX3_PreviewStructCpp* pstPrama);

	//! 通道1停止出图
	/*! 如果是双摄工装，此函数操作的是通道1
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3StartPreview()， _HisFX3Platform_ErrorCode
	*/
	int HisFX3StopPreview();

	//! 通道2开始出图
	/*! 只有在双摄工装上， 此函数才有效
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa _HisFX3_PreviewStructCpp， HisFX3StopPreview_S2()， _HisFX3Platform_ErrorCode
	*/
	int HisFX3StartPreview_S2(struct _HisFX3_PreviewStructCpp* pstPrama);

	//! 通道2停止出图
	/*! 只有在双摄工装上， 此函数才有效
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3StartPreview_S2()， _HisFX3Platform_ErrorCode
	*/
	int HisFX3StopPreview_S2();

	//! 通道1抓图
	/*! 如果是双摄工装，此函数操作的是通道1
	\param[out] ppucBuffer 接收图像数据的buffer指针，必须用_aligned_malloc(size, _HisCacheLine_Aligned)申请内存空间。
	如果传入NULL, 则只会返回ui64FramIndex。
	\param[in] uiBufBytes ppucBuffer申请的内存大小，必须大于一帧图像所需的内存大小
	\param[out] ui64FramIndex 当前帧索引，开始出图之后的第一帧为1，以此类推
	\param[in] uiTimeOut 获取新的一帧的timeout时间
	\param[in] uiConvertFlag 1:[raw10][raw12] 返回[width*height*5/4][width*height*3/2] byte  0: [raw10][raw12] 返回width*height byte
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3StartPreview()， HisFX3GrabFrameSequence(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3GrabFrame(unsigned char **ppucBuffer, unsigned int uiBufBytes, unsigned __int64& ui64FramIndex, unsigned int uiTimeOut = 3000, unsigned int uiConvertFlag = 0);

	//! 通道2抓图
	/*! 如果是双摄工装，此函数操作的是通道2
	\param[out] ppucBuffer 接收图像数据的buffer指针，必须用_aligned_malloc(size, _HisCacheLine_Aligned)申请内存空间。
	如果传入NULL, 则只会返回ui64FramIndex。
	\param[in] uiBufBytes ppucBuffer申请的内存大小，必须大于一帧图像所需的内存大小
	\param[out] ui64FramIndex 当前帧索引，开始出图之后的第一帧为1，以此类推
	\param[in] uiTimeOut 获取新的一帧的timeout时间
	\param[in] uiConvertFlag 1:[raw10][raw12] 返回[width*height*5/4][width*height*3/2] byte  0: [raw10][raw12] 返回width*height byte
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3StartPreview()， HisFX3GrabFrameSequence_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3GrabFrame_S2(unsigned char **ppucBuffer, unsigned int uiBufBytes, unsigned __int64& ui64FramIndex, unsigned int uiTimeOut = 3000, unsigned int uiConvertFlag = 0);

	//! 通道1连续抓帧
	/*! 如果是双摄工装，此函数操作的是通道1
	\param[out] buf 接收图像数据的buffer指针，必须用_aligned_malloc(size, _HisCacheLine_Aligned)申请内存空间。
	\param[in] uiBufBytes buf申请的内存大小，必须大于frames帧图像的大小
	\param[in] frames 设置要抓取的帧的数量
	\param[in] forceSequence true:抓取的帧必须绝对连续  false: 不要求抓取的帧绝对连续
	\param[in] uiTimeOut 单位:ms
	\param[in] uiConvertFlag 1:[raw10][raw12] 返回[width*height*5/4][width*height*3/2] byte  0: [raw10][raw12] 返回width*height byte
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3StartPreview()， HisFX3GrabFrame(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3GrabFrameSequence(void *buf, unsigned int uiBufBytes, int frames, bool forceSequence, unsigned int uiTimeOut = 8000, unsigned int uiConvertFlag = 0);

	//! 通道2连续抓帧
	/*! 如果是双摄工装，此函数操作的是通道1
	\param[out] buf 接收图像数据的buffer指针，必须用_aligned_malloc(size, _HisCacheLine_Aligned)申请内存空间。
	\param[in] uiBufBytes buf申请的内存大小，必须大于frames帧图像的大小
	\param[in] frames 设置要抓取的帧的数量
	\param[in] forceSequence true:抓取的帧必须绝对连续  false: 不要求抓取的帧绝对连续
	\param[in] uiTimeOut 单位:ms
	\param[in] uiConvertFlag 1:[raw10][raw12] 返回[width*height*5/4][width*height*3/2] byte  0: [raw10][raw12] 返回width*height byte
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3StartPreview()，HisFX3GrabFrame_S2(),  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GrabFrameSequence_S2(void *buf, unsigned int uiBufBytes, int frames, bool forceSequence, unsigned int uiTimeOut = 8000, unsigned int uiConvertFlag = 0);

	//! 工装是否已打开
	/*!
	\return true: 已打开  false: 还未打开
	\sa HisFX3isstart()， HisFX3OpenDevice, HisFX3CloseDevice
	*/
	bool HisFX3isopen();

	//! 通道1数据流是否已开启
	/*!
	\return true: 已开启  false: 未开启
	\sa HisFX3isopen()， HisFX3StartPreview(), HisFX3StopPreview()
	*/
	bool HisFX3isstart();

	//! 通道2数据流是否已开启
	/*!  只有在双摄工装上， 此函数才有效
	\return true: 已开启  false: 未开启
	\sa HisFX3isopen()， HisFX3StartPreview_S2(), HisFX3StopPreview_S2()
	*/
	bool HisFX3isstart_S2();

	//! 切换IIC的控制权
	/*! 上位机在操作IIC之前必须先切换IIC操作权到PC端
	\param[in] source 0: 设定控制权为FPGA;  1: 设定控制权为PC
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa _HisFX3Platform_ErrorCode
	*/
	int HisFX3IICExecSource(unsigned char source);

	//! 获取启动时间和稳像时间的测试状态
	/*! 上位机在操作IIC之前必须先切换IIC操作权到PC端
	\param[out] startComplete 启动时间测试是否完成， true为完成， false为未完成
	\param[out] startTime 启动时间，单位:ms; 只有在startComplete为true的情况下才有意义
	\param[out] stableComplete 稳像时间测试是否完成， true为完成， false为未完成
	\param[out] stableTime 稳像时间，单位:ms; 只有在stableComplete为true的情况下才有意义
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa _HisFX3Platform_ErrorCode
	*/
	int GetStartTime(bool* startComplete, double* startTime, bool* stableComplete, double* stableTime);

	//! 控制启动时间和稳像时间的测试状态
	/*!
	\param[in] test 0: 测试;  1: 取消测试
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa _HisFX3Platform_ErrorCode
	*/
	int HisFX3TestStartTime(unsigned char test);

	//! 获取当前open工装的唯一序列号
	/*!  只有在成功调用HisFX3OpenDevice之后才能调用此函数
	\param puiKey 指向unsigned int[4], 如果函数成功， 会复制设备唯一序列号到此数组空间
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa getHardwareKeyList, HisFX3OpenDevice()， HisFX3CloseDevice(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetHardwareKey(unsigned int* puiKey);

	//! 获取电脑上所有工装的唯一序列号
	/*!  只有在HisFX3OpenDevice之前才能调用此函数
	\param[out] puiKey 指向unsigned int, 如果函数成功， 会复制设备唯一序列号到此数组空间
	\param[out] uiKeyCount  返回有多少组序列号，一组序列号用4个unsigned int表示
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3GetHardwareKey, HisFX3OpenDevice()， HisFX3CloseDevice(), _HisFX3Platform_ErrorCode
	*/
	int getHardwareKeyList(unsigned int* puiKeyList, unsigned int& uiKeyCount);

	//! 操作通道1 RST信号
	/*!
	\param bPullHigh true: 置为高电平  false:置为低电平
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3PullPWND(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PullReset(bool bPullHigh);

	//! 操作通道2 RST信号
	/*!    只有在双摄工装上， 此函数才有效
	\param bPullHigh true: 置为高电平  false:置为低电平
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3PullPWND_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PullReset_S2(bool bPullHigh);

	//! 操作通道1 PWDN信号
	/*!
	\param bPullHigh true: 置为高电平  false:置为低电平
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3PullReset(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PullPWND(bool bPullHigh);

	int HisFX3UnlockFlashISX019(unsigned char slave, bool unlock);
	int HisFX3WriteFlashISX019(unsigned char slave, unsigned int reg, unsigned char* data, unsigned int dataSize);
	int HisFX3ReadFlashISX019(unsigned char slave, unsigned int reg, unsigned char* data, unsigned int dataSize);

	int HisFX3WriteSensorISX019(unsigned char slave, unsigned int reg, unsigned char* data, unsigned int dataSize);
	int HisFX3ReadSensorISX019(unsigned char slave, unsigned int reg, unsigned char* data, unsigned int dataSize);

	int HisFX3All2FlashISX019();


	int HisFX3ReadFlashISX019Unit(unsigned char slave, unsigned int reg, unsigned char* data, unsigned int dataSize);
	int HisFX3WriteFlashISX019Unit(unsigned char slave, unsigned int reg, unsigned char* data);
	int HisFX3EraseFlashISX019Unit(unsigned char slave, unsigned int reg);

	// 	int HisFX3WriteIIC_ISX019(unsigned char slave, unsigned char* d, unsigned int s);
	// 	int HisFX3ReadIIC_ISX019(unsigned char slave, unsigned char* w, unsigned int ws, unsigned char* r, unsigned int* rs);

	//! 操作通道2 PWDN信号
	/*!    只有在双摄工装上， 此函数才有效
	\param bPullHigh true: 置为高电平  false:置为低电平
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3PullReset_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PullPWND_S2(bool bPullHigh);

	//! 单条写IIC
	/*!
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[in] ui64Data 要写入的数据
	\param[in] usType 寄存器和数据格式, eg:0x1608-表示地址位写入16bit, 数据位写入8bit。
	支持的格式:0x0808,0x0816,0x1608,0x1616,0x1632,0x0008,0x0016,0x0032
	\param[in] back  true: 判断ACK  false:不判断ACK(耗时更少，但更不安全)
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3ReadI2C(), HisFX3BatchWriteIICNoLimit(), HisFX3BatchReadIICNoLimit(), HisFX3PageWriteIIC(), HisFX3PageReadIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3WriteIIC(unsigned char ucSlave, unsigned int uiReg, unsigned __int64 ui64Data, unsigned short usType, bool back = true);

	//! 单条写通道2 IIC
	/*!    只有在双摄工装上， 此函数才有效
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[in] ui64Data 要写入的数据
	\param[in] usType 寄存器和数据格式, eg:0x1608-表示地址位写入16bit, 数据位写入8bit。
	支持的格式:0x0808,0x0816,0x1608,0x1616,0x1632,0x0008,0x0016,0x0032
	\param[in] back  true: 判断ACK  false:不判断ACK(耗时更少，但更不安全)
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3ReadI2C_S2(), HisFX3BatchWriteIICNoLimit_S2(), HisFX3BatchReadIICNoLimit_S2(), HisFX3PageWriteIIC_S2(), HisFX3PageReadIIC_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3WriteIIC_S2(unsigned char ucSlave, unsigned int uiReg, unsigned __int64 ui64Data, unsigned short usType, bool back = true);

	//! 单条读IIC
	/*!
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[out] pui64Data 读出来的数据
	\param[in] usType 寄存器和数据格式, eg:0x1608-表示地址位写入16bit, 数据位写入8bit。
	支持的格式:0x0808,0x0816,0x1608,0x1616,0x1632,0x0008,0x0016,0x0032
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3WriteIIC(), HisFX3BatchWriteIICNoLimit(), HisFX3BatchReadIICNoLimit(), HisFX3PageWriteIIC(), HisFX3PageReadIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3ReadI2C(unsigned char ucSlave, unsigned int uiReg, unsigned __int64* pui64Data, unsigned short usType);

	//! 单条读IIC(通道2)
	/*!    只有在双摄工装上， 此函数才有效
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[out] pui64Data 读出来的数据
	\param[in] usType 寄存器和数据格式, eg:0x1608-表示地址位写入16bit, 数据位写入8bit。
	支持的格式:0x0808,0x0816,0x1608,0x1616,0x1632,0x0008,0x0016,0x0032
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3WriteIIC_S2(), HisFX3BatchWriteIICNoLimit_S2(), HisFX3BatchReadIICNoLimit_S2(), HisFX3PageWriteIIC_S2(), HisFX3PageReadIIC_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3ReadI2C_S2(unsigned char ucSlave, unsigned int uiReg, unsigned __int64* pui64Data, unsigned short usType);

	//! 批量写入IIC
	/*!
	\param[in] uiCount  要写入的IIC的条数
	\param[in] pucSlave 设备地址数组指针
	\param[in] puiReg 寄存器地址数组指针
	\param[in] puiData 数据数组指针
	\param[in] pusType 格式数组指针, eg:0x1608-表示地址位写入16bit, 数据位写入8bit。
	支持的格式:0x0808,0x0816,0x1608,0x1616,0x1632
	\param[in] usDelay 命令之间的间隔时间，单位: us
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3WriteIIC(), HisFX3ReadIIC(), HisFX3BatchReadIICNoLimit(), HisFX3PageWriteIIC(), HisFX3PageReadIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3BatchWriteIICNoLimit(unsigned int uiCount, unsigned char* pucSlave, unsigned int* puiReg, unsigned int* puiData, unsigned short* pusType, unsigned short usDelay = 10);

	//! 批量写入IIC(通道2)
	/*!
	\param[in] uiCount  要写入的IIC的条数
	\param[in] pucSlave 设备地址数组指针
	\param[in] puiReg 寄存器地址数组指针
	\param[in] puiData 数据数组指针
	\param[in] pusType 格式数组指针, eg:0x1608-表示地址位写入16bit, 数据位写入8bit。
	支持的格式:0x0808,0x0816,0x1608,0x1616,0x1632
	\param[in] usDelay 命令之间的间隔时间，单位: us
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3WriteIIC_S2(), HisFX3ReadIIC_S2(), HisFX3BatchReadIICNoLimit_S2(), HisFX3PageWriteIIC_S2(), HisFX3PageReadIIC_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3BatchWriteIICNoLimit_S2(unsigned int uiCount, unsigned char* pucSlave, unsigned int* puiReg, unsigned int* puiData, unsigned short* pusType, unsigned short usDelay = 10);

	//! 批量读取IIC
	/*!
	\param[in] uiCount  要写入的IIC的条数
	\param[in] pucSlave 设备地址数组指针
	\param[in] puiReg 寄存器地址数组指针
	\param[out] puiData 数据数组指针
	\param[in] pusType 格式数组指针, eg:0x1608-表示地址位写入16bit, 数据位写入8bit。
	支持的格式:0x0808,0x0816,0x1608,0x1616,0x1632
	\param[in] usDelay 命令之间的间隔时间，单位: us
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3WriteIIC(), HisFX3ReadIIC(), HisFX3BatchWriteIICNoLimit(), HisFX3PageWriteIIC(), HisFX3PageReadIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3BatchReadIICNoLimit(unsigned int uiCount, unsigned char* pucSlave, unsigned int* puiReg, unsigned int* puiData, unsigned short* pusType, unsigned short usDelay = 10);

	//! 批量读取IIC(通道2)
	/*!
	\param[in] uiCount  要写入的IIC的条数
	\param[in] pucSlave 设备地址数组指针
	\param[in] puiReg 寄存器地址数组指针
	\param[out] puiData 数据数组指针
	\param[in] pusType 格式数组指针, eg:0x1608-表示地址位写入16bit, 数据位写入8bit。
	支持的格式:0x0808,0x0816,0x1608,0x1616,0x1632
	\param[in] usDelay 命令之间的间隔时间，单位: us
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3WriteIIC_S2(), HisFX3ReadIIC_S2(), HisFX3BatchWriteIICNoLimit_S2(), HisFX3PageWriteIIC_S2(), HisFX3PageReadIIC_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3BatchReadIICNoLimit_S2(unsigned int uiCount, unsigned char* pucSlave, unsigned int* puiReg, unsigned int* puiData, unsigned short* pusType, unsigned short usDelay = 10);

	//! Page写入IIC
	/*!
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[in] uiRegSize 寄存器地址字节长度，1,2,4可选
	\param[in] pucData 数据数组指针
	\param[in] uiDataSize 要写入的数据长度，单位:byte
	\param[in] usDelay 每个BYTE延时usDelay *0.5个始终周期
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3ReadI2C(), HisFX3WriteI2C(), HisFX3BatchWriteIICNoLimit(), HisFX3BatchReadIICNoLimit(), HisFX3PageReadIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageWriteIIC(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize, unsigned short usDelay = 4);

	//! Page模式写入IIC(通道2)
	/*!
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[in] uiRegSize 寄存器地址字节长度，1,2,4可选
	\param[in] pucData 数据数组指针
	\param[in] uiDataSize 要写入的数据长度，单位:byte
	\param[in] usDelay 每个BYTE延时usDelay *0.5个始终周期
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3ReadI2C_S2(), HisFX3WriteI2C_S2(), HisFX3BatchWriteIICNoLimit_S2(), HisFX3BatchReadIICNoLimit_S2(), HisFX3PageReadIIC_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageWriteIIC_S2(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize, unsigned short usDelay = 4);

	//! Page模式读取IIC
	/*!
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[in] uiRegSize 寄存器地址字节长度，1,2,4可选
	\param[out] pucData 数据数组指针
	\param[in] uiDataSize 要读取的数据长度，单位:byte
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3ReadI2C(), HisFX3WriteI2C(), HisFX3BatchWriteIICNoLimit(), HisFX3BatchReadIICNoLimit(), HisFX3PageWriteIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageReadIIC(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize);

	//! Page模式读取IIC(通道2)
	/*!
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[in] uiRegSize 寄存器地址字节长度，1,2,4可选
	\param[out] pucData 数据数组指针
	\param[in] uiDataSize 要读取的数据长度，单位:byte
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3ReadI2C_S2(), HisFX3WriteI2C_S2(), HisFX3BatchWriteIICNoLimit_S2(), HisFX3BatchReadIICNoLimit_S2(), HisFX3PageWriteIIC_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageReadIIC_S2(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize);

	//! Page写入IIC, 无长度限制(通道1)
	/*!
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[in] uiRegSize 寄存器地址字节长度，1,2,4可选
	\param[in] pucData 数据数组指针
	\param[in] uiDataSize 要写入的数据长度，单位:byte
	\param[in] uiPageSize 一个Page的大小，需要查阅EEPROM的规格书，一般是128,256,512,1024...
	\param[in] usByteDelay 每个BYTE延时usDelay *0.5个始终周期
	\param[in] uiPageDelay 每个Page写入之间的延时，单位:ms
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3PageWriteIIC(), HisFX3ReadI2C(), HisFX3WriteI2C(), HisFX3BatchWriteIICNoLimit(), HisFX3BatchReadIICNoLimit(), HisFX3PageReadIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageWriteIICNoLimit(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize, unsigned int uiPageSize, unsigned short usByteDelay = 4, unsigned int uiPageDelay = 100);

	//! Page写入IIC, 无长度限制(通道2)
	/*!
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[in] uiRegSize 寄存器地址字节长度，1,2,4可选
	\param[in] pucData 数据数组指针
	\param[in] uiDataSize 要写入的数据长度，单位:byte
	\param[in] uiPageSize 一个Page的大小，需要查阅EEPROM的规格书，一般是128,256,512,1024...
	\param[in] usByteDelay 每个BYTE延时usDelay *0.5个始终周期
	\param[in] uiPageDelay 每个Page写入之间的延时，单位:ms
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3PageWriteIIC_S2(), HisFX3ReadI2C(), HisFX3WriteI2C(), HisFX3BatchWriteIICNoLimit(), HisFX3BatchReadIICNoLimit(), HisFX3PageReadIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageWriteIICNoLimit_S2(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize, unsigned int uiPageSize, unsigned short usByteDelay = 4, unsigned int uiPageDelay = 100);

	//! Page模式读取IIC, 无长度限制(通道1)
	/*!
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[in] uiRegSize 寄存器地址字节长度，1,2,4可选
	\param[out] pucData 数据数组指针
	\param[in] uiDataSize 要读取的数据长度，单位:byte
	\param[in] uiPageSize 一个Page的大小，需要查阅EEPROM的规格书，一般是128,256,512,1024...
	\param[in] uiPageDelay 每个Page读取之间的延时，单位:ms
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3PageReadIIC(), HisFX3ReadI2C(), HisFX3WriteI2C(), HisFX3BatchWriteIICNoLimit(), HisFX3BatchReadIICNoLimit(), HisFX3PageWriteIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageReadIICNoLimit(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize, unsigned int uiPageSize, unsigned int uiPageDelay = 0);

	//! Page模式读取IIC, 无长度限制(通道2)
	/*!
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[in] uiRegSize 寄存器地址字节长度，1,2,4可选
	\param[out] pucData 数据数组指针
	\param[in] uiDataSize 要读取的数据长度，单位:byte
	\param[in] uiPageSize 一个Page的大小，需要查阅EEPROM的规格书，一般是128,256,512,1024...
	\param[in] uiPageDelay 每个Page读取之间的延时，单位:ms
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3PageReadIIC_S2(), HisFX3ReadI2C(), HisFX3WriteI2C(), HisFX3BatchWriteIICNoLimit(), HisFX3BatchReadIICNoLimit(), HisFX3PageWriteIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageReadIICNoLimit_S2(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize, unsigned int uiPageSize, unsigned int uiPageDelay = 0);

	//! Page模式写入SPI
	/*!
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[in] uiRegSize 寄存器地址字节长度，1,2,4可选
	\param[in] pucData 数据数组指针
	\param[in] uiDataSize 要写入的数据长度，单位:byte
	\param[in] bCSLow 设置操作SPI时的CS信号电平。 true:低电平； false:高电平
	\param[in] bLowFirst true: 低位在前； false:高位在前
	\param[in] clkHigh true: CLK默认是在高电平；false: CLK默认是在低电平；需要R2C >= 3506
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3PageReadSPI(), HisFX3WriteSPI(), HisFX3ReadSPI(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageWriteSPI(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, \
		unsigned char* pucData, unsigned int uiDataSize, bool bCSLow = true, bool bLowFirst = true, bool clkHigh = true);

	//! Page模式读取SPI
	/*!
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[in] uiRegSize 寄存器地址字节长度，1,2,4可选
	\param[out] pucData 数据数组指针
	\param[in] uiDataSize 要写入的数据长度，单位:byte
	\param[in] bCSLow 设置操作SPI时的CS信号电平。 true:低电平； false:高电平
	\param[in] bLowFirst true: 低位在前； false:高位在前
	\param[in] clkHigh true: CLK默认是在高电平；false: CLK默认是在低电平；需要R2C >= 3506
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3PageWriteSPI(), HisFX3WriteSPI(), HisFX3ReadSPI(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageReadSPI(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, \
		unsigned int uiDataSize, bool bCSLow = true, bool bLowFirst = true, bool clkHigh = true);

	//! 单条写SPI
	/*!
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[in] ui64Data 要写入的数据
	\param[in] usType 寄存器和数据格式, eg:0x1608-表示地址位写入16bit, 数据位写入8bit。
	支持的格式:0x0808,0x0816,0x1608,0x1616,0x1632,0x0008,0x0016,0x0032
	\param[in] bCSLow 设置操作SPI时的CS信号电平。 true:低电平； false:高电平
	\param[in] bLowFirst true: 低位在前； false:高位在前
	\param[in] clkHigh true: CLK默认是在高电平；false: CLK默认是在低电平；需要R2C >= 3506
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3ReadSPI(), HisFX3PageWriteSPI(), HisFX3PageReadSPI(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3WriteSPI(unsigned char ucSlave, unsigned int uiReg, unsigned __int64 ui64Data, \
		unsigned short usType, bool bCSLow = true, bool bLowFirst = true, bool clkHigh = true);

	//! 单条读取SPI
	/*!
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[out] pui64Data 读取的数据
	\param[in] usType 寄存器和数据格式, eg:0x1608-表示地址位写入16bit, 数据位写入8bit。
	支持的格式:0x0808,0x0816,0x1608,0x1616,0x1632,0x0008,0x0016,0x0032
	\param[in] bCSLow 设置操作SPI时的CS信号电平。 true:低电平； false:高电平
	\param[in] bLowFirst true: 低位在前； false:高位在前
	\param[in] clkHigh true: CLK默认是在高电平；false: CLK默认是在低电平；需要R2C >= 3506
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3WriteSPI(), HisFX3PageWriteSPI(), HisFX3PageReadSPI(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3ReadSPI(unsigned char ucSlave, unsigned int uiReg, unsigned __int64* pui64Data, \
		unsigned short usType, bool bCSLow = true, bool bLowFirst = true, bool clkHigh = true);

	//! 设置IIC通信速度
	/*!
	\param[in] us1kMultiple 10KHz~1MHz范围可调
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3GetIICSpeed(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3SetIICSpeed(unsigned short us1kMultiple);

	//! 设置IIC通信速度(通道2)
	/*!
	\param[in] us1kMultiple 10KHz~1MHz范围可调
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3GetIICSpeed_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3SetIICSpeed_S2(unsigned short us1kMultiple);

	//! 获取当前IIC通信速度
	/*!
	\param[out] pus1kMultiple 单位：KHz
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3SetIICSpeed(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetIICSpeed(unsigned short* pus1kMultiple);

	//! 获取当前IIC通信速度(通道2)
	/*!
	\param[out] pus1kMultiple 单位：KHz
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3SetIICSpeed_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetIICSpeed_S2(unsigned short* pus1kMultiple);

	//! 设置SPI通信速度
	/*!
	\param[in] us1kMultiple 10KHz~25MHz范围可调, 单位: KHz
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3GetSPISpeed(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3SetSPISpeed(unsigned short us1kMultiple);

	//! 获取当前SPI通信速度
	/*!
	\param[out] pus1kMultiple 单位：KHz
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3SetSPISpeed(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetSPISpeed(unsigned short* pus1kMultiple);

	//! 侦测通道1的从设备地址响应
	/*!
	\param[in] ucSlave 从设备的设备地址
	\return 0:有响应  非0:未响应, 请参考_HisFX3Platform_ErrorCode
	\sa _HisFX3Platform_ErrorCode
	*/
	int HisFX3SlaveResponds(unsigned char ucSlave);

	//! 侦测通道2的从设备地址响应
	/*!
	\param[in] ucSlave 从设备的设备地址
	\return 0:有响应  非0:未响应, 请参考_HisFX3Platform_ErrorCode
	\sa _HisFX3Platform_ErrorCode
	*/
	int HisFX3SlaveResponds_S2(unsigned char ucSlave);

	//! 设置风扇模式【R3X】
	/*!
	\param[in] mode 0：自动  1：开  2：关
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa _HisFX3Platform_ErrorCode
	*/
	int HisFX3SetFanMode(unsigned char mode);

	//! 开关5V12V电压输出【R5】
	/*!
	\param[in] uiV5 0：5V关闭  1：5V打开  2：5V不设置
	\param[in] uiV12 0：12V关闭  1：12V打开  2：12V不设置
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3SetVolt, HisFX3SetVolt_S2, _HisFX3Platform_ErrorCode
	*/
	int HisFX3Set5V12V(unsigned int uiV5 = 2, unsigned int uiV12 = 2);

	//! 设置通道1电压
	/*!
	\param[in] flDOVDD 0.0V~3.5V范围可调, 实际所设电压= flDOVDD *flMultiple
	\param[in] flAVDD 0.0V~3.5V范围可调, 实际所设电压= flAVDD *flMultiple
	\param[in] flDVDD 0.0V~3.5V范围可调, 实际所设电压= flDVDD *flMultiple
	\param[in] flAF 0.0V~3.5V范围可调, 实际所设电压= flAF *flMultiple
	\param[in] flVFuse 0.0V~10.0V范围可调, 实际所设电压= flVFuse *flMultiple
	\param[in] flPOW 0.0V~3.5V范围可调【R5】【R3X】【R5X】, 实际所设电压= flPOW *flMultiple
	\param[in] flIODD 0.0V~3.5V范围可调【板卡内部IO电平】【R5】, 实际所设电压= flIODD *flMultiple
	\param[in] usSwitch 设置电压开关， _HisFX3_Platform_VoltFlag，
	eg,设置AVDD和DVDD电压， _HisFX3_Platform_VlotOn_AVDD | _HisFX3_Platform_VlotOn_DVDD
	\param[in] flMultiple 电压值系数
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3Set5V12V, HisFX3SetVolt_S2, HisFX3GetVolt, _HisFX3Platform_ErrorCode
	*/
	int HisFX3SetVolt(float flDOVDD = 0.0f, float flAVDD = 0.0f, float flDVDD = 0.0f, float flAF = 0.0f, float flVFuse = 0.0f, float flPOW = 0.0f, float flIODD = 0.0f, unsigned short usSwitch = 0xFF, float flMultiple = 0.1f);

	//! 设置通道2电压
	/*!
	\param[in] flDOVDD 0.0V~3.5V范围可调, 实际所设电压= flDOVDD *flMultiple
	\param[in] flAVDD 0.0V~3.5V范围可调, 实际所设电压= flAVDD *flMultiple
	\param[in] flDVDD 0.0V~3.5V范围可调, 实际所设电压= flDVDD *flMultiple
	\param[in] flAF 0.0V~3.5V范围可调, 实际所设电压= flAF *flMultiple
	\param[in] flVFuse 0.0V~10.0V范围可调, 实际所设电压= flVFuse *flMultiple
	\param[in] flPOW 0.0V~3.5V范围可调【R5】, 实际所设电压= flPOW *flMultiple
	\param[in] flIODD 0.0V~3.5V范围可调【板卡内部IO电平】【R5】, 实际所设电压= flIODD *flMultiple
	\param[in] usSwitch 设置电压开关， _HisFX3_Platform_VoltFlag，
	eg,设置AVDD和DVDD电压， _HisFX3_Platform_VlotOn_AVDD | _HisFX3_Platform_VlotOn_DVDD
	\param[in] flMultiple 电压值系数
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3Set5V12V, HisFX3SetVolt, HisFX3GetVolt_S2, _HisFX3Platform_ErrorCode
	*/
	int HisFX3SetVolt_S2(float flDOVDD = 0, float flAVDD = 0, float flDVDD = 0, float flAF = 0, float flVFuse = 0, float flPOW = 0, float flIODD = 0, unsigned short usSwitch = 0xFF, float flMultiple = 0.1f);

	//! 获取通道1当前设置电压
	/*!
	\param[out] pflDOVDD 当前DOVDD设置电压
	\param[out] pflAVDD 当前AVDD设置电压
	\param[out] pflDVDD 当前DVDD设置电压
	\param[out] pflAF 当前AF设置电压
	\param[out] pflVFuse 当前VFuse设置电压
	\param[out] pflPOW 当前POW设置电压
	\param[out] pflIODD 当前IODD设置电压
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3SetVolt,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetVolt(float* pflDOVDD = NULL, float* pflAVDD = NULL, float* pflDVDD = NULL, float* pflAF = NULL, float* pflVFuse = NULL, float* pflPOW = NULL, float* pflIODD = NULL);

	//! 获取通道2当前设置电压
	/*!
	\param[out] pflDOVDD 当前DOVDD设置电压
	\param[out] pflAVDD 当前AVDD设置电压
	\param[out] pflDVDD 当前DVDD设置电压
	\param[out] pflAF 当前AF设置电压
	\param[out] pflVFuse 当前VFuse设置电压
	\param[out] pflPOW 当前POW设置电压
	\param[out] pflIODD 当前IODD设置电压
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3SetVolt_S2,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetVolt_S2(float* pflDOVDD = NULL, float* pflAVDD = NULL, float* pflDVDD = NULL, float* pflAF = NULL, float* pflVFuse = NULL, float* pflPOW = NULL, float* pflIODD = NULL);

	//! 设置通道1 MCLK时钟
	/*!
	\param[in] flMCLK 0~136MHz可调， 单位: MHz
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3GetMCLK,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3SetMCLK(float flMCLK);

	//! 设置通道2 MCLK时钟
	/*!
	\param[in] flMCLK 0~136MHz可调， 单位: MHz
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3GetMCLK_S2,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3SetMCLK_S2(float flMCLK);

	//! 获取通道1当前MCLK设置时钟
	/*!
	\param[out] pflMCLK 单位: MHz
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3SetMCLK,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetMCLK(float* pflMCLK);

	//! 获取通道2当前MCLK设置时钟
	/*!
	\param[out] pflMCLK 单位: MHz
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3SetMCLK_S2,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetMCLK_S2(float* pflMCLK);

	//! 设置并口采集同步信号相移
	/*!
	\param[in] sCountPs18  0:不相移;  1: 90度;  2: 180度;  3: 270度;
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa _HisFX3Platform_ErrorCode
	*/
	int HisFX3DVPPCLKPhaseShift(short sCountPs18);

	//! 获取FPGA程序版本号
	/*!
	\param[out] puiversion 版本号
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa   HisFX3OpenDevice,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetHardwareVersion(unsigned int* puiversion);

	//! 获取开短路程序版本号
	/*!
	\param[out] pusversion 版本号
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa   HisFX3OpenDevice,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetOSVersion(unsigned short* pusversion);

	//! 获取FX3程序版本号
	/*!
	\param[out] pusversion 版本号
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa   HisFX3OpenDevice,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetFX3Version(unsigned short* pusversion);

	int HisFX3CurrentCalibration();

	int HisFX3CurrentCalibration(unsigned int* puiKey, _HisFX3_Current_Calibration* pstCal);
	int HisFX3SetCurrentCalData(_HisFX3_Current_Calibration* pstCal);
	int HisFX3VlotageCalibration(unsigned int* puiKey, _HisFX3_Voltage_Calibration* pstCal);
	int HisFX3SetVoltageCalData(_HisFX3_Voltage_Calibration* pstCal);
	//! 测量通道1工作电流
	/*!
	\param[out] flAVDD 返回的AVDD电流
	\param[out] flDVDD 返回的DVDD电流
	\param[out] flDOVDD 返回的DOVDD电流
	\param[out] flAF 返回的AF电流
	\param[out] flVFuse 返回的VFuse电流
	\param[out] flPOW 返回的POW电流【R5】【R3X】【R5X】
	\param[in] uiFlag 设置要测哪些路的电流值， _HisFX3_Platform_VoltFlag，
	eg,要测AVDD和DVDD电流， _HisFX3_Platform_VlotOn_AVDD | _HisFX3_Platform_VlotOn_DVDD
	\param[in] uiAverageTimes 取uiAverageTimes次数据，然后求平均
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa   HisFX3GetStandbyCurrent,  HisFX3GetWorkCurrent_S2, HisFX3GetStandbyCurrent_S2, _HisFX3_Platform_VoltFlag,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetWorkCurrent(float& flAVDD, float& flDVDD, float& flDOVDD, float& flAF, float& flVFuse, float& flPOW, unsigned int uiFlag = 0xFF, unsigned int uiAverageTimes = 64);

	//! 测量通道2工作电流
	/*!
	\param[out] flAVDD 返回的AVDD电流
	\param[out] flDVDD 返回的DVDD电流
	\param[out] flDOVDD 返回的DOVDD电流
	\param[out] flAF 返回的AF电流
	\param[out] flVFuse 返回的VFuse电流
	\param[out] flPOW 返回的POW电流【R5】【R3X】【R5X】
	\param[in] uiFlag 设置要测哪些路的电流值， _HisFX3_Platform_VoltFlag，
	eg,要测AVDD和DVDD电流， _HisFX3_Platform_VlotOn_AVDD | _HisFX3_Platform_VlotOn_DVDD
	\param[in] uiAverageTimes 取uiAverageTimes次数据，然后求平均
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa   HisFX3GetStandbyCurrent,  HisFX3GetWorkCurrent, HisFX3GetStandbyCurrent_S2, _HisFX3_Platform_VoltFlag,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetWorkCurrent_S2(float& flAVDD, float& flDVDD, float& flDOVDD, float& flAF, float& flVFuse, float& flPOW, unsigned int uiFlag = 0xFF, unsigned int uiAverageTimes = 64);

	//! 测量通道1静态电流
	/*!
	\param[out] flAVDD 返回的AVDD电流
	\param[out] flDVDD 返回的DVDD电流
	\param[out] flDOVDD 返回的DOVDD电流
	\param[out] flAF 返回的AF电流
	\param[out] flPOW 返回的POW电流【R5】【R3X】【R5X】
	\param[in] uiFlag 设置要测哪些路的电流值， _HisFX3_Platform_VoltFlag，
	eg,要测AVDD和DVDD电流， _HisFX3_Platform_VlotOn_AVDD | _HisFX3_Platform_VlotOn_DVDD
	\param[in] bPWND	true:拉PWND进入待机模式，  false:无需拉PWND信号
	\param[in] bReset	true:拉RST进入待机模式，  false:无需拉RST信号
	\param[in] bMCLK	true:MCLK设为0MHz进入待机模式，  false:无需把MCLK始终设为0MHz
	\param[in] bDVDD	true:DVDD设为0V进入待机模式，  false:无需把DVDD进入0V
	\param[in] uiDelay	进入待机模式后延时uiDelay ms之后再测待机电流
	\param[in] uiAverageTimes 取uiAverageTimes次数据，然后求平均
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa   HisFX3GetWorkCurrent,  HisFX3GetWorkCurrent_S2, HisFX3GetStandbyCurrent_S2, _HisFX3_Platform_VoltFlag,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetStandbyCurrent(float& flAVDD, float& flDVDD, float& flDOVDD, float& flAF, float& flPOW, unsigned int uiFlag = 0xFF, \
		bool bPWND = true, bool bReset = true, bool bMCLK = true, bool bDVDD = false, unsigned int uiDelay = 5000, unsigned int uiAverageTimes = 7);

	//! 测量通道2静态电流
	/*!
	\param[out] flAVDD 返回的AVDD电流
	\param[out] flDVDD 返回的DVDD电流
	\param[out] flDOVDD 返回的DOVDD电流
	\param[out] flAF 返回的AF电流
	\param[out] flPOW 返回的POW电流【R5】【R3X】【R5X】
	\param[in] uiFlag 设置要测哪些路的电流值， _HisFX3_Platform_VoltFlag，
	eg,要测AVDD和DVDD电流， _HisFX3_Platform_VlotOn_AVDD | _HisFX3_Platform_VlotOn_DVDD
	\param[in] bPWND	true:拉PWND进入待机模式，  false:无需拉PWND信号
	\param[in] bReset	true:拉RST进入待机模式，  false:无需拉RST信号
	\param[in] bMCLK	true:MCLK设为0MHz进入待机模式，  false:无需把MCLK始终设为0MHz
	\param[in] bDVDD	true:DVDD设为0V进入待机模式，  false:无需把DVDD进入0V
	\param[in] uiDelay	进入待机模式后延时uiDelay ms之后再测待机电流
	\param[in] uiAverageTimes 取uiAverageTimes次数据，然后求平均
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa   HisFX3GetStandbyCurrent,  HisFX3GetWorkCurrent_S2, HisFX3GetWorkCurrent, _HisFX3_Platform_VoltFlag,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetStandbyCurrent_S2(float& flAVDD, float& flDVDD, float& flDOVDD, float& flAF, float& flPOW, unsigned int uiFlag = 0xFF, \
		bool bPWND = true, bool bReset = true, bool bMCLK = true, bool bDVDD = false, unsigned int uiDelay = 5000, unsigned int uiAverageTimes = 7);

	int HisFX3VlotageCalibration();


	//! 正向对地开路测试
	/*!
	\param[in] ucSwitch   0：测试第一路MIPI  1：测试并口	2：测试第二路MIPI  3: CPHY
	\param[inout]   vectorConfigconst  配置要进行开路测试的PIN脚
	\param[in] cuiCurrentWaitTime 电流稳定时间：cuiCurrentWaitTime (ms)
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3OSNegtiveTest,  HisFX3OSShortTest, HisFX3OSOhmTest, _HisFX3Platform_ErrorCode
	*/
	int HisFX3OSPositiveTest(unsigned char ucSwitch, std::vector<_HisFX3OS_Positive_Item>& vectorConfigconst, const unsigned int cuiCurrentWaitTime = 4);

	//! 负向对DOVDD开路测试
	/*!
	\param[in] ucSwitch   0：测试第一路MIPI  1：测试并口	2：测试第二路MIPI
	\param[inout]   vectorConfig  配置要进行测试的PIN脚
	\param[in] cuiCurrentWaitTime 电流稳定时间：cuiCurrentWaitTime (ms)
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  _HisFX3OS_Positive_Item,  HisFX3OSShortTest, HisFX3OSOhmTest, _HisFX3Platform_ErrorCode
	*/
	int HisFX3OSNegtiveTest(unsigned char ucSwitch, std::vector<_HisFX3OS_Negtive_Item>& vectorConfig, const unsigned int cuiCurrentWaitTime = 4);

	//! 短路测试
	/*!
	\param[in] ucSwitch   0：测试第一路MIPI  1：测试并口	2：测试第二路MIPI
	\param[inout]   vectorConfig  配置要进行测试的PIN脚
	\param[in] cuiCurrentWaitTime 电流稳定时间：cuiCurrentWaitTime (ms)
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  _HisFX3OS_Positive_Item,  HisFX3OSNegtiveTest, HisFX3OSOhmTest, _HisFX3Platform_ErrorCode
	*/
	int HisFX3OSShortTest(unsigned char ucSwitch, std::vector<_HisFX3OS_Short_Item>& vectorConfig, const unsigned int cuiCurrentWaitTime = 4);

	//! 开路测试
	/*!
	\param[in] ucSwitch   0：测试MIPI  1：测试并口
	\param[inout]   vectorConfig  配置要进行测试的PIN脚
	\param[in] cuiCurrentWaitTime 电流稳定时间：cuiCurrentWaitTime (ms)
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  _HisFX3OS_Positive_Item,  HisFX3OSNegtiveTest, HisFX3OSShortTest, HisFX3OSOhmTest, _HisFX3Platform_ErrorCode
	*/
	int HisFX3OSOpenTest(unsigned char ucSwitch, std::vector<_HisFX3OS_Open_Item>& vectorConfig, unsigned int cuiCurrentWaitTime);


	//! 阻值测试
	/*!
	\param[in] ucSwitch   0：测试第一路MIPI  1：测试并口	2：测试第二路MIPI
	\param[inout]   stConfig  配置要进行测试的PIN脚
	\param[in] flCurrent 测试阻值时所用的电流， 设为0.0则为1.3mA, 一般可以保持默认值
	\param[in] cuiCurrentWaitTime 电流稳定时间：cuiCurrentWaitTime (ms)
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  _HisFX3OS_Positive_Item,  HisFX3OSNegtiveTest, HisFX3OSOhmTest, _HisFX3Platform_ErrorCode
	*/
	int HisFX3OSOhmTest(unsigned char ucSwitch, _HisFX3OS_OHM_Item& stConfig, float flCurrent = 0.0f, const unsigned int cuiCurrentWaitTime = 4);

	//! 设置通道1的输出IO的电平
	/*!
	\param[in] uiStatus  Bit0: 设置Out0电平 1-高电平，0-低电平； 以此类推...
	\param[in] uiFlag  Bit0: 是否要设置Out0电平 1-要设置，0-不设置； 以此类推...
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3IO_OutPortRead, HisFX3IO_InPortRead
	*/
	int HisFX3IO_OutPortWrite(unsigned int uiStatus, unsigned int uiFlag = 0xFF);

	//! 设置通道2的输出IO的电平
	/*!
	\param[in] uiStatus  Bit0: 设置Out0电平 1-高电平，0-低电平； 以此类推...
	\param[in] uiFlag  Bit0: 是否要设置Out0电平 1-要设置，0-不设置； 以此类推...
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3IO_OutPortRead_S2, HisFX3IO_InPortRead_S2
	*/
	int HisFX3IO_OutPortWrite_S2(unsigned int uiStatus, unsigned int uiFlag = 0xFF);

	//! 获取通道1输出IO口的电平状态
	/*!
	\param[in] uiStatus  Bit0: Out0电平 1-高电平，0-低电平； 以此类推...
	\param[in] uiFlag  Bit0: 是否要获取Out0电平 1-要获取，0-不获取； 以此类推...
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3IO_OutPortWrite, HisFX3IO_InPortRead
	*/
	int HisFX3IO_OutPortRead(unsigned int& uiStatus, unsigned int uiFlag = 0xFF);

	//! 获取通道2输出IO口的电平状态
	/*!
	\param[in] uiStatus  Bit0: Out0电平 1-高电平，0-低电平； 以此类推...
	\param[in] uiFlag  Bit0: 是否要获取Out0电平 1-要获取，0-不获取； 以此类推...
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3IO_OutPortWrite_S2, HisFX3IO_InPortRead_S2
	*/
	int HisFX3IO_OutPortRead_S2(unsigned int& uiStatus, unsigned int uiFlag = 0xFF);

	//! 获取通道1输入IO口的电平状态
	/*!
	\param[in] uiStatus  Bit0: In0电平 1-高电平，0-低电平； 以此类推...
	\param[in] uiFlag  Bit0: 是否要获取In0电平 1-要获取，0-不获取； 以此类推...
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3IO_OutPortWrite, HisFX3IO_OutPortRead
	*/
	int HisFX3IO_InPortRead(unsigned int& uiStatus, unsigned int uiFlag = 0xFF);

	//! 获取通道2输入IO口的电平状态
	/*!
	\param[in] uiStatus  Bit0: In0电平 1-高电平，0-低电平； 以此类推...
	\param[in] uiFlag  Bit0: 是否要获取In0电平 1-要获取，0-不获取； 以此类推...
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3IO_OutPortWrite_S2, HisFX3IO_OutPortRead_S2
	*/
	int HisFX3IO_InPortRead_S2(unsigned int& uiStatus, unsigned int uiFlag = 0xFF);

	int HisFX3LedControl(bool bOn, unsigned int* puiKey = 0);

	int HisFX3BuzzerControl(bool bOn, unsigned int* puiKey = 0);

	int getOSPinNameList(unsigned char ucSwitch, std::vector<std::string>& vecOSPin);
	int getOSPositiveGNDPinName(unsigned char ucSwitch, std::vector<std::string>& vecOSPin);
	int getOSNegtiveDOVDDPinName(unsigned char ucSwitch, std::vector<std::string>& vecOSPin);

	/*
	int HisFX3GetContinusFrames(bool bC1, bool bC2, unsigned int& uiFrameCount, unsigned int uiBufByte1=0, unsigned char** ppBuffer1=0, unsigned int uiBufByte2=0, unsigned char** ppBuffer2=0);
	*/

	int HIsFX3ReadVoltageValue(float* pflDOVDD = 0, float* pflAVDD = 0, float* pflDVDD = 0, float* pflAF = 0, float* pflVFuse = 0, float* pflPOW = 0);
	int HIsFX3ReadVoltageValue_S2(float* pflDOVDD = 0, float* pflAVDD = 0, float* pflDVDD = 0, float* pflAF = 0, float* pflVFuse = 0, float* pflPOW = 0);

	int HisFX3UpdateFPGA(char* pstrPath);
	int HisFX3SetOffLineMode(bool bEnable, char* path);
	bool HisFX3GetOfflineModeInfo(unsigned int* puiWidth, unsigned int* puiHeight, _HisFX3_BaylorMode* pucDataformat, unsigned int* puiFrameByte);
	int HisFX3SetOffLineMode_S2(bool bEnable, char* path);
	bool HisFX3GetOfflineModeInfo_S2(unsigned int* puiWidth, unsigned int* puiHeight, _HisFX3_BaylorMode* pucDataformat, unsigned int* puiFrameByte);
	void getFPGADecodeInfo(std::string& strInfo);
	void getFPGADecodeInfo_S2(std::string& strInfo);
	int GetTemperature(double* fpgaT);
	void getProtocalSupported(std::vector<unsigned int>& vecList, bool bChannel1 = true);
	int getDataFormatSupported(std::vector<_HisFX3_BaylorMode>& vecDataFormat);
	bool isWorkCurrentSupported(unsigned int uiFlag, bool bChannel1 = true);
	bool isStandbyCurrentSupported(unsigned int uiFlag, bool bChannel1 = true);
	bool isOpenShortSupported(bool* bAllPin);
	bool getVoltageSupported(float& flmin, float& flmax, unsigned int uiFlag, bool bChannel1 = true);
	bool getCommunicationProtocalSupported(unsigned int uiFlag, bool bChannel1 = true);
	void getMCLKSupported(float& flmin, float& flmax);
	bool getDDRSupported();
	unsigned int getCameraCountSupported();
	_HisFX3_Platform_Type getCurrentPlatformType();

	//! 设置USB包的大小
	/*!
	\param[in] lsize   单位：Byte  范围：256*1024~4*1024*1024  注意必须是256*1024的整数倍
	\sa  getCurrentBulkTransformSize
	*/
	void setBulkTransformSize(int lsize);

	//! 设置当前USB包的大小
	/*!
	\return 包的大小，单位：Byte
	\sa  setBulkTransformSize
	*/
	int getCurrentBulkTransformSize();

	//! 获取通道1摄像头Sensor输出端帧索引
	/*!
	\return 帧索引
	\sa  getSensorFrameIndex_S2, getUploadFrameIndex, getUploadFrameIndex_S2
	*/
	unsigned __int64 getSensorFrameIndex();

	//! 获取通道2摄像头Sensor输出端帧索引
	/*!
	\return 帧索引
	\sa  getSensorFrameIndex, getUploadFrameIndex, getUploadFrameIndex_S2
	*/
	unsigned __int64 getSensorFrameIndex_S2();

	//! 获取通道1摄像头Sensor错误帧索引
	/*!
	\return 帧索引
	\sa  getSensorFrameIndex_S2, getUploadFrameIndex, getUploadFrameIndex_S2
	*/
	unsigned __int64 getErrorFrameIndex();

	//! 获取通道1摄像头Sensor错误帧索引
	/*!
	\return 帧索引
	\sa  getSensorFrameIndex_S2, getUploadFrameIndex, getUploadFrameIndex_S2
	*/
	unsigned __int64 getErrorFrameIndex_S2();

	//! 获取通道1上传帧索引
	/*!
	\return 帧索引
	\sa  getUploadFrameIndex_S2, getSensorFrameIndex, getSensorFrameIndex_S2
	*/
	unsigned __int64 getUploadFrameIndex();

	//! 获取通道2上传帧索引
	/*!
	\return 帧索引
	\sa  getUploadFrameIndex, getSensorFrameIndex, getSensorFrameIndex_S2
	*/
	unsigned __int64 getUploadFrameIndex_S2();


	void setCurrentPlatformType(_HisFX3_Platform_Type platformType);

	//! 设置USB传输速率
	/*!
	\param[in] uiDelay   范围：10~240 时钟周期， 越小速率越大
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  _HisFX3Platform_ErrorCode
	*/
	int setUSBSpeed(unsigned int uiDelay);

	int LedControl(bool bOn);
	int BuzzerControl(bool bOn);


	/*! 获取错误信息的字符串描述 */
	const char* GetLastError(void);

	bool HisFX3IsOpenLight();



	/************************SUNNY**************************/
	//-------------------------------------新增接口动态改变图像尺寸-------------------------------------------
	int HisFX3ChangeImageSize(unsigned int ucDataFormat, unsigned int uiWidth, unsigned int uiHeight);
	int HisFX3ChangeImageSize_S2(unsigned int ucDataFormat, unsigned int uiWidth, unsigned int uiHeight);

	//新增工装静态电流
	int HisFX3WriteStaticCurrent(bool bWorkCurrent, float flAVDD, float flDVDD, float flDOVDD, float flAF, float flVFuse, float flPOW);
	int HisFX3WriteStaticCurrent_S2(bool bWorkCurrent, float flAVDD, float flDVDD, float flDOVDD, float flAF, float flVFuse, float flPOW);
	int HisFX3ReadStaticCurrent(bool bWorkCurrent, float &flAVDD, float &flDVDD, float &flDOVDD, float &flAF, float &flVFuse, float &flPOW);
	int HisFX3ReadStaticCurrent_S2(bool bWorkCurrent, float &flAVDD_S2, float &flDVDD_S2, float &flDOVDD_S2, float &flAF_S2, float &flVFuse_S2, float &flPOW_S2);
	int HisFX3WriteEEpromFlag(unsigned int uiFlag);
	int HisFX3ReadEEpromFlag(unsigned int &uiFlag);

	int HisFX3SetMIPILane(unsigned char ucLane, bool bDVP_VS_ActiveHigh = false, bool bDVP_HS_ActiveHigh = true);
	int HisFX3GetMIPILane(unsigned char* pucLane, bool* pbDVP_VS_ActiveHigh = NULL, bool* pbDVP_HS_ActiveHigh = NULL);
	int HisFX3SetMIPILane_S2(unsigned char ucLane);
	int HisFX3GetMIPILane_S2(unsigned char* pucLane);
	int HisFX3GetHardGeneration(unsigned int* puiGernation);
	int HisFX3WriteOSIIC(unsigned char ucSlave, unsigned int uiReg, unsigned int uiData, unsigned short usType = 0x1632);
	int HisFX3ReadOSIIC(unsigned char ucSlave, unsigned int uiReg, unsigned int* puiData, unsigned short usType = 0x1632);
	int HisFX3R2OSSwitch(bool bOS);
	int HisFX3R2OSCalibration(unsigned int* puiKey, _HisFX3R2_OSCal_Item* pstCal, unsigned int uiItemCount);
	int HisFX3SetOSCalData(_HisFX3R2_OSCal_Item* pstCal, unsigned int uiItemCount);
	int HisFX3SetGPIO(unsigned short usIO1, unsigned short usIO2);
	int HisFX3GetGPIO(unsigned short* pusIO1, unsigned short* pusIO2);
	int HisFX3OSPositiveTest(unsigned char ucSwitch, _HisFX3OS_Positive_Item* vectorConfig, unsigned int uiItemCount, unsigned int cuiCurrentWaitTime = 2);
	int HisFX3OSNegtiveTest(unsigned char ucSwitch, _HisFX3OS_Negtive_Item* vectorConfig, unsigned int uiItemCount, unsigned int cuiCurrentWaitTime = 2);
	int HisFX3OSShortTest(unsigned char ucSwitch, _HisFX3OS_Short_Item* vectorConfig, unsigned int uiItemCount, unsigned int cuiCurrentWaitTime = 2);
	int HisFX3OSOpenTest(unsigned char ucSwitch, _HisFX3OS_Open_Item* vectorConfig, unsigned int uiItemCount, unsigned int cuiCurrentWaitTime = 2);
	int HisFX3OSPositiveTestOld(unsigned char ucSwitch, _HisFX3OS_Positive_Item* vectorConfig, unsigned int uiItemCount, unsigned int cuiCurrentWaitTime = 2);
	int HisFX3OSNegtiveTestOld(unsigned char ucSwitch, _HisFX3OS_Negtive_Item* vectorConfig, unsigned int uiItemCount, unsigned int cuiCurrentWaitTime = 2);
	int HisFX3OSShortTestOld(unsigned char ucSwitch, _HisFX3OS_Short_Item* vectorConfig, unsigned int uiItemCount, unsigned int cuiCurrentWaitTime = 2);
	int HisFX3OSOhmTestOld(unsigned char ucSwitch, _HisFX3OS_OHM_Item& stConfig, float flCurrent = 0.0f, const unsigned int cuiCurrentWaitTime = 4);
	int HisFX3WriteMIPIIICAPI(unsigned char ucSlave, unsigned int uiReg, unsigned int uiData, unsigned short usType);
	int HisFX3ReadMIPII2CAPI(unsigned char ucSlave, unsigned int uiReg, unsigned int* puiData, unsigned short usType);
	int HisFX3GetContinusFrames(bool bC1, bool bC2, unsigned int& uiFrameCount, unsigned int uiBufByte1 = 0, unsigned char** ppBuffer1 = 0, unsigned int uiBufByte2 = 0, unsigned char** ppBuffer2 = 0);
	int HisFX3GetDeivceCount();
	int HIsFX3ReadVoltageValue(float* pflAVDD, float* pflDVDD, float* pflDOVDD, float* pflAF, float* pflVFuse, float* pflPOW, unsigned int uiFlag);
	int HIsFX3ReadVoltageValue_S2(float* pflAVDD, float* pflDVDD, float* pflDOVDD, float* pflAF, float* pflVFuse, float* pflPOW, unsigned int uiFlag);
	int HisFX3SetDataMode(unsigned char ucdataformat, unsigned int uiWidth, unsigned int uiHeight);
	int HisFX3ImageDataOnOff_S2(bool bOn);
	int HisFX3ImageDataOnOff(bool bOn);
	int HisFX3GetFPGAFrameRate(float* pflRateMIPI1 = 0, float* pflRateMIPI2 = 0, float* pflRateDVP = 0, float* pflRateLVDS = 0, unsigned int uiDelay = 1000);
	int HisFX3GetMIPIInfo(bool& bDataValid, unsigned char& ucDataType, unsigned char& ucLaneNum, unsigned int& uiFrameCount, unsigned int& uiErrorFrameCount, \
		unsigned int& uiVitual0LineCount, unsigned int& uiVitual1LineCount);
	int HisFX3GetMIPIInfo_S2(bool& bDataValid, unsigned char& ucDataType, unsigned char& ucLaneNum, unsigned int& uiFrameCount, unsigned int& uiErrorFrameCount, \
		unsigned int& uiVitual0LineCount, unsigned int& uiVitual1LineCount);
	void setTransfromSize(unsigned int uiSize = 4194304);
	int HisFX3WriteNoneLoadingCurrentValue(bool bS2, float fCurrent[8][5]);
	int HisFX3ReadNoneLoadingStaticCurrent(bool bS2, float fVolVcm, float fVolAvdd, float fVolDvdd, float fVolDovdd, float fVolPow, float &flAF, float &flAVDD, float &flDVDD, float &flDOVDD, float &flPOW);
	int HisFX3GetVolt(unsigned char* pucDOVDD = NULL, unsigned char* pucAVDD = NULL, unsigned char* pucDVDD = NULL, unsigned char* pucAF = NULL, unsigned char* pucVFuse = NULL);
	int HisFX3GetVolt_S2(unsigned char* pucDOVDD = NULL, unsigned char* pucAVDD = NULL, unsigned char* pucDVDD = NULL, unsigned char* pucAF = NULL, unsigned char* pucVFuse = NULL);
	int HisFX3SetVFuseVolt(unsigned char ucVFUSE);
	int HisFX3GetVFuseVolt(unsigned char* pucVFUSE);
	int HisFX3SetVFuseVolt_S2(unsigned char ucVFUSE);
	int HisFX3GetVFuseVolt_S2(unsigned char* pucVFUSE);
	/************************SUNNY**************************/


	int boxIndex;

private:
	int cc;
	int bulkSize;
	void PreviewCfpCpp2C(_HisFX3_PreviewStructCpp* cppcfg, _HisFX3_PreviewStruct* ccfg);
	double mclkSetted[2];
	_HisFX3_PreviewStruct pcfg[2];
};

#endif
