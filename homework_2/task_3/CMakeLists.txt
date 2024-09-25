cmake_minimum_required(VERSION 3.20)
project(task_3 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

add_library(power power.c)

add_executable(task_3 main.c)
target_link_libraries(task_3 PRIVATE power)

add_executable(task_3_test test.c)
target_link_libraries(task_3_test PRIVATE power)
