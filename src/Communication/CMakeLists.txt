# src/Communication/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(Communication)

# 添加头文件
set(SOURCES SerialPort.cpp)
set(HEADERS SerialPort.hpp)

# 添加库
add_library(Communication ${HEADERS} ${SOURCES})