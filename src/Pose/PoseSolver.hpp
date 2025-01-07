/**
 * @file PoseSolver.hpp
 * @author arca@connect.hku.hk
 * @brief 姿态解算
 * @version 0.1
 * @date 2025-01-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __POSE_SOLVER_HPP__
#define __POSE_SOLVER_HPP__

#include <Eigen/Core>
#include <Eigen/Dense>

/**
 * @brief 计算旋转矩阵
 *
 */
class RotationManager {
  public:
    using RotMat_t     = Eigen::Matrix<double, 3, 3>;
    using Queternion_t = Eigen::Quaternion<double>;

    /**
     * @brief 绕 X 轴旋转 theta 弧度的旋转矩阵
     *
     * @param theta 绕 X 轴旋转 theta 弧度
     * @return RotMat_t 旋转矩阵
     */
    static RotMat_t GetRotMat_by_X_Axis(double theta);

    /**
     * @brief 绕 Y 轴旋转 theta 弧度的旋转矩阵
     *
     * @param theta 绕 Y 轴旋转 theta 弧度
     * @return RotMat_t 旋转矩阵
     */
    static RotMat_t GetRotMat_by_Y_Axis(double theta);

    /**
     * @brief 绕 Z 轴旋转 theta 弧度的旋转矩阵
     *
     * @param theta 绕 Z 轴旋转 theta 弧度
     * @return RotMat_t 旋转矩阵
     */
    static RotMat_t GetRotMat_by_Z_Axis(double theta);

    /**
     * @brief 旋转矩阵转四元数
     * 
     * @param rot_mat 
     * @return Queternion_t 
     */
    static Queternion_t RotMat2Queternion(const RotMat_t &rot_mat);
};

#endif