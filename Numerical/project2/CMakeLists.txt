cmake_minimum_required(VERSION 3.6)
project(project2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp BruteMinSearch.h GradientSearch.h)
add_executable(project2 ${SOURCE_FILES})