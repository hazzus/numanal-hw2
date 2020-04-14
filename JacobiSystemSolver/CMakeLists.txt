cmake_minimum_required(VERSION 3.15)
project(JacobiSystemSolver)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp JacobiSystemSolver.cpp JacobiSystemSolver.h)