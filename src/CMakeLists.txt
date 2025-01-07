# src/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(AutoAim)

# 添加子目录
add_subdirectory(Camera)
add_subdirectory(Communication)
add_subdirectory(Filter)
add_subdirectory(Pose)
add_subdirectory(Settings)

find_package(spdlog REQUIRED)
find_package(tf2 REQUIRED)

# 添加主程序
add_executable(auto_aim Main.cpp)

# 添加测试程序
add_executable(test Test.cpp)

# 链接所有库
target_link_libraries(auto_aim
    Calibration
    Capture
    Communication
    Filter
    Pose
    Settings

    # apt 安装的预编译的 spdlog 库
    # 见 https://github.com/gabime/spdlog/blob/v1.x/example/CMakeLists.txt
    spdlog::spdlog
)

target_link_libraries(test
    Calibration
    Capture
    Communication
    Filter
    Pose
    Settings
    spdlog::spdlog
    tf2::tf2
)