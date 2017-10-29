cmake_minimum_required(VERSION 3.8)
project(FreeVibrationOfBeams)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp PinnedPinned.h FreeFree.h FixedFixed.h FixedFree.h)
add_executable(FreeVibrationOfBeams ${SOURCE_FILES})