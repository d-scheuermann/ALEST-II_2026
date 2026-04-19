cmake_minimum_required(VERSION 3.14)
project(T1-ALEST_II)

set(CMAKE_CXX_STANDARD 17)

# Ajusta source e include
include_directories(include)
add_executable(${PROJECT_NAME} src/main.cpp)
