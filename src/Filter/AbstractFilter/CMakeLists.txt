cmake_minimum_required(VERSION 3.16)
project(AbstractFilter)

set(AbstractFilter_SRC
    AbstractFilter.cpp
)

set(AbstractFilter_HEADER
    AbstractFilter.hpp
)

find_package(Eigen3 REQUIRED)

add_library(AbstractFilter ${AbstractFilter_SRC} ${AbstractFilter_HEADER})

target_include_directories(AbstractFilter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(AbstractFilter
    Eigen3::Eigen
)
