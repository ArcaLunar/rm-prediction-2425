cmake_minimum_required(VERSION 3.20)
#######################
#      项目名称        #
#######################
project(auto_aim)

#######################
#    设置 C++ 版本     #
#######################
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# 设置输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

message("output dir: ${CMAKE_SOURCE_DIR}/bin")

enable_testing()
add_subdirectory(tests)
add_subdirectory(src)


