#include "KalmanFilter.hpp"

template <int Z_N, int X_N>
typename KalmanFilter<Z_N, X_N>::VecX
KalmanFilter<Z_N, X_N>::Correct(const VecZ &z_k, const double &cur_time) {
    // 设置时间项
    for (int i = 1; i < X_N; i++) A(i - 1, i) = cur_time - last_time;
    last_time = cur_time;

    // 上一时刻对当前的先验状态估计
    VecX x_k = A * x_k1;
    // 上一时刻对当前的先验估计误差协方差
    P = A * P * A.transpose() + Q;
    // 计算卡尔曼增益
    K = P * H.transpose() * (H * P * H.transpose() + R).inverse();
    // 当前时刻对当前的后验状态估计
    x_k1 = x_k + K * (z_k - H * x_k);
    // 当前时刻对当前的后验估计误差协方差
    P = (MatXX::Identity() - K * H) * P;
    // 返回当前时刻对当前状态的后验估计
    return x_k1;
}

template <int Z_N, int X_N>
void KalmanFilter<Z_N, X_N>::SetTransition(const MatXX &A) {
    this->A = A;
}

template <int Z_N, int X_N>
void KalmanFilter<Z_N, X_N>::SetObservation(const MatZX &H) {
    this->H = H;
}

template <int Z_N, int X_N>
void KalmanFilter<Z_N, X_N>::SetObservationNoise(const MatZZ &R) {
    this->R = R;
}

template <int Z_N, int X_N>
void KalmanFilter<Z_N, X_N>::SetProcessNoise(const MatXX &Q) {
    this->Q = Q;
}

template <int Z_N, int X_N>
void KalmanFilter<Z_N, X_N>::SetInitialState(const VecX &x0) {
    x_k1 = x0;
}
