cmake_minimum_required(VERSION 3.6)
project(frictionSolver)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp frictionSolver.h)
add_executable(frictionSolver ${SOURCE_FILES})