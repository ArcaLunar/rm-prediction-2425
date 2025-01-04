#ifndef _KALMAN_FILTER_HPP_
#define _KALMAN_FILTER_HPP_

#include <Eigen/Dense>

/**
 * @brief 线性卡尔曼滤波器
 * 
 * @tparam Z_N 观测变量维度
 * @tparam X_N 状态变量维度
 */
template <int Z_N, int X_N>
class KalmanFilter {
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
    MatXX R;   // 状态噪声协方差矩阵
    MatXZ K;   // 卡尔曼增益
    MatZX H;   // 观测矩阵
    MatZZ Q;   // 观测噪声协方差矩阵
    VecX x_k1; // 上一时刻的状态估计
    double last_time{0};

  public:
    KalmanFilter() = default;
    void Reset(const MatXX &A, const MatXX &R, const MatZX &H,
               const MatZZ &Q, const VecX &initial, const double &t) {
        this->A    = A;
        this->P    = MatXX::Zero();
        this->R    = R;
        this->H    = H;
        this->Q    = Q;
        this->x_k1 = initial;
    }
    void Reset(const VecX &initial, const double &t) {
        this->x_k1      = initial;
        this->last_time = t;
    }
    void Reset(const double &x, const double &t) {
        this->x_k1       = VecX::Zero();
        this->x_k1(0, 0) = x;
        this->last_time  = t;
    }

    VecX Update(const VecZ &z_k, const double &cur_time) {
        for (int i = 1; i < X_N; i++) {
            A(i - 1, i) = cur_time - last_time;
        }
        last_time = cur_time;

        VecX x_k = A * x_k1;
        P = A * P * A.transpose() + R;
        K = P * H.transpose() * (H * P * H.transpose() + Q).inverse();
        x_k1 = x_k + K * (z_k - H * x_k);
        P = (MatXX::Identity() - K * H) * P;

        return x_k1;
    }
};

#endif
