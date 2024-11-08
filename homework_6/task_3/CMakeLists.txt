project("${homeworkName}_task_3")

add_library(sortedList sortedList.c)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} sortedList)

add_executable(${PROJECT_NAME}_test test.c)
target_link_libraries(${PROJECT_NAME}_test sortedList)
