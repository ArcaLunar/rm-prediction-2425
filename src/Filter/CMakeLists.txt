# src/Filter/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(Filter)

# 添加源文件和头文件
set(FILTER_SOURCES 
    KalmanFilter.cpp
    UnscentedKalmanFilter.cpp
)
set(FILTER_HEADERS 
    KalmanFilter.hpp 
    UnscentedKalmanFilter.hpp
)

# 添加库
add_library(Filter ${FILTER_SOURCES} ${FILTER_HEADERS})
