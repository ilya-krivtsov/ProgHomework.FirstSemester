project("${homeworkName}_task_2")

add_library(phoneBook database.c personEntry.c)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} phoneBook)

add_executable(${PROJECT_NAME}_test test.c)
target_link_libraries(${PROJECT_NAME}_test PRIVATE phoneBook)
