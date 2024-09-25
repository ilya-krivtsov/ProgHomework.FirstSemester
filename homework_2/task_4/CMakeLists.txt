cmake_minimum_required(VERSION 3.20)
project(task_4 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

add_library(fibonacci fib.c)

add_executable(task_4 main.c)
target_link_libraries(task_4 PRIVATE fibonacci)

add_executable(task_4_test test.c)
target_link_libraries(task_4_test PRIVATE fibonacci)
