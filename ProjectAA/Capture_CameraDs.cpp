#include "pch.h"
//#include "Capture.h"
//#include "CameraDS.h"
//#include "SystemLog.h"
//#include "SystemManager.h"
//
//extern CSystemManager    gSystemMgr;
//extern CSystemLog     gSystemLog;
//
//CCameraDS			CamDS;
//
//int CameraDs::init(void)
//{
//	iDevID = gSystemMgr.m_nCtsId;
//	CString cstrLog;
//	cstrLog.Format(L"init id:%d", iDevID);
//	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
//	return TRUE;
//}
//
//int CameraDs::run()
//{
//	int result = TRUE;
//	int cam_cnt = CCameraDS::CameraCount();
//	CString cstrLog;
//	if (cam_cnt <= 0) {
//		cstrLog.Format(L"There is no camera connected.");
//		gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
//		result = FALSE;
//	}
//	else {
//		result = TRUE;
//		cstrLog.Format(L"Find %d camera connected.", cam_cnt);
//		gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
//
//		//if (cam_cnt < 5) {
//		//	MessageBox(HWND_MAIN, "JBSC产品出图USB口连接错误！", "Error", 1);
//		//	return FALSE;
//		//}
//		char cam_name[1024] = { 0 };
//		int rt_val = CamDS.CameraName(iDevID, cam_name, sizeof(cam_name));
//		if (rt_val > 0) {
//			cstrLog.Format(L"camera name is %s", cam_name);
//			gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
//		}
//		else {
//			cstrLog.Format(L"can not get camera name.");
//			gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
//			result = FALSE;
//		}
//	}
//	//iImgHeight = capturedlg.ImgH;
//	//iImgWidth = capturedlg.ImgW; m_nWidth; m_nHeight
//	result = CamDS.OpenCamera(iDevID, FALSE, iImgWidth, iImgHeight);
//	iImgWidth = CamDS.GetWidth();
//	iImgHeight = CamDS.GetHeight();
//	cstrLog.Format(L"Open Cam:%d, web w:%d, h:%d,result:%d---------------------------------", iDevID, iImgWidth, iImgHeight, result);
//	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
//
//	if (result == TRUE) {
//		CamDS.QueryFrame();
//	}
//
//	return result;
//}
//
//int CameraDs::cap(void)
//{
//	int result = TRUE;
//	IplImage *frame;
//	frame = CamDS.QueryFrame();
//	//memcpy(buf, (BYTE *)(s_aa::frame), WEB_CAM_WIDTH * WEB_CAM_HEIGHT * 3);
////	s_aa::frame.convert
//	//for (int i = 0; i < WEB_CAM_HEIGHT; i++) {
//	//	memcpy(buf, (BYTE *)(s_aa::frame->imageData), WEB_CAM_WIDTH * 3);
//	//}
//	return result;
//}
//
//int CameraDs::stop()
//{
//	CamDS.CloseCamera();
//	//release();
//	CString cstrLog;
//	cstrLog.Format(L"close camera.");
//	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
//	return TRUE;
//}
//
//int CameraDs::destroy()
//{
//
//	return TRUE;
//}