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
