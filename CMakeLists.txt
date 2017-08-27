cmake_minimum_required(VERSION 2.6)
project(dc_tp_template)

set(SOURCE_FILES src/my_src.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

add_library(dc-tp-base ${SOURCE_FILES})

add_executable(main src/main.cpp)
target_link_libraries (main dc-tp-base)

add_subdirectory(test)