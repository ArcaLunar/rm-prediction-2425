cmake_minimum_required(VERSION 3.16)
project(Camera)

# 添加子目录
add_subdirectory(Capture) # 捕获图像
add_subdirectory(Calibration) # 相机标定

include_directories(
    Capture
    Calibration
)

add_library(Camera INTERFACE)

target_link_libraries(Camera INTERFACE Capture Calibration)
