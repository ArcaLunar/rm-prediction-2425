# src/Filter/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(Filter)

add_subdirectory(KF)
add_subdirectory(EKF)
add_subdirectory(UKF)

add_library(Filter INTERFACE)
target_link_libraries(Filter INTERFACE KF EKF UKF)