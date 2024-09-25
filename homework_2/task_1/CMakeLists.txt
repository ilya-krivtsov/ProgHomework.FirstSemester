cmake_minimum_required(VERSION 3.20)
project(task_1 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

add_library(halfQSort halfQSort.c)

add_executable(task_1 main.c)
target_link_libraries(task_1 PRIVATE halfQSort)

add_executable(task_1_test test.c)
target_link_libraries(task_1_test PRIVATE halfQSort)
