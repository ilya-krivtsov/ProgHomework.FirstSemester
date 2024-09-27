cmake_minimum_required(VERSION 3.20)
project("${homeworkName}_task_2")

add_library(sortAndSearch sortAndSearch.c)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} sortAndSearch)

add_executable(${PROJECT_NAME}_test test.c)
target_link_libraries(${PROJECT_NAME}_test PRIVATE sortAndSearch)
