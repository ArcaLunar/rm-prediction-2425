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