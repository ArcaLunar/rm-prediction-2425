cmake_minimum_required(VERSION 3.16)
project(EKF)

set(EKF_SRC
    ExtendedKalmanFilter.cpp
)
set(EKF_HEADER
    ExtendedKalmanFilter.hpp
)

add_library(EKF
    ${EKF_SRC}
    ${EKF_HEADER}
)

target_include_directories(EKF PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})