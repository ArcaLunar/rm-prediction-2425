# src/Camera/Calibration/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(Calibration)

# 查找 OpenCV 库
find_package(OpenCV REQUIRED)


# 添加源文件和头文件
set(SOURCES Calibration.cpp)
set(HEADERS Calibration.hpp)

# 添加库
add_library(Calibration ${SOURCES} ${HEADERS})

# 链接 OpenCV 库
target_link_libraries(Calibration ${OpenCV_LIBS})