cmake_minimum_required(VERSION 3.16)
project(Settings)

set(HEADER_FILES Constants.hpp)
set(SOURCES Constants.cpp)

add_library(Settings ${HEADER_FILES} ${SOURCES})
