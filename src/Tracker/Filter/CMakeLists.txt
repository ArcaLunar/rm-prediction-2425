cmake_minimum_required(VERSION 3.16)
project(Filter CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Eigen3 REQUIRED)
find_package(spdlog REQUIRED)

add_library(Filter INTERFACE)
set_target_properties(Filter PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(Filter INTERFACE ./include ${Eigen3_INCLUDE_DIR})

add_library(Presets 
    ./PresetFilter.cpp 
    ./PresetFilter.hpp
)
target_link_libraries(Presets
    Eigen3::Eigen
    spdlog::spdlog
    Filter
)