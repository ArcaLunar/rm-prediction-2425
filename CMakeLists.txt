cmake_minimum_required(VERSION 3.20)
#######################
#      项目名称        #
#######################
project(auto_aim)

#######################
#    设置 C++ 版本     #
#######################
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_subdirectory(src)


# 设置输出路径
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
