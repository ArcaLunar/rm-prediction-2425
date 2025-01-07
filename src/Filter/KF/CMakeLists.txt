cmake_minimum_required(VERSION 3.16)
project(KF)

set(KF_SRC
    KalmanFilter.cpp
)
set(KF_HEADER
    KalmanFilter.hpp
)

find_package(Eigen3 REQUIRED)

add_library(KF
    ${KF_SRC}
    ${KF_HEADER}
)

target_include_directories(KF PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(KF
    Eigen3::Eigen
    AbstractFilter
)
