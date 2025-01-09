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
    this->__OpenCamera();
}

void Camera::HikCamera::__EnumDevices() {
    // 枚举相机设备
    spdlog::info("retriving available cam list ...");
    std::memset(&this->m_devicelist, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
    int nResult = MV_CC_EnumDevices(
        MV_GIGE_DEVICE | MV_USB_DEVICE, &this->m_devicelist
    );
    if (nResult != MV_OK) {
        spdlog::critical("retrieving fails.");
        exit(-1);
    }
    spdlog::info("retrieving succeed");
}

void Camera::HikCamera::__DebugDevices() {
    // 相机的设备 ID
    spdlog::info("finding Hik Camera");
    if (m_devicelist.nDeviceNum == 0) {
        spdlog::critical("no device found.");
        exit(-1);
    }
    for (int i = 0, n = m_devicelist.nDeviceNum; i < n; i++) {
        MV_CC_DEVICE_INFO *pDeviceInfo = m_devicelist.pDeviceInfo[i];
        spdlog::info("checking device {}", i);
        if (pDeviceInfo == nullptr) break;
        this->__PrintDeviceInfo(pDeviceInfo);
        camIndex = i;
    }
    spdlog::info("finding succeed");
}

void Camera::HikCamera::__PrintDeviceInfo(MV_CC_DEVICE_INFO *pDeviceInfo) {
    if (pDeviceInfo == nullptr) { // 设备不存在
        spdlog::critical("device info pointer is null.");
        exit(-1);
    }

    if (pDeviceInfo->nTLayerType == MV_USB_DEVICE) { // USB 相机
        spdlog::info("device type: USB");
    } else if (pDeviceInfo->nTLayerType == MV_GIGE_DEVICE) {
        spdlog::info("device type: GIGE");
    } else {
        spdlog::error("unknown device type, cannot continue");
        exit(-1);
    }
}

void Camera::HikCamera::__CreateHandle() {
    spdlog::info("creating handle for camera {}", this->camIndex);
    int result = MV_CC_CreateHandle(
        &this->handle, m_devicelist.pDeviceInfo[camIndex]
    );
    if (result != MV_OK) {
        spdlog::critical("critical creating handle");
        exit(-1);
    }
    spdlog::info("create success");
}

void Camera::HikCamera::__OpenCamera() {
    spdlog::info("opening camera");
    int result = MV_CC_OpenDevice(this->handle);
    if (result != MV_OK) {
        spdlog::critical("open camera fails");
        exit(-1);
    }
    spdlog::info("open succeed");
}