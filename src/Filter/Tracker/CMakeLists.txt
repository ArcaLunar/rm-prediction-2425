cmake_minimum_required(VERSION 3.16)
project(Tracker)

set(TRACKER_SRC
    Tracker.cpp
)

set(TRACKER_HEADER
    Tracker.hpp
)

add_library(Tracker ${TRACKER_SRC} ${TRACKER_HEADER})

target_include_directories(Tracker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
