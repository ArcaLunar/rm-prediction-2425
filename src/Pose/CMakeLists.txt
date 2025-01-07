cmake_minimum_required(VERSION 3.16)
project(Pose)

# 查找 Eigen, OpenCV 库
find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

set(POSE_SRC
    Pose.cpp
    PoseSolver.cpp
)

set(POSE_HEADERS
    Pose.hpp
    PoseSolver.hpp
)

add_library(Pose SHARED ${POSE_SRC} ${POSE_HEADERS})

target_link_libraries(Pose ${OpenCV_LIBS} Eigen3::Eigen)