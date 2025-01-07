cmake_minimum_required(VERSION 3.16)
project(UF)

set(UKF_SRC
    UnscentedKalmanFilter.cpp
)
set(UF_HEADER
    UnscentedKalmanFilter.hpp
)

add_library(UKF
    ${UKF_SRC}
    ${UKF_HEADER}
)

target_include_directories(UKF PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
