#include "MvCameraControl.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <spdlog/spdlog.h>

void __stdcall ImageCallback(unsigned char *pData,
                             MV_FRAME_OUT_INFO_EX *pFrameInfo,
                             void *pUser) {
    if (pFrameInfo) {
        // 将相机数据转换为 OpenCV 的 Mat 对象
        cv::Mat img(
            pFrameInfo->nHeight, pFrameInfo->nWidth, CV_8UC3, pData);
        // 显示图像
        cv::imshow("Camera Stream", img);
        // 等待 1ms，确保窗口可以刷新
        cv::waitKey(1);
    }
}

int main() {
    spdlog::info("start calibrating");
    int nRet     = MV_OK;
    void *handle = NULL;
    MV_CC_DEVICE_INFO_LIST stDeviceList;
    memset(&stDeviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));

    // 枚举设备
    spdlog::info("looking for devices");
    nRet =
        MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDeviceList);
    if (MV_OK != nRet) {
        spdlog::error("finding devices failed! nRet {}", nRet);
        return -1;
    }

    spdlog::info("found {} devices", stDeviceList.nDeviceNum);
    if (stDeviceList.nDeviceNum == 0) {
        spdlog::error("no device found!");
        return -1;
    }

    // 选择第一个设备
    MV_CC_DEVICE_INFO *pDeviceInfo = stDeviceList.pDeviceInfo[0];
    spdlog::info("device found");
    if (NULL == pDeviceInfo) {
        spdlog::error("device info is NULL!");
        return -1;
    }

    // 创建设备句柄
    nRet = MV_CC_CreateHandle(&handle, pDeviceInfo);
    spdlog::info("create handle");
    if (MV_OK != nRet) {
        spdlog::error("create handle failed! nRet {}", nRet);
        return -1;
    }

    // 打开设备
    nRet = MV_CC_OpenDevice(handle);
    spdlog::info("open device");
    if (MV_OK != nRet) {
        spdlog::error("open device failed! nRet {}", nRet);
        return -1;
    }

    // 开始采集图像
    nRet = MV_CC_RegisterImageCallBackEx(handle, ImageCallback, NULL);
    spdlog::info("register image callback");
    if (MV_OK != nRet) {
        spdlog::error("register image callback failed! nRet {}", nRet);
        return -1;
    }

    nRet = MV_CC_StartGrabbing(handle);
    spdlog::info("start grabbing");
    if (MV_OK != nRet) {
        spdlog::error("start grabbing failed! nRet {}", nRet);
        return -1;
    }

    // 创建窗口
    cv::namedWindow("Camera Stream", cv::WINDOW_NORMAL);
    cv::resizeWindow("Camera Stream", 640, 480);
    

    // 等待按键退出
    cv::waitKey(0);

}