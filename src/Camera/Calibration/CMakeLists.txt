# src/Camera/Calibration/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(Calibration)

# 查找 OpenCV 库
find_package(OpenCV REQUIRED)
find_package(spdlog REQUIRED)

# 添加源文件和头文件
set(SOURCES Calibration.cpp)
set(HEADERS Calibration.hpp)

# 添加库
add_library(Calibration ${SOURCES} ${HEADERS})

# 链接 OpenCV 库
target_link_libraries(Calibration
    ${OpenCV_LIBS}
    spdlog::spdlog
)

# 使得 Calibration 可被所有文件包含
target_include_directories(Calibration PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
