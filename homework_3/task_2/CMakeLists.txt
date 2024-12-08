project("${homeworkName}_task_2")

add_library(sortAndSearch sortAndSearch.c)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} sortAndSearch)

add_executable(${PROJECT_NAME}_test test.c)
target_link_libraries(${PROJECT_NAME}_test sortAndSearch)
