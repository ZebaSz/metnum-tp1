cmake_minimum_required(VERSION 2.6)
project(metnum-tp1)

set(SOURCE_FILES
        src/utils.cpp
        src/matrix.h
        src/gauss.h
        src/cholesky.h
        src/matrix.cpp
        src/mask.h
        src/calibration.h
        src/reconstruct3d.h)


set(PPMLOADER_FILES src/ppmloader/ppmloader.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

add_library(metnum-tp1-base ${PPMLOADER_FILES} ${SOURCE_FILES})

add_executable(main src/main.cpp src/cholesky.h)
target_link_libraries (main metnum-tp1-base)

add_subdirectory(test)
