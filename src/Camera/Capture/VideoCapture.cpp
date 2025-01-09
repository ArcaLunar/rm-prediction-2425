#include "VideoCapture.hpp"
#include "CameraParams.h"
#include "MvCameraControl.h"
// #include "MvObsoleteInterfaces.h"
#include <atomic>
#include <cstdio>
#include <pthread.h>
#include <spdlog/spdlog.h>

#include <cstring>
#include <string>
#include <unistd.h>

Camera::HikCamera::HikCamera() {
    MV_CC_Initialize();
    // 枚举设备
    this->__EnumDevices();
    // 输出设备信息
    this->__DebugDevices();
    this->__CreateHandle();
    this->__OpenCamera();
    this->__InitRetrieveImage();
}

Camera::HikCamera::~HikCamera() {
    spdlog::info("exiting......");
    // 停止捕获图像
    spdlog::info("stop retrieving image");
    int result = MV_CC_StopGrabbing(this->m_handle);
    if (result != MV_OK) {
        spdlog::critical("error stopping");
        // exit(-1);
    }
    spdlog::info("stop succeed");

    // 关闭相机
    spdlog::info("closing camera");
    result = MV_CC_CloseDevice(this->m_handle);
    if (result != MV_OK) {
        spdlog::critical("error closing");
        // exit(-1);
    }
    spdlog::info("close succeed");

    spdlog::info("destroying handle");
    result = MV_CC_DestroyHandle(this->m_handle);
    if (result != MV_OK) {
        spdlog::critical("error destroying");
        // exit(-1);
    }
    spdlog::info("destroy succeed");

    // 释放 SDK
    MV_CC_Finalize();

    spdlog::info("exit successfully");
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
    spdlog::info("creating m_handle for camera {}", this->camIndex);
    int result = MV_CC_CreateHandle(
        &this->m_handle, m_devicelist.pDeviceInfo[camIndex]
    );
    if (result != MV_OK) {
        spdlog::critical("critical creating m_handle");
        exit(-1);
    }
    spdlog::info("create success");
}

void Camera::HikCamera::__OpenCamera() {
    spdlog::info("opening camera");
    int result = MV_CC_OpenDevice(this->m_handle);
    if (result != MV_OK) {
        spdlog::critical("open camera fails");
        exit(-1);
    }
    spdlog::info("open succeed");
}

void Camera::HikCamera::__Setup() {
    // 辅助匿名函数
    auto SetAttr = [&](std::string attr, auto val) {
        spdlog::info("setting camera, {} -> {}", attr, val);
        int result = MV_CC_SetEnumValue(this->m_handle, attr.c_str(), val);
        if (result != MV_OK) {
            spdlog::critical("setting {} to {} failed", attr, val);
            exit(-1);
        }
        spdlog::info("setting {} to {} succeeded.", attr, val);
    };

    // Trigger mode 设置为 off
    SetAttr("TriggerMode", 0);
}

void Camera::HikCamera::__InitRetrieveImage() {
    spdlog::info("initializing image retrieving");
    int result = MV_CC_StartGrabbing(this->m_handle);
    if (result != MV_OK) {
        spdlog::critical("initialization fails");
        exit(-1);
    }
    spdlog::info("initialization succeed");
}

/////////////////////////////////////////
// * 以下为测试用代码

std::atomic_bool flag{false};
void *work(void *pUser) {
    int nRet                 = MV_OK;
    MV_FRAME_OUT stImageInfo = {0};
    memset(&stImageInfo, 0, sizeof(MV_FRAME_OUT));
    while (1) {
        if (flag) break;
        nRet = MV_CC_GetImageBuffer(pUser, &stImageInfo, 1000);
        if (nRet == MV_OK) {
            spdlog::info(
                "get one frame, w={} h={} #frame={}",
                stImageInfo.stFrameInfo.nExtendWidth,
                stImageInfo.stFrameInfo.nExtendHeight,
                stImageInfo.stFrameInfo.nFrameNum
            );
            MV_CC_FreeImageBuffer(pUser, &stImageInfo);
        } else {
            spdlog::warn("No data.");
        }
    }

    return 0;
}

void Camera::HikCamera::TestFunctionality() {
    auto press = [&]() {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        spdlog::debug("Press enter to exit");
        while (getchar() != '\n');
        flag = true;
        // sleep(1);
    };

    pthread_t pid;
    int result = pthread_create(&pid, NULL, work, this->m_handle);
    if (result != 0) {
        spdlog::info("thread create failed");
        return;
    }
    press();
}