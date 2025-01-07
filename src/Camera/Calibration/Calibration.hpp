/**
 * @file Calibration.hpp
 * @author arca@connect.hku.hk
 * @brief 相机标定
 * @version 0.1
 * @date 2025-01-06
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __CABLIBRATION_HPP__
#define __CABLIBRATION_HPP__

#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>
#include <vector>
// #include <opencv2/core/mat.hpp>

struct MonocularCameraParameters {
    cv::Mat cameraMatrix; // 相机内参矩阵K 3*3
    cv::Mat distCoeffs; // 相机的5个畸变系数矩阵：k1, k2, p1, p2, k3 1*5

    // 相机外参（相对于标定板）
    std::vector<cv::Mat> rotationVectors;    // 每幅图像的旋转向量
    std::vector<cv::Mat> translationVectors; // 每幅图像的平移向量

    double RMSE; // 重投影误差（Root Mean Square Error，RMSE）
};

class MonocularCalibrator {
  private:
    int m_ImageWidth;
    int m_ImageHeight;
    cv::Size m_ImgSize;   // 单目图像尺寸
    cv::Size m_BoardSize; // 标定板上每行、列的角点数
    cv::Size
        m_BoardCellSize; // 实际测量得到的标定板上每个棋盘格的大小。单位：mm

    std::vector<cv::Mat> m_Images;
    std::vector<std::vector<cv::Point2f>> m_ImagesCorners;
    std::vector<std::vector<cv::Point3f>> m_ObjectPoints;

    /* ========== Util Functions ========== */
    /**
     * @brief 提取角点
     *
     * @return true
     * @return false
     */
    bool ExtractCorners();
    /**
     * @brief 标定单目相机
     *
     * @param camParams
     */
    void Calibrate(MonocularCameraParameters &camParams);

  public:
    MonocularCalibrator() = default;
    MonocularCalibrator(int imgWidth, int imgHeight)
        : m_ImageWidth(imgWidth),
          m_ImageHeight(imgHeight),
          m_ImgSize(imgWidth, imgHeight) {}

    /**
     * @brief 设置标定板参数
     *
     * @param numCornerRow
     * @param numCornerCol
     * @param cellWidth
     * @param cellHeight
     */
    void SetChessboardParams(int numCornerRow, int numCornerCol,
                             int cellWidth, int cellHeight);

    /**
     * @brief 计算单目相机标定精度
     *
     * @param camParams
     */
    void EvaluateMonocularCalibrationResults(
        const MonocularCameraParameters &camParams);

    void WriteResultToFile(const std::string &camId,
                           const MonocularCameraParameters &camParams,
                           bool saveImages);

    const std::vector<std::vector<cv::Point3f>> &ObjectPoints();
    const std::vector<std::vector<cv::Point2f>> &ImagesCorners();
};

#endif