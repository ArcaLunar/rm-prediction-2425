#include "MvCameraControl.h"
#include "VideoCapture.hpp"
#include <atomic>
#include <spdlog/spdlog.h>
#include <string>
#include <unistd.h>

std::string SavDir = "../calib_imgs/";

std::atomic_bool eflag{false};
std::atomic_int cnt{0};

void *ework(void *pUser) {
    int nRet                 = MV_OK;
    MV_FRAME_OUT stImageInfo = {0};
    memset(&stImageInfo, 0, sizeof(MV_FRAME_OUT));
    while (1) {
        if (cnt >= 50) eflag = true;
        if (eflag) break;
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
            cv::imwrite(SavDir + std::to_string(cnt) + ".jpg", img);
            cnt++;
        }

        MV_CC_FreeImageBuffer(pUser, &stImageInfo);

        sleep(1);
    }

    return 0;
}

int main() {
    Camera::HikCamera cam;
    auto press = [&]() {
        while (getchar() != '\n');
        spdlog::debug("Enter is pressed, exiting");
        eflag = true;
    };

    pthread_t pid;
    int result = pthread_create(&pid, NULL, ework, cam.GetHandle());
    if (result != 0) {
        spdlog::info("thread create failed");
        return 0;
    }
    press();
}