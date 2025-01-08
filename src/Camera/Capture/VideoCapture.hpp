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

#include "Config.hpp"
#include "MvCameraControl.h"
#include <filesystem>
#include <spdlog/spdlog.h>

class CaptureInterface {
  public:
    virtual void ReadFrame();
};

class FrameCapture : CaptureInterface {};

#endif