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

enum class ImageSource { HikCamera, WebCam, ImageFolder, Video };

/**
 * @brief
 *
 */
struct ImageConfig {
    ImageSource srcType;
    std::string pathToImageSrc;

    int frameWidth, frameHeight;

    cv::Mat cameraMatrix; // 相机内参矩阵
    cv::Mat distCoeffs;   // 畸变系数
    double exposureTime;  // 曝光时间

    bool enableGamma;
    double gamma;

    std::string pixelFormat;
};

#endif