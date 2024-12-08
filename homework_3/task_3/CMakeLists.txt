project("${homeworkName}_task_3")

add_library(smartQSort smartQSort.c)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} smartQSort)

add_executable(${PROJECT_NAME}_test test.c)
target_link_libraries(${PROJECT_NAME}_test smartQSort)
