#include "VideoCapture.hpp"
#include "CameraParams.h"
#include "MvCameraControl.h"
#include "PixelType.h"
// #include "MvObsoleteInterfaces.h"
#include <atomic>
#include <cstddef>
#include <cstdio>
#include <opencv2/core/persistence.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <pthread.h>
#include <spdlog/spdlog.h>

#include <cstring>
#include <string>
#include <unistd.h>

constexpr char ConfigFilePath[] = "../../config/camera_config.json";

Camera::HikCamera::HikCamera() {
    // 初始化 SDK
    MV_CC_Initialize();
    // 枚举设备
    this->__EnumDevices();
    // 输出设备信息
    this->__DebugDevices();
    // 创建句柄
    this->__CreateHandle();
    // 打开相机
    this->__OpenCamera();
    // 设置相机参数
    this->__Setup();
    // 初始化图像捕获，准备捕获图像
    this->__InitRetrieveImage();
}

Camera::HikCamera::~HikCamera() {
    spdlog::info("exiting......");
    // 停止捕获图像
    spdlog::info("stop retrieving image");
    int result = MV_CC_StopGrabbing(this->m_handle);
    if (result != MV_OK) spdlog::critical("error stopping");
    spdlog::info("stop succeed");

    // 关闭相机
    spdlog::info("closing camera");
    result = MV_CC_CloseDevice(this->m_handle);
    if (result != MV_OK) spdlog::critical("error closing");
    spdlog::info("close succeed");

    // 销毁句柄
    spdlog::info("destroying handle");
    result = MV_CC_DestroyHandle(this->m_handle);
    if (result != MV_OK) spdlog::critical("error destroying");
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

cv::Mat Camera::HikCamera::ConvertRawToMat(
    MV_FRAME_OUT_INFO_EX *pstImageInfo, MV_FRAME_OUT *pstImage
) {
    cv::Mat result;
    auto mark = pstImageInfo->enPixelType;
    decltype(CV_8UC1) channel_type;
    decltype(cv::COLOR_BayerGB2RGB) transform_type;

    if (mark == PixelType_Gvsp_BayerGB8) {
        channel_type   = CV_8UC1;
        transform_type = cv::COLOR_BayerRG2RGB;
    } else if (mark == PixelType_Gvsp_BGR8_Packed) {
        channel_type   = CV_8UC3;
        transform_type = cv::COLOR_BGR2GRAY;
    } else if (mark == PixelType_Gvsp_BayerGB8) {
        channel_type   = CV_8UC1;
        transform_type = cv::COLOR_BayerGB2RGB;
    } else spdlog::error("unsupported pixel format");

    cv::Mat src(
        pstImageInfo->nHeight,
        pstImageInfo->nWidth,
        channel_type,
        pstImage->pBufAddr
    );
    if (transform_type == cv::COLOR_BGR2GRAY) result = src;
    else cv::cvtColor(src, result, transform_type);

    return result;
}

void Camera::HikCamera::__LoadConfig() {
    // ! 打开配置文件
    cv::FileStorage fs(ConfigFilePath, cv::FileStorage::READ);
    spdlog::info("reading from .config");

    fs["width"] >> this->m_config.Width;
    fs["height"] >> this->m_config.Height;
    spdlog::info(
        "reading from config: W={}, H={}",
        this->m_config.Width,
        this->m_config.Height
    );

    fs["TriggerMode"] >> this->m_config.TriggerMode;
    fs["AcquisitionFrameRateEnable"] >>
        this->m_config.AcquisitionFrameRateEnable;
}

void Camera::HikCamera::__Setup() {
    __LoadConfig();

    // 辅助匿名函数
    auto SetAttr = [&](std::string attr, auto val) {
        spdlog::info("setting camera, {} -> {}", attr, val);
        int result = MV_CC_SetEnumValue(this->m_handle, attr.c_str(), val);
        if (result != MV_OK)
            spdlog::critical("setting {} to {} failed", attr, val);
        spdlog::info("setting {} to {} succeeded.", attr, val);
    };

    // Trigger mode 设置为 off
    SetAttr("TriggerMode", this->m_config.TriggerMode);
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
// !! 以下为测试用代码

std::atomic_bool flag{false};
void *work(void *pUser) {
    int nRet                 = MV_OK;
    MV_FRAME_OUT stImageInfo = {0};
    memset(&stImageInfo, 0, sizeof(MV_FRAME_OUT));
    while (1) {
        if (flag) break;
        nRet = MV_CC_GetImageBuffer(pUser, &stImageInfo, 1000);

        if (nRet != MV_OK) {
            spdlog::warn("No data.");
            continue;
        }

        spdlog::info(
            "get one frame, w={} h={} #frame={}",
            stImageInfo.stFrameInfo.nExtendWidth,
            stImageInfo.stFrameInfo.nExtendHeight,
            stImageInfo.stFrameInfo.nFrameNum
        );
        auto img = Camera::HikCamera::ConvertRawToMat(
            &stImageInfo.stFrameInfo, &stImageInfo
        );
        if (img.empty()) spdlog::warn("Empty image.");
        else {
            spdlog::info("captured");
            // cv::imshow("image", img);
            cv::imwrite("test.jpg", img);
        }

        MV_CC_FreeImageBuffer(pUser, &stImageInfo);

        sleep(1);
    }

    return 0;
}

void Camera::HikCamera::TestFunctionality() {
    auto press = [&]() {
        while (getchar() != '\n');
        spdlog::debug("Enter is pressed, exiting");
        flag = true;
    };

    pthread_t pid;
    int result = pthread_create(&pid, NULL, work, this->m_handle);
    if (result != 0) {
        spdlog::info("thread create failed");
        return;
    }
    press();
}