#include "Calibration.hpp"
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <spdlog/spdlog.h>

bool MonocularCalibrator::ExtractCorners() {
    std::vector<cv::Point2f> corners; // 提取出来的角点
    this->m_ImagesCorners.clear();

    SPDLOG_INFO("Start calibrating Camera...");

    for (auto image : this->m_Images) {
        // 提取角点
        if (cv::findChessboardCorners(image, this->m_BoardSize, corners)) {
            SPDLOG_INFO("Extracted.");
            // 对粗提取到的角点进行亚像素精确化
            cv::Mat gray;
            cv::cvtColor(image, gray, cv::COLOR_RGB2GRAY);
            cv::find4QuadCornerSubpix(gray, corners, cv::Size(11, 11));
            this->m_ImagesCorners.emplace_back(corners); // 保存亚像素角点
            /* 在图像上显示角点位置 */
            cv::drawChessboardCorners(
                image, this->m_BoardSize, corners, true);
            cv::imshow("Camera Calibration", image);
            cv::waitKey(50);
        } else {
            SPDLOG_ERROR(
                "No chessboard corners are found! Images are incorrect.");
            cv::imshow("Bad Image", image);
            cv::waitKey();
            return false;
        }
    }
    return true;
}

void MonocularCalibrator::SetChessboardParams(int numCornerRow,
                                              int numCornerCol,
                                              int cellWidth,
                                              int cellHeight) {
    m_BoardSize     = cv::Size(numCornerRow, numCornerCol);
    m_BoardCellSize = cv::Size(cellWidth, cellHeight);
}