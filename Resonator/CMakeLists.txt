cmake_minimum_required(VERSION 3.8)
project(Resonator)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp driving_frequency.h driving_frequency.cpp)
add_executable(Resonator ${SOURCE_FILES})