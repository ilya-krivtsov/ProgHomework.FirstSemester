cmake_minimum_required(VERSION 3.20)
project(task_2 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

add_library(sortings sortings.c)

add_executable(task_2 main.c)
target_link_libraries(task_2 PRIVATE sortings)

add_executable(task_2_test test.c)
target_link_libraries(task_2_test PRIVATE sortings)
