cmake_minimum_required(VERSION 3.20)
# 项目名称
project(auto_aim)

# 设置 C++ 版本
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)

# 主程序
add_executable(auto_aim src/Main.cpp)

# 寻找依赖
find_package(spdlog REQUIRED)

# 添加依赖
target_link_libraries(auto_aim
    spdlog::spdlog # Pre-compiled library, see https://github.com/gabime/spdlog/blob/v1.x/example/CMakeLists.txt
)

# 设置输出路径
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
