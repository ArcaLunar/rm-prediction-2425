# src/Camera/Capture/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(Capture)

# 查找 OpenCV 库
find_package(OpenCV REQUIRED)

# 添加源文件和头文件
set(CAPTURE_SRC VideoCapture.cpp)
set(CAPTURE_HEADERS VideoCapture.hpp)

# 添加库
add_library(Capture ${CAPTURE_SRC} ${CAPTURE_HEADERS})

# 链接 OpenCV 库
target_link_libraries(Capture ${OpenCV_LIBS})