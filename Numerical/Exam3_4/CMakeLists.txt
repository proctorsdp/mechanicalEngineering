cmake_minimum_required(VERSION 3.6)
project(Exam3_4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp romberg.h centralDerivation.h euler.h rungeKutta.h)
add_executable(Exam3_4 ${SOURCE_FILES})