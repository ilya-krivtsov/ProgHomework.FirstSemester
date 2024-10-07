project("${homeworkName}_task_1")

add_library(halfQSort halfQSort.c)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} PRIVATE halfQSort)

add_executable(${PROJECT_NAME}_test test.c)
target_link_libraries(${PROJECT_NAME}_test PRIVATE halfQSort)
