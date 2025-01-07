#ifndef _KALMAN_FILTER_HPP_
#define _KALMAN_FILTER_HPP_

#include <Eigen/Core>
#include <Eigen/Dense>

/**
 * @brief 线性卡尔曼滤波器
 *
 * @tparam Z_N 观测变量维度
 * @tparam X_N 状态变量维度
 */
template <int Z_N, int X_N>
class KalmanFilter  {
  public:
    using MatXX = Eigen::Matrix<double, X_N, X_N>;
    using MatXZ = Eigen::Matrix<double, X_N, Z_N>;
    using MatZZ = Eigen::Matrix<double, Z_N, Z_N>;
    using MatZX = Eigen::Matrix<double, Z_N, X_N>;
    using VecX  = Eigen::Matrix<double, X_N, 1>;
    using VecZ  = Eigen::Matrix<double, Z_N, 1>;

  private:
    MatXX A;   // 转移矩阵
    MatXX P;   // 估计误差协方差
    MatXX R;   // 观测噪声协方差矩阵
    MatXZ K;   // 卡尔曼增益
    MatZX H;   // 观测矩阵
    MatZZ Q;   // 过程噪声协方差矩阵
    VecX x_k1; // 上一时刻的状态估计
    double last_time{0};

  public:
    KalmanFilter() = default;

    /**
     * @brief 设置转移矩阵
     * 
     * @param A 
     */
    void SetTransition(const MatXX &A = MatXX::Identity());

    /**
     * @brief 设置观测矩阵
     * 
     * @param H 
     */
    void SetObservation(const MatZX &H = MatZX::Identity());

    /**
     * @brief 设置观测噪声协方差矩阵
     * @attention 调参：识别得越精确，R 越小
     * @param R 
     */
    void SetObservationNoise(const MatZZ &R = MatZZ::Identity());

    /**
     * @brief 设置过程噪声协方差矩阵
     * @attention 调参：公式推导得比较粗糙的话，Q 调大一些
     * @param Q 
     */
    void SetProcessNoise(const MatXX &Q = MatXX::Identity());

    /**
     * @brief 设置初始状态
     * 
     * @param x0 
     */
    void SetInitialState(const VecX &x0 = VecX::Zero());

    /**
     * @brief 线性卡尔曼滤波器 状态更新
     *
     * @param z_k 当前时刻的观测值
     * @param cur_time 当前时刻
     * @return VecX 当前时刻下对当前状态的估计
     */
    VecX Correct(const VecZ &z_k, const double &cur_time);
};

#endif
