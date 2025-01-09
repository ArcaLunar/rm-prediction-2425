# src/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(AutoAim CXX)

# 添加子目录
add_subdirectory(Camera)
add_subdirectory(Communication)
add_subdirectory(Filter)
add_subdirectory(Pose)
add_subdirectory(Settings)

# 设置海康威视相机 SDK 路径
set(MvsIncludeDir /opt/MVS/include)

# 查找必要的库
find_package(spdlog REQUIRED)
find_package(tf2 REQUIRED)
find_package(OpenCV REQUIRED)

# 设置头文件路径
include_directories(
    ${MvsIncludeDir}
    ${OpenCV_INCLUDE_DIRS}
)
# 设置库文件路径
link_directories(
    /opt/MVS/lib/64
    ${OpenCV_LIB_DIR}
)

# 相机标定程序
add_executable(cam CalibrationMain.cpp)

# 添加主程序
add_executable(auto_aim Main.cpp)

# 添加测试程序
add_executable(test Test.cpp)

# 链接所有库
target_link_libraries(cam
    ${OpenCV_LIBS}
    MvCameraControl
    MVGigEVisionSDK
    MVRender
    MvUsb3vTL
    MediaProcess
    X11
    spdlog::spdlog
)

target_link_libraries(auto_aim
    Camera
    Communication
    Filter
    Pose
    Settings
    # apt 安装的预编译的 spdlog 库
    # 见 https://github.com/gabime/spdlog/blob/v1.x/example/CMakeLists.txt
    spdlog::spdlog
)

target_link_libraries(test
    Camera
    Communication
    Filter
    Pose
    Settings
    spdlog::spdlog
    tf2::tf2
)
