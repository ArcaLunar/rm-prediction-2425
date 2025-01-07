# src/Filter/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(Filter)

# 添加子目录
add_subdirectory(AbstractFilter)
add_subdirectory(EKF)
add_subdirectory(KF)
add_subdirectory(Tracker)
add_subdirectory(UKF)

# 创建 Filter 库（如果需要）
add_library(Filter INTERFACE)

# 链接子模块
target_link_libraries(Filter INTERFACE
    AbstractFilter
    EKF
    KF
    Tracker
    UKF
)