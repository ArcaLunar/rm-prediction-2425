/**
 * @file VideoCapture.hpp
 * @author arca@connect.hku.hk
 * @brief 相机采集模块
 * @version 0.1
 * @date 2025-01-07
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __VIDEO_CAPTURE_HPP__
#define __VIDEO_CAPTURE_HPP__

#include "CameraParams.h"

namespace Camera {

class CapturerBase {};

enum HikCameraProperties {
    CAP_PROP_FRAMERATE_ENABLE,  // 帧数可调
    CAP_PROP_FRAMERATE,         // 帧数
    CAP_PROP_BURSTFRAMECOUNT,   // 外部一次触发帧数
    CAP_PROP_HEIGHT,            // 图像高度
    CAP_PROP_WIDTH,             // 图像宽度
    CAP_PROP_EXPOSURE_TIME,     // 曝光时间
    CAP_PROP_GAMMA_ENABLE,      // 伽马因子可调
    CAP_PROP_GAMMA,             // 伽马因子
    CAP_PROP_GAINAUTO,          // 亮度
    CAP_PROP_SATURATION_ENABLE, // 饱和度可调
    CAP_PROP_SATURATION,        // 饱和度
    CAP_PROP_OFFSETX,           // X偏置
    CAP_PROP_OFFSETY,           // Y偏置
    CAP_PROP_TRIGGER_MODE,      // 外部触发
    CAP_PROP_TRIGGER_SOURCE,    // 触发源
    CAP_PROP_LINE_SELECTOR      // 触发线

};

/**
 * @brief 一个 HikCamera 类只负责一个相机
 *
 */
class HikCamera : CapturerBase {
  private:
    /// \brief 枚举所有已连接的设备
    void __EnumDevices();

    /// \brief 输出所有设备的信息
    void __DebugDevices();

    /// \brief 打印设备信息
    void __PrintDeviceInfo(MV_CC_DEVICE_INFO *);

    /// \brief 创建用于获取图像的句柄
    void __CreateHandle();

    void __RetrieveImage();

  protected:
    /// \brief 设备列表
    MV_CC_DEVICE_INFO_LIST m_devicelist;
    unsigned int camIndex;
    void *handle;

  public:
    HikCamera();
};

}; // namespace Camera

#endif