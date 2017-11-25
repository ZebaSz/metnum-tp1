cmake_minimum_required(VERSION 2.6)
project(metnum-tp1)

set(SOURCE_FILES
        src/utils.cpp
        src/matrix.h
        src/plu.h
        src/cholesky.h
        src/mask.h
        src/mask.cpp
        src/calibration.h
        src/cholesky.h
        src/reconstruct3d.h
        src/sparse_matrix.h)

set(PPMLOADER_FILES src/ppmloader/ppmloader.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -Wall -pedantic")

add_library(metnum-tp1-base ${PPMLOADER_FILES} ${SOURCE_FILES})

add_executable(procesar src/main.cpp)
target_link_libraries (procesar metnum-tp1-base)

#add_subdirectory(test)
