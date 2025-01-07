cmake_minimum_required(VERSION 3.16)
project(pose)

# 添加源文件
aux_source_directory(./ Pose_SRC)

add_library(pose SHARED ${Pose_SRC})