cmake_minimum_required(VERSION 3.6)
project(Exam3_1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp 3_8_Simpsons.h trpzMethod.h Romberg.h)
add_executable(Exam3_1 ${SOURCE_FILES})