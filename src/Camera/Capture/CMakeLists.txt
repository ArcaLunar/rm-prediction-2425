# src/Camera/Capture/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(Capture)

# 查找 OpenCV 库
find_package(OpenCV REQUIRED)
find_package(spdlog REQUIRED)

# 设置 MVS 头文件路径
include_directories(
    ${MvsIncludeDir}
    ${OpenCV_INCLUDE_DIRS}
)
# 设置 MVS 库文件路径
link_directories(
    /opt/MVS/lib/64
    ${OpenCV_LIB_DIR}
)

# 添加源文件和头文件
set(CAPTURE_SRC VideoCapture.cpp)
set(CAPTURE_HEADERS VideoCapture.hpp)

# 添加库
add_library(Capture ${CAPTURE_SRC} ${CAPTURE_HEADERS})

# 链接 OpenCV 库
target_link_libraries(Capture
    ${OpenCV_LIBS}
    MvCameraControl
    MVGigEVisionSDK
    MVRender
    MvUsb3vTL
    MediaProcess
    X11
    spdlog::spdlog
)

target_include_directories(Capture PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
