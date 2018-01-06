cmake_minimum_required(VERSION 3.8)
project(WatorSim)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp animal.cpp animal.h)

set(CMAKE_CXX_COMPILER /usr/local/bin/g++-7)
set(CMAKE_C_COMPILER /usr/local/bin/gcc-7)
# enable openmp using -fopenmp
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

add_executable(WatorSim ${SOURCE_FILES})