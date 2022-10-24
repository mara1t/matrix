cmake_minimum_required(VERSION 3.16)

project(matrix)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SOURCES src/main.cpp)

add_executable (${PROJECT_NAME} ${SOURCES})


add_compile_options (-Werror -Wall -Wextra -Wpedantic)

target_include_directories (${PROJECT_NAME} PRIVATE include)

#tests

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set (TEST_SOURCES test/matrix_unit_test.cpp)

add_executable(matrix_unit_test ${TEST_SOURCES})

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")


target_include_directories (matrix_unit_test PRIVATE include)
target_link_libraries(matrix_unit_test ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)
