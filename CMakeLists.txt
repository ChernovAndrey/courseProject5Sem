cmake_minimum_required(VERSION 3.8)
project(courseProject5Sem)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp QuickMath.hpp Grid/Grid.h Grid/UniformGrid.h LeastSquare.h)
add_executable(courseProject5Sem ${SOURCE_FILES})