#include "Calibration.hpp"

#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <spdlog/spdlog.h>

#include <chrono>
#include <ctime>
#include <iomanip>
#include <string>
/* ===== Utils Functions ===== */
std::string GetTimeStamp() {
    std::time_t tt = std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now());
    // std::tm tm = *std::gmtime(&tt); //GMT (UTC)
    std::tm tm =
        *std::localtime(&tt); // Locale time-zone, usually UTC by default.
    std::stringstream ss;
    ss << std::put_time(&tm, "%Y_%m_%d_%H_%M_%S");
    return ss.str();
}

bool MonocularCalibrator::ExtractCorners() {
    std::vector<cv::Point2f> corners; // 提取出来的角点
    this->m_ImagesCorners.clear();

    SPDLOG_INFO("start calibration: extracting corners.");

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

void MonocularCalibrator::Calibrate(MonocularCameraParameters &camParams) {
    SPDLOG_INFO("start calibration: calibrating.");
    // 初始化标定板上角点的三维坐标
    this->m_ObjectPoints.clear();
    for (size_t k = 0; k < this->m_Images.size(); ++k) {
        std::vector<cv::Point3f> tempPointsSet;

        for (size_t i = 0; i < this->m_BoardSize.height; ++i) {
            for (size_t j = 0; j < this->m_BoardSize.width; ++j) {
                cv::Point3f realPoint;
                /* 假设标定板放在世界坐标系中z=0的平面上 */
                realPoint.x = i * this->m_BoardCellSize.width;
                realPoint.y = j * this->m_BoardCellSize.height;
                realPoint.z = 0;
                tempPointsSet.push_back(realPoint);
            }
        }

        this->m_ObjectPoints.push_back(tempPointsSet);
    }

    SPDLOG_INFO("calibration finished");

    camParams.RMSE = cv::calibrateCamera(this->m_ObjectPoints,
                                         this->m_ImagesCorners,
                                         this->m_ImgSize,
                                         camParams.cameraMatrix,
                                         camParams.distCoeffs,
                                         camParams.rotationVectors,
                                         camParams.translationVectors);

    SPDLOG_INFO("monocular camera RMSE error: {:.3f}", camParams.RMSE);
}

void MonocularCalibrator::SetChessboardParams(int numCornerRow,
                                              int numCornerCol,
                                              int cellWidth,
                                              int cellHeight) {
    m_BoardSize     = cv::Size(numCornerRow, numCornerCol);
    m_BoardCellSize = cv::Size(cellWidth, cellHeight);
}

void MonocularCalibrator::EvaluateMonocularCalibrationResults(
    const MonocularCameraParameters &camParams) {

    size_t imgCnt = camParams.rotationVectors.size();

    double total_err = 0.0; // 所有图像的平均误差的总和

    std::vector<cv::Point2f> image_points2; /* 保存重新计算得到的投影点 */

    SPDLOG_INFO("evaluating monocular calibration results.");
    SPDLOG_INFO("calibration error for each image:");

    for (size_t i = 0; i < imgCnt; ++i) {
        std::vector<cv::Point3f> tempPointSet = m_ObjectPoints[i];
        /* 通过得到的摄像机内外参数，对空间的三维点进行重新投影计算，得到新的投影点
         */
        cv::projectPoints(tempPointSet,
                          camParams.rotationVectors[i],
                          camParams.translationVectors[i],
                          camParams.cameraMatrix,
                          camParams.distCoeffs,
                          image_points2);
        /* 计算新的投影点和旧的投影点之间的误差*/
        cv::Mat tempImagePointMat =
            cv::Mat(1, m_ImagesCorners[i].size(), CV_32FC2);
        cv::Mat image_points2Mat =
            cv::Mat(1, image_points2.size(), CV_32FC2);

        for (size_t j = 0; j < m_ImagesCorners[i].size(); ++j) {
            image_points2Mat.at<cv::Vec2f>(0, j) =
                cv::Vec2f(image_points2[j].x, image_points2[j].y);
            tempImagePointMat.at<cv::Vec2f>(0, j) = cv::Vec2f(
                m_ImagesCorners[i][j].x, m_ImagesCorners[i][j].y);
        }

        double err = cv::norm(image_points2Mat,
                              tempImagePointMat,
                              cv::NORM_L2); // 每幅图像的平均误差
        total_err += err /= (m_BoardSize.width * m_BoardSize.height);
        SPDLOG_INFO(
            "Image {} calibration error: {:.3f} pixels", i + 1, err);
    }

    SPDLOG_INFO("total average error: {:.3f} pixels", total_err / imgCnt);
}

void MonocularCalibrator::WriteResultToFile(
    const std::string &camId, const MonocularCameraParameters &camParams,
    bool saveImages) {

    std::string timestamp = GetTimeStamp();

    std::string parentDir = std::string("../config/mono_calib_data/") +
                            timestamp + std::string("/");
    std::string imgSaveDir = parentDir + "images/";

    if (saveImages) {
        std::stringstream ss;
        ss << "mkdir " << imgSaveDir;
        std::system(ss.str().c_str());
        ss.str("");

        for (size_t i = 0; i < m_Images.size(); ++i) {
            ss << imgSaveDir << std::setw(2) << std::setfill('0') << i
               << ".png";
            cv::imwrite(ss.str(), m_Images[i]);
            ss.str("");
        }
    }

    cv::FileStorage fsWriter(parentDir +
                                 std::string("MonoCalibResults.json"),
                             cv::FileStorage::WRITE);
    fsWriter << "CamId" << camId;
    fsWriter << "Calib_Date" << timestamp;
    fsWriter << "Image_Size" << m_ImgSize;
    fsWriter << "Root_Mean_Squared_Error" << camParams.RMSE;
    fsWriter << "CamMat" << camParams.cameraMatrix;
    fsWriter << "DistCoeffs" << camParams.distCoeffs;
    fsWriter.release();
}

const std::vector<std::vector<cv::Point3f>> &
MonocularCalibrator::ObjectPoints() {
    return m_ObjectPoints;
}

const std::vector<std::vector<cv::Point2f>> &
MonocularCalibrator::ImagesCorners() {
    return m_ImagesCorners;
}