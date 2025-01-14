#ifndef __PRESET_FILER_HPP__
#define __PRESET_FILER_HPP__

#include "LinearizedSystemModel.hpp"
#include "Matrix.hpp"
#include "StandardBase.hpp"
#include <Eigen/Dense>

/**
 * @brief 对小车中心进行建模
 *
 * @tparam stateDim 状态变量维度
 */
template <typename T, int stateDim = 8>
class StateVector : public Kalman::Vector<T, stateDim> {
  public:
    KALMAN_VECTOR(StateVector, T, stateDim);

    // 建模状态：
    // x, vx, y, vy, z, r, theta, vtheta
};

template <typename T = double, template <class> class CovBase = Kalman::StandardBase>
class SystemModel : public Kalman::LinearizedSystemModel<StateVector<T>, Kalman::Vector<T, 0>, CovBase> {
  public:
    using S = StateVector<T>;
    using C = Kalman::Vector<T, 0>;

    S f(S &old, C &c) const {
        S x;
        
    }
};

#endif