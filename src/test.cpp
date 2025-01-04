#include <iostream>
#include <random>

#include "KalmanFilter.hpp"

std::mt19937 randomizer(std::random_device{}());

int main() {
    constexpr int N    = 20;
    constexpr double K = 2.5;
    Eigen::Matrix<double, 1, N> noise =
        Eigen::Matrix<double, 1, N>::Random();
    Eigen::Matrix<double, 1, N> data =
        Eigen::Matrix<double, 1, N>::LinSpaced(0, K * (N - 1));
    data += noise;
    std::cout << data << std::endl;
}