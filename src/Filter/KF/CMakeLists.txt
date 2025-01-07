cmake_minimum_required(VERSION 3.16)
project(KF)

set(KF_SRC
    KalmanFilter.cpp
)
set(KF_HEADER
    KalmanFilter.hpp
)

add_library(KF
    ${KF_SRC}
    ${KF_HEADER}
)
