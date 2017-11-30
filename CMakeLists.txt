cmake_minimum_required(VERSION 3.8)
project(WatorSim)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp animal.cpp animal.h)
add_executable(WatorSim ${SOURCE_FILES})