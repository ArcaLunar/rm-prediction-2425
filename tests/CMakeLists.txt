cmake_minimum_required(VERSION 3.16)
project(testing)

add_executable(test_filter ./filter_test.cpp)
target_link_libraries(test_filter PRIVATE Filter)

add_test(NAME test_filter COMMAND $<TARGET_FILE:test_filter>)