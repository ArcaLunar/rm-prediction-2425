#include "PoseSolver.hpp"

RotationManager::RotMat_t
RotationManager::GetRotMat_by_X_Axis(double theta) {
    RotationManager::RotMat_t rot_mat;
    // clang-format off
    rot_mat <<
    1,     0     ,      0     , 
    0, cos(theta), -sin(theta), 
    0, sin(theta),  cos(theta);
    // clang-format on
    return rot_mat;
}

RotationManager::RotMat_t
RotationManager::GetRotMat_by_Y_Axis(double theta) {
    RotationManager::RotMat_t rot_mat;
    // clang-format off
    rot_mat <<
    cos(theta),  0, sin(theta), 
        0,       1,      0    , 
    -sin(theta), 0, cos(theta);
    // clang-format on
    return rot_mat;
}

RotationManager::RotMat_t
RotationManager::GetRotMat_by_Z_Axis(double theta) {
    RotationManager::RotMat_t rot_mat;
    // clang-format off
    rot_mat <<
    cos(theta), -sin(theta), 0, 
    sin(theta),  cos(theta), 0, 
        0     ,      0     , 1;
    // clang-format on
    return rot_mat;
}

RotationManager::Queternion_t RotationManager::RotMat2Queternion(
    const RotationManager::RotMat_t &rot_mat) {
    /// \warning 简化版本的转换，可能需要考虑正负号的问题
    RotationManager::Queternion_t result;
    double trace = rot_mat.trace();
    result.w()   = std::sqrt(trace + 1) / 2;
    result.x()   = (rot_mat(2, 1) - rot_mat(1, 2)) / (4 * result.w());
    result.y()   = (rot_mat(0, 2) - rot_mat(2, 0)) / (4 * result.w());
    result.z()   = (rot_mat(1, 0) - rot_mat(0, 1)) / (4 * result.w());
    return result;
}