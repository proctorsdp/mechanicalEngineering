cmake_minimum_required(VERSION 3.6)
project(TemperaturePoly)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp tempPoly.h)
add_executable(TemperaturePoly ${SOURCE_FILES})