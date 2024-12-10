project("${homeworkName}_task_1")

add_library(bracketsBalance bracketsBalance.c)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} bracketsBalance)
target_link_libraries(${PROJECT_NAME} stack)

add_executable(${PROJECT_NAME}_test test.c)
target_link_libraries(${PROJECT_NAME}_test bracketsBalance)
target_link_libraries(${PROJECT_NAME}_test stack)
