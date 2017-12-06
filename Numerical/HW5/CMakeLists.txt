cmake_minimum_required(VERSION 3.6)
project(HW5)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp goldenSection.h parabolicInterp.h newtonMethod.h)
add_executable(HW5 ${SOURCE_FILES})