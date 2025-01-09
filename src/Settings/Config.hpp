/**
 * @file Constants.hpp
 * @author arca@connect.hku.hk
 * @brief 定义了一些常量
 * @version 0.1
 * @date 2025-01-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __CONSTANTS_HPP__
#define __CONSTANTS_HPP__

// true = 打印调试信息
#define DEBUG true

#include <opencv2/core/core.hpp>
#include <string>

enum class AimingMode {

};

/**
 * @brief
 *
 */
namespace Camera {

struct CameraConfig {
    bool AcquisitionFrameRateEnable;
    int AcquisitionFrameRate;

    int Width, Height;
    double exposure_time;

    bool adjustable_gamma;
    int gamma;

    int gain_auto;

    bool adjustable_saturation;
    int saturation;

    int offset_x, offset_y;

    int TriggerMode;
    int TriggerSource;
    int line_selector;
    int PayloadSize;
};

}; // namespace Camera
struct ImageConfig {
    int frameWidth, frameHeight;

    cv::Mat cameraMatrix; // 相机内参矩阵
    cv::Mat distCoeffs;   // 畸变系数
    double exposureTime;  // 曝光时间

    bool enableGamma;
    double gamma;

    std::string pixelFormat;
};

#endif