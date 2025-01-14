cmake_minimum_required(VERSION 3.16)
project(Filter CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Eigen3 REQUIRED)

aux_source_directory(./src SOURCES)

include_directories(
    ./include
    ${Eigen3_INCLUDE_DIR}
)

add_library(Filter INTERFACE)
set_target_properties(Filter PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(Filter INTERFACE ./include)
