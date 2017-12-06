cmake_minimum_required(VERSION 3.6)
project(RootSolver)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp rootSolver.h)
add_executable(RootSolver ${SOURCE_FILES})