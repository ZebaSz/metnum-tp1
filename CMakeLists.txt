cmake_minimum_required(VERSION 2.6)
project(metnum-tp1)

set(SOURCE_FILES )

set(PPMLOADER_FILES src/ppmloader/ppmloader.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

add_library(metnum-tp1-base ${PPMLOADER_FILES} ${SOURCE_FILES})

add_executable(main src/main.cpp src/gauss.cpp src/gauss.h)
target_link_libraries (main metnum-tp1-base)

#add_subdirectory(test)