#include "VideoCapture.hpp"
#include "CameraParams.h"
#include "MvCameraControl.h"
#include <spdlog/spdlog.h>

#include <cstring>

Camera::HikCamera::HikCamera() {
    // 枚举设备
    this->__EnumDevices();
    // 输出设备信息
    this->__DebugDevices();
    this->__CreateHandle();
}

void Camera::HikCamera::__EnumDevices() {
    // 枚举相机设备
    std::memset(&this->m_devicelist, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
    int nResult = MV_CC_EnumDevices(
        MV_GIGE_DEVICE | MV_USB_DEVICE, &this->m_devicelist
    );
    if (nResult != MV_OK) {
        spdlog::error("enum devices failed.");
        exit(-1);
    }
}

void Camera::HikCamera::__DebugDevices() {
    // 相机的设备 ID
    if (m_devicelist.nDeviceNum == 0) {
        spdlog::error("no device found.");
        exit(-1);
    }
    for (int i = 0, n = m_devicelist.nDeviceNum; i < n; i++) {
        MV_CC_DEVICE_INFO *pDeviceInfo = m_devicelist.pDeviceInfo[i];
        spdlog::info("checking device {}", i);
        if (pDeviceInfo == nullptr) break;
        this->__PrintDeviceInfo(pDeviceInfo);
        camIndex = i;
    }
}

void Camera::HikCamera::__PrintDeviceInfo(MV_CC_DEVICE_INFO *pDeviceInfo) {
    if (pDeviceInfo == nullptr) { // 设备不存在
        spdlog::error("device info pointer is null.");
        exit(-1);
    }

    if (pDeviceInfo->nTLayerType == MV_USB_DEVICE) { // USB 相机
        spdlog::info("device type: USB");
    } else if (pDeviceInfo->nTLayerType == MV_GIGE_DEVICE) {
        spdlog::info("device type: GIGE");
    } else {
        spdlog::error("unknown device type.");
        exit(-1);
    }
}

void Camera::HikCamera::__CreateHandle() {
    spdlog::info("creating handle for camera {}", this->camIndex);
    int result = MV_CC_CreateHandle(
        &this->handle, m_devicelist.pDeviceInfo[camIndex]
    );
    if (result != MV_OK) {
        spdlog::critical("error creating handle");
        exit(-1);
    }
    spdlog::info("create success");
}