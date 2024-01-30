cmake_minimum_required(VERSION 3.26)
project(GenCalculator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBRARIES OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(GenCalculator main.cpp icon.rc Inout.h
        GenCross.h)
