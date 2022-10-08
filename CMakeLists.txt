cmake_minimum_required(VERSION 3.16)

project(matrix)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SOURCES src/main.cpp)

add_executable (${PROJECT_NAME} ${SOURCES})



add_compile_options (-g -Werror -Wall -Wextra -Wpedantic)

target_include_directories (${PROJECT_NAME} PRIVATE include)
